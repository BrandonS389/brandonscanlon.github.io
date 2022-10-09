//#define NEWTHERM
#if defined (NEWTHERM)
/*******************************************************************************
 * New code for the high-temp thermistors to measure oil temps
 *  
 * Part Number: BC_PDK_400_DG_FWR
 *  File Name: bc_pdk_400_dg_thermistor.c
 *  Date: 29 May 2018
 *
 *  Author: Peter J. D'Aloisio
 *  Company: Amaranthine, LLC
 *  (c) 2018 Amaranthine, LLC
 *
 *  Licensee: Biomass Controls, LLC
 *
 *  The material contained herein is confidential and proprietary.
 *******************************************************************************
 *  Revision History:   See the bc_pdk_400_dg_main.c source file.
 *******************************************************************************
 *  Microcontroller: PIC18F86K22    Internal Oscillator == 3.6864 MHz.
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

    #include <stdint.h>    /* For uint8_t definition */

#endif

#include "cs_woodmaster_400_user.h"
#include "cs_woodmaster_400_thermistor.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declarations                   */
/******************************************************************************/

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
static volatile uint8_t highByte;
static volatile uint8_t lowByte;

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
static volatile ThermistorDataUnion_t ThermistorDataPacketUnion;

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/
static int16_t GetThermistorDataPacket(const int8_t ThermistorSensorId,
                    volatile ThermistorDataUnion_t * const ThermistorDataConstruct,
                    const int16_t ThermistorDataPacketByteCount);

static int16_t TestForThermistorFault(const ThermistorDataUnion_t ThermistorDataConstruct);

static uint16_t ExtractThermistorTemperatureData(const ThermistorDataUnion_t ThermistorDataConstruct);

static uint16_t ConvertThermistorDataToDegreesC (const uint16_t ThermistorData);

static uint16_t ConvertDGThermistorDataToDegreesC (const ThermistorDataUnion_t ThermistorDataConstruct);

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        int16_t GetThermistorTemperature_C
 *                                     (const int8_t ThermistorSensorId,
 *                              volatile uint16_t * const ThermistorTemperature)
 *
 * Description:     GetThermistorTemperature_C() uses several helper functions
 *                  in order to read the temperature, in Celsius, of a specified
 *                  thermistor temperature sensor. Negative temperatures will
 *                  be read as zero degrees Celsius.
 *
 * Dependencies:    cs_pdk_400_thermistor.h
 *
 * PreConditions:   SPI serial port is configured and open.
 *
 * Inputs:          An argument that specifies from which sensor to read the
 *                  temperature.
 *
 * Output:          Thermistor sensor and/or thermistor function error status.
 *
 * Side Effects:    If no errors; ThermistorTemperature will contain the zero
 *                  or greater temperature, in Celsius, of a specified
 *                  thermistor temperature sensor.
 ******************************************************************************/
int16_t GetThermistorTemperature_C (const int8_t ThermistorSensorId,
                                volatile uint16_t * const ThermistorTemperature)
{
    int16_t functionFaultStatus;
/*    uint16_t extractedData; Removed (commented) for DG 103395 thermistor. */

    functionFaultStatus = GetThermistorDataPacket(ThermistorSensorId,
                                                  &ThermistorDataPacketUnion,
                                            THERMISTOR_DATA_PACKET_BYTE_COUNT);
/*
    if (functionFaultStatus == NO_THERMISTOR_FAULT_IND)
    {
        functionFaultStatus = TestForThermistorFault(ThermistorDataPacketUnion);
    }
 * 
 *      Removed (commented) for DG 103395 thermistor.
 * 
*/
    if (functionFaultStatus == NO_THERMISTOR_FAULT_IND)
    {
/*
        extractedData = ExtractThermistorTemperatureData(ThermistorDataPacketUnion);
 * 
        *ThermistorTemperature = ConvertThermistorDataToDegreesC (extractedData);
 * 
 *      Removed (commented) for DG 103395 thermistor.
*/
        *ThermistorTemperature = ConvertDGThermistorDataToDegreesC(ThermistorDataPacketUnion);
    }

    return functionFaultStatus;
}/* end GetThermistorTemperature_C() */

/*******************************************************************************
 * Function:        static int16_t GetThermistorDataPacket
 *                                          (const int8_t ThermistorSensorId,
 *              volatile ThermistorDataUnion_t * const ThermistorDataConstruct,
 *                                  const int16_t ThermistorDataPacketByteCount)
 *
 * Description:     GetThermistorDataPacket() uses the SPI bus to read data from
 *                  a Thermistor to Digital IC that is associated with the
 *                  sensor ID that is passed as the ThermistorSensorId argument.
 *
 * Dependencies:    cs_pdk_400_thermistor.h, cs_pdk_400_user.h,
 *                  Macros m_WATER_IN_TEMP_SLAVE_SEL_TRUE(),
 *                  m_WATER_OUT_TEMP_SLAVE_SEL_TRUE(),
 *                  m_WATER_IN_TEMP_SLAVE_SEL_FALSE(),
 *                  m_WATER_OUT_TEMP_SLAVE_SEL_FALSE()
 *
 * PreConditions:   SPI serial port is configured and open.
 *
 * Inputs:          An argument that is used to determine from which sensor
 *                  to obtain the data packet and the address of a data union
 *                  of ThermistorDataUnion_t type in which to store the data.
 *
 * Output:          The fault status of the operation.
 *
 * Side Effects:    The type ThermistorDataUnion_t data union is populated
 *                  with thermistor data.
 ******************************************************************************/
static int16_t GetThermistorDataPacket(const int8_t ThermistorSensorId,
                    volatile ThermistorDataUnion_t * const ThermistorDataConstruct,
                    const int16_t ThermistorDataPacketByteCount)
{
    int16_t byteCount;
    int16_t functionFaultStatus = NO_THERMISTOR_FAULT_IND;

    switch (ThermistorSensorId)
    {
        case INLET_WT_THERMISTOR_ID :
            m_WATER_IN_TEMP_SLAVE_SEL_TRUE()
            break;

        case OUTLET_WT_THERMISTOR_ID :
            m_WATER_OUT_TEMP_SLAVE_SEL_TRUE()
            break;

        default :
            functionFaultStatus = GTIDP_FUNCT_ARG_RELATED_FAULT_IND;
            break;
    }

    __delay_us(100);               /* 2us slave select circuit settling time. */

    if (functionFaultStatus == NO_THERMISTOR_FAULT_IND)
    {
        for (byteCount = (ThermistorDataPacketByteCount - 1); byteCount >= 0; --byteCount)
        {
            ThermistorDataConstruct->thermistorDataPacketByteArray[byteCount] = ReadSPI();
        }

        ThermistorDataConstruct->thermistorDataPacketByteArray[0] =
                (((ThermistorDataConstruct->thermistorDataPacketByteArray[1] <<
                   THERMISTOR_BYTE_LEFT_SHIFT) & 0xF8) |
                ((ThermistorDataConstruct->thermistorDataPacketByteArray[0] >>
                  THERMISTOR_BYTE_RIGHT_SHIFT) & 0x07));
        
        ThermistorDataConstruct->thermistorDataPacketByteArray[1] =
                ((ThermistorDataConstruct->thermistorDataPacketByteArray[1] >>
                 THERMISTOR_BYTE_RIGHT_SHIFT) & 0x07);
    }

    switch (ThermistorSensorId)
    {
        case INLET_WT_THERMISTOR_ID :
            m_WATER_IN_TEMP_SLAVE_SEL_FALSE()
            break;

        case OUTLET_WT_THERMISTOR_ID :
            m_WATER_OUT_TEMP_SLAVE_SEL_FALSE()
            break;

        default :
            functionFaultStatus = GTIDP_FUNCT_ARG_RELATED_FAULT_IND;
            break;
    }

    __delay_ms(100);                /* 80ms A/D conversion time is required
                                     * by the thermistor-to-digital IC. */

    return functionFaultStatus;

}/* end GetThermistorDataPacket() */

