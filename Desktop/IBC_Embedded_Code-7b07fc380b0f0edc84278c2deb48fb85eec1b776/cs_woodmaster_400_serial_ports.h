/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_serial_ports.h
 *  Date: 9 February 2015
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
#ifndef	CS_PDK_400_SERIAL_PORTS_H_
#define	CS_PDK_400_SERIAL_PORTS_H_

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declaration                 */
/******************************************************************************/

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
uint8_t TransmitRS232SerialData (const uint16_t DataDestinationDevice,
                                 const volatile uint32_t TotalSeconds,
                                 const char * const OperationalStateName,
                                 const uint16_t WaterInTemperatureValue,
                                 const uint16_t WaterOutTemperatureValue,
                                 const uint16_t O2Value,
                                 const uint16_t FireTemperatureValue,
                                 const uint16_t FireCjTemperatureValue,
                                 const uint16_t CatTemperatureValue,
                                 const uint16_t CatCjTemperatureValue,
                                 const uint16_t StackTemperatureValue,
                                 const uint16_t StackCjTemperatureValue,
                                 const uint16_t FlowMeterValue,
                                 const uint8_t HighLimPotValue,
                                 const uint8_t DifferentialPotValue,
                                 const uint8_t FanCmdSpeedValue,
                                 const uint8_t CombDamperPercent,
                                 const uint8_t CatDamperPercent,
                                 const uint32_t SensorStatusBits,
                                 const uint16_t inducerFanFeedback,
                                 const float oxygenRunSetpoint,
                                 const float waterOutTemperatureRunSetpoint,
                                 const uint8_t rebootFlag);

uint8_t TransmitRS485DriveDataPacket (const uint8_t DataPacket[],
                                      const uint8_t DataPacketByteLen);

 uint8_t SelectRS232DataCommBus (const uint8_t RS232BusSpecifier);
/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/
#define REMOTE_TERMINAL_IS_DATA_DESTINATION 1u
#define LOCAL_DISPLAY_IS_DATA_DESTINATION 2u

#define SELECT_RS232_DATA_TERMINAL_BUS 1u
#define SELECT_RS232_LOCAL_DISPLAY_BUS 2u
#define DESELECT_RS232_DISPLAY_BUS 3u

#define NO_SERIAL_PORT_FAULTS 0u

#define NO_TERMINAL_PRESENT_ON_RS232_PORT 1u
#define INVALID_RS232_DEST_DEVICE_SPECIFIED 2u
#define USART_FOR_RS232_IS_NOT_CONFIGURED 3u

#define USART_FOR_RS485_IS_NOT_CONFIGURED 4u

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

#endif	/* CS_PDK_400_SERIAL_PORTS_H_ */

/***** EOF for cs_pdk_400_serial_ports.h **************************************/
