/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_wattnode.c
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

#include "cs_woodmaster_400_wattnode.h"
#include "cs_woodmaster_400_user.h"


/******************************************************************************/
/* PC-Lint Options                                                            */
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
/* Global Variable And Typed Constant Defining Declarations                   */
/******************************************************************************/
volatile uint8_t wattNodeMinuteReg;

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
static volatile bool switchHistory = (bool)SWITCH_RELEASED;

volatile uint8_t wattNodePulseAccumulator = 0u;

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
bool ProcessWattNodeInput (const bool switchInput)
{
    bool switchState;

    switchState = SwitchFilterDebouncer (switchInput);

    if (RisingEdgeDetector (&switchHistory, switchState))
    {
        ++pulses;
    }

    return switchState;

}


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

float DetermineCoefficients() {
    if (voltage==120) {
        WattNodeCoefficient = 0.0250;  //0.0250 is for the WNB-3Y-208-P model
        currentRating = 20.0;  //20 is the Amps rated for the current transformer
    }
    else if(voltage==240) {
        WattNodeCoefficient = 0.04792;  //0.04792 is for the WNB-3Y-400-P model
        currentRating = 15.0;  //15 is the Amps rated for the current transformer
    }
    else{
        WattNodeCoefficient = 1.0;  //should never happen
        currentRating = 1.0;  //should never happen
    }
}

float CalculateEnergy ()
{
    float energy,power;
    
    DetermineCoefficients();
    
    energy = (WattNodeCoefficient)*(currentRating)*(2*(float)pulses);  // Calculate the Power in Wh per pulse
    
    if(pulsescount==0) {
        power1 = energy/(120.0/3600.0);
        pulsescount = ++pulsescount;
        //(pulses)=0;
    }
    else {
        power2 = energy/(120.0/3600.0);
        pulsescount = 0;
        //(pulses)=0;
    }
    power = energy/((120.0/3600.0));
    
    if(power2 > 0) {
        power = (power1+power2)/(2.0);
        (pulses)=0;
    }
    else {// power 2 = 0 first time through
        power = power1;
       (pulses)=0;
    }
    
    return (power);
    
    //Old Code from Michael P.
    //float energy = (.0250)*(20.0)*(float)(pulses); //0.0250 = coefficient for wattNode model, 20 amp CT
    //float power = energy/(120.0/3600.0);
    //(pulses) = 0;
    
    //return power;
           
}/* end CalculateEnergy () */

/*
float CalculateEnergy ()
{
    float coefficient, currentRating,voltage;
    
    voltage=VOLTAGE;
    
    if(voltage == 120){
        coefficient = .0250;
        currentRating = 20.0;//0.0250 = coefficient for wattNode model, 20 amp CT
    }
    else { // voltage == 240
        coefficient = .04792;
        currentRating = 15.0;
    }
    
    float energy = coefficient*(currentRating)*(float)(pulses); 
    float power = energy/(120.0/3600.0);  // Andrew and Jeff not sure what the 120 is, apparently not voltage....
    (pulses) = 0;
    
    return power;
           
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