/*******************************************************************************
 * Function:        static int16_t TestForThermistorFault
 *                      (const ThermistorDataUnion_t ThermistorDataConstruct);
 *
 * Description:     TestForTcFault() examines the value passed in the type
 *                  ThermistorDataUnion_t construct in order to determine and
 *                  report, via over-range or under-range values, a potentially
 *                  shorted or open sensor circuit. The thermistor is a NTC
 *                  device.
 *
 * Dependencies:    cs_pdk_400_thermistor.h
 *
 * PreConditions:   None
 *
 * Inputs:          Data as read from one of the Thermistor to Digital ICs and
 *                  passed as a type ThermistorDataUnion_t construct.
 *
 * Output:          Numerical data that indicates what type of potential fault,
 *                  if any, was detected.
 *
 * Side Effects:    None
 ******************************************************************************/
static int16_t TestForThermistorFault(const ThermistorDataUnion_t ThermistorDataConstruct)
{
    int16_t functionFaultStatus;

    if (((ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_SIGN_BIT_MASK) != 0) &&
        ((uint16_t)(ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_DATA_BITS_MASK) <=
         ((uint16_t)THERMISTOR_OPEN_CIRCUIT_FAULT_TEST_VALUE)))
    {                                                   /* Negative value. */
            functionFaultStatus = THERMISTOR_OPEN_CIRCUIT_FAULT_IND;
    }

    else if (((ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_SIGN_BIT_MASK) == 0) &&
             ((((uint16_t)(ThermistorDataConstruct.thermistorDataPacket)) &
             ((uint16_t)THERMISTOR_DATA_BITS_MASK)) >=
             ((uint16_t)THERMISTOR_SHORT_CIRCUIT_FAULT_TEST_VALUE)))
    {                                                   /* Positive value. */
            functionFaultStatus = THERMISTOR_SHORT_CIRCUIT_FAULT_IND;
    }

    else
    {
        functionFaultStatus = NO_THERMISTOR_FAULT_IND;
    }
    
    return functionFaultStatus;
}/* end TestForThermistorFault() */

/*******************************************************************************
 * Function:        static uint16_t ExtractThermistorTemperatureData
 *                      (const ThermistorDataUnion_t ThermistorDataConstruct);
 *
 * Description:     ExtractThermistorTemperatureData() extracts positive
 *                  thermistor data values from the data passed in the type
 *                  ThermistorDataUnion_t construct or zero in the case of
 *                  negative thermistor data values.
 *
 * Dependencies:    cs_pdk_400_thermistor.h
 *
 * PreConditions:   None
 *
 * Inputs:          Data as read from one of the Thermistor to Digital ICs and
 *                  passed as a type ThermistorDataUnion_t construct.
 *
 * Output:          A zero or positive thermistor data value.
 *
 * Side Effects:    None
 ******************************************************************************/
static uint16_t ExtractThermistorTemperatureData(const ThermistorDataUnion_t ThermistorDataConstruct)
{
    uint16_t temperatureData;

    if (ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_SIGN_BIT_MASK)
    {                                               /* Negative temperature. */
        temperatureData = 0u;
    }

    else
    {
        temperatureData = (ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_DATA_BITS_MASK);
    }

    return temperatureData;
}/* end ExtractThermistorTemperatureData() */

/*******************************************************************************
 * Function:        static uint16_t ConvertThermistorDataToDegreesC
 *                                          (const uint16_t ThermistorData)
 *
 * Description:     ConvertThermistorDataToDegreesC() applies appropriate
 *                  conversion factors to the value passed in the ThermistorData
 *                  argument in order to linearize and convert ThermistorData
 *                  to degrees Celsius.
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          Positive (0 or greater) data as extracted from the data that
 *                  was read from one of the Thermistor to Digital ICs and
 *                  passed as the ThermistorData argument.
 *
 * Output:          The thermistor temperature in degrees Celsius.
 *
 * Side Effects:    None
 ******************************************************************************/
