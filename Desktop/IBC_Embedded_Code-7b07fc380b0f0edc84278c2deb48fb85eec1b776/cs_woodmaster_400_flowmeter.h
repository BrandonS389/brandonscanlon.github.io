/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_flowmeter.h
 *  Date: 2 January 2015
 *
 *  Author: Peter J. D'Aloisio
 *  Company: Amaranthine, LLC
 *  (c) 2015 Amaranthine, LLC
 *
 *  Licensee: ClearStak, LLC
 *
 *  The material contained herein is confidential and proprietary.
 *******************************************************************************
 *  Revision History:   See the cs_pdk_400_main.c source file.
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
#ifndef	CS_PDK_400_FLOWMETER_H_
#define	CS_PDK_400_FLOWMETER_H_

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declaration                 */
/******************************************************************************/
extern volatile uint8_t flowMeterMinuteReg;
extern volatile uint8_t flowMeterPulseAccumulator;

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
bool ProcessFlowmeterInput (volatile uint8_t * const flowPulseAccumulator, const bool switchInput);
uint8_t CalculateFlowmeterGpm (volatile uint8_t * const flowPulseAccumulator);

/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/
                                        /* For reference in understanding
                                         * the operation of the associated
                                         * SwitchFilterDebouncer() C code. */

#define ONE_POINT_ZERO          0xFF    /* 1.0 is equivalent to 0xFF. */

#define ZERO_POINT_TWO_FIVE     0x3F    /* Approximately 0.25 of 0xFF.
                                         * This is implimented here by using
                                         * two logical right shifts. */

#define ZERO_POINT_SEVEN_FIVE   0xC0    /* Approximately 0.75 of 0xFF.
                                         * In code this will be implimented
                                         * by subtracting the result of two
                                         * logical right shifts of an original
                                         * integer value (0.25 of the original
                                         * integer value) from the orignal
                                         * integer value. */

                                        /* The flow meter is connected to
                                         * SwitchInputOne on the controller
                                         * board and is active logic high at
                                         * the microcontroller. */

#define SCHMITT_TRIGGER_UPPER_THRESHOLD 0xF0
#define SCHMITT_TRIGGER_LOWER_THRESHOLD 0x0F

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

#endif	/* CS_PDK_400_FLOWMETER_H_ */

/***** EOF for cs_pdk_400_flowmeter.h *****************************************/
