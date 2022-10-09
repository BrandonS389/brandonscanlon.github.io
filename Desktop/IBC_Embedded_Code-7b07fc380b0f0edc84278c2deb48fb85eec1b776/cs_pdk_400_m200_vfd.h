/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_m200_vfd.h
 *  Date: 23 Febuary 2015
 *
 *  Author: Michael
 *  Company: BMC, LLC
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
#ifndef	CS_PDK_400_SK_VFD_H_
#define	CS_PDK_400_SK_VFD_H_

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declarations                */
/******************************************************************************/
//extern SkDriveMessageDataUnion_t SkVfdMessageDataUnion;

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
uint8_t ConfigureVfd (const uint8_t DriveId,
                      const uint16_t MotorRatedFullLoadCurrent,
                      const uint16_t MotorRatedFullLoadRpm,
                      const uint16_t MotorRatedVoltage,
                      const uint16_t MotorRatedFrequency,
                      const uint16_t MotorRatedPowerFactor);

uint8_t AdjustVfdMotorOperation (const uint8_t MotorDriveId, const uint8_t Command,
                                 const uint8_t PercentSpeedSetting,
                                 const uint16_t MotorRatedFullSpeedFrequency,
                                 const uint8_t MotorMinPercentSpeedLimit,
                                 const uint8_t MotorMaxPercentSpeedLimit);

/******************************************************************************/
/* Global enums                                                               */
/******************************************************************************/

/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/
#define NO_FW_VFD_FUNCTION_FAULTS       0u
#define VFD_ADDR_OUT_OF_RANGE           1u
#define VFD_FUNCT_CODE_NOT_SUPPORTED    2u
#define INVALID_VFD_FUNCT_CODE          4u
#define INVALID_VFD_MOTOR_COMMAND       5u

#define STOP_MOTOR  0u                  /* Operational commands. */
#define RUN_MOTOR   1u

#define MOTOR_RAMP_RELEASE  0u
#define MOTOR_RAMP_HOLD     1u

#define RAMP_MOTOR_SPEED_DN 0u
#define RAMP_MOTOR_SPEED_UP 1u

#define LOWEST_VFD_DRIVE_ADDR   1u
#define HIGHEST_VFD_DRIVE_ADDR  99u     /* Valid VFD motor control addresses
                                         * range from 1 to 99 and valid PWM
                                         * motor control addresses range from
                                         * 100 to 102. */
/*----------------------------------------------------------------------------*/
#define NO_ADJ_VFD_MOTOR_FUNCTION_FAULTS      0u
#define BAD_ADJ_VFD_MOTOR_FUNCT_COMMAND       1u
#define BAD_ADJ_VFD_MOTOR_FUNCT_DRIVE_ID      2u
#define BAD_ADJ_VFD_MOTOR_FUNCT_SPEED_SETTING 3u

/*----- Emerson SK series VFD related constants ------------------------------*/

#define ONE_REGISTER    1u              /* Actual argument that specifies one
                                         * register to the
                                         * NumberOfRegistersToWrite formal
                                         * parameter of a function. */

#define SINGLE_REGISTER_BYTE_LEN    2u  /* A single data register in the SK
                                         * series VFD is two bytes in length. */

#define RW_MULTIPLE_DATA_PACKET_BYTE_LEN   48u
                                        /* Up to sixteen 16-bit data words
                                         * (32 bytes of data) may be
                                         * read or written to the drive in a
                                         * single data packet read or write
                                         * operation. The data packet will
                                         * also contain up to thirteen bytes of
                                         * overhead information, including the
                                         * two byte checksum.
                                         * (Using function code 23)*/

#define WRITE_SINGLE_DATA_PACKET_BYTE_LEN   8u
                                        /* A complete data packet that is used to
                                         * transmit the data for a single
                                         * 16-bit variable frequency drive
                                         * register contains eight bytes.
                                         * (Using function code 6) */