static uint16_t ConvertThermistorDataToDegreesC (const uint16_t ThermistorData)
{
    double thermistorDegreesC;

    if (ThermistorData <= 326u)
    {
        thermistorDegreesC = ThermistorData * 0.125;
    }

    else if ((326u < ThermistorData) && (ThermistorData <= 357u))
    {
        thermistorDegreesC = ThermistorData * 0.127;
    }

    else if ((357u < ThermistorData) && (ThermistorData <= 377u))
    {
        thermistorDegreesC = ThermistorData * 0.128;
    }

    else if ((377u < ThermistorData) && (ThermistorData <= 390u))
    {
        thermistorDegreesC = ThermistorData * 0.129;
    }

    else if ((390u < ThermistorData) && (ThermistorData <= 405u))
    {
        thermistorDegreesC = ThermistorData * 0.130;
    }

    else if ((405u < ThermistorData) && (ThermistorData <= 414u))
    {
        thermistorDegreesC = ThermistorData * 0.131;
    }

    else if ((414u < ThermistorData) && (ThermistorData <= 423u))
    {
        thermistorDegreesC = ThermistorData * 0.132;
    }

    else if ((423u < ThermistorData) && (ThermistorData <= 434u))
    {
        thermistorDegreesC = ThermistorData * 0.133;
    }

    else if ((434u < ThermistorData) && (ThermistorData <= 442u))
    {
        thermistorDegreesC = ThermistorData * 0.134;
    }

    else if ((442u < ThermistorData) && (ThermistorData <= 447u))
    {
        thermistorDegreesC = ThermistorData * 0.135;
    }

    else if ((447u < ThermistorData) && (ThermistorData <= 455u))
    {
        thermistorDegreesC = ThermistorData * 0.136;
    }

    else if ((455u < ThermistorData) && (ThermistorData <= 462u))
    {
        thermistorDegreesC = ThermistorData * 0.137;
    }

    else if ((462u < ThermistorData) && (ThermistorData <= 467u))
    {
        thermistorDegreesC = ThermistorData * 0.138;
    }

    else if ((467u < ThermistorData) && (ThermistorData <= 478u))
    {
        thermistorDegreesC = ThermistorData * 0.139;
    }

    else if ((478u < ThermistorData) && (ThermistorData <= 480u))
    {
        thermistorDegreesC = ThermistorData * 0.140;
    }

    else if ((480u < ThermistorData) && (ThermistorData <= 482u))
    {
        thermistorDegreesC = ThermistorData * 0.141;
    }

    else if ((482u < ThermistorData) && (ThermistorData <= 489u))
    {
        thermistorDegreesC = ThermistorData * 0.142;
    }

    else if ((489u < ThermistorData) && (ThermistorData <= 493u))
    {
        thermistorDegreesC = ThermistorData * 0.143;
    }

    else if ((493u < ThermistorData) && (ThermistorData <= 497u))
    {
        thermistorDegreesC = ThermistorData * 0.144;
    }

    else if ((497u < ThermistorData) && (ThermistorData <= 502u))
    {
        thermistorDegreesC = ThermistorData * 0.145;
    }

    else if ((502u < ThermistorData) && (ThermistorData <= 506u))
    {
        thermistorDegreesC = ThermistorData * 0.146;
    }

    else if ((506u < ThermistorData) && (ThermistorData <= 509u))
    {
        thermistorDegreesC = ThermistorData * 0.147;
    }

    else if ((509u < ThermistorData) && (ThermistorData <= 513u))
    {
        thermistorDegreesC = ThermistorData * 0.148;
    }

    else if ((513u < ThermistorData) && (ThermistorData <= 516u))
    {
        thermistorDegreesC = ThermistorData * 0.149;
    }

    else if ((516u < ThermistorData) && (ThermistorData <= 519u))
    {
        thermistorDegreesC = ThermistorData * 0.150;
    }

    else if ((519u < ThermistorData) && (ThermistorData <= 522u))
    {
        thermistorDegreesC = ThermistorData * 0.151;
    }

    else if ((522u < ThermistorData) && (ThermistorData <= 525u))
    {
        thermistorDegreesC = ThermistorData * 0.152;
    }

    else if ((525u < ThermistorData) && (ThermistorData <= 528u))
    {
        thermistorDegreesC = ThermistorData * 0.153;
    }

    else if ((528u < ThermistorData) && (ThermistorData <= 532u))
    {
        thermistorDegreesC = ThermistorData * 0.154;
    }

    else if ((532u < ThermistorData) && (ThermistorData <= 534u))
    {
        thermistorDegreesC = ThermistorData * 0.155;
    }

    else if ((534u < ThermistorData) && (ThermistorData <= 537u))
    {
        thermistorDegreesC = ThermistorData * 0.156;
    }

    else if ((537u < ThermistorData) && (ThermistorData <= 541u))
    {
        thermistorDegreesC = ThermistorData * 0.157;
    }

    else if ((541u < ThermistorData) && (ThermistorData <= 543u))
    {
        thermistorDegreesC = ThermistorData * 0.158;
    }

    else if ((543u < ThermistorData) && (ThermistorData <= 546u))
    {
        thermistorDegreesC = ThermistorData * 0.159;
    }

    else if ((546u < ThermistorData) && (ThermistorData <= 549u))
    {
        thermistorDegreesC = ThermistorData * 0.160;
    }

    else if ((549u < ThermistorData) && (ThermistorData <= 550u))
    {
        thermistorDegreesC = ThermistorData * 0.161;
    }

    else if ((550u < ThermistorData) && (ThermistorData <= 552u))
    {
        thermistorDegreesC = ThermistorData * 0.162;
    }

    else if ((552u < ThermistorData) && (ThermistorData <= 554u))
    {
        thermistorDegreesC = ThermistorData * 0.163;
    }

    else if ((554u < ThermistorData) && (ThermistorData <= 556u))
    {
        thermistorDegreesC = ThermistorData * 0.164;
    }

    else if ((556u < ThermistorData) && (ThermistorData <= 558u))
    {
        thermistorDegreesC = ThermistorData * 0.165;
    }

    else if ((558u < ThermistorData) && (ThermistorData <= 559u))
    {
        thermistorDegreesC = ThermistorData * 0.166;
    }

    else if ((559u < ThermistorData) && (ThermistorData <= 561u))
    {
        thermistorDegreesC = ThermistorData * 0.167;
    }

    else if ((561u < ThermistorData) && (ThermistorData <= 563u))
    {
        thermistorDegreesC = ThermistorData * 0.168;
    }

    else if ((563u < ThermistorData) && (ThermistorData <= 564u))
    {
        thermistorDegreesC = ThermistorData * 0.169;
    }

    else if ((564u < ThermistorData) && (ThermistorData <= 566u))
    {
        thermistorDegreesC = ThermistorData * 0.170;
    }

    else if ((566u < ThermistorData) && (ThermistorData <= 568u))
    {
        thermistorDegreesC = ThermistorData * 0.171;
    }

    else if ((568u < ThermistorData) && (ThermistorData <= 569u))
    {
        thermistorDegreesC = ThermistorData * 0.172;
    }

    else if ((569u < ThermistorData) && (ThermistorData <= 571u))
    {
        thermistorDegreesC = ThermistorData * 0.173;
    }

    else if ((571u < ThermistorData) && (ThermistorData <= 572u))
    {
        thermistorDegreesC = ThermistorData * 0.174;
    }

    else if ((572u < ThermistorData) && (ThermistorData <= 574u))
    {
        thermistorDegreesC = ThermistorData * 0.175;
    }

    else if ((574u < ThermistorData) && (ThermistorData <= 575u))
    {
        thermistorDegreesC = ThermistorData * 0.176;
    }

    else if ((575u < ThermistorData) && (ThermistorData <= 576u))
    {
        thermistorDegreesC = ThermistorData * 0.177;
    }

    else if ((576u < ThermistorData) && (ThermistorData <= 577u))
    {
        thermistorDegreesC = ThermistorData * 0.178;
    }

    else if ((577u < ThermistorData) && (ThermistorData <= 578u))
    {
        thermistorDegreesC = ThermistorData * 0.179;
    }

    else if ((578u < ThermistorData) && (ThermistorData <= 579u))
    {
        thermistorDegreesC = ThermistorData * 0.180;
    }

    else if ((579u < ThermistorData) && (ThermistorData <= 581u))
    {
        thermistorDegreesC = ThermistorData * 0.181;
    }

    else if ((581u < ThermistorData) && (ThermistorData <= 582u))
    {
        thermistorDegreesC = ThermistorData * 0.182;
    }

    else if ((582u < ThermistorData) && (ThermistorData <= 583u))
    {
        thermistorDegreesC = ThermistorData * 0.183;
    }

    else if ((583u < ThermistorData) && (ThermistorData <= 584u))
    {
        thermistorDegreesC = ThermistorData * 0.184;
    }

    else if ((584u < ThermistorData) && (ThermistorData <= 585u))
    {
        thermistorDegreesC = ThermistorData * 0.185;
    }

    else if ((585u < ThermistorData) && (ThermistorData <= 586u))
    {
        thermistorDegreesC = ThermistorData * 0.186;
    }

    else if ((586u < ThermistorData) && (ThermistorData <= 587u))
    {
        thermistorDegreesC = ThermistorData * 0.187;
    }

    else
    {
        thermistorDegreesC = ThermistorData * 0.187;
    }                               /* ThermistorData > 587. */

    return (uint16_t)thermistorDegreesC;

}/* end ConvertThermistorDataToDegreesC() */

