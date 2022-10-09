/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_user.h
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
#ifndef	CS_PDK_400_THERMOCOUPLE_H_
#define	CS_PDK_400_THERMOCOUPLE_H_

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declaration                 */
/******************************************************************************/

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
int16_t GetTcTemperature_C (const int8_t TcSensorId, const int8_t DataId,
                            volatile float * const TcTemperature);

/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/
#define POST_CAT_THERMOCOUPLE_ID    0       /* Thermocouple sensor IDs. */
#define STACK_THERMOCOUPLE_ID       1
#define FIRE_THERMOCOUPLE_ID        2

#define THERMOCOUPLE_DATA   1
#define COLD_JUNCTION_DATA  2               /* For dataId arguments for the
                                             * ExtractTcData() function. */

#define NO_TC_FAULT_IND 0x0000              /* Indicates that no TC or TC
                                             * related fault was detected. */

#define TC_OPEN_CIRCUIT_FAULT_IND 0x0001    /* Error bit value indicates that
                                             * the thermocouple IC has detected
                                             * a sensor fault of type open
                                             * sensor circuit. */

#define TC_SHORT_TO_GND_FAULT_IND 0x0002    /* Error bit value indicates that
                                             * the thermocouple IC has detected
                                             * a sensor fault of type sensor
                                             * circuit short to ground. */

#define TC_SHORT_TO_VCC_FAULT_IND 0x0004    /* Error bit value indicates that
                                             * the thermocouple IC has detected
                                             * a sensor fault of type sensor
                                             * circuit short to Vcc. */

#define GTODP_FUNCT_ARG_RELATED_FAULT_IND   0x0208
                                             /* When the GetTcDataPacket()
                                              * function returns this value, it
                                              * indicates that a bad argument
                                              * was passed to the function. */

#define BAD_EXTRACT_TC_TEMP_FUNCTION_ARG_FAULT_IND  0xE000
                                            /* When the ExtractTcTemperatureData
                                             * function returns this value, it
                                             * indicates that a bad argument
                                             * was passed to this function. */

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/
#if (0)
#define NUMBER_OF_TC_SENSORS        3       /* The total number of thermocouple
                                             * sensors that have assigned
                                             * IDs. */
#endif

#define TC_DATA_PACKET_BYTE_COUNT   4       /* The thermocouple data packet is
                                             * four bytes (32-bits) wide. */
#if (0)
#define TC_DATA_FAULT_BIT_MASK 0x030F
#endif

#define TC_TEMPERATURE_SIGN_BIT_LOC 0x8000  /* TC sensor temperature data sign
                                             * bit location in the specified
                                             * thermocouple temperature data
                                             * packet. */

#define CJ_TEMPERTURE_SIGN_BIT_LOC  0x8000  /* Cold junction temperature data
                                             * sign bit location in the
                                             * specified cold junction data
                                             * packet. */

#define CJ_DATA_RIGHT_SHIFT 8               /* Number of bits to rotate the
                                             * coldJunctionData data packet
                                             * to the right in order to extract
                                             * cold junction temperature
                                             * data. */

#define TC_DATA_SHIFT 4                     /* Number of bits to shift the
                                             * thermocoupleData data packet to
                                             * the right and to the left in
                                             * order to extract thermocouple
                                             * temperature data. */

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
typedef union
{
    uint32_t tcDataPacket;

    uint8_t tcDataPacketByteArray[TC_DATA_PACKET_BYTE_COUNT];

    struct
    {
        uint16_t tcTemperatureDataPacket;

        uint16_t tcColdJunctionDataPacket;
    };

} ThermocoupleDataUnion_t;

#endif	/* CS_PDK_400_THERMOCOUPLE_H_ */

/***** EOF for cs_pdk_400_thermocouple.h **************************************/
