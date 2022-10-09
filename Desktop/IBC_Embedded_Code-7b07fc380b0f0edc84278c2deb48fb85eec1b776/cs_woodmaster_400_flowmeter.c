/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_flowmeter.c
 *  Date: 2 January 2015
 *
 *  Author: Peter J. D'Aloisio
 *  Company: Amaranthine, LLC
 *  (c) 2015 Amaranthine, LLC
 *
 *  Licensee: ClearStak, LLC
 * 
 * VERSIONS
 * 
 * HARD CODED GPM AT 49 BASED ON PUMP SPECS FOR GI-ONE: JEFF W: 1/25/2017
 * 3/8/17: set to 19 for GI-2: JW
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
 *          THIS IS IMPORTANT:
 *          I realize this file is called 'flowmeter', but really it is for any
 *          switch input debouncing
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
#include <stdbool.h>

#endif

#include "cs_woodmaster_400_flowmeter.h"
#include "cs_woodmaster_400_user.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declarations                   */
/******************************************************************************/
volatile uint8_t flowMeterMinuteReg;

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
static volatile bool switchHistory = (bool)SWITCH_RELEASED;

volatile uint8_t flowMeterPulseAccumulator = 0u;

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/
static bool SwitchFilterDebouncer (const bool rawSwitchInput);

static bool RisingEdgeDetector (volatile bool * const switchStateHistory,
                                const bool switchCurrentState);

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        bool ProcessFlowmeterInput (volatile uint8_t * const flowPulseAccumulator,
 *                                                      const bool switchInput)
 *
 * Description:     ProcessFlowmeterInput() accepts the switch input from a
 *                  flow meter, debounces this input, and based on rising edges
 *                  of the debounced switch input, adjusts a pulse accumulation
 *                  register.
 *
 * Dependencies:    cs_pdk_400_flowmeter.h, SwitchFilterDebouncer(),
 *                  RisingEdgeDetector(), flowPulseHistory.
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    None
 ******************************************************************************/
bool ProcessFlowmeterInput (volatile uint8_t * const flowPulseAccumulator,
                            const bool switchInput)
{
    bool switchState;

    switchState = SwitchFilterDebouncer (switchInput);

    if (RisingEdgeDetector (&switchHistory, switchState))
    {
        ++(*flowPulseAccumulator);
    }

    return switchState;

}/* end ProcessFlowmeterInput () */


/*******************************************************************************
 * Function:        uint8_t CalculateFlowmeterGpm
 *                              (volatile uint8_t * const flowPulseAccumulator)
 *
 * Description:     CalculateFlowmeterGpm() calculates gallons-per-minute based
 *                  on a two minute accumulation of pulses from a one pulse per
 *                  gallon flow meter.
 *
 * PreConditions:   None
 *
 * Dependencies:    cs_pdk_400_flowmeter.h
 *
 * Inputs:          The address of a register than contains the number of
 *                  accumulated pulses.
 *
 * Output:          Integral gallons per minute.
 *
 * Side Effects:    The register that contained the number of accumulated
 *                  pulses is reset to zero.
 ******************************************************************************/
uint8_t CalculateFlowmeterGpm (volatile uint8_t * const flowPulseAccumulator)
{
    uint8_t flowGpm;
    
    flowGpm = ((*flowPulseAccumulator)/2);

    (*flowPulseAccumulator) = 0;
    
   // flowGpm = 19; 
    return flowGpm;   
           
}/* end CalculateFlowmeterGpm () */



/*******************************************************************************
 * Function:        static bool SwitchFilterDebouncer (const bool rawSwitchInput)
 *
 * Description:     SwitchFilterDebouncer() is the firmware equivalent of a
 *                  first order digital filter (RC filter) in series with a
 *                  schmitt trigger. In the presence of a steady state input
 *                  argument, it takes approximately 11 function cycles
 *                  (function calls) to do a full integration between Schmitt
 *                  trigger levels.
 *
 * Dependencies:    cs_pdk_400_flowmeter.h
 *
 * PreConditions:   None
 *
 * Inputs:          The signal from an electromechanical (or equivalent) switch
 *                  as applied to a digital input of a microcontroller.
 *
 * Output:          A debounced version of the above described input.
 *
 * Side Effects:    None
 ******************************************************************************/
