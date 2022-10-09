/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_message.c
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
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */

#endif

#include <stdio.h>
#include <string.h>

#include "cs_woodmaster_400_message.h"
#include "cs_woodmaster_400_user.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declaration                    */
/******************************************************************************/
volatile uint8_t serialDataXmitIntervalTimer = 8u;
volatile char assembledMessage[SERIAL_MSSG_LENGTH];

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
static const uint32_t SecondsLimitValue = (uint32_t)31536000;   /* One year. */
#define START_UP_STATE 0
#define START_UP_STATE 1
#define WARM_START_STATE 2
#define SMOKE_STATE 3
#define COOK_STATE 4
#define HOLD_STATE 5
#define SHUTDOWN_STATE 6
#define LOCKOUT_STATE 7
#define MAX_OPERATION_STATE 7


const char * const opStateNameTextArray[] = {
    "STAND_BY_STATE",                                   // 0
    "CHECKING_SYSTEM_STATE",                            // 1
    "PRIME_STATE",                                      // 2
    "START_UP_STATE",                                   // 3
    "BOOST_STATE",                                      // 4
    "RUN_STATE",                                        // 5
    "IDLE_STATE",                                       // 6
    "SHUTDOWN_STATE"};                                  // 7
    /* not currently in use
    "LOCKOUT_STATE",                                    // 8
    "*",                                                // 9 
    "*",                                                // 10 
    "*",                                                // 11 
    "*",                                                // 12 
    "*",                                                // 13 
    "*",                                                // 14 
    "*",                                                // 15 
    "FIRE_TC_OPEN_CIRCUT_FAULT_STATE",                  // 16 
    "FIRE_TC_SHORT_TO_GND_FAULT_STATE",                 // 17 
    "*",                                                // 18 
    "FIRE_TC_SHORT_TO_VCC_FAULT_STATE",                 // 19 
    "*",                                                // 20 
    "*",                                                // 21 
    "*",                                                // 22 
    "POST_CAT_TC_OPEN_CIRCUT_FAULT_STATE",              // 23 
    "*",                                                // 24 
    "*",                                                // 25 
    "*",                                                // 26 
    "*",                                                // 27 
    "*",                                                // 28 
    "*",                                                // 29 
    "*",                                                // 30 
    "POST_CAT_TC_SHORT_TO_GND_FAULT_STATE",             // 31 
    "POST_CAT_TC_SHORT_TO_VCC_FAULT_STATE",             // 32 
    "*",                                                // 33 
    "STACK_TC_OPEN_CIRCUT_FAULT_STATE",                 // 34 
    "*",                                                // 35 
    "*",                                                // 36 
    "*",                                                // 37 
    "STACK_TC_SHORT_TO_GND_FAULT_STATE",                // 38 
    "*",                                                // 39 
    "*",                                                // 40 
    "*",                                                // 41 
    "*",                                                // 42 
    "*",                                                // 43 
    "*",                                                // 44 
    "*",                                                // 45 
    "STACK_TC_SHORT_TO_VCC_FAULT_STATE",                // 46 
    "BAD_FIRE_GTODP_FUNCT_ARG_FAULT_STATE",             // 47 
    "*",                                                // 48 
    "BAD_FIRE_TC_TEMP_FUNCTION_ARG_FAULT_STATE",        // 49 
    "*",                                                // 50 
    "*",                                                // 51 
    "*",                                                // 52 
    "BAD_POST_CAT_GTODP_FUNCT_ARG_FAULT_STATE",         // 53 
    "*",                                                // 54 
    "*",                                                // 55 
    "*",                                                // 56 
    "*",                                                // 57 
    "*",                                                // 58 
    "*",                                                // 59 
    "*",                                                // 60 
    "BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_FAULT_STATE",    // 61 
    "BAD_STACK_GTODP_FUNCT_ARG_FAULT_STATE",            // 62 
    "*",                                                // 63 
    "BAD_STACK_TC_TEMP_FUNCTION_ARG_FAULT_STATE",       // 64 
    "*",                                                // 65 
    "*",                                                // 66 
    "*",                                                // 67 
    "INLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE",        // 68 
    "*",                                                // 69 
    "*",                                                // 70 
    "*",                                                // 71 
    "*",                                                // 72 
    "*",                                                // 73 
    "*",                                                // 74 
    "*",                                                // 75 
    "INLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE",       // 76 
    "OUTLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE",       // 77 
    "*",                                                // 78 
    "OUTLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE",      // 79 
    "*",                                                // 80 
    "*",                                                // 81 
    "*",                                                // 82 
    "BAD_INLET_GTIDP_FUNCT_ARG_FAULT_STATE",            // 83 
    "*",                                                // 84 
    "*",                                                // 85 
    "*",                                                // 86 
    "*",                                                // 87 
    "*",                                                // 88 
    "*",                                                // 89 
    "*",                                                // 90 
    "BAD_OUTLET_GTIDP_FUNCT_ARG_FAULT_STATE",           // 91 
    "*",                                                // 92 
    "*",                                                // 93 
    "*",                                                // 94 
    "MULTIPLE_SENSOR_FAULTS_STATE",                     // 95 
    "Pdk"};                                             // 96 

 */
