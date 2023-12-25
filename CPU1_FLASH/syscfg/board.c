/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	CMPSSLITE_init();
	CPUTIMER_init();
	GPIO_init();
	SCI_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// ANALOG -> CURR_SENSE_PINS Pinmux
	//
	// Analog PinMux for A12/C1
	GPIO_setPinConfig(GPIO_238_GPIO238);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(238, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A15/C7, C4/A14
	GPIO_setPinConfig(GPIO_233_GPIO233);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(233, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A4/C14
	GPIO_setPinConfig(GPIO_225_GPIO225);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(225, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A5/C2
	GPIO_setPinConfig(GPIO_244_GPIO244);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(244, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A7/C3
	GPIO_setPinConfig(GPIO_245_GPIO245);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(245, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A8/C11
	GPIO_setPinConfig(GPIO_241_GPIO241);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(241, GPIO_ANALOG_ENABLED);
	// GPIO4 -> SWITCH1 Pinmux
	GPIO_setPinConfig(GPIO_4_GPIO4);
	// GPIO18 -> SWITCH2 Pinmux
	GPIO_setPinConfig(GPIO_18_GPIO18);
	// GPIO16 -> SWITCH3 Pinmux
	GPIO_setPinConfig(GPIO_16_GPIO16);
	// GPIO33 -> SWITCH4 Pinmux
	GPIO_setPinConfig(GPIO_33_GPIO33);
	// GPIO12 -> SWITCH5 Pinmux
	GPIO_setPinConfig(GPIO_12_GPIO12);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(12, GPIO_ANALOG_DISABLED);
	// GPIO13 -> SWITCH6 Pinmux
	GPIO_setPinConfig(GPIO_13_GPIO13);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(13, GPIO_ANALOG_DISABLED);
	// GPIO230 -> SWITCH7 Pinmux
	GPIO_setPinConfig(GPIO_230_GPIO230);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(230, GPIO_ANALOG_DISABLED);
	// GPIO227 -> SWITCH8 Pinmux
	GPIO_setPinConfig(GPIO_227_GPIO227);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(227, GPIO_ANALOG_DISABLED);
	// GPIO224 -> SWITCH9 Pinmux
	GPIO_setPinConfig(GPIO_224_GPIO224);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(224, GPIO_ANALOG_DISABLED);
	// GPIO242 -> SWITCH10 Pinmux
	GPIO_setPinConfig(GPIO_242_GPIO242);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(242, GPIO_ANALOG_DISABLED);
	// GPIO226 -> SWITCH11 Pinmux
	GPIO_setPinConfig(GPIO_226_GPIO226);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(226, GPIO_ANALOG_DISABLED);
	// GPIO28 -> SWITCH12 Pinmux
	GPIO_setPinConfig(GPIO_28_GPIO28);
	// AGPIO -> GPIO mode selected
	GPIO_setAnalogMode(28, GPIO_ANALOG_DISABLED);
	// GPIO29 -> SWITCH13 Pinmux
	GPIO_setPinConfig(GPIO_29_GPIO29);
	// GPIO6 -> SWITCH14 Pinmux
	GPIO_setPinConfig(GPIO_6_GPIO6);
	// GPIO5 -> SWITCH15 Pinmux
	GPIO_setPinConfig(GPIO_5_GPIO5);
	// GPIO7 -> SWITCH16 Pinmux
	GPIO_setPinConfig(GPIO_7_GPIO7);
	// GPIO2 -> SWITCH17 Pinmux
	GPIO_setPinConfig(GPIO_2_GPIO2);
	// GPIO3 -> SWITCH18 Pinmux
	GPIO_setPinConfig(GPIO_3_GPIO3);
	//
	// SCIA -> UART Pinmux
	//
	GPIO_setPinConfig(UART_SCIRX_PIN_CONFIG);
	GPIO_setPadConfig(UART_SCIRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(UART_SCIRX_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(UART_SCITX_PIN_CONFIG);
	GPIO_setPadConfig(UART_SCITX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(UART_SCITX_GPIO, GPIO_QUAL_ASYNC);


}

//*****************************************************************************
//
// CMPSS-LITE Configurations
//
//*****************************************************************************
void CMPSSLITE_init(){
	CURRENT_SENSE1_init();
	CURRENT_SENSE2_init();
	CURRENT_SENSE3_init();
}

void CURRENT_SENSE1_init(){
    //
    // Select the value for CMP3HPMXSEL.
    //
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_3,4U);
    //
    // Select the value for CMP3HNMXSEL.
    //
    ASysCtl_selectCMPHNMuxValue(ASYSCTL_CMPHNMUX_SELECT_3,1U);
    //
    // Select the value for CMP3LPMXSEL.
    //
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_3,4U);
    //
    // Sets the configuration for the high comparator.
    //
    CMPSSLITE_configHighComparator(CURRENT_SENSE1_BASE,(CMPSS_INSRC_PIN));
    //
    // Sets the configuration for the low comparator.
    //
    CMPSSLITE_configLowComparator(CURRENT_SENSE1_BASE,(CMPSS_INSRC_DAC));
    //
    // Sets the configuration for the internal comparator DACs.
    //
    CMPSSLITE_configDAC(CURRENT_SENSE1_BASE, CMPSS_DACVAL_SYSCLK);
    //
    // Sets the value of the internal DAC of the high comparator.
    //
    CMPSSLITE_setDACValueHigh(CURRENT_SENSE1_BASE,0U);
    //
    // Sets the value of the internal DAC of the low comparator.
    //
    CMPSSLITE_setDACValueLow(CURRENT_SENSE1_BASE,0U);
    //
    //  Configures the digital filter of the high comparator.
    //
    CMPSSLITE_configFilterHigh(CURRENT_SENSE1_BASE, 0U, 1U, 1U);
    //
    // Configures the digital filter of the low comparator.
    //
    CMPSSLITE_configFilterLow(CURRENT_SENSE1_BASE, 0U, 1U, 1U);
    //
    // Sets the comparator hysteresis settings.
    //
    CMPSSLITE_setHysteresis(CURRENT_SENSE1_BASE,0U);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    //
    CMPSSLITE_disableLatchResetOnPWMSYNCHigh(CURRENT_SENSE1_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    //
    CMPSSLITE_disableLatchResetOnPWMSYNCLow(CURRENT_SENSE1_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    //
    CMPSSLITE_configBlanking(CURRENT_SENSE1_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    //
    CMPSSLITE_disableBlanking(CURRENT_SENSE1_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    //
    CMPSSLITE_configLatchOnPWMSYNC(CURRENT_SENSE1_BASE,false,false);
    //
    // Enables the CMPSSLITE module.
    //
    CMPSSLITE_enableModule(CURRENT_SENSE1_BASE);
    //
    // Delay for CMPSSLITE DAC to power up.
    //
    DEVICE_DELAY_US(500);
}
void CURRENT_SENSE2_init(){
    //
    // Select the value for CMP4HPMXSEL.
    //
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_4,1U);
    //
    // Select the value for CMP4HNMXSEL.
    //
    ASysCtl_selectCMPHNMuxValue(ASYSCTL_CMPHNMUX_SELECT_4,0U);
    //
    // Select the value for CMP4LPMXSEL.
    //
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_4,1U);
    //
    // Sets the configuration for the high comparator.
    //
    CMPSSLITE_configHighComparator(CURRENT_SENSE2_BASE,(CMPSS_INSRC_PIN));
    //
    // Sets the configuration for the low comparator.
    //
    CMPSSLITE_configLowComparator(CURRENT_SENSE2_BASE,(CMPSS_INSRC_DAC));
    //
    // Sets the configuration for the internal comparator DACs.
    //
    CMPSSLITE_configDAC(CURRENT_SENSE2_BASE, CMPSS_DACVAL_SYSCLK);
    //
    // Sets the value of the internal DAC of the high comparator.
    //
    CMPSSLITE_setDACValueHigh(CURRENT_SENSE2_BASE,0U);
    //
    // Sets the value of the internal DAC of the low comparator.
    //
    CMPSSLITE_setDACValueLow(CURRENT_SENSE2_BASE,0U);
    //
    //  Configures the digital filter of the high comparator.
    //
    CMPSSLITE_configFilterHigh(CURRENT_SENSE2_BASE, 0U, 1U, 1U);
    //
    // Configures the digital filter of the low comparator.
    //
    CMPSSLITE_configFilterLow(CURRENT_SENSE2_BASE, 0U, 1U, 1U);
    //
    // Sets the comparator hysteresis settings.
    //
    CMPSSLITE_setHysteresis(CURRENT_SENSE2_BASE,0U);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    //
    CMPSSLITE_disableLatchResetOnPWMSYNCHigh(CURRENT_SENSE2_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    //
    CMPSSLITE_disableLatchResetOnPWMSYNCLow(CURRENT_SENSE2_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    //
    CMPSSLITE_configBlanking(CURRENT_SENSE2_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    //
    CMPSSLITE_disableBlanking(CURRENT_SENSE2_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    //
    CMPSSLITE_configLatchOnPWMSYNC(CURRENT_SENSE2_BASE,false,false);
    //
    // Enables the CMPSSLITE module.
    //
    CMPSSLITE_enableModule(CURRENT_SENSE2_BASE);
    //
    // Delay for CMPSSLITE DAC to power up.
    //
    DEVICE_DELAY_US(500);
}
void CURRENT_SENSE3_init(){
    //
    // Select the value for CMP2HPMXSEL.
    //
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_2,4U);
    //
    // Select the value for CMP2HNMXSEL.
    //
    ASysCtl_selectCMPHNMuxValue(ASYSCTL_CMPHNMUX_SELECT_2,1U);
    //
    // Select the value for CMP2LPMXSEL.
    //
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_2,4U);
    //
    // Sets the configuration for the high comparator.
    //
    CMPSSLITE_configHighComparator(CURRENT_SENSE3_BASE,(CMPSS_INSRC_PIN));
    //
    // Sets the configuration for the low comparator.
    //
    CMPSSLITE_configLowComparator(CURRENT_SENSE3_BASE,(CMPSS_INSRC_DAC));
    //
    // Sets the configuration for the internal comparator DACs.
    //
    CMPSSLITE_configDAC(CURRENT_SENSE3_BASE, CMPSS_DACVAL_SYSCLK);
    //
    // Sets the value of the internal DAC of the high comparator.
    //
    CMPSSLITE_setDACValueHigh(CURRENT_SENSE3_BASE,0U);
    //
    // Sets the value of the internal DAC of the low comparator.
    //
    CMPSSLITE_setDACValueLow(CURRENT_SENSE3_BASE,0U);
    //
    //  Configures the digital filter of the high comparator.
    //
    CMPSSLITE_configFilterHigh(CURRENT_SENSE3_BASE, 0U, 1U, 1U);
    //
    // Configures the digital filter of the low comparator.
    //
    CMPSSLITE_configFilterLow(CURRENT_SENSE3_BASE, 0U, 1U, 1U);
    //
    // Sets the comparator hysteresis settings.
    //
    CMPSSLITE_setHysteresis(CURRENT_SENSE3_BASE,0U);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    //
    CMPSSLITE_disableLatchResetOnPWMSYNCHigh(CURRENT_SENSE3_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    //
    CMPSSLITE_disableLatchResetOnPWMSYNCLow(CURRENT_SENSE3_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    //
    CMPSSLITE_configBlanking(CURRENT_SENSE3_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    //
    CMPSSLITE_disableBlanking(CURRENT_SENSE3_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    //
    CMPSSLITE_configLatchOnPWMSYNC(CURRENT_SENSE3_BASE,false,false);
    //
    // Enables the CMPSSLITE module.
    //
    CMPSSLITE_enableModule(CURRENT_SENSE3_BASE);
    //
    // Delay for CMPSSLITE DAC to power up.
    //
    DEVICE_DELAY_US(500);
}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	TIMER_10S_init();
}

void TIMER_10S_init(){
	CPUTimer_setEmulationMode(TIMER_10S_BASE, CPUTIMER_EMULATIONMODE_STOPATZERO);
	CPUTimer_setPreScaler(TIMER_10S_BASE, 0U);
	CPUTimer_setPeriod(TIMER_10S_BASE, 1200000000U);
	CPUTimer_enableInterrupt(TIMER_10S_BASE);
	CPUTimer_stopTimer(TIMER_10S_BASE);

	CPUTimer_reloadTimerCounter(TIMER_10S_BASE);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	SWITCH1_init();
	SWITCH2_init();
	SWITCH3_init();
	SWITCH4_init();
	SWITCH5_init();
	SWITCH6_init();
	SWITCH7_init();
	SWITCH8_init();
	SWITCH9_init();
	SWITCH10_init();
	SWITCH11_init();
	SWITCH12_init();
	SWITCH13_init();
	SWITCH14_init();
	SWITCH15_init();
	SWITCH16_init();
	SWITCH17_init();
	SWITCH18_init();
}

void SWITCH1_init(){
	GPIO_setPadConfig(SWITCH1, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH1, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH1, GPIO_DIR_MODE_OUT);
}
void SWITCH2_init(){
	GPIO_setPadConfig(SWITCH2, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH2, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH2, GPIO_DIR_MODE_OUT);
}
void SWITCH3_init(){
	GPIO_setPadConfig(SWITCH3, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH3, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH3, GPIO_DIR_MODE_OUT);
}
void SWITCH4_init(){
	GPIO_setPadConfig(SWITCH4, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH4, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH4, GPIO_DIR_MODE_OUT);
}
void SWITCH5_init(){
	GPIO_setPadConfig(SWITCH5, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH5, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH5, GPIO_DIR_MODE_OUT);
}
void SWITCH6_init(){
	GPIO_setPadConfig(SWITCH6, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH6, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH6, GPIO_DIR_MODE_OUT);
}
void SWITCH7_init(){
	GPIO_setPadConfig(SWITCH7, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH7, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH7, GPIO_DIR_MODE_OUT);
}
void SWITCH8_init(){
	GPIO_setPadConfig(SWITCH8, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH8, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH8, GPIO_DIR_MODE_OUT);
}
void SWITCH9_init(){
	GPIO_setPadConfig(SWITCH9, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH9, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH9, GPIO_DIR_MODE_OUT);
}
void SWITCH10_init(){
	GPIO_setPadConfig(SWITCH10, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH10, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH10, GPIO_DIR_MODE_OUT);
}
void SWITCH11_init(){
	GPIO_setPadConfig(SWITCH11, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH11, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH11, GPIO_DIR_MODE_OUT);
}
void SWITCH12_init(){
	GPIO_setPadConfig(SWITCH12, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH12, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH12, GPIO_DIR_MODE_OUT);
}
void SWITCH13_init(){
	GPIO_setPadConfig(SWITCH13, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH13, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH13, GPIO_DIR_MODE_OUT);
}
void SWITCH14_init(){
	GPIO_setPadConfig(SWITCH14, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH14, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH14, GPIO_DIR_MODE_OUT);
}
void SWITCH15_init(){
	GPIO_setPadConfig(SWITCH15, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH15, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH15, GPIO_DIR_MODE_OUT);
}
void SWITCH16_init(){
	GPIO_setPadConfig(SWITCH16, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH16, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH16, GPIO_DIR_MODE_OUT);
}
void SWITCH17_init(){
	GPIO_setPadConfig(SWITCH17, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH17, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH17, GPIO_DIR_MODE_OUT);
}
void SWITCH18_init(){
	GPIO_setPadConfig(SWITCH18, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(SWITCH18, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(SWITCH18, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Setings for INT_TIMER_10S
	Interrupt_register(INT_TIMER_10S, &INT_TIMER_10S_ISR);
	Interrupt_enable(INT_TIMER_10S);
}
//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
void SCI_init(){
	UART_init();
}

void UART_init(){
	SCI_clearInterruptStatus(UART_BASE, SCI_INT_RXFF | SCI_INT_TXFF | SCI_INT_FE | SCI_INT_OE | SCI_INT_PE | SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY);
	SCI_clearOverflowStatus(UART_BASE);
	SCI_resetTxFIFO(UART_BASE);
	SCI_resetRxFIFO(UART_BASE);
	SCI_resetChannels(UART_BASE);
	SCI_setConfig(UART_BASE, DEVICE_LSPCLK_FREQ, UART_BAUDRATE, (SCI_CONFIG_WLEN_8|SCI_CONFIG_STOP_ONE|SCI_CONFIG_PAR_NONE));
	SCI_disableLoopback(UART_BASE);
	SCI_performSoftwareReset(UART_BASE);
	SCI_enableFIFO(UART_BASE);
	SCI_enableModule(UART_BASE);
}