static bool SwitchFilterDebouncer (const bool rawSwitchInput)
{
    bool debouncedSwitchOutput;
    static volatile uint16_t filterOutputValue = (bool)SWITCH_RELEASED;
    static volatile bool debouncedSwitchStateHistory = (bool)SWITCH_RELEASED;
/*----------------------------------------------------------------------------*/
                                /* The firmware based digital filter. */
    if ((rawSwitchInput == (bool)SWITCH_ACTUATED) && (filterOutputValue < (uint16_t)SCHMITT_TRIGGER_UPPER_THRESHOLD))
    {
        if (filterOutputValue < ((int16_t)ZERO_POINT_TWO_FIVE >> 1))
        {
            filterOutputValue = ((uint16_t)ZERO_POINT_TWO_FIVE >> 1);
        }
                                /* Seed filterOutputValue in order to
                                 * make its lowest value an appropriate and
                                 * non-zero value. */
        else
        {
            filterOutputValue = (filterOutputValue + (filterOutputValue >> 2));
        }
                                /* Add 25% of filterOutputValue to
                                 * the filterOutputValue variable. */
    }
    
    else if (filterOutputValue > (uint16_t)SCHMITT_TRIGGER_LOWER_THRESHOLD)
    {
        filterOutputValue = (filterOutputValue - (filterOutputValue >> 2));
    }
                                /* Subtract 25% of filterOutputValue from
                                 * the filterOutputValue variable. */
/*----------------------------------------------------------------------------*/
                                /* The firmware based schmitt trigger. */
    if (filterOutputValue >= SCHMITT_TRIGGER_UPPER_THRESHOLD)
    {
        debouncedSwitchStateHistory = (bool)SWITCH_ACTUATED;
        debouncedSwitchOutput = (bool)SWITCH_ACTUATED;
    }

    else if (filterOutputValue <= SCHMITT_TRIGGER_LOWER_THRESHOLD)
    {
        debouncedSwitchStateHistory = (bool)SWITCH_RELEASED;
        debouncedSwitchOutput = (bool)SWITCH_RELEASED;
    }

    else
    {
        debouncedSwitchOutput = debouncedSwitchStateHistory;
    }

    return debouncedSwitchOutput;

}/* end SwitchFilterDebouncer() */


/*******************************************************************************
 * Function:        static bool RisingEdgeDetector (volatile bool * const switchStateHistory,
 *                                    const bool switchCurrentState)
 *
 * Description:     RisingEdgeDetector() returns logic 1 when the value of
 *                  the currentFlowPulse argument creates a rising edge when
 *                  compared to the value of flowPulseHistory.
 *
 * Dependencies:    cs_pdk_400_flowmeter.h
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the state of a debounced switch.
 *
 * Output:          Logic one if the currentFlowPulse argument has transitioned
 *                  from logic zero to logic one (rising edge).
 *
 * Side Effects:    flowPulseHistory contains the value of the currentFlowPulse
 *                  argument.
 ******************************************************************************/
static bool RisingEdgeDetector (volatile bool * const switchStateHistory, const bool switchCurrentState)
{
    bool stateHistory;

    stateHistory = *switchStateHistory;

    if (switchCurrentState == (bool)SWITCH_ACTUATED)
    {
        *switchStateHistory = (bool)SWITCH_ACTUATED;
    }

    else
    {
        *switchStateHistory = (bool)SWITCH_RELEASED;
    }

    return ((stateHistory ^ switchCurrentState) && switchCurrentState);

}/* end RisingEdgeDetector () */

/***** EOF for cs_pdk_400_flowmeter.c *****************************************/
