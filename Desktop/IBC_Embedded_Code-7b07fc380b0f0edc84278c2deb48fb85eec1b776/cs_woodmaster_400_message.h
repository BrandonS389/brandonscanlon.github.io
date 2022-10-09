/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_message.h
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
#ifndef	CS_PDK_400_MESSAGE_H_
#define	CS_PDK_400_MESSAGE_H_

#include "cs_woodmaster_400_user.h"
/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/
#define LED_DISPLAY_UID 255                     /* Default UID for Silicon
                                                 * Craft SC4Dlite 4-digit
                                                 * LED display. */

#define	LED_DISPLAY_SEGMENT_CMD 'a'             /* For individual segment
                                                 * control. */

#define	LED_DISPLAY_ASCII_CMD   'b'             /* For displaying ASCII
                                                 * coded characters. */

#define	LED_DISPLAY_DP_CMD  'c'                 /* For displaying decimal
                                                 * points. */

#define	LED_DISPLAY_INTEGER_CMD 'f'             /* For displaying 16-bit
                                                 * integer values. */

#define	LED_DISPLAY_BCD_CMD 'd'                 /* For displaying BCD coded
                                                 * values. */

#define	BLANK_ASHACTER 'z'                     /* For blanking the display
                                                 * digit positions. */

#define	ENERGIZE_DP1    0x01                    /* Decimal point command. */

#define	DEENERGIZE_ALL_DP   0x00                /* Decimal point command. */

#define WATER_TEMP_DP_DISPLAY   0x08
#define	STACK_TEMP_DP_DISPLAY   0x0C
#define	CAT_TEMP_DP_DISPLAY     0x0E            /* Decimal point indicator
                                                 * patterns that are used to
                                                 * indidicate which
                                                 * temperature is being
                                                 * displayed on the remote
                                                 * user interface. */

#define CATALYST_TEMPERATURE    0x01
#define WATER_OUTLET_TEMPERATURE    0x02
#define STACK_TEMPERATURE   0x03
                                                /* These three constants are
                                                 * used to keep track of what
                                                 * value is currently displayed
                                                 * on the remote user
                                                 * interface. */

#define DISPLAY_INTERVAL_TIME_S   0x05          /* The amount of time, in
                                                 * seconds that each
                                                 * sequentially displayed OWF
                                                 * parameter will be
                                                 * displayed. */

#define DATA_XMIT_INTERVAL_TIME_S   0x05        /* The amount of time, in
                                                 * seconds, between serial port
                                                 * data transmissions. */

#define DISPLAY_FLASH_INTERVAL_TIME_S   0x01    /* Flashing frequency used by
                                                 * the remote user interface
                                                 * when displaying temperature
                                                 * values that are out of range.
                                                 * (seconds on-time, seconds
                                                 * off-time) */

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/
#define	SERIAL_MSSG_LENGTH 400                  /* 304 needed for the current
                                                 * longest message. */

#define UNITS_STR_LEN 55                        /* 48 need for the longest
                                                 * operational state string. */

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declaration                 */
/******************************************************************************/
extern volatile uint8_t serialDataXmitIntervalTimer;
extern volatile char assembledMessage[];
extern const char * const opStateNameTextArray[];

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
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
                   const uint8_t rebootFlag);

void LimitSecondsToOneYear (volatile uint32_t * const TotalSeconds);
uint16_t ConvertDegCToDegF (const uint16_t DataInDegC);
void SecondsToHrMinSec (const volatile uint32_t TotalSeconds,
                            uint16_t * const Hours, uint16_t * const Minutes,
                            uint16_t * const Seconds);
/******************************************************************************/
/* Global variables                                                            */
/******************************************************************************/
    
    
    
    uint16_t scaledWaterInTempValue;
    uint16_t scaledWaterOutTempValue;
    float scaledFireTempValue;
    uint16_t scaledFireCjTempValue;
    float scaledCatTempValue;
//    uint16_t scaledCatCjTempValue;
    float scaledStackTempValue;
 //   uint16_t scaledStackCjTempValue;

    uint16_t sensorStatusMSByte;
    uint16_t sensorStatusLSByte;
    
    char unitsString[UNITS_STR_LEN];
    
#define MAX_OUTPUT_VALUE_LENGTH 25
    
   
    /*char* scaledWaterInTempValueString, scaledWaterOutTempValueString, oxygenSensorDataString, 
            scaledFireTempValueString, scaledFireCjTempValueString, scaledCatTempValueString,
            scaledCatCjTempValueString, scaledStackTempValueString, scaledStackCjTempValueString,
            flowMeterGpmString, highLimitPotSetPercentString, differentialPotSetPercentString, 
            inducerPercentFanSpeedString, primaryDamperPositionString, secondaryDamperPositionString, 
            secondaryDamperPositionString, inducerFanSpeedFeedbackString, 
            OXYGEN_RUN_STATE_SETPOINTString, WATER_OUT_TEMPERATURE_RUN_STATE_SETPOINTString, 
            REBOOTString;*/


/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

#endif	/* CS_PDK_400_MESSAGE_H_ */

/***** EOF for cs_pdk_400_message.h *******************************************/
