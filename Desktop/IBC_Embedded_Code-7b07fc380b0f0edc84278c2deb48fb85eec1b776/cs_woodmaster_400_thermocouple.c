/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_thermocouple.c
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

#include <stdint.h>         /* For uint8_t definition */

#endif

#include "cs_woodmaster_400_thermocouple.h"
#include "cs_woodmaster_400_user.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declaration                    */
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
static volatile ThermocoupleDataUnion_t TcDataPacketUnion;

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/
static int16_t GetTcDataPacket(const int8_t TcSensorId,
                    volatile ThermocoupleDataUnion_t * const TcDataConstruct,
                    const int16_t TcDataPacketByteCount);

static int16_t TestForTcFault(const ThermocoupleDataUnion_t TcDataConstruct);

static int16_t ExtractTcTemperatureData(const ThermocoupleDataUnion_t TcDataConstruct,
                                 const int8_t DataId,
                                 volatile float * const TcTemperature);

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        int16_t GetTcTemperature_C (const int8_t TcSensorId,
 *                                              const int8_t DataId,
 *                                      volatile uint16_t * const TcTemperature)
 *
 * Description:     GetTcTemperature() uses several helper functions in order
 *                  to read the temperature, in Celsius, of a specified
 *                  thermocouple temperature sensor. Negative temperatures will
 *                  be read as zero degrees Celsius.
 *
 * Dependencies:    cs_pdk_400_thermocouple.h, GetTcDataPacket(),
 *                  TestForTcFault(), ExtractTcTemperatureData()
 *
 * PreConditions:   SPI serial port is configured and open.
 *
 * Inputs:          An argument that specifies from which sensor to read the
 *                  temperature and an argument that specifies whether to
 *                  obtain the thermocouple sensor or the associated cold
 *                  junction temperature and the address of an unsigned
 *                  integer in which to store the data.
 *
 * Output:          Thermocouple sensor and/or thermocouple function error
 *                  status.
 *
 * Side Effects:    If no errors; TcTemperature will contain the zero or greater
 *                  temperature, in Celsius, of a specified thermocouple
 *                  temperature sensor.
 ******************************************************************************/
int16_t GetTcTemperature_C (const int8_t TcSensorId, const int8_t DataId,
                            volatile float * const TcTemperature)
{
    int16_t tcSensorFaultStatus;

    tcSensorFaultStatus = GetTcDataPacket(TcSensorId, &TcDataPacketUnion,
                                          TC_DATA_PACKET_BYTE_COUNT);

    if (tcSensorFaultStatus == NO_TC_FAULT_IND)
    {
        tcSensorFaultStatus = TestForTcFault(TcDataPacketUnion);
    }

    if (tcSensorFaultStatus == NO_TC_FAULT_IND)
    {
        tcSensorFaultStatus = ExtractTcTemperatureData(TcDataPacketUnion,
                                                       DataId, TcTemperature);
    }

    return tcSensorFaultStatus;
}/* end GetTcTemperature_C() */

/*******************************************************************************
 * Function:        static int16_t GetTcDataPacket(const int8_t TcSensorId,
 *                              ThermocoupleDataUnion_t * const TcDataConstruct,
 *                              const int16_t TcDataPacketByteCount)
 *
 * Description:     GetTcDataPacket() uses the SPI bus to read data from a
 *                  Thermocouple to Digital IC that is associated with
 *                  the sensor ID that is passed as the TcSensorId argument.
 *
 * Dependencies:    cs_pdk_400_thermocouple.h, cs_pdk_400_user.h, Macros
 *                  m_CAT_TEMP_SLAVE_SEL_TRUE(), m_STACK_TEMP_SLAVE_SEL_TRUE(),
 *                  m_FIRE_TEMP_SLAVE_SEL_TRUE(), m_CAT_TEMP_SLAVE_SEL_FALSE(),
 *                  m_STACK_TEMP_SLAVE_SEL_FALSE(),
 *                  m_FIRE_TEMP_SLAVE_SEL_FALSE()
 *
 * PreConditions:   SPI serial port is configured and open.
 *
 * Inputs:          An argument that is used to determine from which sensor
 *                  to obtain the data packet and an argument that specifies
 *                  the address of a data union of ThermocoupleDataUnion_t type
 *                  in which to store the data and an argument that specifies
 *                  the number of bytes that are contained in the obtained data
 *                  packet.
 *
 * Output:          The fault status of the operation.
 *
 * Side Effects:    The type ThermocoupleDataUnion_t data union is populated
 *                  with thermocouple data.
 ******************************************************************************/