/*******************************************************************************
 * Function:        static uint16_t ConvertDGThermistorDataToDegreesC
 *                                          (const ThermistorDataUnion_t ThermistorDataConstruct)
 *
 * Description:     ConvertDGThermistorDataToDegreesC() applies appropriate
 *                  conversion factors to the value passed in the
 *                  ThermistorDataConstruct argument in order to convert
 *                  ThermistorData to degrees Celsius.
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          Data that was obtained from the Thermistor to Digital ICs
 *                  and passed as the ThermistorData argument.
 *
 * Output:          The thermistor temperature in degrees Celsius.
 *
 * Side Effects:    None
 ******************************************************************************/
static uint16_t ConvertDGThermistorDataToDegreesC (const ThermistorDataUnion_t ThermistorDataConstruct)
{
    uint16_t RawDgThermistorData = ThermistorDataConstruct.thermistorDataPacket;
    uint16_t DgThermistorData;
    
    DgThermistorData = (RawDgThermistorData & THERMISTOR_DATA_BITS_MASK);
                                /* Temperature data without the sign bit. */
    
    if (RawDgThermistorData & THERMISTOR_SIGN_BIT_MASK)
    {                                               /* If sign bit is set... */
        if (DgThermistorData <= 898) return 28;
        else if (DgThermistorData <= 899) return 29;
        else if (DgThermistorData <= 900) return 32;
        else if (DgThermistorData <= 901) return 34;
        else if (DgThermistorData <= 902) return 36;
        else if (DgThermistorData <= 903) return 38;
        else if (DgThermistorData <= 904) return 40;
        else if (DgThermistorData <= 905) return 42;
        else if (DgThermistorData <= 906) return 43;
        else if (DgThermistorData <= 907) return 45;
        else if (DgThermistorData <= 908) return 46;
        else if (DgThermistorData <= 909) return 48;
        else if (DgThermistorData <= 910) return 49;
        else if (DgThermistorData <= 911) return 50;
        else if (DgThermistorData <= 912) return 52;
        else if (DgThermistorData <= 913) return 53;
        else if (DgThermistorData <= 914) return 54;
        else if (DgThermistorData <= 915) return 55;
        else if (DgThermistorData <= 916) return 56;
        else if (DgThermistorData <= 917) return 57;
        else if (DgThermistorData <= 918) return 58;
        else if (DgThermistorData <= 919) return 59;
        else if (DgThermistorData <= 920) return 60;
        else if (DgThermistorData <= 921) return 61;
        else if (DgThermistorData <= 922) return 62;
        else if (DgThermistorData <= 923) return 63;
        else if (DgThermistorData <= 924) return 64;
        else if (DgThermistorData <= 925) return 65;
        else if (DgThermistorData <= 926) return 66;
        else if (DgThermistorData <= 928) return 67;
        else if (DgThermistorData <= 929) return 68;
        else if (DgThermistorData <= 930) return 69;
        else if (DgThermistorData <= 932) return 70;
        else if (DgThermistorData <= 933) return 71;
        else if (DgThermistorData <= 934) return 72;
        else if (DgThermistorData <= 936) return 73;
        else if (DgThermistorData <= 937) return 74;
        else if (DgThermistorData <= 939) return 75;
        else if (DgThermistorData <= 940) return 76;
        else if (DgThermistorData <= 942) return 77;
        else if (DgThermistorData <= 943) return 78;
        else if (DgThermistorData <= 945) return 79;
        else if (DgThermistorData <= 947) return 80;
        else if (DgThermistorData <= 948) return 81;
        else if (DgThermistorData <= 950) return 82;
        else if (DgThermistorData <= 952) return 83;
        else if (DgThermistorData <= 954) return 84;
        else if (DgThermistorData <= 956) return 85;
        else if (DgThermistorData <= 957) return 86;
        else if (DgThermistorData <= 959) return 87;
        else if (DgThermistorData <= 961) return 88;
        else if (DgThermistorData <= 964) return 89;
        else if (DgThermistorData <= 966) return 90;
        else if (DgThermistorData <= 968) return 91;
        else if (DgThermistorData <= 970) return 92;
        else if (DgThermistorData <= 972) return 93;
        else if (DgThermistorData <= 974) return 94;
        else if (DgThermistorData <= 977) return 95;
        else if (DgThermistorData <= 979) return 96;
        else if (DgThermistorData <= 981) return 97;
        else if (DgThermistorData <= 984) return 98;
        else if (DgThermistorData <= 986) return 99;
        else if (DgThermistorData <= 989) return 100;
        else if (DgThermistorData <= 991) return 101;
        else if (DgThermistorData <= 994) return 102;
        else if (DgThermistorData <= 997) return 103;
        else if (DgThermistorData <= 999) return 104;
        else if (DgThermistorData <= 1002) return 105;
        else if (DgThermistorData <= 1005) return 106;
        else if (DgThermistorData <= 1008) return 107;
        else if (DgThermistorData <= 1010) return 108;
        else if (DgThermistorData <= 1014) return 109;
        else if (DgThermistorData <= 1017) return 110;
        else if (DgThermistorData <= 1019) return 111;
        else if (DgThermistorData <= 1022) return 112;
        else return 113;
    }/* end if() */
    
    else
    {
        if (DgThermistorData <= 5) return 114;
        else if (DgThermistorData <= 8) return 115;
        else if (DgThermistorData <= 11) return 116;
        else if (DgThermistorData <= 14) return 117;
        else if (DgThermistorData <= 17) return 118;
        else if (DgThermistorData <= 21) return 119;
        else if (DgThermistorData <= 24) return 120;
        else if (DgThermistorData <= 27) return 121;
        else if (DgThermistorData <= 31) return 122;
        else if (DgThermistorData <= 34) return 123;
        else if (DgThermistorData <= 38) return 124;
        else if (DgThermistorData <= 42) return 125;
        else if (DgThermistorData <= 45) return 126;
        else if (DgThermistorData <= 49) return 127;
        else if (DgThermistorData <= 52) return 128;
        else if (DgThermistorData <= 56) return 129;
        else if (DgThermistorData <= 60) return 130;
        else if (DgThermistorData <= 63) return 131;
        else if (DgThermistorData <= 67) return 132;
        else if (DgThermistorData <= 71) return 133;
        else if (DgThermistorData <= 75) return 134;
        else if (DgThermistorData <= 79) return 135;
        else if (DgThermistorData <= 82) return 136;
        else if (DgThermistorData <= 86) return 137;
        else if (DgThermistorData <= 90) return 138;
        else if (DgThermistorData <= 94) return 139;
        else if (DgThermistorData <= 98) return 140;
        else if (DgThermistorData <= 102) return 141;
        else if (DgThermistorData <= 106) return 142;
        else if (DgThermistorData <= 110) return 143;
        else if (DgThermistorData <= 114) return 144;
        else if (DgThermistorData <= 118) return 145;
        else if (DgThermistorData <= 122) return 146;
        else if (DgThermistorData <= 126) return 147;
        else if (DgThermistorData <= 131) return 148;
        else if (DgThermistorData <= 135) return 149;
        else if (DgThermistorData <= 139) return 150;
        else if (DgThermistorData <= 143) return 151;
        else if (DgThermistorData <= 147) return 152;
        else if (DgThermistorData <= 151) return 153;
        else if (DgThermistorData <= 156) return 154;
        else if (DgThermistorData <= 160) return 155;
        else if (DgThermistorData <= 164) return 156;
        else if (DgThermistorData <= 168) return 157;
        else if (DgThermistorData <= 172) return 158;
        else if (DgThermistorData <= 177) return 159;
        else if (DgThermistorData <= 181) return 160;
        else if (DgThermistorData <= 185) return 161;
        else if (DgThermistorData <= 189) return 162;
        else if (DgThermistorData <= 193) return 163;
        else if (DgThermistorData <= 198) return 164;
        else if (DgThermistorData <= 202) return 165;
        else if (DgThermistorData <= 206) return 166;
        else if (DgThermistorData <= 210) return 167;
        else if (DgThermistorData <= 214) return 168;
        else if (DgThermistorData <= 219) return 169;
        else if (DgThermistorData <= 223) return 170;
        else if (DgThermistorData <= 227) return 171;
        else if (DgThermistorData <= 231) return 172;
        else if (DgThermistorData <= 235) return 173;
        else if (DgThermistorData <= 239) return 174;
        else if (DgThermistorData <= 243) return 175;
        else if (DgThermistorData <= 247) return 176;
        else if (DgThermistorData <= 251) return 177;
        else if (DgThermistorData <= 255) return 178;
        else if (DgThermistorData <= 260) return 179;
        else if (DgThermistorData <= 264) return 180;
        else if (DgThermistorData <= 267) return 181;
        else if (DgThermistorData <= 271) return 182;
        else if (DgThermistorData <= 275) return 183;
        else if (DgThermistorData <= 279) return 184;
        else if (DgThermistorData <= 283) return 185;
        else if (DgThermistorData <= 287) return 186;
        else if (DgThermistorData <= 291) return 187;
        else if (DgThermistorData <= 295) return 188;
        else if (DgThermistorData <= 299) return 189;
        else if (DgThermistorData <= 302) return 190;
        else if (DgThermistorData <= 306) return 191;
        else if (DgThermistorData <= 310) return 192;
        else if (DgThermistorData <= 313) return 193;
        else if (DgThermistorData <= 317) return 194;
        else if (DgThermistorData <= 321) return 195;
        else if (DgThermistorData <= 324) return 196;
        else if (DgThermistorData <= 328) return 197;
        else if (DgThermistorData <= 332) return 198;
        else if (DgThermistorData <= 335) return 199;
        else if (DgThermistorData <= 338) return 200;
        else if (DgThermistorData <= 342) return 201;
        else if (DgThermistorData <= 345) return 202;
        else if (DgThermistorData <= 349) return 203;
        else if (DgThermistorData <= 352) return 204;
        else if (DgThermistorData <= 356) return 205;
        else if (DgThermistorData <= 359) return 206;
        else if (DgThermistorData <= 362) return 207;
        else if (DgThermistorData <= 365) return 208;
        else if (DgThermistorData <= 369) return 209;
        else if (DgThermistorData <= 372) return 210;
        else if (DgThermistorData <= 375) return 211;
        else if (DgThermistorData <= 378) return 212;
        else if (DgThermistorData <= 381) return 213;
        else if (DgThermistorData <= 383) return 214;
        else if (DgThermistorData <= 388) return 215;
        else if (DgThermistorData <= 391) return 216;
        else if (DgThermistorData <= 394) return 217;
        else if (DgThermistorData <= 397) return 218;
        else if (DgThermistorData <= 400) return 219;
        else if (DgThermistorData <= 402) return 220;
        else if (DgThermistorData <= 405) return 221;
        else if (DgThermistorData <= 408) return 222;
        else if (DgThermistorData <= 411) return 223;
        else if (DgThermistorData <= 414) return 224;
        else if (DgThermistorData <= 416) return 225;
        else if (DgThermistorData <= 419) return 226;
        else if (DgThermistorData <= 422) return 227;
        else if (DgThermistorData <= 425) return 228;
        else if (DgThermistorData <= 427) return 229;
        else if (DgThermistorData <= 430) return 230;
        else if (DgThermistorData <= 433) return 231;
        else if (DgThermistorData <= 435) return 232;
        else if (DgThermistorData <= 438) return 233;
        else if (DgThermistorData <= 440) return 234;
        else if (DgThermistorData <= 443) return 235;
        else if (DgThermistorData <= 445) return 236;
        else if (DgThermistorData <= 447) return 237;
        else if (DgThermistorData <= 450) return 238;
        else if (DgThermistorData <= 452) return 239;
        else if (DgThermistorData <= 454) return 240;
        else if (DgThermistorData <= 457) return 241;
        else if (DgThermistorData <= 459) return 242;
        else if (DgThermistorData <= 461) return 243;
        else if (DgThermistorData <= 463) return 244;
        else if (DgThermistorData <= 465) return 245;
        else if (DgThermistorData <= 467) return 246;
        else if (DgThermistorData <= 469) return 247;
        else if (DgThermistorData <= 472) return 248;
        else if (DgThermistorData <= 474) return 249;
        else return 250;
    }/* end else */
}/* end ConvertDGThermistorDataToDegreesC() */

