// Includes
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

// Defines
#define ON 1                // define "ON" state for code readability
#define OFF 0               // define "OFF" state for code readability
#define NUM_SWITCHES 18     // defines maximum number of switches to control
#define NUM_PHASES 3        // defines maximum number of phases to control
#define BUFSIZE 32          // defines size of all message buffers

// Global variables
uint32_t state = 0;                                     // holds current state of switches as the 18 least significant bits of a bitmask
uint32_t phases[3] = { 0b111111111111111111, 0, 0 };    // holds switches registered on phases 1, 2, and 3 (default all switches on phase 1)
uint8_t zcs = OFF;                                      // holds current state of ZCS
uint8_t timer_fired = 0;                                // flag for whether the 10 second zero current crossing detection timer fired

// array such that switch_num_mapping[<switch_num> - 1] gives the corresponding GPIO pin number
uint8_t switch_num_mapping[18] = {
      SWITCH1, SWITCH2, SWITCH3, SWITCH4, SWITCH5, SWITCH6,
      SWITCH7, SWITCH8, SWITCH9, SWITCH10, SWITCH11, SWITCH12,
      SWITCH13, SWITCH14, SWITCH15, SWITCH16, SWITCH17, SWITCH18
};

// array such that comparator_num_mapping[<phase_num> - 1] gives the address of the corresponding CMPSS_LITE module
uint32_t comparator_num_mapping[3] = { CURRENT_SENSE1_BASE, CURRENT_SENSE2_BASE, CURRENT_SENSE3_BASE };

// ********************************************************* String Utilities ****************************************************** //

/*
 * Implementation of strncmp, modified slightly from one found online
 */
int strncmp(char *s1, char *s2, uint8_t n)
{
    do {
        if (*s1 != *s2++) {
            return (*(unsigned char *)s1 - *(unsigned char *)--s2);
        }
        if (*s1++ == 0) {
            break;
        }
    } while (--n != 0);

    return 0;
}

/*
 * Function to clear a buffer buf of length len (set all bits to 0)
 */
void clear_buf (char *buf, uint8_t len)
{
    int i;
    for (i = 0; i < len; i++) {
        buf[i] = '\0';
    }
}

/*
 * Function to recover a 32-bit bitmask from the first four bytes of the given buffer
 */
uint32_t buf_to_mask (char *buf)
{
    // initialize all bits to 0
    uint32_t mask = 0;

    // bit-shift the first four bytes of buf and bitwise-OR them together to recover mask
    mask = (((uint32_t)buf[0]) << 24) | (((uint32_t)buf[1]) << 16) | (((uint32_t)buf[2]) << 8) | (uint32_t)buf[3];

    return mask;
}

/*
 * Function to pack a 32-bit bitmask into the first four bytes of the given buffer
 */
void mask_to_buf (char *buf, uint32_t mask)
{
    buf[0] = (char)((mask >> 24) & 0b11111111);
    buf[1] = (char)((mask >> 16) & 0b11111111);
    buf[2] = (char)((mask >> 8) & 0b11111111);
    buf[3] = (char)(mask & 0b11111111);
}

// *********************************************** Comparator (Current Sensing) Utility ********************************************* //

/*
 * Fetches the comparator output value of the current sensor attached to specified phase
 */
uint8_t get_comparator_value (uint8_t phase_num)
{
    uint32_t ret = CMPSS_getStatus(comparator_num_mapping[phase_num - 1]);
    return ret & CMPSS_COMPSTS_COMPHSTS;
}

// ******************************************************* CPUTimer Interrupt ****************************************************** //
/*
 * Interrupt service handler for 10 second timer
 */
