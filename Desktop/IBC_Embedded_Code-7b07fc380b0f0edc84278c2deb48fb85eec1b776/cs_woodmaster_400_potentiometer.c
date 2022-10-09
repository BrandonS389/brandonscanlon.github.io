/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_potentiometer.c
 *  Date: 23 February 2015
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

/******************************************************************************/
/* Include Header Files                                                       */
/******************************************************************************/
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>

#endif

#include "cs_woodmaster_400_potentiometer.h"
#include "cs_woodmaster_400_user.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declarations                   */
/******************************************************************************/

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        uint8_t GetPotentiometerPercent (uint8_t PotentiometerId)
 *
 * Description:     GetPotentiometerPercent() reads the analog input that is
 *                  associated with the potentiometer specified by
 *                  PotentiometerId and converts it to percent.
 *
 * Dependencies:    cs_pdk_400_user.h
 *
 * PreConditions:   The the microcontroller port pins and the analog-to-digital
 *                  converter are properly configured.
 *
 * Inputs:          An argument that specifies which potentiometer is to be
 *                  read.
 *
 * Output:          The percent of travel for the specified potentiometer.
 *
 * Side Effects:    None
 ******************************************************************************/
uint8_t GetPotentiometerPercent (uint8_t PotentiometerId)
{
    bool functionErrorState;
    int16_t adcResult;

    switch (PotentiometerId)
    {
        case HIGH_LIMIT_POT :

            (void) SetChanADC (WT_HIGH_LIMIT_POT);

            functionErrorState = CLEAR;

            break;

        case DIFFERENTIAL_POT :

            (void) SetChanADC (WT_DIFF_POT);

            functionErrorState = CLEAR;

            break;

        default :

            functionErrorState = SET;

            break;
    }

    if (functionErrorState == CLEAR)
    {
        __delay_us(200);            /* 200us A/D channel select settling
                                     * time. */
        (void) ConvertADC();

        while (BusyADC())
        {
            ;
        }                           /* Start the A/D conversion and wait for
                                     * ADC conversion completion. */

        adcResult = ReadADC();
    }

    else
    {
        adcResult = 0;
    }

    if (adcResult < 200)
    {
        adcResult = 0;
    }

    if (adcResult > 3890)
    {
        adcResult = 4095;
    }                                   /* Compensate for potentiometer
                                         * end-of-travel value tolerance. */

    return (uint8_t)(adcResult/4095.0 * 100);   /* Convert ADC result to integer
                                                 * percent. */
}

/***** EOF for cs_pdk_400_potentiometer.c *************************************/