/***** EOF for bc_pdk_400_dg_thermistor.c *************************************/
#endif

#ifndef NEWTHERM  //using old thermistors on Controller 1

/*******************************************************************************
 * Original thermistor code for measuring water temp 
 * Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_thermistor.c
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

#include "cs_woodmaster_400_user.h"
#include "cs_woodmaster_400_thermistor.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declarations                   */
/******************************************************************************/

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
static volatile uint8_t highByte;
static volatile uint8_t lowByte;

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
static volatile ThermistorDataUnion_t ThermistorDataPacketUnion;

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/
static int16_t GetThermistorDataPacket(const int8_t ThermistorSensorId,
                    volatile ThermistorDataUnion_t * const ThermistorDataConstruct,
                    const int16_t ThermistorDataPacketByteCount);

static int16_t TestForThermistorFault(const ThermistorDataUnion_t ThermistorDataConstruct);

static uint16_t ExtractThermistorTemperatureData(const ThermistorDataUnion_t ThermistorDataConstruct);

static uint16_t ConvertThermistorDataToDegreesC (const uint16_t ThermistorData);

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        int16_t GetThermistorTemperature_C
 *                                     (const int8_t ThermistorSensorId,
 *                              volatile uint16_t * const ThermistorTemperature)
 *
 * Description:     GetThermistorTemperature_C() uses several helper functions
 *                  in order to read the temperature, in Celsius, of a specified
 *                  thermistor temperature sensor. Negative temperatures will
 *                  be read as zero degrees Celsius.
 *
 * Dependencies:    cs_pdk_400_thermistor.h
 *
 * PreConditions:   SPI serial port is configured and open.
 *
 * Inputs:          An argument that specifies from which sensor to read the
 *                  temperature.
 *
 * Output:          Thermistor sensor and/or thermistor function error status.
 *
 * Side Effects:    If no errors; ThermistorTemperature will contain the zero
 *                  or greater temperature, in Celsius, of a specified
 *                  thermistor temperature sensor.
 ******************************************************************************/
