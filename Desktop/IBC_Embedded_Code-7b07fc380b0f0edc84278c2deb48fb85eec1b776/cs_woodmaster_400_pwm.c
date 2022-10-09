/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_pwm.c
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

/******************************************************************************/
/* Include Header Files                                                       */
/******************************************************************************/
#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */

#endif

#include "cs_woodmaster_400_pwm.h"
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
 * Function:        uint16_t SetPwmPercent (uint8_t PwmPercent, uint8_t PwmOutputId)
 *
 * Description:     SetPwmPercent() sets the duty cycle of the specified PWM
 *                  output to the value specified by the PwmPercent argument.
 *
 * Dependencies:    cs_pdk_400_pwm.h
 *
 * PreConditions:   The microcontroller port pins and the PWM modules are
 *                  properly configured.
 *
 * Inputs:          An argument that specifies the desired percent duty cycle
 *                  and an argument that specifies the PWM output that will be
 *                  set to the desired percent duty cycle.
 *
 * Output:          An integer that specifies the actual value that was used to
 *                  set the specified PWM module.
 *
 * Side Effects:    None
 ******************************************************************************/
uint16_t SetPwmPercent (uint8_t PwmPercent, uint8_t PwmOutputId)
{
    uint16_t pwmDutyCycle = (uint16_t)((PwmPercent/100.0) * 1023);
                      
   if( PwmOutputId == PWM_PORT_CN11){
//        // scale for earth dampers(2-10VDC instead of 0.5 to 18VDC, which is how the 
//        // 4.0.X hardware is configured))
       float percent = (float)PwmPercent;
       float transformedPercent = (percent * 0.444) + 10.6;
       uint8_t scaledPWMPercent = (uint8_t)transformedPercent;
       pwmDutyCycle = (uint16_t)((scaledPWMPercent/100.0) * 1023);
    }
    switch (PwmOutputId)
    {
        case PWM_PORT_CN9 : //ID Fan
            SetDCPWM4 (pwmDutyCycle);
            break;

        case PWM_PORT_CN10 : // inducer fan position
            SetDCPWM6 (pwmDutyCycle);
            break;

        case PWM_PORT_CN11 : //secondary air damper
            SetDCPWM8 (pwmDutyCycle);
            break;

        default :

            break;
    }
        
  
    return pwmDutyCycle;
}

/*******************************************************************************
 * Function:        None
 *
 * Description:     None
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    None
 ******************************************************************************/

/***** EOF for cs_pdk_400_pwm.c ***********************************************/
