/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_sk_vfd.c
 *  Date: 23 February 2015
 *
 *  Author: Peter J. D'Aloisio
 *  Company: ejguk 6fye6 v, LLC
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
#include <stdbool.h>

#endif

#include "cs_pdk_400_sk_vfd.h"
#include "cs_woodmaster_400_user.h"
#include "cs_woodmaster_400_serial_ports.h"
#include "cs_woodmaster_400_configuration.h"

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
                                // Table of CRC values for the high�order byte
static const uint8_t CrcHighByteArray[] =
    {0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
     0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
     0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
     0x00, 0xC1, 0x81, 0x40};

				// Table of CRC values for the low�order byte
static const uint8_t CrcLowByteArray[] =
    {0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
     0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
     0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
     0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
     0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
     0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
     0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
     0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
     0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
     0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
     0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
     0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
     0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
     0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
     0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
     0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
     0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
     0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
     0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
     0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
     0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
     0x41, 0x81, 0x80, 0x40};

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
SkDriveMessageDataUnion_t SkVfdMessageDataUnion;

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/
static uint16_t PercentMtrSpdToThreeDigitHz (const uint8_t PercentMotorSpeed,
                                             const uint16_t MotorRatedFsFrequency);

static uint16_t CalcModbusCrc16 (const uint8_t Data[],
                                 const uint8_t DataLen,
                                 const uint8_t Crc16LSByteTable[],
                                 const uint8_t Crc16MSByteTable[]);

static uint8_t BuildSkVfdWriteRequest (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                       const uint8_t DriveId,
                                       const uint8_t FunctionCode,
                                       const uint16_t FirstRegisterAddress,
                                       const uint16_t NumberOfRegistersToWrite,
                                       const int16_t RegisterData,
                                       const uint8_t RegisterDataByteCount,
                                       const uint8_t Crc16LSByteTable[],
                                       const uint8_t Crc16MSByteTable[]);

static uint8_t SaveDataToSkDriveEeprom (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                        const uint8_t DriveAddr,
                                        const uint8_t Crc16LSByteTable[],
                                        const uint8_t Crc16MSByteTable[]);

static uint8_t SkDriveUsePresetSpeedReg (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                         const uint8_t DrvAddr,
                                         const uint8_t SpeedReg,
                                         const uint8_t Crc16LSByteTable[],
                                         const uint8_t Crc16MSByteTable[]);

static uint8_t SkMotorStartStopCtrl(SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                    const uint8_t VfdId, const bool CtrlCommand,
                                    const uint8_t Crc16LSByteTable[],
                                    const uint8_t Crc16MSByteTable[]);

static uint8_t SkSetMotorPercentSpeed (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                       const uint8_t VfdAddr,
                                       const uint8_t MotorDesiredPercentSpeed,
                                       const uint16_t MotorRatedFullSpeedFrequency,
                                       const uint16_t SpeedRegAddress,
                                       const uint8_t Crc16LSByteTable[],
                                       const uint8_t Crc16MSByteTable[]);

static uint8_t SkMotorRampHoldReleaseCtrl (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                           const uint8_t VfdAddr, const bool CtrlCommand,
                                           const uint8_t Crc16LSByteTable[],
                                           const uint8_t Crc16MSByteTable[]);

static uint8_t SkRampTheMotorSpeed (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                    const uint8_t VfdAddr, const bool DirectionCommand,
                                    const uint8_t MotorMinOperatingPercentSpeed,
                                    const uint8_t MotorMaxOperatingPercentSpeed,
                                    const uint16_t MotorRatedFullSpeedFrequency,
                                    const uint8_t Crc16LSByteTable[],
                                    const uint8_t Crc16MSByteTable[]);

static uint8_t ConfigureTheSkDrive (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                    const uint8_t DriveId,
                                    const uint16_t MotorRatedFullLoadCurrent,
                                    const uint16_t MotorRatedFullLoadRpm,
                                    const uint16_t MotorRatedVoltage,
                                    const uint16_t MotorRatedFrequency,
                                    const uint16_t MotorRatedPowerFactor,
                                    const uint8_t Crc16LSByteTable[],
                                    const uint8_t Crc16MSByteTable[]);

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        None
 *
 * Description:     None
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    None
 ******************************************************************************/