int16_t GetThermistorTemperature_C (const int8_t ThermistorSensorId,
                                volatile uint16_t * const ThermistorTemperature)
{
    int16_t functionFaultStatus;
    uint16_t extractedData;

    functionFaultStatus = GetThermistorDataPacket(ThermistorSensorId,
                                                  &ThermistorDataPacketUnion,
                                            THERMISTOR_DATA_PACKET_BYTE_COUNT);

    if (functionFaultStatus == NO_THERMISTOR_FAULT_IND)
    {
        functionFaultStatus = TestForThermistorFault(ThermistorDataPacketUnion);
    }

    if (functionFaultStatus == NO_THERMISTOR_FAULT_IND)
    {
        extractedData = ExtractThermistorTemperatureData(ThermistorDataPacketUnion);

        *ThermistorTemperature = ConvertThermistorDataToDegreesC (extractedData);
    }

    return functionFaultStatus;
}/* end GetThermistorTemperature_C() */

/*******************************************************************************
 * Function:        static int16_t GetThermistorDataPacket
 *                                          (const int8_t ThermistorSensorId,
 *              volatile ThermistorDataUnion_t * const ThermistorDataConstruct,
 *                                  const int16_t ThermistorDataPacketByteCount)
 *
 * Description:     GetThermistorDataPacket() uses the SPI bus to read data from
 *                  a Thermistor to Digital IC that is associated with the
 *                  sensor ID that is passed as the ThermistorSensorId argument.
 *
 * Dependencies:    cs_pdk_400_thermistor.h, cs_pdk_400_user.h,
 *                  Macros m_WATER_IN_TEMP_SLAVE_SEL_TRUE(),
 *                  m_WATER_OUT_TEMP_SLAVE_SEL_TRUE(),
 *                  m_WATER_IN_TEMP_SLAVE_SEL_FALSE(),
 *                  m_WATER_OUT_TEMP_SLAVE_SEL_FALSE()
 *
 * PreConditions:   SPI serial port is configured and open.
 *
 * Inputs:          An argument that is used to determine from which sensor
 *                  to obtain the data packet and the address of a data union
 *                  of ThermistorDataUnion_t type in which to store the data.
 *
 * Output:          The fault status of the operation.
 *
 * Side Effects:    The type ThermistorDataUnion_t data union is populated
 *                  with thermistor data.
 ******************************************************************************/
static int16_t GetThermistorDataPacket(const int8_t ThermistorSensorId,
                    volatile ThermistorDataUnion_t * const ThermistorDataConstruct,
                    const int16_t ThermistorDataPacketByteCount)
{
    int16_t byteCount;
    int16_t functionFaultStatus = NO_THERMISTOR_FAULT_IND;

    switch (ThermistorSensorId)
    {
        case INLET_WT_THERMISTOR_ID :
            m_WATER_IN_TEMP_SLAVE_SEL_TRUE()
            break;

        case OUTLET_WT_THERMISTOR_ID :
            m_WATER_OUT_TEMP_SLAVE_SEL_TRUE()
            break;

        default :
            functionFaultStatus = GTIDP_FUNCT_ARG_RELATED_FAULT_IND;
            break;
    }

    __delay_us(100);               /* 2us slave select circuit settling time. */

    if (functionFaultStatus == NO_THERMISTOR_FAULT_IND)
    {
        for (byteCount = (ThermistorDataPacketByteCount - 1); byteCount >= 0; --byteCount)
        {
            ThermistorDataConstruct->thermistorDataPacketByteArray[byteCount] = ReadSPI();
        }
        
        ThermistorDataConstruct->thermistorDataPacketByteArray[0] =
                (((ThermistorDataConstruct->thermistorDataPacketByteArray[1] <<
                   THERMISTOR_BYTE_LEFT_SHIFT) & 0xF8) |
                ((ThermistorDataConstruct->thermistorDataPacketByteArray[0] >>
                  THERMISTOR_BYTE_RIGHT_SHIFT) & 0x07));
        
        ThermistorDataConstruct->thermistorDataPacketByteArray[1] =
                ((ThermistorDataConstruct->thermistorDataPacketByteArray[1] >>
                 THERMISTOR_BYTE_RIGHT_SHIFT) & 0x07);
    }

    switch (ThermistorSensorId)
    {
        case INLET_WT_THERMISTOR_ID :
            m_WATER_IN_TEMP_SLAVE_SEL_FALSE()
            break;

        case OUTLET_WT_THERMISTOR_ID :
            m_WATER_OUT_TEMP_SLAVE_SEL_FALSE()
            break;

        default :
            functionFaultStatus = GTIDP_FUNCT_ARG_RELATED_FAULT_IND;
            break;
    }

    __delay_ms(2);                /* 80ms A/D conversion time is required
                                     * by the thermistor-to-digital IC. */

    return functionFaultStatus;

}/* end GetThermistorDataPacket() */

