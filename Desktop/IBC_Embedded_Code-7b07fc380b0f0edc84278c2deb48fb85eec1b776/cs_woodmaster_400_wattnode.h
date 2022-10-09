/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_wattnode.h
 *  Date: 2 January 2015
 *
 *  Author: Michael Paquette
 *  Company: BMC, LLC
 *  (c) 2015 BMC, LLC
 *
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
#ifndef	CS_PDK_400_WATTNODE_H_
#define	CS_PDK_400_WATTNODE_H_


/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declaration                 */
/******************************************************************************/
extern volatile uint8_t wattNodeMinuteReg;
uint32_t pulses = 0;
uint8_t pulsescount = 0;
float power1 = 0;
float power2 = 0;
uint8_t voltage = 230;
float WattNodeCoefficient, currentRating;


/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
bool ProcessWattNodeInput (const bool switchInput);
float DetermineCoefficients ();
float CalculateEnergy ();


/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/



/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

#endif	/* CS_PDK_400_WATTNODE_H_ */

/***** EOF for cs_pdk_400_wattnode.h *****************************************/