static int16_t GetTcDataPacket(const int8_t TcSensorId,
                        volatile ThermocoupleDataUnion_t * const TcDataConstruct,
                        const int16_t TcDataPacketByteCount)
{
    int16_t byteCount;
    int16_t functionFaultStatus = NO_TC_FAULT_IND;

    switch (TcSensorId)
    {
        case POST_CAT_THERMOCOUPLE_ID :
            m_CAT_TEMP_SLAVE_SEL_TRUE()
            break;
            
        case STACK_THERMOCOUPLE_ID :
            m_STACK_TEMP_SLAVE_SEL_TRUE()
            break;
            
        case FIRE_THERMOCOUPLE_ID :
            m_FIRE_TEMP_SLAVE_SEL_TRUE()
            break;
            
        default :
            functionFaultStatus = GTODP_FUNCT_ARG_RELATED_FAULT_IND;
            break;
    }

    __delay_us(40);                 /* 40us slave select settling time. */

    if (functionFaultStatus == NO_TC_FAULT_IND)
    {
        for (byteCount = (TcDataPacketByteCount - 1); byteCount >= 0; --byteCount)
        {
            TcDataConstruct->tcDataPacketByteArray[byteCount] = ReadSPI();
        }               /* Data is read in big-endian byte and bit order. */
    }
    
    switch (TcSensorId)
    {
        case POST_CAT_THERMOCOUPLE_ID :
            m_CAT_TEMP_SLAVE_SEL_FALSE()
            break;
            
        case STACK_THERMOCOUPLE_ID :
            m_STACK_TEMP_SLAVE_SEL_FALSE()
            break;
            
        case FIRE_THERMOCOUPLE_ID :
            m_FIRE_TEMP_SLAVE_SEL_FALSE()
            break;
            
        default :
            functionFaultStatus = GTODP_FUNCT_ARG_RELATED_FAULT_IND;
            break;
    }

     __delay_ms(50);                /* 100ms conversion time required by the
                                     * thermocouple-to-digital IC. */
    
    return functionFaultStatus;

}/* end GetTcDataPacket() */

/*******************************************************************************
 * Function:        static int16_t TestForTcFault(const ThermocoupleDataUnion_t TcDataConstruct)
 *
 * Description:     TestForTcFault() examines certain bits in the passed in
 *                  the type ThermocoupleDataUnion_t construct in order to
 *                  determine and report any detected sensor faults.
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          Data as read from one of the Thermocouple to Digital ICs and
 *                  passed as a type ThermocoupleDataUnion_t construct.
 *
 * Output:          Numerical data that indicates what type of fault, if any,
 *                  was reported by the Thermocouple to Digital IC and stored
 *                  in the ThermocoupleDataUnion_t construct.
 *
 * Side Effects:    None
 ******************************************************************************/