/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/
/*static void SecondsToHrMinSec (const volatile uint32_t TotalSeconds,
                               uint16_t * const Hours, uint16_t * const Minutes,
                               uint16_t * const Seconds);



static uint16_t ConvertDegCToDegF (const uint16_t DataInDegC);*/

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        static void SecondsToHrMinSec
 *                                      (const volatile uint32_t TotalSeconds,
 *                                       uint16_t * const Hours,
 *                                       uint16_t * const Minutes,
 *                                       uint16_t * const Seconds)
 *
 * Description:     SecondsToHrMinSec() converts seconds to hours, minutes and
 *                  serconds.
 *
 * Dependencies:    None
 *
 * PreConditions:   The TotalSeconds input is limited to 31,536,000 seconds
 *                  which converts to 8760 hours or one year.
 *
 * Inputs:          An argument that specifies the number of seconds to convert
 *                  and three arguments that specify the addresses unsigned
 *                  integers into which to store the hours, minutes and seconds
 *                  results of the conversion.
 *
 * Output:          None
 *
 * Side Effects:    Hours, Minutes and Seconds will contain the results of the
 *                  conversion.
 ******************************************************************************/
void SecondsToHrMinSec (const volatile uint32_t TotalSeconds,
                            uint16_t * const Hours, uint16_t * const Minutes,
                            uint16_t * const Seconds)
{
    *Seconds = (uint16_t)(TotalSeconds%(uint8_t)60);
                                /* The remainder is seconds less than 60
                                 * seconds. */
    *Minutes = (uint16_t)((TotalSeconds/(uint8_t)60)%(uint8_t)60);
                                /*The remainder is minutes less than 60
                                 * minutes. */
    *Hours = (uint16_t)(TotalSeconds/(uint16_t)3600);
                                /* The integer quotient is the whole
                                 * hours. */
    return;
}/* end SecondsToHrMinSec() */


