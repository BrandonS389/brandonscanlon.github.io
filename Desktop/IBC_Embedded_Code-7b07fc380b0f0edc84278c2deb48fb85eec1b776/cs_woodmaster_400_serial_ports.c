/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_serial_ports.c
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

#include "cs_woodmaster_400_serial_ports.h"
#include "cs_woodmaster_400_user.h"
#include "cs_woodmaster_400_message.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declarations                   */
/******************************************************************************/

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
static bool RS485TranceiverEnabled = (bool) FALSE;

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/
//static uint8_t SelectRS232DataCommBus (const uint8_t RS232BusSpecifier);

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        static uint8_t SelectRS232DataCommBus (const uint8_t RS232BusSpecifier)
 *
 * Description:     SelectRS232DataCommBus activates the appropriate RS232
 *                  serial bus tranceiver.
 *
 * Dependencies:    cs_pdk_400_user.h, Macros
 *                  m_RS232_DISPLAY_TCVR_SET_ACTIVE(),
 *                  m_RS232_DISPLAY_TCVR_EN_SET_ENABLED(),
 *                  m_RS232_DISPLAY_TCVR_SET_SHUTDOWN(),
 *                  m_RS232_DISPLAY_TCVR_EN_SET_DISABLED(),
 *                  m_RS232_DATA_TCVR_SET_ACTIVE(),
 *                  m_RS232_DATA_TCVR_EN_SET_ENABLED(),
 *                  m_RS232_DATA_TCVR_SET_SHUTDOWN(),
 *                  m_RS232_DATA_TCVR_EN_SET_DISABLED()
 *
 * PreConditions:   The microcontroller I/O pins are properly configured.
 *
 * Inputs:          An argument that specifies which RS232 serial bus will be
 *                  selected and enabled.
 *
 * Output:          Function status (success/failure).
 *
 * Side Effects:    None
 ******************************************************************************/
static uint8_t SelectRS232DataCommBus(const uint8_t RS232BusSpecifier) {
    uint8_t selectFunctionStatus = 0u;

    switch (RS232BusSpecifier) {
        case SELECT_RS232_DATA_TERMINAL_BUS:

            m_RS232_DISPLAY_TCVR_SET_SHUTDOWN()
            m_RS232_DISPLAY_TCVR_EN_SET_DISABLED()
            __delay_ms(1);
            m_RS232_DATA_TCVR_SET_ACTIVE()
            m_RS232_DATA_TCVR_EN_SET_ENABLED()

            break;
            /*----------------------------------------------------------------------------*/
        case SELECT_RS232_LOCAL_DISPLAY_BUS:

            m_RS232_DATA_TCVR_SET_SHUTDOWN()
            m_RS232_DATA_TCVR_EN_SET_DISABLED()
            __delay_ms(1);
            m_RS232_DISPLAY_TCVR_SET_ACTIVE()
            m_RS232_DISPLAY_TCVR_EN_SET_ENABLED()

            break;
            /*----------------------------------------------------------------------------*/
        case DESELECT_RS232_DISPLAY_BUS:

            m_RS232_DATA_TCVR_SET_SHUTDOWN()
            m_RS232_DATA_TCVR_EN_SET_DISABLED()
            m_RS232_DISPLAY_TCVR_SET_SHUTDOWN()
            m_RS232_DISPLAY_TCVR_EN_SET_DISABLED()

            break;
            /*----------------------------------------------------------------------------*/
        default: /* Invalid bus specifier. */

            m_RS232_DATA_TCVR_SET_SHUTDOWN()
            m_RS232_DATA_TCVR_EN_SET_DISABLED()
            m_RS232_DISPLAY_TCVR_SET_SHUTDOWN()
            m_RS232_DISPLAY_TCVR_EN_SET_DISABLED()

            selectFunctionStatus = 1u;

            break;

    }//end switch

    return selectFunctionStatus;

}//end SelectRS232DataCommBus()

