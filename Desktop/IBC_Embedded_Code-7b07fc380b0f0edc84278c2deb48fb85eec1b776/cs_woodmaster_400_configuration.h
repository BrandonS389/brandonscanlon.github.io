/*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_configuration.h // NO IT IS CS_WOODMASTER_400_CONFIGURATION.H
 *  Date: 23 February 2015
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
 * JANUARY 20, 2017
 * BY: JEFF W
 * FOR: UPDATING NEW FANS AND MOTORS FOR GI-1
 * 
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
#ifndef	CS_PDK_400_CONFIGURATION_H_
#define	CS_PDK_400_CONFIGURATION_H_

// define here whether 50 or 60 HZ or a combination, thereof..
#define HZ60  

/******************************************************************************/
/* Include Header Files                                                       */
/******************************************************************************/

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declarations                */
/******************************************************************************/

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/

/******************************************************************************/
/* Global enums                                                               */
/******************************************************************************/

/******************************************************************************/
/* Universal #define Macros                                                   */
/******************************************************************************/
#define USE_5VDC_POWER  YES         /* Define as YES if +5VDC power is required
                                     * for external loads such as the gateway
                                     * (CN25), the local digital display (CN15)
                                     * or the USB power port (CN17). Otherwise,
                                     * define as NO. */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
                                            /* Valid VFD motor control addresses
                                             * range from 1 to 99 and valid PWM
                                             * motor control addresses range
                                             * from 100 to 102. */
#define	FUEL_FEED_AUGER_VFD     1
#define COMBUSTION_FAN_VFD      2
#define	ASH_REMOVAL_AUGER_VFD   3
#define DRAG_CHAIN_AUGER_VFD    4

#define	CATALYST_FAN_VFD        5
#define FORCED_AIR_FAN_VFD      6
#define OIL_PUMP_VFD            7
#define INDUCER_FAN_VFD         8
#define BIN_VIBRATOR_VFD        9
#define HOPPER_AUGER_VFD        10

#define SOME_FAN1_PWM           100         /* R3G or equivalent self-powered
                                             * PWM fan on controller connector
                                             * CN10.*/

#define SOME_FAN2_PWM           101         /* G1G or equivalent
                                             * controller-powered PWM fan on
                                             * controller connector CN9. */

#define SOME_FAN3_PWM           102         /* G1G or equivalent
                                             * controller-powered PWM fan on
                                             * controller connector CN11. */

/******************************************************************************/
/* Global #define Macros                                                      */
// SPECIFIC MOTOR RATINGS CAME FROM ANDREW B 1/20/17
// updated to 50hz settings 2/19
// updated 4/30/19 by Brendon to use Hybrid, combo settings (50HZ ash/fuel 60 fan)
// details of this history here: https://docs.google.com/document/d/1bpQBjTSfrmsTef0OXkuJBghB8uMl6p9nON133wLuW00
/******************************************************************************/

#if defined (HZ50)
#define	ASH_MOTOR_RATED_CURRENT                 32u       /* .32 Amp. */ 
#define ASH_MOTOR_RATED_FULL_LOAD_RPM           1300u     /* 4-pole, 50Hz motor. */
#define ASH_MOTOR_RATED_VOLTAGE                 230u      /* 230 volts, 3-phase. */
#define ASH_MOTOR_RATED_FULL_SPEED_FREQ         500u      /* 50 Hz. */
#define ASH_MOTOR_RATED_POWER_FACTOR            80u       /* 0.80 */
#define ASH_MOTOR_RATED_MIN_SPEED_FREQ          0u        /* 0.0Hz.*/

#define	FUEL_MOTOR_RATED_CURRENT                32u       /* .32 Amp. */ 
#define FUEL_MOTOR_RATED_FULL_LOAD_RPM          1300u     /* 4-pole, 50Hz motor. */
#define FUEL_MOTOR_RATED_VOLTAGE                230u      /* 230 volts, 3-phase. */
#define FUEL_MOTOR_RATED_FULL_SPEED_FREQ        500u      /* 50 Hz. */
#define FUEL_MOTOR_RATED_POWER_FACTOR           91u       /* 0.80 */
#define FUEL_MOTOR_RATED_MIN_SPEED_FREQ         0u        /* 0.0Hz.*/