/*******************************************************************************
 * Function:        void BuildMessage (volatile char * const messageBuffer,
 *                                  const volatile uint32_t TotalSeconds,
 *                                  const char OpStateName[],
 *                                  const uint16_t WaterInTemperatureValue,
 *                                  const uint16_t WaterOutTemperatureValue,
 *                                  const uint16_t O2Value,
 *                                  const uint16_t FireTemperatureValue,
 *                                  const uint16_t CatTemperatureValue,
 *                                  const uint16_t StackTemperatureValue,
 *                                  const uint16_t FireCjTemperatureValue,
 *                                  const uint16_t CatCjTemperatureValue,
 *                                  const uint16_t StackCjTemperatureValue,
 *                                  const uint16_t FlowMeterValue,
 *                                  const uint8_t HighLimPotValue,
 *                                  const uint8_t DifferentialPotValue,
 *                                  const uint8_t FanCmdSpeedPcntValue,
 *                                  const uint8_t CombDamperPcntValue,
 *                                  const uint8_t CatDamperPcntValue,
 *                                  const uint32_t SensorStatus)
 *
 * Description:     BuildMessage() constructs the message string that will
 *                  eventually be serially transmitted by the controller board.
 *
 * Dependencies:    cs_pdk_400_flowmeter.h, SecondsToHrMinSec(),
 *                  ConvertDegCToDegF()
 *
 * PreConditions:   None
 *
 * Inputs:          Arguments that specify integral values for the message
 *                  constituents and an argument that specifies the address of
 *                  a character array of sufficient size to hold the resulting
 *                  message string.
 *
 * Output:          None
 *
 * Side Effects:    messageBuffer contains the resulting message string.
 ******************************************************************************/
void BuildMessage (volatile char * const messageBuffer,
                   const volatile uint32_t TotalSeconds,
                   const char OpStateName[],
                   const uint16_t WaterInTemperatureValue,
                   const uint16_t WaterOutTemperatureValue,
                   const uint16_t O2Value,
                   const uint16_t FireTemperatureValue,
                   const uint16_t CatTemperatureValue,
                   const uint16_t StackTemperatureValue,
                   const uint16_t FireCjTemperatureValue,
                   const uint16_t CatCjTemperatureValue,
                   const uint16_t StackCjTemperatureValue,
                   const uint16_t FlowMeterValue,
                   const uint8_t HighLimPotValue,
                   const uint8_t DifferentialPotValue,
                   const uint8_t FanCmdSpeedPcntValue,
                   const uint8_t CombDamperPcntValue,
                   const uint8_t CatDamperPcntValue,
                   const uint32_t SensorStatus,
                   const uint16_t inducerFanFeedback,
                   const float oxygenRunSetpoint,
                   const float waterOutTemperatureRunSetpoint,
                   const uint8_t rebootFlag)
{
    uint16_t hours;
    uint16_t minutes;
    uint16_t seconds;
    
    uint16_t scaledWaterInTempValue;
    uint16_t scaledWaterOutTempValue;
    uint16_t scaledFireTempValue;
    uint16_t scaledFireCjTempValue;
    uint16_t scaledCatTempValue;
    uint16_t scaledCatCjTempValue;
    uint16_t scaledStackTempValue;
    uint16_t scaledStackCjTempValue;

    uint16_t sensorStatusMSByte;
    uint16_t sensorStatusLSByte;
    
    char unitsString[UNITS_STR_LEN];
/*----------------------------------------------------------------------------*/
    if ((strlen (OpStateName)) < (sizeof(unitsString))){
        (void)strcpy (unitsString, OpStateName);
    }
    else {
        (void)strcpy (unitsString, "szER");
    }

    SecondsToHrMinSec (TotalSeconds, &hours, &minutes, &seconds);
/*----------------------------------------------------------------------------*/
    if (DegCDegFJumper == JUMPER_OUT){               /* Jumper is not present. */
        scaledWaterInTempValue = WaterInTemperatureValue;
        scaledWaterOutTempValue = WaterOutTemperatureValue;
        scaledFireTempValue = FireTemperatureValue;
        scaledFireCjTempValue = FireCjTemperatureValue;
        scaledCatTempValue = CatTemperatureValue;
        scaledCatCjTempValue = CatCjTemperatureValue;
        scaledStackTempValue = StackTemperatureValue;
        scaledStackCjTempValue = StackCjTemperatureValue;

        (void)strncat (unitsString, "_C", (sizeof(unitsString) - (strlen(unitsString) - 1)));

    }//end if()
    else {                                           /* Jumper is present. */
        scaledWaterInTempValue = ConvertDegCToDegF (WaterInTemperatureValue);
        scaledWaterOutTempValue = ConvertDegCToDegF (WaterOutTemperatureValue);
        scaledFireTempValue = ConvertDegCToDegF (FireTemperatureValue);
        scaledFireCjTempValue = ConvertDegCToDegF (FireCjTemperatureValue);
        scaledCatTempValue = ConvertDegCToDegF (CatTemperatureValue);
        scaledCatCjTempValue = ConvertDegCToDegF (CatCjTemperatureValue);
        scaledStackTempValue = ConvertDegCToDegF (StackTemperatureValue);
        scaledStackCjTempValue = ConvertDegCToDegF (StackCjTemperatureValue);

        (void)strncat (unitsString, "_F", (sizeof(unitsString) - (strlen(unitsString) - 1)));
    }//end else
/*----------------------------------------------------------------------------*/
    sensorStatusMSByte = (uint16_t)(SensorStatus >> 16);
    sensorStatusLSByte = (uint16_t)SensorStatus;
/*----------------------------------------------------------------------------*/
    sprintf (messageBuffer, "RunTime=%04u:%02u:%02u Status=%s WaterInTemp=%03u WaterOutTemp=%03u O2Level=%04u FireTemp=%04u CatalystTemp=%04u StackTemp=%04u FlowRate=%03u HighLimPot=%03u DiffPot=%03u FanCmd=%03u CombDamper=%03u CatDamper=%03u FireCjTemp=%03u CatCjTemp=%03u StackCjTemp=%03u CN10Rpm=%03u SensorStatus=%04x%04x WaterOutTempSetpoint=%f O2LevelSetpoint=%f Reboot=%d\r\n",
             hours, minutes, seconds, unitsString, scaledWaterInTempValue,
             scaledWaterOutTempValue, O2Value, scaledFireTempValue,
             scaledCatTempValue, scaledStackTempValue, FlowMeterValue,
             HighLimPotValue, DifferentialPotValue, FanCmdSpeedPcntValue,
             CombDamperPcntValue, CatDamperPcntValue, scaledFireCjTempValue,
             scaledCatCjTempValue, scaledStackCjTempValue, inducerFanFeedback, sensorStatusMSByte, 
             sensorStatusLSByte,waterOutTemperatureRunSetpoint,oxygenRunSetpoint,rebootFlag);
    

    return;

}/* end BuildMessage() */