uint8_t AdjustVfdMotorOperation (const uint8_t MotorDriveId, const uint8_t Command,
                                 const uint8_t PercentSpeedSetting,
                                 const uint16_t MotorRatedFullSpeedFrequency,
                                 const uint8_t MotorMinPercentSpeedLimit,
                                 const uint8_t MotorMaxPercentSpeedLimit)
{
    uint8_t functionFaultStatus = NO_ADJ_VFD_MOTOR_FUNCTION_FAULTS;

    if ((MotorDriveId >= LOWEST_VFD_DRIVE_ADDR) && (MotorDriveId <= HIGHEST_VFD_DRIVE_ADDR))
    {
        switch (Command)
        {
            case MOTOR_STOP :

                functionFaultStatus = SkMotorStartStopCtrl(&SkVfdMessageDataUnion,
                                                    MotorDriveId, STOP_MOTOR,
                                                    CrcLowByteArray,
                                                    CrcHighByteArray);
            break;

            case MOTOR_RUN :

                functionFaultStatus = SkMotorStartStopCtrl(&SkVfdMessageDataUnion,
                                                    MotorDriveId, RUN_MOTOR,
                                                    CrcLowByteArray,
                                                    CrcHighByteArray);
            break;

            case SET_MOTOR_SPEED :

                if ((PercentSpeedSetting >= MotorMinPercentSpeedLimit) &&
                    (PercentSpeedSetting <= MotorMaxPercentSpeedLimit))
                {
                    functionFaultStatus = SkSetMotorPercentSpeed (&SkVfdMessageDataUnion,
                                          MotorDriveId, PercentSpeedSetting,
                                          MotorRatedFullSpeedFrequency,
                                          PRESET_SPEED_TWO_REG, CrcLowByteArray,
                                          CrcHighByteArray);
                }
                else
                {
                    functionFaultStatus = BAD_ADJ_VFD_MOTOR_FUNCT_SPEED_SETTING;
                }

            break;

            case RAMP_MOTOR_SPEED_UPWARD :

                functionFaultStatus = SkRampTheMotorSpeed (&SkVfdMessageDataUnion,
                                    MotorDriveId, RAMP_MOTOR_SPEED_UP,
                                    MotorMinPercentSpeedLimit,
                                    MotorMaxPercentSpeedLimit,
                                    MotorRatedFullSpeedFrequency,
                                    CrcLowByteArray, CrcHighByteArray);
            break;

            case RAMP_MOTOR_SPEED_DOWNWARD :

                functionFaultStatus = SkRampTheMotorSpeed (&SkVfdMessageDataUnion,
                                    MotorDriveId, RAMP_MOTOR_SPEED_DN,
                                    MotorMinPercentSpeedLimit,
                                    MotorMaxPercentSpeedLimit,
                                    MotorRatedFullSpeedFrequency,
                                    CrcLowByteArray, CrcHighByteArray);
            break;

            case HOLD_MOTOR_SPEED :

                functionFaultStatus = SkMotorRampHoldReleaseCtrl (&SkVfdMessageDataUnion,
                                            MotorDriveId, MOTOR_RAMP_HOLD,
                                            CrcLowByteArray, CrcHighByteArray);
            break;

            default :

            functionFaultStatus = BAD_ADJ_VFD_MOTOR_FUNCT_COMMAND;

            break;
        }
    }

    else
    {
        functionFaultStatus = BAD_ADJ_VFD_MOTOR_FUNCT_DRIVE_ID;
    }

    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        static uint16_t PercentMtrSpdToThreeDigitHz
 *                                          (const uint8_t PercentMotorSpeed,
 *                                           const uint16_t MotorRatedFsFrequency)
 *
 * Description:     PercentMtrSpdToThreeDigitHz() converts the three-digit
 *                  integer percent motor speed argument (0 - 100) to a
 *                  three-digit integer motor frequency in Hz, such that the
 *                  LSDigit of this integer result can be interpreted by the
 *                  Emerson SK series VFD as tenths of a Hz.
 *
 *
 * Dependencies:    None
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies, in integer percent, a motor
 *                  speed that ranges from 0 to 100 that will be converted to
 *                  an appropriate motor operating frequency and an argument
 *                  that specifies, in integer Hz., a three-digit value that is
 *                  interpreted as the frequency less the decimal point
 *                  (typically 500 for 50.0 Hz or 600 for 60 Hz.) at which the
 *                  motor is rated to run at maximum speed.
 *
 * Output:          A three-digit integer motor operating frequency such that
 *                  the LSDigit represents tenths of a Hz.
 *
 * Side Effects:    None
 ******************************************************************************/
static uint16_t PercentMtrSpdToThreeDigitHz (const uint8_t PercentMotorSpeed,
                                             const uint16_t MotorRatedFsFrequency)
{
    return (uint16_t)((MotorRatedFsFrequency * (PercentMotorSpeed / 100.0)));
}

/*******************************************************************************
 * Function:        static uint16_t CalcModbusCrc16 (const uint8_t Data[],
 *                                                   const uint8_t DataLen,
 *                                            const uint8_t Crc16LSByteTable[],
 *                                            const uint8_t Crc16MSByteTable[])
 *
 * Description:     CalcModbusCrc16() determines the MODBUS specified CRC16
 *                  checksum for the data contained within the construct that
 *                  is specified by the Data[] argument.
 *                  The returned CRC16 checksum value is in LSByte:MSByte order.
 *
 * Dependencies:    CrcLowByteArray[], CrcHighByteArray[]
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct
 *                  that contains the data upon which the CRC16 checksum will
 *                  be calculated, an argument that specifies the length of the
 *                  construct that was specified in the first argument and two
 *                  arguments that specifies the address of data arrays that
 *                  contain the low and high bytes of pre-calculated CRC16
 *                  checksums.
 *
 * Output:          The CRC16 checksum value for the Data[] argument.
 *
 * Side Effects:    None
 ******************************************************************************/
static uint16_t CalcModbusCrc16 (const uint8_t Data[],
                                 const uint8_t DataLen,
                                 const uint8_t Crc16LSByteTable[],
                                 const uint8_t Crc16MSByteTable[])
{
    uint8_t i;                          /* Index into CRC lookup table. */
    uint8_t j;                          /* Index into the data array. */
    
    uint8_t crcHiByte = 0xFF;           /* Initialized high byte of the CRC. */
    uint8_t crcLoByte = 0xFF;           /* Initialized low byte of the CRC. */

    for (j = 0; j < DataLen; j++)
    {
        i = crcLoByte ^ Data[j];
        crcLoByte = crcHiByte ^ Crc16MSByteTable[i];
        crcHiByte = Crc16LSByteTable[i];
    }

    return ((((uint16_t) crcHiByte) << 8) | ((uint16_t) crcLoByte));
}

/*******************************************************************************
 * Function:        static uint8_t BuildSkVfdWriteRequest
 *                      (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                       const uint8_t DriveId,
 *                       const uint8_t FunctionCode,
 *                       const uint16_t FirstRegisterAddress,
 *                       const uint16_t NumberOfRegistersToWrite,
 *                       const int16_t RegisterData,
 *                       const uint8_t RegisterDataByteCount,
 *                       const uint8_t Crc16LSByteTable[],
 *                       const uint8_t Crc16MSByteTable[])
 *
 * Description:     BuildSkVfdWriteRequest() properly places the arguments
 *                  passed as DriveId, FunctionCode, FirstRegisterAddress and
 *                  RegisterData into the SkMessageDataUnion and then using a
 *                  helper function, in conjunction with the
 *                  Crc16LowByteTable[] and Crc16HighByteTable[] data tables,
 *                  calculates and places an appropriate CRC16 checksum of the
 *                  data at the appropriate location in the SkMessageDataUnion.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, CalcModbusCrc16(), Crc16LowByteTable[]
 *                  and Crc16HighByteTable[].
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD Write Request will be placed
 *                  and several arguments that specify the data that is to be
 *                  incorporated into the constructed SK VFD Write Request.
 *                  Also, two arguments that specify the address of data arrays
 *                  that will be used in order to calculate a CRC16 checksum
 *                  that will then be incorporated into the constructed SK VFD
 *                  Write Request.
 *
 * Output:          The BuildSkVfdWriteRequest() function error status.
 *
 * Side Effects:    SkMessageDataUnion will contain the constructed SK VFD
 *                  Write request.
 ******************************************************************************/
static uint8_t BuildSkVfdWriteRequest (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                       const uint8_t DriveId,
                                       const uint8_t FunctionCode,
                                       const uint16_t FirstRegisterAddress,
                                       const uint16_t NumberOfRegistersToWrite,
                                       const int16_t RegisterData,
                                       const uint8_t RegisterDataByteCount,
                                       const uint8_t Crc16LSByteTable[],
                                       const uint8_t Crc16MSByteTable[])
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;

    uint16_t checksum;

    uint16_t u16temp;

    if (DriveId > 247)
    {
        functionFaultStatus =  VFD_ADDR_OUT_OF_RANGE;
                                        /* Range check the slave address
                                         * value. */
    }

    switch (FunctionCode)
    {
        case RD_MULT_16BIT_REGS :

            functionFaultStatus = VFD_FUNCT_CODE_NOT_SUPPORTED;
                                        /* This firmware does not currently
                                         * support this function code. */
            break;
/*----------------------------------------------------------------------------*/
        case WR_SINGLE_REG :            /* Place the command data into the
                                         * data buffer. */

            VfdMssgDataUnion->driveFrameData.vfdAddress = DriveId;

            VfdMssgDataUnion->driveFrameData.functionCode = FunctionCode;

            u16temp = ((FirstRegisterAddress - 1) << 8);
            u16temp = u16temp | ((FirstRegisterAddress - 1) >> 8);
                                        /* Swap the MSByte and LSByte. The VFD
                                         * increments the received register
                                         * address, so we decrement it here so
                                         * that it will be correct once the VFD
                                         * receives and increments it. */

            VfdMssgDataUnion->driveFrameData.driveRegisterDataUnion.
                                               masterSingleWriteRequest.
                                               registerAddress = u16temp;

            u16temp = (RegisterData << 8);
            u16temp = u16temp | (RegisterData >> 8);
                                        /* Swap the MSByte and LSByte. */

            VfdMssgDataUnion->driveFrameData.driveRegisterDataUnion.
                                                masterSingleWriteRequest.
                                               registerData = u16temp;

            checksum = CalcModbusCrc16 (VfdMssgDataUnion->DriveDataPacket, 6,
                                        Crc16LSByteTable, Crc16MSByteTable);
                                        /* Calculate the CRC-16 checksum
                                         * for the six bytes of
                                         * DriveDataPacket. */

            VfdMssgDataUnion->driveFrameData.driveRegisterDataUnion.
                                               masterSingleWriteRequest.
                                               crc16CheckSum = checksum;

            break;
/*----------------------------------------------------------------------------*/
        case WR_MULT_16BIT_REGS :

            functionFaultStatus = VFD_FUNCT_CODE_NOT_SUPPORTED;
                                        /* This firmware does not currently
                                         * support this function code. */
            break;
/*----------------------------------------------------------------------------*/
        case RD_WR_MULT_16BIT_REGS :

            functionFaultStatus = VFD_FUNCT_CODE_NOT_SUPPORTED;
                                        /* This firmware does not currently
                                         * support this function code. */
            break;
/*----------------------------------------------------------------------------*/
        default :

            functionFaultStatus = INVALID_VFD_FUNCT_CODE;
                                        /* Invalid function code value. */
            break;
    }//end switch

    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        static uint8_t SaveDataToSkDriveEeprom
 *                      (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                       const uint8_t DriveAddr,
 *                       const uint8_t Crc16LSByteTable[],
 *                       const uint8_t Crc16MSByteTable[])
 *
 * Description:     SaveDataToSkDriveEeprom() through the use of helper
 *                  functions commands the VFD to save its configuration data to
 *                  VFD EEPROM upon a VFD reset cycle and then it commands the
 *                  VFD to execute a reset cycle.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, cs_pdk_400_serial_ports.h,
 *                  BuildSkVfdWriteRequest() and TransmitRS485DriveDataPacket.
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD save command data packet will
 *                  be placed prior to its being serially transmitted to the
 *                  VFD, an argument that specifies the address of the VFD to
 *                  which the command is being sent and two arguments that
 *                  specify the address of data arrays that will be used by a
 *                  helper function in order to calculate a CRC16 checksum that
 *                  will then be incorporated into the constructed SK VFD save
 *                  command data packet.
 *
 * Output:          The SaveDataToSkDriveEeprom() function error status.
 *
 * Side Effects:    SkMssgDataUnion will contain the constructed SK VFD command
 *                  data packet which will have already been serially
 *                  transmitted to the VFD.
 ******************************************************************************/
static uint8_t SaveDataToSkDriveEeprom (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                        const uint8_t DriveAddr,
                                        const uint8_t Crc16LSByteTable[],
                                        const uint8_t Crc16MSByteTable[])
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;

    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveAddr,
                                   WR_SINGLE_REG, SAVE_DATA_UPON_RESET_REG,
                                   WRITE_SINGLE_DATA_PACKET_BYTE_LEN,
                                   SAVE_DRIVE_DATA, SINGLE_REGISTER_BYTE_LEN,
                                   Crc16LSByteTable, Crc16MSByteTable);
					/* Command the VFD to save its
                                         * configuration data to the drive's
                                         * EEPROM upon a drive reset cycle. */
    if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
    {
        functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                             WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

        __delay_ms(250);                /* 250ms slave response delay. */
    }

    if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
    {
        functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion,
                                        DriveAddr,
                                        WR_SINGLE_REG, USER_TRIP_REG,
                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN,
                                        RESET_DRIVE, SINGLE_REGISTER_BYTE_LEN,
                                        Crc16LSByteTable, Crc16MSByteTable);
                                        /* Reset the drive in order to affect
                                         * the saving of the drive configuration
                                         * data to the drive's EEPROM. */
    }
    
    if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
    {
        functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

        __delay_ms(255);                /* 250ms slave response delay. */

        /*__delay_ms(500);
        __delay_ms(500);
        __delay_ms(500);
        __delay_ms(500);
        __delay_ms(500);
        __delay_ms(500);                /* Allow the drive three seconds to
                                         * save the data. */
    }

    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        static uint8_t SkDriveUsePresetSpeedReg (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                                              const uint8_t DrvAddr,
 *                                              const uint8_t SpeedReg,
 *                                              const uint8_t Crc16LSByteTable[],
 *                                              const uint8_t Crc16MSByteTable[])
 *
 * Description:     SkDriveUsePresetSpeedReg() through the use of helper
 *                  functions commands the VFD to a specified register as its
 *                  motor speed reference.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, cs_pdk_400_serial_ports.h,
 *                  BuildSkVfdWriteRequest() and TransmitRS485DriveDataPacket.
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD save command data packet will
 *                  be placed prior to its being serially transmitted to the
 *                  VFD, an argument that specifies the address of the VFD to
 *                  which the command is being sent, an argument that specifies
 *                  the desired VFD preset speed register and two arguments
 *                  that specify the address of data arrays that will be used by
 *                  a helper function in order to calculate a CRC16 checksum
 *                  that will then be incorporated into the constructed SK VFD
 *                  command data packet.
 *
 * Output:          The SkDriveUsePresetSpeedReg() function error status.
 *
 * Side Effects:    SkVfdMssgDataUnion will contain the constructed SK VFD
 *                  command data packet which will have already been serially
 *                  transmitted to the VFD.
 ******************************************************************************/