#define	COMB_FAN_MOTOR_RATED_CURRENT            60u       /* .60 Amp. */
#define COMB_FAN_MOTOR_RATED_FULL_LOAD_RPM      2850u     /* 4-pole, 50Hz motor. */
#define COMB_FAN_MOTOR_RATED_VOLTAGE            230u      /* 230 volts, 3-phase. */
#define COMB_FAN_MOTOR_RATED_FULL_SPEED_FREQ    500u      /* 50 Hz. */
#define COMB_FAN_MOTOR_RATED_POWER_FACTOR       87u       /* 0.85 */
#define COMB_FAN_MOTOR_RATED_MIN_SPEED_FREQ     0u        /* 0.0Hz.*/

#endif

#if defined (HZ60)

// set back to project original 5/1/19 until we can finalize changes

#define	ASH_MOTOR_RATED_CURRENT  31u            /* .31 Amp., changed to .33 by BL Pr06 */ 
#define ASH_MOTOR_RATED_FULL_LOAD_RPM 1600u     /* changed from 1680 by BS 6/22/2022 4-pole, 60Hz motor. Pr07 */
#define ASH_MOTOR_RATED_VOLTAGE  230u           /* 230 volts, 3-phase. Pr08*/
#define ASH_MOTOR_RATED_FULL_SPEED_FREQ  600u   /* 60 Hz. Pr39 */
#define ASH_MOTOR_RATED_POWER_FACTOR 80u        /* 0.80 Pr09*/

#define	FUEL_MOTOR_RATED_CURRENT  48u            /* changed from .57 Amp. by BL back to .57 from .48 5/22/19 to crank manure through Pr06 */ 
#define FUEL_MOTOR_RATED_FULL_LOAD_RPM 1680u     /*  changed from 1800 by BL, 4-pole, 60Hz motor. Pr07 */
#define FUEL_MOTOR_RATED_VOLTAGE  230u           /* 230 volts, 3-phase. Pr08*/
#define FUEL_MOTOR_RATED_FULL_SPEED_FREQ  600u   /* 60 Hz. Pr39*/
#define FUEL_MOTOR_RATED_POWER_FACTOR 91u        /* 0.80 Pr09*/

#define	COMB_FAN_MOTOR_RATED_CURRENT  65u            /* .65 Amp. Pr06 */
#define COMB_FAN_MOTOR_RATED_FULL_LOAD_RPM 3300u     /* changed from 1800 by BL, 4-pole, 60Hz motor. Pr07*/
#define COMB_FAN_MOTOR_RATED_VOLTAGE  230u           /* 230 volts, 3-phase. Pr08 */
#define COMB_FAN_MOTOR_RATED_FULL_SPEED_FREQ  600u   /* 60 Hz. */
#define COMB_FAN_MOTOR_RATED_POWER_FACTOR 87u        /* 0.85 */


// #define	OIL_PUMP_MOTOR_RATED_CURRENT  280u            /* 2.8 Amp. */
// #define OIL_PUMP_MOTOR_RATED_FULL_LOAD_RPM 1500u     /* . */
// #define OIL_PUMP_MOTOR_RATED_VOLTAGE  230u           /* 230 volts, 3-phase. */
// #define OIL_PUMP_MOTOR_RATED_FULL_SPEED_FREQ  600u   /* 60 Hz. */
// #define OIL_PUMP_MOTOR_RATED_POWER_FACTOR 78u        /* 78 */

