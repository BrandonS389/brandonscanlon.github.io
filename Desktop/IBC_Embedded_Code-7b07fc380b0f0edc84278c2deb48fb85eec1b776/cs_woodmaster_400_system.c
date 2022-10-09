/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_system.c
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

#endif

#include "cs_woodmaster_400_system.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/*PC-Lint is not picking up nested compiler specific library #include <>s so
 * the following errors have been check for this file and are being suppressed.
 * If this file is modified, these error suppressions must be temporarily
 * suspended in order to re-lint the file.*/

/*lint -e10 Supresses 'Expecting a structure or a union' */
/*lint -e40 Supresses 'Undeclared identifier' */
/*lint -e63 Supresses 'Expected an lvalue' */

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declaration                     */
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
 * Function:        void ConfigureOscillator(void)
 *
 * Description:     Configures the microcontroller's internal oscillator for
 *                  operation at 1MHz.
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    OSCCONbits.IRCF value may be changed.
 ******************************************************************************/
void ConfigureOscillator(void)
{
    OSCCONbits.IRCF = 3;     /* Set the internal clock oscillator speed
                               to 1MHz. */
    return;
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
}/* end ConfigureOscillator() */

/***** EOF for cs_pdk_400_system.c ********************************************/