static uint8_t SkDriveUsePresetSpeedReg (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                         const uint8_t DrvAddr,
                                         const uint8_t SpeedReg,
                                         const uint8_t Crc16LSByteTable[],
                                         const uint8_t Crc16MSByteTable[])
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;

    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DrvAddr,
                                    WR_SINGLE_REG, PRESET_SPEED_SELECTOR_REG,
                                    WRITE_SINGLE_DATA_PACKET_BYTE_LEN,
                                    SpeedReg, SINGLE_REGISTER_BYTE_LEN,
                                    Crc16LSByteTable, Crc16MSByteTable);
					/* Configure the drive to use preset
                                         * speed register number 'SpeedReg' for
                                         * associated motor speed value. */

    if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
    {
        functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                             WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

        __delay_ms(255);                /* 250ms slave response delay. */
    }

    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        static uint8_t SkMotorStartStopCtrl(SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                                  const uint8_t VfdId, const bool CtrlCommand,
 *                                  const uint8_t Crc16LSByteTable[],
 *                                  const uint8_t Crc16MSByteTable[])
 *
 * Description:     SkMotorStartStopCtrl() through the use of helper functions
 *                  commands the VFD to start or stop a motor.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, cs_pdk_400_serial_ports.h,
 *                  BuildSkVfdWriteRequest() and TransmitRS485DriveDataPacket.
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD save command data packet will
 *                  be placed prior to its being serially transmitted to the
 *                  VFD, an argument that specifies the address of the VFD to
 *                  which the command is being sent, an argument that specifies
 *                  the desired motor start or stop action and two arguments
 *                  that specify the address of data arrays that will be used by
 *                  a helper function in order to calculate a CRC16 checksum
 *                  that will then be incorporated into the constructed SK VFD
 *                  command data packet.
 *
 * Output:          The MotorStartStopCtrl() function error status.
 *
 * Side Effects:    SkVfdMessageDataUnion will contain the constructed SK VFD
 *                  command data packet which will have already been serially
 *                  transmitted to the VFD.
 ******************************************************************************/