// // added 5/9/19 for Native 1 project
// #define	HOPPER_MOTOR_RATED_CURRENT  250u            /* 2.5 Amp. */
// #define HOPPER_MOTOR_RATED_FULL_LOAD_RPM 1690u     /* . */
// #define HOPPER_MOTOR_RATED_VOLTAGE  230u           /* 230 volts, 3-phase. */
// #define HOPPER_MOTOR_RATED_FULL_SPEED_FREQ  600u   /* 60 Hz. */
// #define HOPPER_MOTOR_RATED_POWER_FACTOR 71u        /* 71 */
#endif
/*----------------------------------------------------------------------------*/
#define CAT_FAN_ACCELERATION_RATE_S 1977u
                                        /* 16-bit value for VFD parameter 2.11.
                                         * 197.7 seconds per 100Hz becomes
                                         * 118.6 seconds per 60 Hz. For use
                                         * with 30 second 0 to 100% pot
                                         * ramp rate. */

#define CAT_FAN_DECELERATION_RATE_S 1977u
                                        /* 16-bit value for VFD parameter 2.21.
                                         * 197.7 seconds per 100Hz becomes
                                         * 118.6.0 seconds per 60 Hz. For use
                                         * with 30 second 0 to 100% pot
                                         * ramp rate. */

#define COMB_FAN_ACCELERATION_RATE_S 2000u
                                        /* 16-bit value for parameter 2.11.
                                         * 200.0 seconds per 100Hz becomes
                                         * 120.0 seconds per 60 Hz. For use
                                         * with 60 second 0 to 100% pot
                                         * ramp rate. */

#define COMB_FAN_DECELERATION_RATE_S 2000u
                                        /* 16-bit value for parameter 2.21.
                                         * 200.0 seconds per 100Hz becomes
                                         * 120.0 seconds per 60 Hz. For use
                                         * with 60 second 0 to 100% pot
                                         * ramp rate. */
#if(0)
#define CAT_MTR_POT_RAMP_RATE_S 120u    /* 16-bit value for parameter 9.32.
                                         * This constant defines the time that
                                         * it takes for the AC drive's
                                         * motorized pot function to ramp the
                                         * OWF's fan speed from 0% to 100%.
                                         * Valid values for this constant range
                                         * from 0 to 250 seconds. */

 #define COMB_MTR_POT_RAMP_RATE_S 120u  /* 16-bit value for parameter 9.32.
                                         * This constant defines the time that
                                         * it takes for the AC drive's
                                         * motorized pot function to ramp the
                                         * OWF's fan speed from 0% to 100%.
                                         * Valid values for this constant range
                                         * from 0 to 250 seconds. */
#endif
/*----------------------------------------------------------------------------*/
/* POWERUP_STATE */
/*----------------------------------------------------------------------------*/
/* STARTUP_STATE */
/*----------------------------------------------------------------------------*/
/* PREHEAT_STATE */
/*----------------------------------------------------------------------------*/
#define REHEAT_STATE_COMB_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define REHEAT_STATE_COMB_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */

#define REHEAT_STATE_CAT_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define REHEAT_STATE_CAT_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */
/*----------------------------------------------------------------------------*/
#define BOOST_STATE_COMB_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define BOOST_STATE_COMB_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */

#define BOOST_STATE_CAT_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define BOOST_STATE_CAT_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */
/*----------------------------------------------------------------------------*/
#define RUN_STATE_COMB_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define RUN_STATE_COMB_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */

#define RUN_STATE_CAT_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define RUN_STATE_CAT_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */
/*----------------------------------------------------------------------------*/
#define IDLE_STATE_COMB_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define IDLE_STATE_COMB_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */

#define IDLE_STATE_CAT_FAN_ACCELERATION_RATE 1u
                                        /* One second per 100Hz acceleration
                                         * rate. */

#define IDLE_STATE_CAT_FAN_DECELERATION_RATE 1u
                                        /* One second per 100Hz deceleration
                                         * rate. */
/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/

#endif	/* CS_PDK_400_CONFIGURATION_H_ */

/***** EOF for cs_pdk_400_configuration.h *************************************/