/*******************************************************************************
 * Function:        static int16_t TestForThermistorFault
 *                      (const ThermistorDataUnion_t ThermistorDataConstruct);
 *
 * Description:     TestForTcFault() examines the value passed in the type
 *                  ThermistorDataUnion_t construct in order to determine and
 *                  report, via over-range or under-range values, a potentially
 *                  shorted or open sensor circuit. The thermistor is a NTC
 *                  device.
 *
 * Dependencies:    cs_pdk_400_thermistor.h
 *
 * PreConditions:   None
 *
 * Inputs:          Data as read from one of the Thermistor to Digital ICs and
 *                  passed as a type ThermistorDataUnion_t construct.
 *
 * Output:          Numerical data that indicates what type of potential fault,
 *                  if any, was detected.
 *
 * Side Effects:    None
 ******************************************************************************/
static int16_t TestForThermistorFault(const ThermistorDataUnion_t ThermistorDataConstruct)
{
    int16_t functionFaultStatus;

    if (((ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_SIGN_BIT_MASK) != 0) &&
        ((uint16_t)(ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_DATA_BITS_MASK) <=
         ((uint16_t)THERMISTOR_OPEN_CIRCUIT_FAULT_TEST_VALUE)))
    {                                                   /* Negative value. */
            functionFaultStatus = THERMISTOR_OPEN_CIRCUIT_FAULT_IND;
    }

    else if (((ThermistorDataConstruct.thermistorDataPacket & THERMISTOR_SIGN_BIT_MASK) == 0) &&
             ((((uint16_t)(ThermistorDataConstruct.thermistorDataPacket)) &
             ((uint16_t)THERMISTOR_DATA_BITS_MASK)) >=
             ((uint16_t)THERMISTOR_SHORT_CIRCUIT_FAULT_TEST_VALUE)))
    {                                                   /* Positive value. */
            functionFaultStatus = THERMISTOR_SHORT_CIRCUIT_FAULT_IND;
    }

    else
    {
        functionFaultStatus = NO_THERMISTOR_FAULT_IND;
    }
    
    return functionFaultStatus;
}/* end TestForThermistorFault() */

/*******************************************************************************
 * Function:        static uint16_t ExtractThermistorTemperatureData
 *                      (const ThermistorDataUnion_t ThermistorDataConstruct);
 *
 * Description:     ExtractThermistorTemperatureData() extracts positive
 *                  thermistor data values from the data passed in the type
 *                  ThermistorDataUnion_t construct or zero in the case of
 *                  negative thermistor data values.
 *
 * Dependencies:    cs_pdk_400_thermistor.h
 *
 * PreConditions:   None
 *
 * Inputs:          Data as read from one of the Thermistor to Digital ICs and
 *                  passed as a type ThermistorDataUnion_t construct.
 *
 * Output:          A zero or positive thermistor data value.
 *
 * Side Effects:    None
 ******************************************************************************/
static uint16_t ExtractThermistorTemperatureData(const ThermistorDataUnion_t ThermistorDataConstruct)
{
    uint16_t temperatureData;

    if (ThermistorDataConstruct.thermistorDataPacket & ((uint16_t)THERMISTOR_SIGN_BIT_MASK))
    {                                               /* Negative temperature. */
        temperatureData = 0u;
    }

    else
    {
        temperatureData = (ThermistorDataConstruct.thermistorDataPacket & ((uint16_t)THERMISTOR_DATA_BITS_MASK));
    }

    return temperatureData;
}/* end ExtractThermistorTemperatureData() */

/*******************************************************************************
 * Function:        static uint16_t ConvertThermistorDataToDegreesC
 *                                          (const uint16_t ThermistorData)
 *
 * Description:     ConvertThermistorDataToDegreesC() applies appropriate
 *                  conversion factors to the value passed in the ThermistorData
 *                  argument in order to linearize and convert ThermistorData
 *                  to degrees Celsius.
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          Positive (0 or greater) data as extracted from the data that
 *                  was read from one of the Thermistor to Digital ICs and
 *                  passed as the ThermistorData argument.
 *
 * Output:          The thermistor temperature in degrees Celsius.
 *
 * Side Effects:    None
 ******************************************************************************/