static uint8_t SkMotorStartStopCtrl(SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                    const uint8_t VfdId, const bool CtrlCommand,
                                    const uint8_t Crc16LSByteTable[],
                                    const uint8_t Crc16MSByteTable[])
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;
    
    switch (CtrlCommand)
    {
        case STOP_MOTOR :
            
            functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion,
                            VfdId, WR_SINGLE_REG,
                            DRIVE_CTRL_WORD_REG,
                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN, ENABLE_DRIVE,
                            SINGLE_REGISTER_BYTE_LEN, Crc16LSByteTable,
                            Crc16MSByteTable);
                                        /* Set the control word to stop the
                                         * motor. */
            break;

        case RUN_MOTOR :
            
            functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion,
                            VfdId, WR_SINGLE_REG,
                            DRIVE_CTRL_WORD_REG,
                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN, RUN_FORWARD,
                            SINGLE_REGISTER_BYTE_LEN, Crc16LSByteTable,
                            Crc16MSByteTable);
                                        /* Set the control word to run the
                                         * motor in the forward direction. */
            break;

        default :

            functionFaultStatus = INVALID_VFD_MOTOR_COMMAND;

            break;
    }
    
    if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
    {
        functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                             WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

        __delay_ms(255);                /* 250ms slave response delay. */
    }

    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        static uint8_t SkSetMotorPercentSpeed (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                  const uint8_t VfdAddr, const uint8_t MotorDesiredPercentSpeed,
 *                  const uint8_t MotorMaxOperatingPercentSpeed,
 *                  const unsigned int SpeedRegAddress,
 *                  const uint8_t Crc16LSByteTable[],
 *                  const uint8_t Crc16MSByteTable[])
 *
 * Description:     SkSetMotorPercentSpeed() through the use of helper functions
 *                  converts a percent motor speed to 0 - 60 Hz and transmits
 *                  this result over MODBUS serial data link to the VFD.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, cs_pdk_400_serial_ports.h,
 *                  PercentMtrSpdToThreeDigitHz(), BuildSkVfdWriteRequest()
 *                  and TransmitRS485DriveDataPacket.
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD save command data packet will
 *                  be placed prior to its being serially transmitted to the
 *                  VFD, an argument that specifies the address of the VFD to
 *                  which the command is being sent, an argument that specifies
 *                  the desired motor percent speed as a percent of full rated
 *                  motor speed, an argument that specifies the motor's rated
 *                  full speed frequency, an argument that specifies to which
 *                  VFD data register the speed in Hz will be written and two
 *                  arguments that specify the address of data arrays that will
 *                  be used by a helper function in order to calculate a CRC16
 *                  checksum that will then be incorporated into the constructed
 *                  SK VFD command data packet.
 *
 * Output:          The SetMotorPercentSpeed() function error status.
 *
 * Side Effects:    VfdMessageDataUnion will contain the constructed SK VFD
 *                  command data packet which will have already been serially
 *                  transmitted to the VFD.
 ******************************************************************************/
