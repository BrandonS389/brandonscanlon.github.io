/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_thermistor.h
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
#ifndef	CS_PDK_400_THERMISTOR_H_
#define	CS_PDK_400_THERMISTOR_H_

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declaration                 */
/******************************************************************************/

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
int16_t GetThermistorTemperature_C (const int8_t ThermistorSensorId,
                               volatile uint16_t * const ThermistorTemperature);

/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/
#if 0
#define WT_CELSIUS_MULTIPLIER 0.125         /* LSBit weight for the thermistor
                                             * IC output value is .125
                                             * degrees C. */
#endif

#define INLET_WT_THERMISTOR_ID     1        /* Sensor IDs. */
#define OUTLET_WT_THERMISTOR_ID    2

#define NO_THERMISTOR_FAULT_IND 0x0000      /* Indicates that no TC or TC
                                             * related fault was detected. */

#define THERMISTOR_SHORT_CIRCUIT_FAULT_IND 0x0005
                                            /* Error bit value indicates that
                                             * the thermistor data value
                                             * indicates the potential for a
                                             * sensor fault of type shorted
                                             * sensor circuit. */

#define THERMISTOR_OPEN_CIRCUIT_FAULT_IND 0x0006
                                            /* Error bit value indicates that
                                             * the thermistor data value
                                             * indicates the potential for a
                                             * a sensor fault of type open
                                             * sensor circuit. */

#define GTIDP_FUNCT_ARG_RELATED_FAULT_IND   0x0007
                                        /* When the GetThermistorDataPacket()
                                         * function returns this value, it
                                         * indicates that a bad argument
                                         * was passed to the function. */
/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/
#if (0)
#define NUMBER_OF_THERMISTOR_SENSORS    2   /* The total number of thermistor
                                             * sensors that have assigned
                                             * IDs. */
#endif

#define THERMISTOR_BYTE_RIGHT_SHIFT 5
#define THERMISTOR_BYTE_LEFT_SHIFT  3       /* The thermisor to digital IC
                                             * outputs 11 bits of data, in big
                                             * endian format, which will be
                                             * read as two 8 bit values into
                                             * two bytes of a data structure and
                                             * then right shifted (right
                                             * justified)*/

#define THERMISTOR_DATA_PACKET_BYTE_COUNT   2
                                            /* The thermistor data packet is
                                             * two bytes (16-bits) wide. */

#define THERMISTOR_DATA_BITS_MASK 0x03FF    /* AND mask to that is used isolate
                                             * and determine the temperature
                                             * data value (bits 0 - 9) of the
                                             * output of the thermistor to
                                             * digital IC. */

#define THERMISTOR_SIGN_BIT_MASK 0x0400     /* AND mask to that is used to
                                             * isolate and determine the value
                                             * of the sign bit (bit 10) of the
                                             * output value of the thermistor
                                             * to digital IC. */

#define THERMISTOR_SHORT_CIRCUIT_FAULT_TEST_VALUE 0x0258
                                            /* If the thermistor to digital
                                             * IC outputs a positive value that
                                             * is greater than or equal to this
                                             * value, ~ +112.2 degrees C,
                                             * (non-linearized) then a sensor
                                             * short circuit will be assumed. */

#define THERMISTOR_OPEN_CIRCUIT_FAULT_TEST_VALUE 0x038A
                                            /* If, in the presence of the sign
                                             * bit, the thermistor to digital
                                             * IC outputs a value that is less
                                             * than or equal to this value,
                                             * then a sensor open circuit will
                                             * be assumed. */

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
typedef union
{
    uint16_t thermistorDataPacket;

    uint8_t thermistorDataPacketByteArray[THERMISTOR_DATA_PACKET_BYTE_COUNT];

} ThermistorDataUnion_t;

#endif	/* CS_PDK_400_THERMISTOR_H_ */

/***** EOF for cs_pdk_400_thermistor.h ****************************************/