static uint16_t ConvertThermistorDataToDegreesC (const uint16_t ThermistorData)
{
    double thermistorDegreesC;

    if (ThermistorData <= 326u)
    {
        thermistorDegreesC = ThermistorData * 0.125;
    }

    else if ((326u < ThermistorData) && (ThermistorData <= 357u))
    {
        thermistorDegreesC = ThermistorData * 0.127;
    }

    else if ((357u < ThermistorData) && (ThermistorData <= 377u))
    {
        thermistorDegreesC = ThermistorData * 0.128;
    }

    else if ((377u < ThermistorData) && (ThermistorData <= 390u))
    {
        thermistorDegreesC = ThermistorData * 0.129;
    }

    else if ((390u < ThermistorData) && (ThermistorData <= 405u))
    {
        thermistorDegreesC = ThermistorData * 0.130;
    }

    else if ((405u < ThermistorData) && (ThermistorData <= 414u))
    {
        thermistorDegreesC = ThermistorData * 0.131;
    }

    else if ((414u < ThermistorData) && (ThermistorData <= 423u))
    {
        thermistorDegreesC = ThermistorData * 0.132;
    }

    else if ((423u < ThermistorData) && (ThermistorData <= 434u))
    {
        thermistorDegreesC = ThermistorData * 0.133;
    }

    else if ((434u < ThermistorData) && (ThermistorData <= 442u))
    {
        thermistorDegreesC = ThermistorData * 0.134;
    }

    else if ((442u < ThermistorData) && (ThermistorData <= 447u))
    {
        thermistorDegreesC = ThermistorData * 0.135;
    }

    else if ((447u < ThermistorData) && (ThermistorData <= 455u))
    {
        thermistorDegreesC = ThermistorData * 0.136;
    }

    else if ((455u < ThermistorData) && (ThermistorData <= 462u))
    {
        thermistorDegreesC = ThermistorData * 0.137;
    }

    else if ((462u < ThermistorData) && (ThermistorData <= 467u))
    {
        thermistorDegreesC = ThermistorData * 0.138;
    }

    else if ((467u < ThermistorData) && (ThermistorData <= 478u))
    {
        thermistorDegreesC = ThermistorData * 0.139;
    }

    else if ((478u < ThermistorData) && (ThermistorData <= 480u))
    {
        thermistorDegreesC = ThermistorData * 0.140;
    }

    else if ((480u < ThermistorData) && (ThermistorData <= 482u))
    {
        thermistorDegreesC = ThermistorData * 0.141;
    }

    else if ((482u < ThermistorData) && (ThermistorData <= 489u))
    {
        thermistorDegreesC = ThermistorData * 0.142;
    }

    else if ((489u < ThermistorData) && (ThermistorData <= 493u))
    {
        thermistorDegreesC = ThermistorData * 0.143;
    }

    else if ((493u < ThermistorData) && (ThermistorData <= 497u))
    {
        thermistorDegreesC = ThermistorData * 0.144;
    }

    else if ((497u < ThermistorData) && (ThermistorData <= 502u))
    {
        thermistorDegreesC = ThermistorData * 0.145;
    }

    else if ((502u < ThermistorData) && (ThermistorData <= 506u))
    {
        thermistorDegreesC = ThermistorData * 0.146;
    }

    else if ((506u < ThermistorData) && (ThermistorData <= 509u))
    {
        thermistorDegreesC = ThermistorData * 0.147;
    }

    else if ((509u < ThermistorData) && (ThermistorData <= 513u))
    {
        thermistorDegreesC = ThermistorData * 0.148;
    }

    else if ((513u < ThermistorData) && (ThermistorData <= 516u))
    {
        thermistorDegreesC = ThermistorData * 0.149;
    }

    else if ((516u < ThermistorData) && (ThermistorData <= 519u))
    {
        thermistorDegreesC = ThermistorData * 0.150;
    }

    else if ((519u < ThermistorData) && (ThermistorData <= 522u))
    {
        thermistorDegreesC = ThermistorData * 0.151;
    }

    else if ((522u < ThermistorData) && (ThermistorData <= 525u))
    {
        thermistorDegreesC = ThermistorData * 0.152;
    }

    else if ((525u < ThermistorData) && (ThermistorData <= 528u))
    {
        thermistorDegreesC = ThermistorData * 0.153;
    }

    else if ((528u < ThermistorData) && (ThermistorData <= 532u))
    {
        thermistorDegreesC = ThermistorData * 0.154;
    }

    else if ((532u < ThermistorData) && (ThermistorData <= 534u))
    {
        thermistorDegreesC = ThermistorData * 0.155;
    }

    else if ((534u < ThermistorData) && (ThermistorData <= 537u))
    {
        thermistorDegreesC = ThermistorData * 0.156;
    }

    else if ((537u < ThermistorData) && (ThermistorData <= 541u))
    {
        thermistorDegreesC = ThermistorData * 0.157;
    }

    else if ((541u < ThermistorData) && (ThermistorData <= 543u))
    {
        thermistorDegreesC = ThermistorData * 0.158;
    }

    else if ((543u < ThermistorData) && (ThermistorData <= 546u))
    {
        thermistorDegreesC = ThermistorData * 0.159;
    }

    else if ((546u < ThermistorData) && (ThermistorData <= 549u))
    {
        thermistorDegreesC = ThermistorData * 0.160;
    }

    else if ((549u < ThermistorData) && (ThermistorData <= 550u))
    {
        thermistorDegreesC = ThermistorData * 0.161;
    }

    else if ((550u < ThermistorData) && (ThermistorData <= 552u))
    {
        thermistorDegreesC = ThermistorData * 0.162;
    }

    else if ((552u < ThermistorData) && (ThermistorData <= 554u))
    {
        thermistorDegreesC = ThermistorData * 0.163;
    }

    else if ((554u < ThermistorData) && (ThermistorData <= 556u))
    {
        thermistorDegreesC = ThermistorData * 0.164;
    }

    else if ((556u < ThermistorData) && (ThermistorData <= 558u))
    {
        thermistorDegreesC = ThermistorData * 0.165;
    }

    else if ((558u < ThermistorData) && (ThermistorData <= 559u))
    {
        thermistorDegreesC = ThermistorData * 0.166;
    }

    else if ((559u < ThermistorData) && (ThermistorData <= 561u))
    {
        thermistorDegreesC = ThermistorData * 0.167;
    }

    else if ((561u < ThermistorData) && (ThermistorData <= 563u))
    {
        thermistorDegreesC = ThermistorData * 0.168;
    }

    else if ((563u < ThermistorData) && (ThermistorData <= 564u))
    {
        thermistorDegreesC = ThermistorData * 0.169;
    }

    else if ((564u < ThermistorData) && (ThermistorData <= 566u))
    {
        thermistorDegreesC = ThermistorData * 0.170;
    }

    else if ((566u < ThermistorData) && (ThermistorData <= 568u))
    {
        thermistorDegreesC = ThermistorData * 0.171;
    }

    else if ((568u < ThermistorData) && (ThermistorData <= 569u))
    {
        thermistorDegreesC = ThermistorData * 0.172;
    }

    else if ((569u < ThermistorData) && (ThermistorData <= 571u))
    {
        thermistorDegreesC = ThermistorData * 0.173;
    }

    else if ((571u < ThermistorData) && (ThermistorData <= 572u))
    {
        thermistorDegreesC = ThermistorData * 0.174;
    }

    else if ((572u < ThermistorData) && (ThermistorData <= 574u))
    {
        thermistorDegreesC = ThermistorData * 0.175;
    }

    else if ((574u < ThermistorData) && (ThermistorData <= 575u))
    {
        thermistorDegreesC = ThermistorData * 0.176;
    }

    else if ((575u < ThermistorData) && (ThermistorData <= 576u))
    {
        thermistorDegreesC = ThermistorData * 0.177;
    }

    else if ((576u < ThermistorData) && (ThermistorData <= 577u))
    {
        thermistorDegreesC = ThermistorData * 0.178;
    }

    else if ((577u < ThermistorData) && (ThermistorData <= 578u))
    {
        thermistorDegreesC = ThermistorData * 0.179;
    }

    else if ((578u < ThermistorData) && (ThermistorData <= 579u))
    {
        thermistorDegreesC = ThermistorData * 0.180;
    }

    else if ((579u < ThermistorData) && (ThermistorData <= 581u))
    {
        thermistorDegreesC = ThermistorData * 0.181;
    }

    else if ((581u < ThermistorData) && (ThermistorData <= 582u))
    {
        thermistorDegreesC = ThermistorData * 0.182;
    }

    else if ((582u < ThermistorData) && (ThermistorData <= 583u))
    {
        thermistorDegreesC = ThermistorData * 0.183;
    }

    else if ((583u < ThermistorData) && (ThermistorData <= 584u))
    {
        thermistorDegreesC = ThermistorData * 0.184;
    }

    else if ((584u < ThermistorData) && (ThermistorData <= 585u))
    {
        thermistorDegreesC = ThermistorData * 0.185;
    }

    else if ((585u < ThermistorData) && (ThermistorData <= 586u))
    {
        thermistorDegreesC = ThermistorData * 0.186;
    }

    else if ((586u < ThermistorData) && (ThermistorData <= 587u))
    {
        thermistorDegreesC = ThermistorData * 0.187;
    }

    else
    {
        thermistorDegreesC = ThermistorData * 0.187;
    }                               /* ThermistorData > 587. */

    return (uint16_t)thermistorDegreesC;

}/* end ConvertThermistorDataToDegreesC() */

/***** EOF for cs_pdk_400_thermistor.c ****************************************/
#endif