/*******************************************************************************
 * Function:        uint8_t TransmitRS232SerialData
 *                                     (const uint16_t DataDestinationDevice,
 *                                      const volatile uint32_t TotalSeconds,
 *                                      const char * const OpStateName,
 *                                      const uint16_t WaterInTemperatureValue,
 *                                      const uint16_t WaterOutTemperatureValue,
 *                                      const uint16_t O2Value,
 *                                      const uint16_t FireTemperatureValue,
 *                                      const uint16_t FireCjTemperatureValue,
 *                                      const uint16_t CatTemperatureValue,
 *                                      const uint16_t CatCjTemperatureValue,
 *                                      const uint16_t StackTemperatureValue,
 *                                      const uint16_t StackCjTemperatureValue,
 *                                      const uint16_t FlowMeterValue,
 *                                      const uint8_t HighLimPotValue,
 *                                      const uint8_t DifferentialPotValue,
 *                                      const uint8_t FanCmdSpeedValue,
 *                                      const uint8_t CombDamperPercent,
 *                                      const uint8_t CatDamperPercent,
 *                                      const uint32_t SensorStatusBits)
 *
 * Description:     TransmitRS232SerialData() verifies that the appropriate
 *                  USART on the microcontroller has been opened and configured
 *                  and, through the use of a helper function, selects and
 *                  enables the appropriate RS232 tranceiver IC and, if
 *                  required, verifies that a data terminal device is active
 *                  on the controller board's RS232 serial port before
 *                  transmitting RS232 serial data. Upon completion of the data
 *                  transmission, this function, through the use of a helper
 *                  function, de-selects and disables the RS232 tranceiver IC.
 *
 * Dependencies:    cs_pdk_400_user.h, cs_pdk_400_message.h, Macros
 *                  m_RS232_DATA_TCVR_CTS_ASSERT(),
 *                  m_RS232_DATA_TCVR_CTS_DEASSERT()
 *
 * PreConditions:   Microcontroller USART2 has been opened and configured.
 *
 * Inputs:          Arguments that specify the data values to transmit and an
 *                  argument that specifies the destination device for the
 *                  transmitted data.
 *
 * Output:          Integers 0 for success, 1 for data terminal device was
 *                  selected but the data terminal device is not asserting a
 *                  handshake (RTS) signal or 3 for microcontroller USART2 has
 *                  not been opened and configured.
 *
 * Side Effects:    None
 ******************************************************************************/
uint8_t TransmitRS232SerialData(const uint16_t DataDestinationDevice,
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
        const uint8_t rebootFlag) {
    uint8_t rs232XmitStatus = NO_SERIAL_PORT_FAULTS;

    if (OpStatusBits.Usart2IsConfigured == (bool) TRUE) {
        if (DataDestinationDevice == (uint16_t) REMOTE_TERMINAL_IS_DATA_DESTINATION) {
            if ((RS232DataTermRts == RS232_RTS_ASSERTED) &&
                    (RS232_DATA_TCVR_CTS == RS232_CTS_DEASSERTED)) {
                m_RS232_DATA_TCVR_CTS_ASSERT()
            } /* If there is a remote terminal connected
                                     * to the controller's serial port then
                                     * assert the CTS handshake signal. */

            if ((RS232DataTermRts == RS232_RTS_DEASSERTED) &&
                    (RS232_DATA_TCVR_CTS == RS232_CTS_ASSERTED)) {
                m_RS232_DATA_TCVR_CTS_DEASSERT();
            } /* If the remote terminal has been
                                     * disconnected from the controller's
                                     * serial port then de-assert the CTS
                                     * handshake signal. */

            if ((RS232DataTermRts == RS232_RTS_ASSERTED) &&
                    (RS232_DATA_TCVR_CTS == RS232_CTS_ASSERTED)) {
                //(void)SelectRS232DataCommBus ((uint8_t)SELECT_RS232_DATA_TERMINAL_BUS);
                //__delay_ms(1);


                BuildMessage(assembledMessage, TotalSeconds,
                        OperationalStateName,
                        WaterInTemperatureValue,
                        WaterOutTemperatureValue, O2Value,
                        FireTemperatureValue,
                        CatTemperatureValue,
                        StackTemperatureValue,
                        FireCjTemperatureValue,
                        CatCjTemperatureValue,
                        StackCjTemperatureValue,
                        FlowMeterValue,
                        HighLimPotValue,
                        DifferentialPotValue,
                        FanCmdSpeedValue,
                        CombDamperPercent,
                        CatDamperPercent,
                        SensorStatusBits,
                        inducerFanFeedback,
                        oxygenRunSetpoint,
                        waterOutTemperatureRunSetpoint,
                        rebootFlag);



                puts2USART(assembledMessage);
            }/* Transmit appropriate data in an
                                     * appropriate fashion to the remote
                                     * data terminal. */

            else {
                rs232XmitStatus = NO_TERMINAL_PRESENT_ON_RS232_PORT;
            } /* Cannot transmit to the selected
                                     * destination device because it is not
                                     * connected to the serial port
                                     * (i.e., no handshake signals). */
        }
            /*else if (DataDestinationDevice == (uint16_t)LOCAL_DISPLAY_IS_DATA_DESTINATION)
            {
                //(void)SelectRS232DataCommBus ((uint8_t)SELECT_RS232_LOCAL_DISPLAY_BUS);
                //__delay_ms(1);
            }                           /* Transmit appropriate data in an
             * appropriate fashion to the local
             * display. */

        else {
            rs232XmitStatus = INVALID_RS232_DEST_DEVICE_SPECIFIED;
        } /* Cannot transmit because no valid
                                     * destination device has been
                                     * selected. */
    } else {
        rs232XmitStatus = USART_FOR_RS232_IS_NOT_CONFIGURED;
    } /* Cannot transmit because the required
                                     * USART is not configured for
                                     * operation. */

    //(void)SelectRS232DataCommBus ((uint8_t)DESELECT_RS232_DISPLAY_BUS);

    return rs232XmitStatus;
}