#define SAVE_DRIVE_DATA 1000u           /* Writing a value of 1000 to
                                         * parameter X.00 of any parameter
                                         * menu and then resetting the drive
                                         * will cause all user save (US)
                                         * parameter data to be saved into the
                                         * drive's EPROM. */
#if (0)
#define MOTOR_FULL_SPEED_HZ 60
#endif

//----- Function Codes ---------------------------------------------------------

#define RD_MULT_16BIT_REGS      3u
                                        
#define WR_SINGLE_REG           6u
                                        
#define WR_MULT_16BIT_REGS      16u
                                        
#define RD_WR_MULT_16BIT_REGS   23u     /* These are the function codes that
                                         * determine the format and contents
                                         * of the variable frequency drive
                                         * message data that the controller
                                         * (master) is sending. If a reception
                                         * exception occurs, the VFD (slave)
                                         * will respond using these codes such
                                         * that bit 7 of these codes will be
                                         * set to logic one in order to indicate
                                         * the occurrence of an exception. */

/*----- VFD menu 1 data constants --------------------------------------------*/

                                        /* Speed reference selection, limits
                                         * and filters. */

#define SELECT_PRESET_SPEED_ZERO    0u  /* 16-bit value for parameter 1.15
                                         * Digital terminal inputs. */

#define SELECT_PRESET_SPEED_ONE     1u  /* 16-bit value for parameter 1.15
                                         * Preset register 1 selected depending
                                         * on the state of Pr 1.49. */

#define SELECT_PRESET_SPEED_TWO     2u  /* 16-bit value for parameter 1.15
                                         * Preset register 2 selected. */

#define SELECT_PRESET_SPEED_THREE   3u  /* 16-bit value for parameter 1.15
                                         * Preset register 3 selected. */

#define SELECT_PRESET_SPEED_FOUR    4u  /* 16-bit value for parameter 1.15
                                         * Preset register 4 selected. */

#define SELECT_PRESET_SPEED_FIVE    5u  /* 16-bit value for parameter 1.15
                                         * Preset register 5 selected. */

#define SELECT_PRESET_SPEED_SIX     6u  /* 16-bit value for parameter 1.15
                                         * Preset register 6 selected. */

#define SELECT_PRESET_SPEED_SEVEN   7u  /* 16-bit value for parameter 1.15
                                         * Preset register 7 selected. */

#define SELECT_PRESET_SPEED_EIGHT   8u  /* 16-bit value for parameter 1.15
                                         * Preset register 8 selected. */

/*----- VFD menu 2 data constants --------------------------------------------*/

                                        /* Ramps. */

#define ENABLE_RAMP_HOLD    1u          /* 16-bit value for parameter 2.03. */

#define DISABLE_RAMP_HOLD   0u          /* 16-bit value for parameter 2.03. */

#define S_RAMP_ACCELERATION_LIMIT   15u
                                        /* 16-bit value for parameter 2.07.
                                         * 15 is the factory default. */

#define ACCELERATION_1_RATE  REHEAT_STATE_COMB_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.11. */

#define ACCELERATION_2_RATE  REHEAT_STATE_CAT_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.12. */

#define ACCELERATION_3_RATE  BOOST_STATE_COMB_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.13. */

#define ACCELERATION_4_RATE  BOOST_STATE_CAT_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.14. */

#define ACCELERATION_5_RATE  RUN_STATE_COMB_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.15. */

#define ACCELERATION_6_RATE  RUN_STATE_CAT_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.16. */

#define ACCELERATION_7_RATE  IDLE_STATE_COMB_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.17. */

#define ACCELERATION_8_RATE  IDLE_STATE_CAT_FAN_ACCELERATION_RATE
                                        /* 16-bit value for parameter 2.18. */

#define DECELERATION_1_RATE  REHEAT_STATE_COMB_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.21. */