static uint8_t SkSetMotorPercentSpeed (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                       const uint8_t VfdAddr,
                                       const uint8_t MotorDesiredPercentSpeed,
                                       const uint16_t MotorRatedFullSpeedFrequency,
                                       const uint16_t SpeedRegAddress,
                                       const uint8_t Crc16LSByteTable[],
                                       const uint8_t Crc16MSByteTable[])
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;
    
    uint16_t Hz;

    if (MotorDesiredPercentSpeed <= 100u) /* Range check the percent argument. */
    {
        Hz = PercentMtrSpdToThreeDigitHz (MotorDesiredPercentSpeed,
                                          MotorRatedFullSpeedFrequency);
#if (0)
        Hz = (uint16_t) (((((float) Percent)/100.0) * 60.0) * 10);
#endif
                                        /* Convert the motor speed percent to
                                         * a Hz value that ranges from 0 - 60Hz.
                                         * The result of this calculation
                                         * will be a 3-digit integer whose
                                         * least significant digit will be
                                         * interpreted by the motor drive as
                                         * tenths of a Hz. */
        
        functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion,
                                            VfdAddr, WR_SINGLE_REG,
                                            SpeedRegAddress,
                                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN,
                                            Hz, SINGLE_REGISTER_BYTE_LEN,
                                            Crc16LSByteTable, Crc16MSByteTable);
                                        /* Set the drive's preset speed number
                                         * two register to the desired motor
                                         * speed (Hz). */

        if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
        {
            functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                             WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

            __delay_ms(255);                /* 250ms slave response delay. */
        }
    }

    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        static uint8_t SkMotorRampHoldReleaseCtrl (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                              const uint8_t VfdAddr, const bool CtrlCommand,
 *                              const uint8_t Crc16LSByteTable[],
 *                              const uint8_t Crc16MSByteTable[])
 *
 * Description:     SkMotorRampHoldReleaseCtrl() through the use of helper
 *                  functions holds or releases motor ramping as done by the
 *                  variable speed drive if the actual motor speed output of the
 *                  drive is different from the value of the motor speed
 *                  command.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, cs_pdk_400_serial_ports.h,
 *                  BuildSkVfdWriteRequest() and TransmitRS485DriveDataPacket.
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD configuration command data
 *                  packets will be placed prior to its being serially
 *                  transmitted to the VFD, an argument that specifies the
 *                  address of the VFD to which the command is being sent, an
 *                  argument that specifies whether to hold or release motor
 *                  speed ramping and two arguments that specify the address of
 *                  data arrays that will be used by a helper function in order
 *                  to calculate a CRC16 checksum that will then be incorporated
 *                  into the constructed SK VFD command data packet.
 *
 * Output:          The SkMotorRampHoldReleaseCtrl() function error status.
 *
 * Side Effects:    VfdMessageDataUnion will contain the constructed SK VFD
 *                  command data packet which will have already been serially
 *                  transmitted to the VFD.
 ******************************************************************************/