/*******************************************************************************
 * Function:        uint8_t TransmitRS485DriveDataPacket (const uint8_t DataPacket[],
 *                                                        const uint8_t DataPacketByteLen)
 *
 * Description:     TransmitRS485DriveDataPacket() verifies that the appropriate
 *                  USART on the microcontroller has been opened and configured.
 *                  The first time that this function runs, it enables the RS485
 *                  tranciever IC.
 *
 * Dependencies:    cs_pdk_400_user.h, Macros m_RS485_DE_ASSERT()
 *                  m_RS485_RE_ASSERT()
 *
 * PreConditions:   Microcontroller USART1 has been opened and configured.
 *
 * Inputs:          An argument that specifies the address of an array of data
 *                  bytes to be transmitted and and argument that specifies the
 *                  number of bytes in the array of data.
 *
 * Output:          Integers 0 for success, or 3 for microcontroller USART1 has
 *                  not been opened and configured.
 *
 * Side Effects:    None
 ******************************************************************************/
uint8_t TransmitRS485DriveDataPacket(const uint8_t DataPacket[],
        const uint8_t DataPacketByteLen) {
    uint8_t rs485XmitStatus = NO_SERIAL_PORT_FAULTS;

    uint8_t index, dataByte;

    if (OpStatusBits.Usart1IsConfigured == (bool) TRUE) {
        if (RS485TranceiverEnabled == (bool) FALSE) {
            m_RS485_DE_ASSERT()
            m_RS485_RE_ASSERT() /* Enable the RS485 bus driver and
                                     * enable the receiver output (i.e. for
                                     * the serial data signal back to the
                                     * microcontroller). */

            __delay_ms(250); /* 250ms delay to clear any spurious
                                     * serial data from the devices on the
                                     * RS485 serial bus. (i.e. this delay
                                     * causes a data reception timeout.) */

            RS485TranceiverEnabled = (bool) TRUE;
        }

        di(); /* Disable the interrupts so that they
                                     * cannot cause a MODBUS inter-byte serial
                                     * transmission timing violation. */

        for (index = 0; index < DataPacketByteLen; index++) {
            dataByte = DataPacket[index]; /* Prefetch. */

            while (Busy1USART()); /* Wait for the completion of the
                                    * transmission of the current data
                                     * byte. */

            Write1USART(dataByte);

        }//end for()

        while (Busy1USART());
            /* Wait for the completion of the
                                    * transmission of the final byte in the
                                     * data packet. */

        ei();
    }
    else {
        rs485XmitStatus = USART_FOR_RS485_IS_NOT_CONFIGURED;
    } /* Cannot transmit because the required
                                     * USART is not configured for
                                     * operation. */

    return rs485XmitStatus;
}

/***** EOF for cs_pdk_400_serial_ports.c **************************************/
