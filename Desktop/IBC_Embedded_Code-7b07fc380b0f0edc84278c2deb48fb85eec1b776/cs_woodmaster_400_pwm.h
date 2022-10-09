/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_pwm.h
 *  Date: 17 February 2015
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
#ifndef	CS_PDK_400_PWM_H_
#define	CS_PDK_400_PWM_H_

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declarations                */
/******************************************************************************/

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
uint8_t GetPotentiometerPercent (uint8_t PotentiometerId);

uint16_t SetPwmPercent (uint8_t PwmPercent, uint8_t PwmOutputId);

/******************************************************************************/
/* Global enums                                                               */
/******************************************************************************/

/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/
#define PWM_PORT_CN9 1

#define PWM_PORT_CN10 2

#define PWM_PORT_CN11 3

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

#endif	/* CS_PDK_400_PWM_H_ */

/***** EOF for cs_pdk_400_pwm.h ***********************************************/