/*******************************************************************************
 * Function:        void LimitSecondsToOneYear (volatile uint32_t * const TotalSeconds)
 *
 * Description:     LimitSecondsToOneYear() limits the total accumulated seconds
 *                  register value to one year's worth of seconds.
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the sddress of an unsigned long
 *                  integer that contains the seconds value that is to be
 *                  limited in magnitude to one year.
 *
 * Output:          None
 *
 * Side Effects:    TotalSeconds contains a value that has been reset to zero
 *                  if its orignal value exceeded one year's worth of seconds.
 ******************************************************************************/
void LimitSecondsToOneYear (volatile uint32_t * const TotalSeconds)
{
    if ((*TotalSeconds) > SecondsLimitValue)
    {
        (*TotalSeconds) = (uint8_t)0;
    }

    return;

}/* end LimitSecondsMagnitude() */


/*******************************************************************************
 * Function:        static uint16_t ConvertDegCToDegF (const uint16_t DataInDegC)
 *
 * Description:     ConvertDegCToDegF() converts DataInDegC to degrees
 *                  Fahrenheit.
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the value of degrees Celsius that
 *                  is to be converted to degrees Fahrenheit.
 *
 * Output:          Integral degrees Fahrenheit.
 *
 * Side Effects:    None
 ******************************************************************************/
uint16_t ConvertDegCToDegF (const uint16_t DataInDegC)
{
    return ((uint16_t) (((double)DataInDegC * 1.8) + 32));

}/* end ConvertDegCToDegF() */

/***** EOF for cs_pdk_400_message.c *******************************************/