static int16_t TestForTcFault(const ThermocoupleDataUnion_t TcDataConstruct)
{
    int16_t tcFaultType;

    if (TcDataConstruct.tcDataPacket & (uint16_t)TC_OPEN_CIRCUIT_FAULT_IND)
    {
        tcFaultType = TC_OPEN_CIRCUIT_FAULT_IND;
    }
    else if (TcDataConstruct.tcDataPacket & (uint16_t)TC_SHORT_TO_GND_FAULT_IND)
    {
        tcFaultType = TC_SHORT_TO_GND_FAULT_IND;
    }
    else if (TcDataConstruct.tcDataPacket & (uint16_t)TC_SHORT_TO_VCC_FAULT_IND)
    {
        tcFaultType = TC_SHORT_TO_VCC_FAULT_IND;
    }
    else
    {
        tcFaultType = NO_TC_FAULT_IND;
    }

    return tcFaultType;
    
}/* end TestForTcFault() */

/*******************************************************************************
 * Function:    static int16_t ExtractTcTemperatureData
 *                              (const ThermocoupleDataUnion_t TcDataConstruct,
 *                               const int8_t DataId,
 *                               volatile uint16_t * const TcTemperature);
 *
 * Description:     ExtractTcTemperatureData() extracts sensor or cold junction
 *                  temperature data from a Thermocouple to Digital IC data
 *                  packet. The fractional part of the temperature data is
 *                  discarded.
 *
 * Dependencies:    cs_pdk_400_thermocouple.h
 *
 * PreConditions:   None
 *
 * Inputs:          Data as read from one of the Thermocouple to Digital ICs and
 *                  a DataId specifier that specifies which of either the sensor
 *                  temperature or the cold junction temperature is to be
 *                  extracted and the address of an unsigned integer in which
 *                  to store the data.
 *
 * Output:          The fault status of the operation.
 *
 * Side Effects:    TcTemperature is populated with the requested temperature.
 ******************************************************************************/
static int16_t ExtractTcTemperatureData(const ThermocoupleDataUnion_t TcDataConstruct,
                                        const int8_t DataId,
                                        volatile float * const TcTemperature)
{
    int16_t tcFaultType = NO_TC_FAULT_IND;

//    uint16_t tempTcTemperature;

    switch (DataId)
    {
        case THERMOCOUPLE_DATA :

            if (TcDataConstruct.tcTemperatureDataPacket & (uint16_t)TC_TEMPERATURE_SIGN_BIT_LOC)
            {
                *TcTemperature = 0u;
            }               /* No negative thermocouple temperature values
                             * (i.e. < 0 degrees C) are resolved by this
                             * function. */
            else
            {

                uint16_t tempTemperature = ((TcDataPacketUnion.tcDataPacketByteArray[3] << 6) |
                                  (TcDataPacketUnion.tcDataPacketByteArray[2] >> 2));
                float integerValue = (float)(tempTemperature >> 2);
                float fractionValue = ((float)(tempTemperature & 3)) / 4;
                *TcTemperature = integerValue + fractionValue;
#if(0)         
                *TcTemperature = ((((uint16_t)(TcDataPacketUnion.tcDataPacketByteArray[3])) << TC_DATA_SHIFT) |
                                  (((uint16_t)(TcDataPacketUnion.tcDataPacketByteArray[2]) >> TC_DATA_SHIFT) & 0x000F));
#endif
            }              

            break;
//------------------------------------------------------------------------------
        case COLD_JUNCTION_DATA :

            if (TcDataConstruct.tcColdJunctionDataPacket & (uint16_t)CJ_TEMPERTURE_SIGN_BIT_LOC)
            {
                *TcTemperature = 0u;
            }               /* No negative cold junction temperature values
                             * (i.e. < 0 degrees C) are resolved by this
                             * function. */
            else
            {
                *TcTemperature = TcDataPacketUnion.tcDataPacketByteArray[1];
            }               /* The sign bit (MSBit) is zero. */

            break;
//------------------------------------------------------------------------------
        default :

            tcFaultType = (int16_t)BAD_EXTRACT_TC_TEMP_FUNCTION_ARG_FAULT_IND;
                                        /* Indicates invalid DataId value. */
            break;
    }//end switch

    return tcFaultType;

}/* end ExtractTcTemperatureData() */

/***** EOF for cs_pdk_400_themocouple.c ***************************************/