static uint8_t SkMotorRampHoldReleaseCtrl (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                           const uint8_t VfdAddr, const bool CtrlCommand,
                                           const uint8_t Crc16LSByteTable[],
                                           const uint8_t Crc16MSByteTable[])
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;
    
    switch (CtrlCommand)
    {
        case MOTOR_RAMP_HOLD :

            functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion,
                            VfdAddr, WR_SINGLE_REG,
                            RAMP_HOLD_REG,
                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN, ENABLE_RAMP_HOLD,
                            SINGLE_REGISTER_BYTE_LEN, Crc16LSByteTable,
                            Crc16MSByteTable);
                                        /* Set the ramp hold register to stop
                                         * motor speed ramping and hold the
                                         * motor speed steady. (User save.)
                                         * Pr 2.03. */
            break;

        case MOTOR_RAMP_RELEASE :

            functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion,
                            VfdAddr, WR_SINGLE_REG,
                            RAMP_HOLD_REG,
                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN,
                            DISABLE_RAMP_HOLD, SINGLE_REGISTER_BYTE_LEN,
                            Crc16LSByteTable, Crc16MSByteTable);
                                        /* Set the ramp hold register to allow
                                         * motor speed ramping. (User save.)
                                         * Pr 2.03. */
            break;

        default :

            functionFaultStatus = INVALID_VFD_MOTOR_COMMAND;

            break;
    }
    
    if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
    {
        functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

        __delay_ms(255);                    /* 250ms slave response delay. */
    }

    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        static uint8_t SkRampTheMotorSpeed (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                          const uint8_t VfdAddr, const bool DirectionCommand,
 *                          const uint8_t MotorMinOperatingPercentSpeed,
 *                          const uint8_t MotorMaxOperatingPercentSpeed,
 *                          const uint8_t Crc16LSByteTable[],
 *                          const uint8_t Crc16MSByteTable[])
 *
 * Description:     SkRampTheMotorSpeed() through the use of helper functions
 *                  causes the specified motor to either ramp up to a specified
 *                  maximum speed or ramp down to a specified minimum speed.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, cs_pdk_400_serial_ports.h,
 *                  BuildSkVfdWriteRequest() and TransmitRS485DriveDataPacket.
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD configuration command data
 *                  packets will be placed prior to its being serially
 *                  transmitted to the VFD, an argument that specifies the
 *                  address of the VFD to which the command is being sent, an
 *                  argument that specifies whether to ramp the motor speed
 *                  upward or downward, an argument that specifies the desired
 *                  minimum motor percent speed (percent of rated full speed),
 *                  an argument that specifies the desired maximum motor percent
 *                  speed (percent of rated full speed),  an argument that
 *                  specifies the motor's rated full speed frequency,and two
 *                  arguments that specify the address of data arrays that will
 *                  be used by a helper function in order to calculate a CRC16
 *                  checksum that will then be incorporated into the constructed
 *                  SK VFD command data packet.
 *
 * Output:          The SkRampTheMotorSpeed() function error status.
 *
 * Side Effects:    VfdMessageDataUnion will contain the constructed SK VFD
 *                  command data packet which will have already been serially
 *                  transmitted to the VFD.
 ******************************************************************************/