#define DECELERATION_2_RATE  REHEAT_STATE_CAT_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.22. */

#define DECELERATION_3_RATE  BOOST_STATE_COMB_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.23. */

#define DECELERATION_4_RATE  BOOST_STATE_CAT_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.24. */

#define DECELERATION_5_RATE  RUN_STATE_COMB_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.25. */

#define DECELERATION_6_RATE  RUN_STATE_CAT_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.26. */

#define DECELERATION_7_RATE  IDLE_STATE_COMB_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.27. */

#define DECELERATION_8_RATE  IDLE_STATE_CAT_FAN_DECELERATION_RATE
                                        /* 16-bit value for parameter 2.28. */

#define RAMP_RATE_UNITS_0 0u            /* 16-bit value for parameter 2.39.
                                         * 0 = 1s/100Hz; resolution = 0.005s */

#define RAMP_RATE_UNITS_1 1u            /* 16-bit value for parameter 2.39.
                                         * 1 = 10s/100Hz; resolution = 0.05s */

#define RAMP_RATE_UNITS_2 2u            /* 16-bit value for parameter 2.39.
                                         * 2 = 100s/100Hz; resolution = 0.5s. */

/*----- VFD menu 5 data constants --------------------------------------------*/

                                        /* Motor control. */

/*----- VFD menu 6 data constants --------------------------------------------*/

                                        /* Drive sequencer and clock. */

#define TERMINAL_B4_IS_ENABLE   0u      /* 16-bit value for parameter 6.04.
                                         * Terminal B4 is the drive enable
                                         * terminal, terminal B5 is the run
                                         * run forward terminal and terminal
                                         * B6 is the run reverse terminal. All
                                         * of these terminal commands are
                                         * non-latching. */

#define RESET_AND_ENABLE_DRIVE  0x2081  /* 16-bit value for the control word
                                         * parameter 6.42. The drive enable bit
                                         * is set to one, the auto/manual bit is
                                         * set to one and the reset drive bit is
                                         * set to one. */

#define DISABLE_DRIVE   0x0080          /* 16-bit value for the control word
                                         * parameter 6.42. the auto/manual bit
                                         * is set to one and the drive enable
                                         * bit is set to zero. */

#define ENABLE_DRIVE    0x0081          /* 16-bit value for the control word
                                         * parameter 6.42. The auto/manual bit
                                         * is set to one and the drive enable
                                         * bit is set to one. */

#define RUN_FORWARD 0x0083		/* 16-bit value for the control word
                                         * parameter 6.42. The auto/manual bit
                                         * is set to one, the run forward bit is
                                         * set to one and the drive enable bit
                                         * is set to one. */

#define ENABLE_CTRL_WORD    1u          /* 16-bit value for parameter 6.43. */

#define DISABLE_CTRL_WORD   0u          /* 16-bit value for parameter 6.43. */

/*----- VFD menu 9 data constants --------------------------------------------*/

                                        /* Programmable logic, motorized pot
                                         * and binary sum. */

#define MTR_POT_DESTINATION PRESET_SPEED_ONE_REG
                                        /* 16-bit value for perameter 9.25.
                                         * The preset speed one register is set
                                         * to be the motorized pot output
                                         * destination register. */

/*----- VDF menu 10 data constants -------------------------------------------*/

                                        /* Status logic and diagnostic
                                         * information. */

#define RESET_DRIVE 100                 /* 16-bit value for parameter 10.38.
                                         * Writing this value over the serial
                                         * comm bus to parameter 10.38, the
                                         * user trip register, will reset the
                                         * VFD. */

/*----- VFD menu 11 data constants -------------------------------------------*/

                                        /* General drive setup. */

#define USE_PRESET_SPEEDS   3u          /* 16-bit value for parameter 11.27.
                                         * PR(3) sets the VFD to be able to
                                         * operate off of the four preset speed
                                         * registers. The exact register that
                                         * will be used is specified
                                         * elsewhere. */

