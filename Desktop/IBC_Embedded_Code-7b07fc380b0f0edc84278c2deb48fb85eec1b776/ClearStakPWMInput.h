/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_thermistor.h
 *  Date: 25 March 2015
 *
 *  Author: Peter J. D'Aloisio
 *  Company: Amaranthine, LLC
 *  (c) 2015 Amaranthine, LLC
 *
 *  Licensee: ClearStak, LLC
 *
 *  The material contained herein is confidential and proprietary.
 *******************************************************************************
 *  Revision History: See the cs_pdk_400_main.c source file.
 *******************************************************************************
 *  Microcontroller: PIC18F86K22    Internal Oscillator == 1MHz.
 *******************************************************************************
 *  Notes:  Coding for a source file for an Outdoor Wood Furnace Low Emission
 *          Controller model number IBC 4.0.0
 *
 *          This source file contains ...
 *******************************************************************************
 *  THIS SOFTWARE/FIRMWARE IS PROVIDED IN AN "AS IS" CONDITION. NO
 *  WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 *  LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *  PARTICULAR PURPOSE APPLY TO THIS SOFTWARE/FIRMWARE. THE COMPANY
 *  SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL
 *  OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER. ACCEPTANCE AND/OR
 *  USE OF THIS SOFTWARE/FIRMWARE SHALL CONSTITUTE ACCEPTANCE OF THESE TERMS
 *  AND CONDITIONS.
 ******************************************************************************/
#ifndef CS_PDK_400_TACHOMETER_H
#define	CS_PDK_400_TACHOMETER_H

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Typedefs                                                                   */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions (Typedefs)                                      */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declarations                */
/******************************************************************************/
/*extern volatile uint16_t CN9CaptureIntervalValue;
extern volatile uint16_t CN9T1Value;
extern volatile uint16_t CN9T2RawValueBuffer;
extern volatile uint24_t CN9T2Value;

extern volatile uint16_t CN10CaptureIntervalValue;
extern volatile uint16_t CN10T1Value;
extern volatile uint16_t CN10T2RawValueBuffer;
extern volatile uint24_t CN10T2Value;

extern volatile uint16_t CN11CaptureIntervalValue;
extern volatile uint16_t CN11T1Value;
extern volatile uint16_t CN11T2RawValueBuffer;
extern volatile uint24_t CN11T2Value;


extern volatile uint16_t cn9NewCapturedValue;   /* CN9, CCP5 and TMR1. 
extern volatile uint16_t cn10NewCapturedValue;  /* CN10, CCP7 and TMR5. 
extern volatile uint16_t cn11NewCapturedValue;  /* CN11, CCP9 and TMR7. 
                                        /* The most recent (new) value captured
                                         * by the CCP module. 

extern volatile uint16_t cn9OldCapturedValue;
extern volatile uint16_t cn10OldCapturedValue;
extern volatile uint16_t cn11OldCapturedValue;
                                    /* Used to hold the (old) value that was
                                     * previously captured by the CCP module.
                                     * The old captured value is subtracted
                                     * from the new captured value in order to
                                     * calculate the number of timer counts in
                                     * the tachometer pulse period. */

extern volatile uint16_t cn9RpmBuffer;
extern volatile uint16_t cn10RpmBuffer;
extern volatile uint16_t cn11RpmBuffer;
/*
extern uint16_t cn9Rpm;
extern uint16_t cn10Rpm;
extern uint16_t cn11Rpm;            /* The cnXRpmBuffer registers and the
                                     * cnXRpm registers are used to double
                                     * buffer the tachometer RPM values in order
                                     * to compensate for potentially non-atomic
                                     * register operations in the event of
                                     * ISR operations. The cnXRpmBuffer
                                     * registers are written to during ISR
                                     * operations. */

extern volatile uint8_t cn9TachPulseTimer;
extern volatile uint8_t cn10TachPulseTimer;
extern volatile uint8_t cn11TachPulseTimer;
/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
uint24_t GetCN9Feedback();
uint24_t GetCN10Feedback();
uint24_t GetCN11Feedback();
/******************************************************************************/
/* Global enums                                                               */
/******************************************************************************/

/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/
#define MOTOR_PORT_CN9  1u
#define MOTOR_PORT_CN10 2u
#define MOTOR_PORT_CN11 3u

#define CN9_TACH_PULSES_PER_REVOLUTION 3.0

#define CN10_TACH_PULSES_PER_REVOLUTION 1.0

#define CN11_TACH_PULSES_PER_REVOLUTION 3.0

#define SECONDS_PER_MINUTE 60.0
#define PULES_PER_INT 16u

#define FOSC_DIVIDED_BY_4 0.000004
//
#define TACH_TIMER1_CONSTANT 115200     /* (Fosc/4)/8 */
#define TACH_TIMER5_CONSTANT 115200     /* (Fosc/4)/8 */
#define TACH_TIMER7_CONSTANT 115200     /* (Fosc/4)/8 */

#endif	/* CS_PDK_400_TACHOMETER_H */

/***** EOF for cs_pdk_400_tachometer.h ****************************************/