static uint8_t SkRampTheMotorSpeed (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                    const uint8_t VfdAddr, const bool DirectionCommand,
                                    const uint8_t MotorMinOperatingPercentSpeed,
                                    const uint8_t MotorMaxOperatingPercentSpeed,
                                    const uint16_t MotorRatedFullSpeedFrequency,
                                    const uint8_t Crc16LSByteTable[],
                                    const uint8_t Crc16MSByteTable[])
{

    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;

    switch (DirectionCommand)
    {
        case RAMP_MOTOR_SPEED_DN :

            functionFaultStatus = SkMotorRampHoldReleaseCtrl (VfdMssgDataUnion,
                                                VfdAddr, MOTOR_RAMP_RELEASE,
                                                Crc16LSByteTable,
                                                Crc16MSByteTable);
                                        /* Allow the motor speed to ramp. */

            functionFaultStatus = SkSetMotorPercentSpeed (VfdMssgDataUnion,
                                        VfdAddr, MotorMinOperatingPercentSpeed,
                                        MotorRatedFullSpeedFrequency,
                                        PRESET_SPEED_TWO_REG, Crc16LSByteTable,
                                        Crc16MSByteTable);
                                        /* Setting the preset speed two
                                         * register to
                                         * MotorMinOperatingPercentSpeed will
                                         * cause the motor speed to ramp
                                         * downward if the actual motor speed
                                         * output of the drive is higher than
                                         * the value of
                                         * MotorMinOperatingPercentSpeed.*/
            break;

        case RAMP_MOTOR_SPEED_UP :

            functionFaultStatus = SkMotorRampHoldReleaseCtrl (VfdMssgDataUnion,
                                                VfdAddr, MOTOR_RAMP_RELEASE,
                                                Crc16LSByteTable,
                                                Crc16MSByteTable);
                                        /* Allow the motor speed to ramp. */

            functionFaultStatus = SkSetMotorPercentSpeed (VfdMssgDataUnion,
                                        VfdAddr, MotorMaxOperatingPercentSpeed,
                                        MotorRatedFullSpeedFrequency,
                                        PRESET_SPEED_TWO_REG, Crc16LSByteTable,
                                        Crc16MSByteTable);
                                        /* Setting the preset speed two
                                         * register to
                                         * MotorMaxOperatingPercentSpeed will
                                         * cause the motor speed to ramp
                                         * upward if the actual motor speed
                                         * output of the drive is lower than
                                         * the value of
                                         * MotorMaxOperatingPercentSpeed.*/
            break;

        default :

            functionFaultStatus = INVALID_VFD_MOTOR_COMMAND;

            break;
    }

    if (functionFaultStatus == NO_FW_VFD_FUNCTION_FAULTS)
    {
        functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                            WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

        __delay_ms(255);                    /* 250ms slave response delay. */
    }

    return functionFaultStatus;
}


/*******************************************************************************
 * Function:        static uint8_t ConfigureTheSkDrive (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
 *                                          const uint8_t DriveId,
 *                                          const uint16_t MotorRatedCurrent,
 *                                          const uint16_t MotorRatedFullLoadRpm,
 *                                          const uint16_t MotorRatedVoltage,
 *                                          const uint16_t MotorRatedFrequency,
 *                                          const uint16_t MotorRatedPowerFactor,
 *                                          const uint8_t Crc16LSByteTable[],
 *                                          const uint8_t Crc16MSByteTable[])
 *
 * Description:     ConfigureTheSkDrive() through the use of helper functions
 *                  configures a specified Emerson Control Techniques variable
 *                  speed drive by writing data to the drive via a serial bus.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, cs_pdk_400_serial_ports.h,
 *                  BuildSkVfdWriteRequest() and TransmitRS485DriveDataPacket.
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the construct into
 *                  which the constructed SK VFD configuration command data
 *                  packets will be placed prior to its being serially
 *                  transmitted to the VFD, an argument that specifies the
 *                  address of the VFD to which the command is being sent, motor
 *                  specific arguments that specify the motor's rated full load
 *                  current, full load RPM, voltage rating, frequency rating and
 *                  power factor and two arguments that specify the address of
 *                  data arrays that will be used by a helper function in order
 *                  to calculate a CRC16 checksum that will then be incorporated
 *                  into the constructed SK VFD command data packet.
 *
 * Output:          The ConfigureTheSkDrive() function error status.
 *
 * Side Effects:    VfdMessageDataUnion will contain the constructed SK VFD
 *                  command data packet which will have already been serially
 *                  transmitted to the VFD.
 ******************************************************************************/
static uint8_t ConfigureTheSkDrive (SkDriveMessageDataUnion_t * const VfdMssgDataUnion,
                                    const uint8_t DriveId,
                                    const uint16_t MotorRatedFullLoadCurrent,
                                    const uint16_t MotorRatedFullLoadRpm,
                                    const uint16_t MotorRatedVoltage,
                                    const uint16_t MotorRatedFrequency,
                                    const uint16_t MotorRatedPowerFactor,
                                    const uint8_t Crc16LSByteTable[],
                                    const uint8_t Crc16MSByteTable[])
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DRIVE_CTRL_WORD_REG,
                                                  ONE_REGISTER, DISABLE_DRIVE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                        /* Set the drive control word to
                                         * disable the VFD. Pr 6.42. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  CTRL_WORD_ENABLE_REG,
                                                  ONE_REGISTER,
                                                  ENABLE_CTRL_WORD,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Enable the control word. Pr 6.43. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  START_STOP_LOGIC_SELECT_REG,
                                                  ONE_REGISTER,
                                                  TERMINAL_B4_IS_ENABLE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Enable the control word. Actioned
                                          * upon drive reset.
                                          * (User save.) Pr 6.04. */
    
    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);
    
    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DRIVE_CONFIGURATION_REG,
                                                  ONE_REGISTER,
                                                  USE_PRESET_SPEEDS,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive to use the four
                                          * preset speed registers for motor
                                          * speed settings. Actioned upon drive
                                          * reset. (User save.)
                                          * Pr 11.27. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*============================================================================*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_ONE_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_1_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 1 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.11. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_TWO_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_2_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 2 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.12. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_THREE_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_3_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 3 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.13. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_FOUR_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_4_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 4 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.14. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_FIVE_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_5_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 5 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.15. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
    ClrWdt();
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_SIX_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_6_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 6 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.16. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_SEVEN_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_7_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 7 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.17. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  ACCELERATION_RATE_EIGHT_REG,
                                                  ONE_REGISTER,
                                                  ACCELERATION_8_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's acceleration
                                          * rate 8 register for a particular
                                          * acceleration rate. (User save.)
                                          * Pr 2.18. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*============================================================================*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_ONE_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_1_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 1 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.21. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_TWO_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_2_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 2 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.22. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_THREE_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_3_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 3 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.23. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_FOUR_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_4_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 4 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.24. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
    ClrWdt();
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_FIVE_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_5_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 5 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.25. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_SIX_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_6_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 6 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.26. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_SEVEN_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_7_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 7 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.27. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DECELERATION_RATE_EIGHT_REG,
                                                  ONE_REGISTER,
                                                  DECELERATION_8_RATE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive's deceleration
                                          * rate 8 register for a particular
                                          * deceleration rate. (User save.)
                                          * Pr 2.28. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*============================================================================*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  MOTOR_RATED_FREQUENCY_REG,
                                                  ONE_REGISTER,
                                                  MotorRatedFrequency,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive for the motor
                                          * rated power factor. (User save.)
                                          * Pr 5.06. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  MOTOR_RATED_CURRENT_REG,
                                                  ONE_REGISTER,
                                                  MotorRatedFullLoadCurrent,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive for the motor
                                          * rated current. (User save.)
                                          * Pr 5.07. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */
    
    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  MOTOR_RATED_FULL_LOAD_RPM_REG,
                                                  ONE_REGISTER,
                                                  MotorRatedFullLoadRpm,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive for the motor
                                          * rated full load RPM. (User save.)
                                          * Pr 5.08. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */
    
    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
    ClrWdt();
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  MOTOR_RATED_VOLTAGE_REG,
                                                  ONE_REGISTER,
                                                  MotorRatedVoltage,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive for the motor
                                          * rated voltage. (User save.)
                                          * Pr 5.09. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  MOTOR_RATED_POWER_FACTOR_REG,
                                                  ONE_REGISTER,
                                                  MotorRatedPowerFactor,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                         /* Configure the drive for the motor
                                          * rated power factor. (User save.)
                                          * Pr 5.10. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */

    functionFaultStatus = SaveDataToSkDriveEeprom (VfdMssgDataUnion,
                                                   DriveId,
                                                   Crc16LSByteTable,
                                                   Crc16MSByteTable);
                                         /* SaveDataToSkDriveEeprom() also
                                          * initiates a drive reset. */