#define	LOAD_USA_DEFAULTS   2u          /* 16-bit value for parameter 11.43.
                                         * USA(2) sets the VFD to its USA
                                         * defaults and resets the VFD when the
                                         * VFD becomes inactive. */

/*----- VFD menu 12 data constants -------------------------------------------*/

                                        /* Programmable threshold and variable
                                         * selector. */

#define INPUT1_PLUS_INPUT2_MODE 2u      /* 16-bit value for parameter 12.10.
                                         * Sets the VFD to the
                                         * Output = Input1 + Input2 mode. */

/*----- VFD advanced parameters ----------------------------------------------*/

                /* Two-byte values in the form of menu:parameter (i.e. xx.yy)
                 * that are used for addressing 16-bit parameter registers of
                 * an Emerson Commander SK AC variable speed motor drive. The
                 * register address is calculated as ((xx * 100) + (yy - 1)) for
                 * 16-bit register access and as 16384 + ((xx * 100) + (yy - 1))
                 * for 32-bit register access. (User Save) means that the value
                 * that is being programmed into the register is saved into
                 * the VFD EEPROM when the user initiates a parameter save. */

/*----- VFD menu 1 parameter register addresses ------------------------------*/

                                            /* Speed reference selection,
                                             * limits and filters. */

#define SAVE_DATA_UPON_RESET_REG 1000u       /* 16-bit parameter register.
                                             * Set this register to a value
                                             * of 1000 and then reset the
                                             * drive to initiate a parameter
                                             * save in order to save certain
                                             * data to VFD EEPROM.
                                             * Address 1.00. */

#define MAXIMUM_SET_SPEED_REG 1006u          /* 16-bit parameter register.
                                             * Can be programmed with values
                                             * of 00 to 5500 (0.0 - 550.0) Hz.
                                             * Address 1.06. (User save.) */

#define MINIMUM_SET_SPEED_REG 1007u          /* 16-bit parameter register.
                                             * Can be programmed with values
                                             * of 00 to the value contained in
                                             * parameter 1.06.
                                             * (0.0 to value in 1.06) Hz.
                                             * Address 1.07 (User save.) */

#define PRESET_SPEED_SELECTOR_REG 1015u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * preset reference 0 to preset
                                             * reference 8.
                                             * Address 1.15. (User save.) */

#define	PRESET_SPEED_ONE_REG 1021u           /* 16-bit parameter register.
                                             * Can be programmed with values
                                             * of -5500 to +5500.
                                             * (-550.0 to +550.0) Hz.
                                             * Address 1.21. (User save.) */

#define	PRESET_SPEED_TWO_REG 1022u           /* 16-bit parameter register.
                                             * Can be programmed with values
                                             * of -5500 to +5500.
                                             * (-550.0 to +550.0) Hz.
                                             * Address 1.22. (User save.) */

#define	PRESET_SPEED_THREE_REG 1023u         /* 16-bit parameter register.
                                             * Can be programmed with values
                                             * of -5500 to +5500
                                             * (-550.0 to +550.0) Hz.
                                             * Address 1.23. (User save.) */

/*----- VFD menu 2 parameter register addresses ------------------------------*/

                                            /* Ramps. */

#define RAMP_HOLD_REG 2003u                  /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 2.03. (User save) */

#define S_RAMP_ENABLE_REG 2006u              /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 2.06. (User save) */

#define S_RAMP_ACCELERATION_LIMIT_REG 2007u  /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 3000.
                                             * (0.0 to 300.0 seconds^2)/100Hz.
                                             * Address 2.07. (User save.) */

#define ACCELERATION_RATE_SELECTOR_REG 2010u /* 16-Bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 9.
                                             * Address 2.10. (User save.) */

#define ACCELERATION_RATE_ONE_REG 2011u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.11 (User save.) */