__interrupt void INT_TIMER_10S_ISR (void)
{
    // set the timer_fired flag to 1
    timer_fired = 1;

    // clear the interrupt group so that we can get additional interrupts in the future (see TI timer_ex1_cputimer example)
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

// **************************************************** GPIO (Switch) Utilities **************************************************** //

/*
 * Function to turn a switch on or off
 *  - switch_num: unsigned int from 1 to 18
 *  - desired_state: ON (1) or OFF (0)
 */
void set_switch_state(uint8_t switch_num, uint8_t desired_state)
{
    if (switch_num >= 1 && switch_num <= 18) {
        GPIO_writePin(switch_num_mapping[switch_num - 1], desired_state);
    }
}

/*
 * Function to set the switch state to specified state. Handles ZCS.
 *  - desired_state: 32-bit bitmap with least significant 18 bits dictating desired state of the 18 switches
 *  For example, if desired_state is 0b0000 0000 0000 0000 0001 0001 0001 0001, this would mean the desired
 *  state is switch numbers 1, 5, 9, 13, and 17 on
 *  Returns a status of 0 (ok) or 1 (zcs timeout)
 */
uint8_t set_all_switches(uint32_t desired_state)
{
    uint8_t i;
    uint8_t phase;
    uint8_t ret = 0;

    if (zcs == OFF) {
        // if ZCS off, just set all the switches as desired
        for (i = 1; i <= NUM_SWITCHES; i++) {
            set_switch_state(i, (desired_state >> (i - 1)) & 1);
        }
    } else {
        // if ZCS ON, wait for each phase to cross 0 (if there are switches registered on the phase), then set that phase's switches
        for (phase = 1; phase <= NUM_PHASES; phase++) {
            // only need to proceed if phase has switches registered on it
            if (phases[phase - 1] != 0) {
                // get the comparator value at this moment
                uint8_t original_comp_value = get_comparator_value(phase);

                // set up the timer, which will fire after 10 seconds and cause loop to break if zero crossing hasn't been detected yet
                timer_fired = 0;
                CPUTimer_reloadTimerCounter(TIMER_10S_BASE);
                CPUTimer_startTimer(TIMER_10S_BASE);

                // while the comparator has not yet changed from the original value and the timer has not fired yet, block
                while ((get_comparator_value(phase) == original_comp_value) && !timer_fired);

                // if timer fired, set the return value to 1, and don't turn on this phase's switches
                if (timer_fired == 1) {
                    ret = 1;
                } else {
                    // switch all of the switches in this phase to desired state
                    for (i = 1; i <= NUM_SWITCHES; i++) {
                        // if this switch is in this phase, set its desired state
                        if (phases[phase - 1] & ((uint32_t)1 << (i - 1))) {
                            set_switch_state(i, (desired_state >> (i - 1)) & 1);
                        }
                    }
                }
            }
        }
    }
    return ret;
}

// ****************************************************** Read/Write to SCI  ***************************************************** //

/*
 * Read one character from the SCI connection (copied from SCI EchoBack example from TI)
 */
uint16_t read_char ()
{
    uint16_t received_char = SCI_readCharBlockingFIFO(UART_BASE);
    uint16_t rxStatus = 0U;
    rxStatus = SCI_getRxStatus(UART_BASE);

    if ((rxStatus & SCI_RXSTATUS_ERROR) != 0) {
        // If Execution stops here there is some error
        // Analyze SCI_getRxStatus() API return value
        ESTOP0;
    }
    return received_char;
}

/*
 * Read a full message from the SCI connection
 *  - msg is a pointer to a buffer which is large enough to store the received message
 */
void read_msg (char *msg)
{
    uint16_t msg_len = read_char(); // read the length of the message as first byte
    int i;
    for (i = 0; i < msg_len; i++) {
        msg[i] = read_char();
    }
}

/*
 * Write a message on the SCI connection
 *  - message is a pointer to a buffer with a string terminated by '\n' to be written
 *  - len is the length of the message, in bytes, including '\n' but not '\0'
 */
void write_msg (char *msg, uint8_t len)
{
    char buf[BUFSIZE];
    buf[0] = (char) len; // put len as first byte of buffer

    // put rest of message into buffer
    int i;
    for (i = 0; i < len; i++) {
        buf[i + 1] = msg[i];
    }

    // send the buffer over the connection
    SCI_writeCharArray(UART_BASE, (uint16_t*)buf, len + 1);
}

// ***************************************************** Message Handling  ****************************************************** //

/*
 * Process a ZCS command message (turn ZCS on or off)
 */
void process_zcs_msg (char *msg)
{
    if (strncmp(msg + 4, "ON", 2) == 0) {
        zcs = ON;
        write_msg("OK\n", 3);
    } else if (strncmp(msg + 4, "OFF", 3) == 0) {
        zcs = OFF;
        write_msg("OK\n", 3);
    } else {
        write_msg("ERR BAD ARG\n", 12);
    }
}

/*
 * Process a SW command message (set state of the switches)
 */
void process_sw_msg (char *msg)
{
    uint32_t desired_state, ret = 0;

    // bitmask will be in bytes 4, 5, 6, and 7, or indices 3, 4, 5, and 6
    desired_state = buf_to_mask(msg + 3);

    // change the switch state (set_all_switches takes care of ZCS)
    ret = set_all_switches(desired_state);
    if (ret == 0) {
        write_msg("OK\n", 3);
    } else {
        write_msg("ERR ZCS TMOUT\n", 14);
    }

}

/*
 * Process a PHASE command message (set the phase definitions)
 */
void process_phase_msg (char *msg)
{
    // first bitmask starts at byte 7, second starts at byte 11, third starts at byte 15
    phases[0] = buf_to_mask(msg + 6);
    phases[1] = buf_to_mask(msg + 10);
    phases[2] = buf_to_mask(msg + 14);

    write_msg("OK\n", 3);
}

/*
 * Process a ZCS query message (client asks whether ZCS is enabled or not)
 */
void process_zcs_query_msg ()
{
    if (zcs == ON) {
        write_msg("ZCS ON\n", 7);
    } else {
        write_msg("ZCS OFF\n", 8);
    }
}

/*
 * Process a SW query message (client asks what the state of the switches is)
 */
void process_sw_query_msg ()
{
    // read the state of all of the switches
    uint32_t state_to_report = 0;
    int i;
    for (i = 0; i < NUM_SWITCHES; i++) {
        state_to_report |= GPIO_readPin(switch_num_mapping[i]) << i;
    }

    // put all of the state into the message
    char msg[BUFSIZE];
    msg[0] = 'S';
    msg[1] = 'W';
    msg[2] = ' ';
    mask_to_buf(msg + 3, state_to_report);
    msg[7] = '\n';
    msg[8] = '\0';

    // write to the SCI connection
    write_msg(msg, 8);
}

/*
 * Process a PHASE query message (client asks what the current phase definition are)
 */
void process_phase_query_msg()
{
    char msg[BUFSIZE];
    char header_str[BUFSIZE] = "PHASE ";
    int i;

    // copy the header into the msg buffer first
    for (i = 0; header_str[i] != '\0'; i++) {
        msg[i] = header_str[i];
    }

    // copy the three bitmasks sequentially into the msg buffer
    mask_to_buf(msg + i, phases[0]);
    mask_to_buf(msg + i + 4, phases[1]);
    mask_to_buf(msg + i + 8, phases[2]);

    msg[i + 12] = '\n';

    // write to the SCI connection
    write_msg(msg, 19);
}

// ***************************************************** Switch LED testing  ***************************************************** //

/*
 * For testing purposes only...
 * Sets the switches to a few easily recognizable patterns with delays in between
 * Used to verify the 32-bit bitmask defining the state
 */
void bitmask_test ()
{
    // all off
    set_all_switches(0);
    DEVICE_DELAY_US(1000000);

    // all on
    set_all_switches(0b111111111111111111);
    DEVICE_DELAY_US(2000000);

    // all even on
    set_all_switches(0b101010101010101010);
    DEVICE_DELAY_US(2000000);

    // all odd on
    set_all_switches(0b010101010101010101);
    DEVICE_DELAY_US(2000000);

    // first and last
    set_all_switches(0b100000000000000001);
    DEVICE_DELAY_US(2000000);

    // all off
    set_all_switches(0);
}

//
/*
 * For testing purposes only...
 * Turns all switches on from 1 to 18 with small delay in between
 * Then turns all switches off from 1 to 18 with small delay in between
 */
void cascade_switches_test ()
{
    int i;
    for (i = 1; i <= NUM_SWITCHES; i++) {
        set_switch_state(i, ON);
        DEVICE_DELAY_US(250000);
    }
    DEVICE_DELAY_US(1000000);
    for (i = 1; i <= NUM_SWITCHES; i++) {
        set_switch_state(i, OFF);
        DEVICE_DELAY_US(250000);
    }
    DEVICE_DELAY_US(1000000);
}

// ******************************************************** Main Function ******************************************************** //
void main(void)
{

    // ******************** Initialization (from TI example) *********************** //
    Device_init();                  // Initialize device clock and peripherals
    Device_initGPIO();              // Disable pin locks and enable internal pull-ups.
    Interrupt_initModule();         // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    Interrupt_initVectorTable();    // Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).
    Board_init();                   // Configure ePWM1, ePWM2, and TZ GPIOs/Modules
    C2000Ware_libraries_init();     // C2000Ware Library initialization

    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    EINT;
    ERTM;

    // ********************************** Main Code ******************************** //

    // Set all switches off on boot
    set_all_switches(0);

    // Buffer to hold all messages
    char msg[BUFSIZE];

    // Enter main control loop
    while (1) {

        // clear msg
        clear_buf(msg, 16);

        // get a new message from client; blocks until new message received
        read_msg(msg);

        // if ZCS query message received, handle it
        if (strncmp(msg, "ZCS?", 4) == 0) {
            process_zcs_query_msg();
            continue;
        }

        // if ZCS message received, handle it
        if (strncmp(msg, "ZCS", 3) == 0) {
            process_zcs_msg(msg);
            continue;
        }

        // if SW query message received, handle it
        if (strncmp(msg, "SW?", 3) == 0) {
            process_sw_query_msg();
            continue;
        }

        // if SW message received, handle it
        if (strncmp(msg, "SW", 2) == 0) {
            process_sw_msg(msg);
            continue;
        }

        // if PHASE query message received, handle it
        if (strncmp(msg, "PHASE?", 6) == 0) {
            process_phase_query_msg();
            continue;
        }

        // if PHASE message received, handle it
        if (strncmp(msg, "PHASE", 5) == 0) {
            process_phase_msg(msg);
            continue;
        }
    }
}

// End of File