/*============================================================================*/
    functionFaultStatus = SkDriveUsePresetSpeedReg (VfdMssgDataUnion, DriveId,
                                                    SELECT_PRESET_SPEED_TWO,
                                                    Crc16LSByteTable,
                                                    Crc16MSByteTable);
                                         /* Configure the drive to use preset
                                          * speed register two. (User save.)
                                          * Pr 1.15. */
/*----------------------------------------------------------------------------*/
    functionFaultStatus = BuildSkVfdWriteRequest (VfdMssgDataUnion, DriveId,
                                                  WR_SINGLE_REG,
                                                  DRIVE_CTRL_WORD_REG,
                                                  ONE_REGISTER, ENABLE_DRIVE,
                                                  SINGLE_REGISTER_BYTE_LEN,
                                                  Crc16LSByteTable,
                                                  Crc16MSByteTable);
                                        /* Set the drive control word to
                                         * enable the VFD. Pr 6.42. */

    functionFaultStatus = TransmitRS485DriveDataPacket (VfdMssgDataUnion->DriveDataPacket,
                                                        WRITE_SINGLE_DATA_PACKET_BYTE_LEN);

    __delay_ms(255);                    /* 250ms slave response delay. */
/*----------------------------------------------------------------------------*/
    ClrWdt();
    
    return functionFaultStatus;
}

/*******************************************************************************
 * Function:        uint8_t ConfigureVfd (const uint8_t DriveId,
 *                  const uint16_t MotorRatedFullLoadCurrent,
 *                  const uint16_t MotorRatedFullLoadRpm,
 *                  const uint16_t MotorRatedVoltage,
 *                  const uint16_t MotorRatedFrequency,
 *                  const uint16_t MotorRatedPowerFactor)
 *
 * Description:     ConfigureVfd() through the use of helper functions
 *                  configures a specified variable speed drive.
 *
 * Dependencies:    cs_pdk_400_sk_vfd.h, and ConfigureTheSkDrive()
 *
 * PreConditions:   None
 *
 * Inputs:          An argument that specifies the address of the VFD the is to
 *                  be configured and motor specific arguments that specify the
 *                  motor's rated full load current, full load RPM, voltage
 *                  rating, frequency rating and power factor.
 *
 * Output:          The ConfigureVfd() function error status.
 *
 * Side Effects:    None
 ******************************************************************************/
uint8_t ConfigureVfd (const uint8_t DriveId,
                      const uint16_t MotorRatedFullLoadCurrent,
                      const uint16_t MotorRatedFullLoadRpm,
                      const uint16_t MotorRatedVoltage,
                      const uint16_t MotorRatedFrequency,
                      const uint16_t MotorRatedPowerFactor)
{
    uint8_t functionFaultStatus = NO_FW_VFD_FUNCTION_FAULTS;

    functionFaultStatus = ConfigureTheSkDrive (&SkVfdMessageDataUnion, DriveId,
                                               MotorRatedFullLoadCurrent,
                                               MotorRatedFullLoadRpm,
                                               MotorRatedVoltage,
                                               MotorRatedFrequency,
                                               MotorRatedPowerFactor,
                                               CrcLowByteArray,
                                               CrcHighByteArray);

    return functionFaultStatus;
}

/***** EOF for cs_pdk_400_sk_vfd.c ********************************************/