#define ACCELERATION_RATE_TWO_REG 2012u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.12 (User save.) */

#define ACCELERATION_RATE_THREE_REG 2013u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.13 (User save.) */

#define ACCELERATION_RATE_FOUR_REG 2014u     /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.14 (User save.) */

#define ACCELERATION_RATE_FIVE_REG 2015u     /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.15 (User save.) */

#define ACCELERATION_RATE_SIX_REG 2016u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.16 (User save.) */

#define ACCELERATION_RATE_SEVEN_REG 2017u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.17 (User save.) */

#define ACCELERATION_RATE_EIGHT_REG 2018u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0 * the resolution
                                             * specified by Pr 2.39)s/Hz.)
                                             * Address 2.18 (User save.) */

#define DECELERATION_RATE_SELECTOR_REG 2020u /* 16-Bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 9.
                                             * Address 2.20. (User save.) */

#define DECELERATION_RATE_ONE_REG 2021u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.21 (User save.) */

#define DECELERATION_RATE_TWO_REG 2022u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.22 (User save.) */

#define DECELERATION_RATE_THREE_REG 2023u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.23 (User slave.) */

#define DECELERATION_RATE_FOUR_REG 2024u     /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.24 (User save.) */

#define DECELERATION_RATE_FIVE_REG 2025u     /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.25 (User save.) */

#define DECELERATION_RATE_SIX_REG 2026u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.26 (User save.) */

#define DECELERATION_RATE_SEVEN_REG 2027u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.27 (User save.) */

#define DECELERATION_RATE_EIGHT_REG 2028u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00 to 32000.
                                             * (0.0 to 3200.0  * the resolution
                                             * specified by Pr 2.39)/Hz.)s/Hz.)
                                             * Address 2.28 (User save.) */

#define RAMP_RATE_UNITS_REG 2039u        /* 16-bit parameter register.
                                         * Can be programmed with 0, 1 or 2 as
                                         * follows:
                                         * 0 = 1s/100Hz; resolution = 0.005s
                                         * 1 = 10s/100Hz; resolution = 0.05s
                                         * 2 = 100s/100Hz; resolution = 0.5s.
                                         * Address 2.39 (User save.) */

/*----- VFD menu 5 parameter register addresses ------------------------------*/

                                            /* Motor control. */

#define MOTOR_RATED_FREQUENCY_REG   5006u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 00.0 550.0 Hz.
                                             * Address 5.06. (User save.) */

#define MOTOR_RATED_CURRENT_REG 5007u        /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 000 to the VFD rated current.
                                             * (0.00 to rated current)
                                             * Address 5.07. (User save.) */

#define MOTOR_RATED_FULL_LOAD_RPM_REG 5008u  /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 9999 RPM.
                                             * Address 5.08. (User save.) */

#define MOTOR_RATED_VOLTAGE_REG 5009u        /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to VFD rated output voltage
                                             * Address 5.09. (User save.) */

#define MOTOR_RATED_POWER_FACTOR_REG 5010u   /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 000 to 100.
                                             * (0.00 to 1.00)
                                             * Address 5.10. (User save.) */

#define DYNAMIC_V_TO_F_SELECT_REG 5013u      /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 5.13. (User save.) */

#define SLIP_COMPENSATION_ENABLE_REG 5027u   /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 5.27. (User save.) */

/*----- VFD menu 6 parameter register addresses ------------------------------*/

#define START_STOP_LOGIC_SELECT_REG 6004u    /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 6. This controller uses
                                             * value 0 to make terminal B4 the
                                             * drive enable input. Actioned upon
                                             * drive reset.
                                             * Address 6.04. (User save.) */

#define SEQUENCER_LATCHING_ENABLE_REG 6040u  /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 6.40. */

#define DRIVE_CTRL_WORD_REG 6042u            /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 32767.
                                             * Address 6.42. */

#define CTRL_WORD_ENABLE_REG 6043u           /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 6.43. */

