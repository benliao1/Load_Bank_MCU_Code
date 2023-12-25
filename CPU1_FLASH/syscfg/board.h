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

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// ANALOG -> CURR_SENSE_PINS Pinmux
//
//
// GPIO4 - GPIO Settings
//
#define SWITCH1_GPIO_PIN_CONFIG GPIO_4_GPIO4
//
// GPIO18 - GPIO Settings
//
#define SWITCH2_GPIO_PIN_CONFIG GPIO_18_GPIO18
//
// GPIO16 - GPIO Settings
//
#define SWITCH3_GPIO_PIN_CONFIG GPIO_16_GPIO16
//
// GPIO33 - GPIO Settings
//
#define SWITCH4_GPIO_PIN_CONFIG GPIO_33_GPIO33
//
// GPIO12 - GPIO Settings
//
#define SWITCH5_GPIO_PIN_CONFIG GPIO_12_GPIO12
//
// GPIO13 - GPIO Settings
//
#define SWITCH6_GPIO_PIN_CONFIG GPIO_13_GPIO13
//
// GPIO230 - GPIO Settings
//
#define SWITCH7_GPIO_PIN_CONFIG GPIO_230_GPIO230
//
// GPIO227 - GPIO Settings
//
#define SWITCH8_GPIO_PIN_CONFIG GPIO_227_GPIO227
//
// GPIO224 - GPIO Settings
//
#define SWITCH9_GPIO_PIN_CONFIG GPIO_224_GPIO224
//
// GPIO242 - GPIO Settings
//
#define SWITCH10_GPIO_PIN_CONFIG GPIO_242_GPIO242
//
// GPIO226 - GPIO Settings
//
#define SWITCH11_GPIO_PIN_CONFIG GPIO_226_GPIO226
//
// GPIO28 - GPIO Settings
//
#define SWITCH12_GPIO_PIN_CONFIG GPIO_28_GPIO28
//
// GPIO29 - GPIO Settings
//
#define SWITCH13_GPIO_PIN_CONFIG GPIO_29_GPIO29
//
// GPIO6 - GPIO Settings
//
#define SWITCH14_GPIO_PIN_CONFIG GPIO_6_GPIO6
//
// GPIO5 - GPIO Settings
//
#define SWITCH15_GPIO_PIN_CONFIG GPIO_5_GPIO5
//
// GPIO7 - GPIO Settings
//
#define SWITCH16_GPIO_PIN_CONFIG GPIO_7_GPIO7
//
// GPIO2 - GPIO Settings
//
#define SWITCH17_GPIO_PIN_CONFIG GPIO_2_GPIO2
//
// GPIO3 - GPIO Settings
//
#define SWITCH18_GPIO_PIN_CONFIG GPIO_3_GPIO3

//
// SCIA -> UART Pinmux
//
//
// SCIA_RX - GPIO Settings
//
#define GPIO_PIN_SCIA_RX 0
#define UART_SCIRX_GPIO 0
#define UART_SCIRX_PIN_CONFIG GPIO_0_SCIA_RX
//
// SCIA_TX - GPIO Settings
//
#define GPIO_PIN_SCIA_TX 1
#define UART_SCITX_GPIO 1
#define UART_SCITX_PIN_CONFIG GPIO_1_SCIA_TX

//*****************************************************************************
//
// CMPSS-LITE Configurations
//
//*****************************************************************************
#define CURRENT_SENSE1_BASE CMPSSLITE3_BASE
void CURRENT_SENSE1_init();
#define CURRENT_SENSE2_BASE CMPSSLITE4_BASE
void CURRENT_SENSE2_init();
#define CURRENT_SENSE3_BASE CMPSSLITE2_BASE
void CURRENT_SENSE3_init();

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define TIMER_10S_BASE CPUTIMER0_BASE
void TIMER_10S_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define SWITCH1 4
void SWITCH1_init();
#define SWITCH2 18
void SWITCH2_init();
#define SWITCH3 16
void SWITCH3_init();
#define SWITCH4 33
void SWITCH4_init();
#define SWITCH5 12
void SWITCH5_init();
#define SWITCH6 13
void SWITCH6_init();
#define SWITCH7 230
void SWITCH7_init();
#define SWITCH8 227
void SWITCH8_init();
#define SWITCH9 224
void SWITCH9_init();
#define SWITCH10 242
void SWITCH10_init();
#define SWITCH11 226
void SWITCH11_init();
#define SWITCH12 28
void SWITCH12_init();
#define SWITCH13 29
void SWITCH13_init();
#define SWITCH14 6
void SWITCH14_init();
#define SWITCH15 5
void SWITCH15_init();
#define SWITCH16 7
void SWITCH16_init();
#define SWITCH17 2
void SWITCH17_init();
#define SWITCH18 3
void SWITCH18_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_TIMER_10S
#define INT_TIMER_10S INT_TIMER0
#define INT_TIMER_10S_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_TIMER_10S_ISR(void);

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
#define UART_BASE SCIA_BASE
#define UART_BAUDRATE 57600
#define UART_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define UART_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define UART_CONFIG_PAR SCI_CONFIG_PAR_NONE
void UART_init();

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	CMPSSLITE_init();
void	CPUTIMER_init();
void	GPIO_init();
void	INTERRUPT_init();
void	SCI_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