/*----- VFD menu 9 parameter register addresses ------------------------------*/

                                            /* Programmable logic, motorized
                                             * pot and binary sum. */

#define MOTORIZED_POT_RATE_REG 9023u         /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 250 seconds from 0% to 100%.
                                             * Address 9.23. (User save.) */

#define MTR_POT_DESTINATION_REG 9025u        /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 000 to 2151.
                                             * Appropriate values of
                                             * Pr 0.00 to Pr 21.51.
                                             * (Default is Pr 0.00).
                                             * Address 9.25 (User save.) */

#define MOTORIZED_POT_UP_REG 9026u           /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 9.26. */

#define MOTORIZED_POT_DOWN_REG 9027u         /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 9.27. */

#define MOTORIZED_POT_RESET_REG 9028u        /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (off) or 1 (on).
                                             * Address 9.28. */

/*----- VFD menu 10 parameter register addresses -----------------------------*/

                                            /* Status logic and diagnostic
                                             * information. */

#define USER_TRIP_REG 10038u                 /* 16-bit parameter register.
                                             * Writing a value of 100 to this
                                             * register causes a VFD reset.
                                             * Address 10.38. */

/*----- VFD menu 11 parameter register addresses -----------------------------*/

                                            /* General drive setup. */

#define DRIVE_CONFIGURATION_REG 11027u       /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 8. This controller uses
                                             * value 3 to cause the VFD to take
                                             * its speed reference from one of
                                             * the preset registers as is
                                             * specified elsewhere. Actioned
                                             * upon drive reset.
                                             * Address 11.27. (User save.) */

#define	LOAD_DEFAULTS_REG 11043u             /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 (no), 1 (Eur) or 2 (USA).
                                             * Address 11.43. (User save.) */

/*----- VFD menu 12 parameter register addresses -----------------------------*/

                                            /* Programmable threshold and
                                             * variable selector. */

#define VARIABLE_SELECTOR_1_SOURCE_1_REG 12008u
                                            /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 000 to 2151.
                                             * Appropriate values of
                                             * Pr 0.00 to Pr 21.51.
                                             * (Default is Pr 0.00).
                                             * Address 12.08. (User save.) */

#define VARIABLE_SELECTOR_1_SOURCE_2_REG 12009u
                                            /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 000 to 2151.
                                             * Appropriate values of
                                             * Pr 0.00 to Pr 21.51.
                                             * (Default is Pr 0.00).
                                             * Address 12.09. (User save.) */

#define VARIABLE_SELECTOR_1_MODE_REG 12010u  /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 0 to 9. This controller uses
                                             * value 2
                                             * (output = input1 + input2)
                                             * Address 12.10. (User save.) */

#define VARIABLE_SELECTOR_1_DESTINATION_REG 12011u
                                            /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * 000 to 2151.
                                             * Appropriate values of
                                             * Pr 0.00 to Pr 21.51.
                                             * (Default is Pr 0.00).
                                             * Address 12.11. (User save.) */

#define VARIABLE_SELECTOR_1_SOURCE_1_SCALING_REG 12013u
                                            /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * -4000 to +4000.
                                             * (-4.000 to +4.000)
                                             * Address 12.13. (User save.) */

#define VARIABLE_SELECTOR_1_SOURCE_2_SCALING_REG 12014u
                                            /* 16-bit parameter register.
                                             * Can be programmed with values of
                                             * -4000 to +4000.
                                             * (-4.000 to +4.000)
                                             * Address 12.14. (User save.) */

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
typedef union
{
    uint8_t DriveDataPacket[RW_MULTIPLE_DATA_PACKET_BYTE_LEN];

//===== All Drive Data Packets =================================================

    struct
    {
        uint8_t vfdAddress;

        uint8_t functionCode;
//------------------------------------------------------------------------------
        union
        {
            uint8_t driveDataBuffer[RW_MULTIPLE_DATA_PACKET_BYTE_LEN - 2];

            struct
            {                                   /* Function code 3. */

                uint16_t startRegAddr;          /* Start register address
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t numOf16BitRegs;        /* Number of contiguous 16-bit
                                                 * registers to read
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (little endian
                                                 * byte order). */
            }masterMultiReadRequest;

            struct
            {                                   /* Function code 3. */

                uint8_t dataLength;             /* Length (in bytes) of register
                                                 * data in the read block.
                                                 * (32 bytes maximum.) */

                uint16_t registerData[16];      /* Register data 0 MSByte:LSByte
                                                 * (big endian byte order). */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (located at
                                                 * structure byte offset
                                                 * 3+dataLength:4+dataLength). */
            }slaveMultiReadResponse;

            struct
            {                                   /* Function code 6. */

                uint16_t registerAddress;       /* Register address
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t registerData;          /* Register data MSByte:LSByte
                                                 * (big endian order). */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (little endian
                                                 * byte order). */
            }masterSingleWriteRequest;

            struct
            {                                   /* Function code 6. */

                uint16_t registerAddress;       /* Register address
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t registerData;          /* Register data MSByte:LSByte
                                                 * (big endian order). */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (little endian
                                                 * byte order). */
            }slaveSingleWriteResponse;

            struct
            {                                   /* Function code 16. */

                uint16_t startRegAddr;          /* Start register address
                                                 * MSByte:LSByte (big endian
                                                 * byte order. */

                uint16_t numOf16BitRegs;        /* Number of contiguous 16-bit
                                                 * registers to write. */

                uint8_t dataLength;             /* Length (in bytes) of register
                                                 * data to be written. (32 bytes
                                                 * maximum.) */

                uint16_t registerData[16];      /* Register data 0 MSByte:LSByte
                                                 * (big endian byte order). */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (located at
                                                 * structure byte offset
                                                 * 7+dataLength:7+dataLength). */
            }masterMultiWriteRequest;

            struct
            {                                   /* Function code 16. */

                uint16_t startRegAddr;          /* Start register address
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t numOf16BitRegs;        /* Number of contiguous 16-bit
                                                 * registers written. */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (little endian
                                                 * byte order). */
            }slaveMultiWriteResponse;

            struct
            {                                   /* Function code 23. */

                uint16_t startReadRegAddr;      /* Start read register address
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t numOf16BitReadRegs;    /* Number of contiguous 16-bit
                                                 * registers to read
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t startWriteRegAddr;     /* Start write register address
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint16_t numOf16BitWritwRegs;   /* Number of contiguous 16-bit
                                                 * registers to write
                                                 * MSByte:LSByte (big endian
                                                 * byte order). */

                uint8_t dataLength;             /* Length (in bytes) of register
                                                 * data to be written. (32 bytes
                                                 * maximum.) */

                uint16_t registerData[16];      /* Register data 0 MSByte:LSByte
                                                 * (big endian byte order). */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (located at
                                                 * structure byte offset
                                                 * 11+dataLength:12+dataLength). */
            }masterMultiReadWriteRequest;

            struct
            {                                   /* Function code 23. */

                uint8_t dataLength;             /* Length (in bytes) of register
                                                 * data in the read block.
                                                 * (32 bytes maximum.) */

                uint16_t registerData[16];      /* Register data 0 MSByte:LSByte
                                                 * (big endian byte order). */

                uint16_t crc16CheckSum;         /* LSByte:MSByte (located at
                                                 * structure byte offset
                                                 * 3+dataLength:4+dataLength) */
            }slaveMultiReadWriteResponse;

	}driveRegisterDataUnion;

    }driveFrameData;

} SkDriveMessageDataUnion_t;

#endif	/* CS_PDK_400_SK_VFD_H_ */

/***** EOF for cs_pdk_400_sk_vfd.h ********************************************/
