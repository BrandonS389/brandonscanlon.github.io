#if(0)
/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_woodmaster_400_main.c
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
 *  Revision History:   v4.0.0 Date: 2 January 2015 - Original Coding
 *                      Compiler: Microchip xc8 v1.34
 *                      IDE: Microchip MPLABX v3.00
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

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdio.h>
#include <stdbool.h>        /* For true/false definition */

#endif

#include "ClearStakMain.h"


/* Data collection logic */

/*----------------------------------------------------------------------------*/
void getCurrentValuesFromSensors() {
    sensorFaultBitWord = ReadTemperatureSensors(&fireTemperature,
            &fireColdJctTemperature,
            &postCatTemperature,
            &postCatColdJctTemperature,
            &stackTemperature,
            &stackColdJctTemperature,
            &waterInletTemperature,
            &waterOutletTemperature);

    oxygenSensorData = (uint16_t) GetOxySensorData();
    /* Obtain the post catalyst oxygen level
     * data. */

    /*----------------------------------------------------------------------------*/
    /* The flow meter is processed by the ISR. */
    /*----------------------------------------------------------------------------*/
}
/*----------------------------------------------------------------------------*/


/* Actuator processes */

/*----------------------------------------------------------------------------*/
// On-Off control of the catalyst damper

//void controlCatalystDamperFromOxygenLevel() {
    /* if (opState != LOCKOUT_STATE) {
         if ((oxygenSensorData > (catDamperO2Target + CAT_DAMPER_O2_HYSTERESIS)) || (postCatTemperature > CAT_DAMPER_FORCE_OPEN_CAT_TEMPERATURE_C)) {
             (void) SetMotorDamperCmdPosition(CAT_MOTOR_DAMPER, motorCatDamperMaxPercentOpen);
         } else if (oxygenSensorData < (catDamperO2Target - CAT_DAMPER_O2_HYSTERESIS)) {
             (void) SetMotorDamperCmdPosition(CAT_MOTOR_DAMPER, motorCatDamperMinPercentOpen);
         } else {
             (void) StopTheMotorDamper(CAT_MOTOR_DAMPER);
         }
     }*/
//}

// On-Off control of the combustion damper

//void controlCombustionDamper() {
    /* Damper direction logic reversal from the
     * code block above 06.05.15 10:30 AM. */
    //if (oxygenSensorData >= COMB_DAMPER_MIN_O2_LEVEL_AD) { /* Less O2. */
    //    combustionDamperO2Timer = 0;
    //} else if (combustionDamperO2Timer >= COMB_DAMPER_MIN_O2_LEVEL_TIME_S) {
    //    combustionDamperO2Timer = COMB_DAMPER_MIN_O2_LEVEL_TIME_S;
    //} /* For true timing of low O2 time in the
    /* construct below. */

    //    if ((opState == COLD_START_STATE) || (opState == WARM_START_STATE) ||
    //            (opState == HOT_START_STATE) || (opState == RUN_STATE) ||
    //            (opState == IDLE_STATE) || (opState == RELOAD_STATE)) {
    //        if ((fireTemperature > (COMB_DAMPER_FIRE_TARGET_C + COMB_DAMPER_FIRE_HYSTERESIS_C)) ||
    //                ((oxygenSensorData < COMB_DAMPER_MAX_O2_LEVEL_AD) &&
    //                (combustionDamperO2Timer >= COMB_DAMPER_MIN_O2_LEVEL_TIME_S))) { /* More O2. */
    //            (void) SetMotorDamperCmdPosition(COMB_MOTOR_DAMPER, motorCombDamperMinPercentOpen);
    //        } else if (((FIRETemperature < (COMB_DAMPER_FIRE_TARGET_C - COMB_DAMPER_FIRE_HYSTERESIS_C)) ||
    //                (waterOutletTemperature <= CONDENSING_WATER_TEMP_C)) &&
    //                (oxygenSensorData >= COMB_DAMPER_MIN_O2_LEVEL_AD)) { /* Less O2. */
    //            (void) SetMotorDamperCmdPosition(COMB_MOTOR_DAMPER, motorCombDamperMaxPercentOpen);
    //        } else {
    //            (void) StopTheMotorDamper(COMB_MOTOR_DAMPER);
    //        }
    /* In the normal and non startup operational
     * states, the combustion damper responds
     * primarily to fire temperature. Combustion
     * damper operation is limited by the
     * catalyst temperature in order to protect
     * the catalyst from overheating. If the O2
     * level is too low and the catalyst damper
     * is fully open then the combustion damper
     * will start to close in order to assist
     * the fully open catalyst damper with
     * O2 level control.*/
    // }
//}

void LEDProcess() {
    if (oxygenSensorData >= LOW_O2_LEVEL_SETPOINT) {
        m_LOW_OXY_LED_SET_ON() /* Higher == less oxygen. */
    } else {
        m_LOW_OXY_LED_SET_OFF()
    }
    /*----------------------------------------------------------------------------*/
    if (postCatTemperature <= CAT_MULTI_STATE_ADVANCE_TEMP_C) {
        catTemperatureSecondsTimer = 0;
    } else if (catTemperatureSecondsTimer >= CAT_MULTI_STATE_ADVANCE_TEMP_TIME_S) {
        catTemperatureSecondsTimer = CAT_MULTI_STATE_ADVANCE_TEMP_TIME_S;
    }
    /*----------------------------------------------------------------------------*/
    if (waterOutletTemperature >= WATER_TEMP_HIGH_LIMIT_TEMP_C) {
        if (HEAT_CALL_LED == LED_ON) {
            opStateSecondsTimer = 0;
            (void) SetMotorDamperCmdPosition(COMB_MOTOR_DAMPER, IDLE_STATE_COMB_DAMPER_MIN_OPEN_PCNT);
            opState = IDLE_STATE;
        }

        OpStatusBits.CallForHeat = FALSE;
        m_HEAT_CALL_LED_SET_OFF()
    } else if (waterOutletTemperature <= (WATER_TEMP_HIGH_LIMIT_TEMP_C - WATER_TEMP_DIFFERENTIAL_TEMP_C)) {
        OpStatusBits.CallForHeat = TRUE;
        m_HEAT_CALL_LED_SET_ON()
    }
}

void serialOutputProcess() {
    if (serialDataXmitIntervalTimer > (uint8_t) DATA_XMIT_INTERVAL_TIME_S) {
        motorCombDamperPercentOpen = DamperPositionSecondsToPercent(motorCombDamperTimer);
        motorCatDamperPercentOpen = DamperPositionSecondsToPercent(motorCatDamperTimer);

        (void) TransmitRS232SerialData((uint16_t) REMOTE_TERMINAL_IS_DATA_DESTINATION,
                runTimeSeconds,
                opStateNameTextArray[opState],
                waterInletTemperature,
                waterOutletTemperature,
                oxygenSensorData,
                fireTemperature,
                fireColdJctTemperature,
                postCatTemperature,
                postCatColdJctTemperature,
                stackTemperature,
                stackColdJctTemperature,
                flowMeterGpm,
                highLimitPotSetPercent,
                differentialPotSetPercent,
                cn10FanPercentSpeedCommand,
                motorCombDamperPercentOpen,
                motorCatDamperPercentOpen,
                sensorFaultBitWord);

        serialDataXmitIntervalTimer = 0u;
    }
}

void catalystHeaterProcess() {
    if (opState != LOCKOUT_STATE)
        /* TODO: Inhibit cat heater operation during sensor fault states, too! */ {
        if (INTERRUPTED_CAT_HEATER == NO) {
            m_CAT_HEATER_SET_ON()
            m_CAT_HEATER_LED_SET_ON()
        } else if ((opState == RELOAD_STATE) && (oxygenSensorData < RELOAD_STATE_CAT_HEATER_INHIBIT_O2_LEVEL)) {
            m_CAT_HEATER_SET_OFF()
            m_CAT_HEATER_LED_SET_OFF()
        } else {
            if (postCatTemperature < CAT_HEATER_CAT_DWELL_TEMP_C) {
                m_CAT_HEATER_SET_ON()
                m_CAT_HEATER_LED_SET_ON()
                catHeaterSecondsTimer = 0;
            } else if (catHeaterSecondsTimer >= CAT_HEATER_CAT_DWELL_TEMP_TIME_S) {
                catHeaterSecondsTimer = CAT_HEATER_CAT_DWELL_TEMP_TIME_S;

                if (fireTemperature >= CAT_HEATER_MIN_FIRE_TEMP_C) {
                    m_CAT_HEATER_SET_OFF()
                    m_CAT_HEATER_LED_SET_OFF()
                }
            }
        }
        /* The catalyst heater is capable of
         * operating in all operational states
         * except the LOCKOUT_STATE. */
    }
}


/*----------------------------------------------------------------------------*/


/* System functions for managing state transitions */

/*----------------------------------------------------------------------------*/
void systemSetupProcess() {
    ClrWdt();

    ConfigureOscillator(); /* Configure the oscillator for the device */
    /*----------------------------------------------------------------------------*/
    InitializeSystem();
    /* Initialize I/O and Peripherals for application */

    (void) PowerOnSelfTest(&opState, POWERUP_STATE);
    /* If P.O.S.T is successful then set
     * firmware for the state machine's
     * power-up state. */
    /*----------------------------------------------------------------------------*/
    m_O2_HEATER_PWR_SET_ON(); /* We warm the catalyst and the O2 sensor
                                     * even while we wait for the dampers to
                                     * complete their homing operation. */

            /*----------------------------------------------------------------------------*/
    (void) SetPwmPercent(DAMPER_HOMING_INDUCER_FAN_SPEED_PCNT, PWM_PORT_CN10);

    MotorDamperStatusBits.MotorDampersToHome = (bool) TRUE;
    m_SET_COMB_DAMPER_DIRECTION_CLOSE();
    m_SET_CAT_DAMPER_DIRECTION_CLOSE();
    m_SET_COMB_DAMPER_MOTOR_CTRL_RUN();
    m_SET_CAT_DAMPER_MOTOR_CTRL_RUN();
    motorDamperHomingTimer = 0;

    while (motorDamperHomingTimer < (DAMPER_FULL_TRAVEL_TIME_S + 10)) {
        ClrWdt();
    }
    m_SET_COMB_DAMPER_MOTOR_CTRL_STOP();
    m_SET_CAT_DAMPER_MOTOR_CTRL_STOP();

    (void) SetPwmPercent(0, PWM_PORT_CN10);

    motorCombDamperTimer = 0;
    motorCatDamperTimer = 0;
    motorCombDamperTargetTime = 0;
    motorCatDamperTargetTime = 0;

    MotorDamperStatusBits.MotorDampersToHome = (bool) FALSE;
    /* Home both dampers. */
    /*----------------------------------------------------------------------------*/
    WRITETIMER0(TMR0_01_SEC_PRELOAD_VALUE);
    oneSecondTimer = CLEAR;
    opStateSecondsTimer = CLEAR;
    /*----------------------------------------------------------------------------*/

}

void setCurrentStateAndCatchErrors() {
    if (sensorFaultBitWord == (uint32_t) NO_SENSOR_FAULT_BITS) {
        if ((opState != POWERUP_STATE) && (opState != COLD_START_STATE) &&
                (opState != WARM_START_STATE) && (opState != HOT_START_STATE) &&
                (opState != RUN_STATE) && (opState != IDLE_STATE) &&
                (opState != RELOAD_STATE) && (opState != LOCKOUT_STATE)) {
            opState = POWERUP_STATE;
        } else if ((opState == IDLE_STATE) &&
                (OpStatusBits.CallForHeat == TRUE)) {
            opStateSecondsTimer = 0u;
            runStateO2SecondsTimer = 0u;
            opState = POWERUP_STATE;
        } else if ((opState == POWERUP_STATE) &&
                (OpStatusBits.CallForHeat == FALSE) &&
                (waterOutletTemperature >= WATER_TEMP_HIGH_LIMIT_TEMP_C)) {

            opStateSecondsTimer = 0;
            (void) SetMotorDamperCmdPosition(COMB_MOTOR_DAMPER, IDLE_STATE_COMB_DAMPER_MIN_OPEN_PCNT);
            m_HEAT_CALL_LED_SET_OFF();
            opState = IDLE_STATE;
        } else if ((opState == POWERUP_STATE) &&
                (OpStatusBits.CallForHeat == FALSE) &&
                (waterOutletTemperature < WATER_TEMP_HIGH_LIMIT_TEMP_C)) {
            OpStatusBits.CallForHeat = TRUE;
            opStateSecondsTimer = 0u;
            runStateO2SecondsTimer = 0u;
            opState = POWERUP_STATE;
            /* This if() else if() statement
             * takes care of power cycle events
             * that happen when the water outlet
             * temperature is in the
             * high-limit to low-limit
             * hysteresis band. */
        }
    } else {
        opState = SensorFaultBitsToOpStateIndex(sensorFaultBitWord);
    }
}

void setLimitsAndSetPointsByState() {
    /* State-by-state limit and target
     * initialization. cn10FanSpeedMaxPercent is
     * initialized elsewhere in code, either
     * where the BDH related code is invoked or
     * in IDLE_STATE. */
    if (opState == COLD_START_STATE) {
        cn10FanSpeedMinPercent = COLD_START_STATE_INDUCER_FAN_MIN_SPEED_PCNT;
        motorCatDamperMinPercentOpen = COLD_START_STATE_CAT_DAMPER_MIN_OPEN_PCNT;
        motorCatDamperMaxPercentOpen = COLD_START_STATE_CAT_DAMPER_MAX_OPEN_PCNT;
        motorCombDamperMinPercentOpen = COLD_START_STATE_COMB_DAMPER_MIN_OPEN_PCNT;
        motorCombDamperMaxPercentOpen = COLD_START_STATE_COMB_DAMPER_MAX_OPEN_PCNT;

        if (postCatTemperature >= CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = CAT_OVER_TEMP_CAT_DAMPER_O2_TARGET;
        } else if (postCatTemperature < CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = COLD_START_STATE_CAT_DAMPER_O2_TARGET;
        }
    }

    if (opState == WARM_START_STATE) {
        cn10FanSpeedMinPercent = WARM_START_STATE_INDUCER_FAN_MIN_SPEED_PCNT;
        motorCatDamperMinPercentOpen = WARM_START_STATE_CAT_DAMPER_MIN_OPEN_PCNT;
        motorCatDamperMaxPercentOpen = WARM_START_STATE_CAT_DAMPER_MAX_OPEN_PCNT;
        motorCombDamperMinPercentOpen = WARM_START_STATE_COMB_DAMPER_MIN_OPEN_PCNT;
        motorCombDamperMaxPercentOpen = WARM_START_STATE_COMB_DAMPER_MAX_OPEN_PCNT;

        if (postCatTemperature >= CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = CAT_OVER_TEMP_CAT_DAMPER_O2_TARGET;
        } else if (postCatTemperature < CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = WARM_START_STATE_CAT_DAMPER_O2_TARGET;
        }
    }

    if (opState == HOT_START_STATE) {
        cn10FanSpeedMinPercent = HOT_START_STATE_INDUCER_FAN_MIN_SPEED_PCNT;
        motorCatDamperMinPercentOpen = HOT_START_STATE_CAT_DAMPER_MIN_OPEN_PCNT;
        motorCatDamperMaxPercentOpen = HOT_START_STATE_CAT_DAMPER_MAX_OPEN_PCNT;
        motorCombDamperMinPercentOpen = HOT_START_STATE_COMB_DAMPER_MIN_OPEN_PCNT;
        motorCombDamperMaxPercentOpen = HOT_START_STATE_COMB_DAMPER_MAX_OPEN_PCNT;

        if (postCatTemperature >= CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = CAT_OVER_TEMP_CAT_DAMPER_O2_TARGET;
        } else if (postCatTemperature < CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = HOT_START_STATE_CAT_DAMPER_O2_TARGET;
        }
    }

    if (opState == RUN_STATE) {
        cn10FanSpeedMinPercent = RUN_STATE_INDUCER_FAN_MIN_SPEED_PCNT;
        motorCatDamperMinPercentOpen = RUN_STATE_CAT_DAMPER_MIN_OPEN_PCNT;
        motorCatDamperMaxPercentOpen = RUN_STATE_CAT_DAMPER_MAX_OPEN_PCNT;
        motorCombDamperMinPercentOpen = RUN_STATE_COMB_DAMPER_MIN_OPEN_PCNT;
        motorCombDamperMaxPercentOpen = RUN_STATE_COMB_DAMPER_MAX_OPEN_PCNT;

        if (postCatTemperature >= CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = CAT_OVER_TEMP_CAT_DAMPER_O2_TARGET;
        } else if (postCatTemperature < CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = RUN_STATE_CAT_DAMPER_O2_TARGET;
        } /* Elsewhere in code where RUN_STATE is
                                     * invoked, this variable is initialized
                                     * to RUN_STATE_CAT_DAMPER_O2_TARGET in
                                     * order to cover the 'inbetween'
                                     * conditions that are not covered above. */
    }

    if (opState == RELOAD_STATE) {
        cn10FanSpeedMinPercent = RELOAD_STATE_INDUCER_FAN_MIN_SPEED_PCNT;
        motorCatDamperMinPercentOpen = RELOAD_STATE_CAT_DAMPER_MIN_OPEN_PCNT;
        motorCatDamperMaxPercentOpen = RELOAD_STATE_CAT_DAMPER_MAX_OPEN_PCNT;
        motorCombDamperMinPercentOpen = RELOAD_STATE_COMB_DAMPER_MIN_OPEN_PCNT;
        motorCombDamperMaxPercentOpen = RELOAD_STATE_COMB_DAMPER_MAX_OPEN_PCNT;

        if (postCatTemperature >= CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = CAT_OVER_TEMP_CAT_DAMPER_O2_TARGET;
        } else if (postCatTemperature < CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = RELOAD_STATE_CAT_DAMPER_O2_TARGET;
        }
    }

    if (opState == IDLE_STATE) {
        motorCatDamperMinPercentOpen = IDLE_STATE_CAT_DAMPER_MIN_OPEN_PCNT;
        motorCatDamperMaxPercentOpen = IDLE_STATE_CAT_DAMPER_MAX_OPEN_PCNT;
        motorCombDamperMinPercentOpen = IDLE_STATE_COMB_DAMPER_MIN_OPEN_PCNT;
        motorCombDamperMaxPercentOpen = IDLE_STATE_COMB_DAMPER_MAX_OPEN_PCNT;

        if (postCatTemperature >= CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = CAT_OVER_TEMP_CAT_DAMPER_O2_TARGET;
        } else if (postCatTemperature < CATALYST_MAX_ALLOWED_TEMPERATURE_C) {
            catDamperO2Target = IDLE_STATE_CAT_DAMPER_O2_TARGET;
        }
    }
}
/*----------------------------------------------------------------------------*/


/* Control logic by state*/

/*----------------------------------------------------------------------------*/
void powerUpStateControl() {
    MotorDamperStatusBits.MotorDampersToHome = (bool) FALSE;

}

void coldStartStateControl() {
    if (((postCatTemperature >= COLD_START_STATE_CAT_ESC_TEMP_C) &&
            (fireTemperature >= COLD_START_STATE_FIRE_ESC_TEMP_C) &&
            (waterOutletTemperature > COLD_START_STATE_MIN_WO_ESC_TEMP_C)) ||
            ((postCatTemperature > CAT_MULTI_STATE_ADVANCE_TEMP_C) &&
            (catTemperatureSecondsTimer >= CAT_MULTI_STATE_ADVANCE_TEMP_TIME_S))) {
        (void) StopTheMotorDamper(CAT_MOTOR_DAMPER);
        (void) StopTheMotorDamper(COMB_MOTOR_DAMPER);

        __delay_ms(500);
        __delay_ms(500); /* One second delay in order to be sure
                                        * that the ISR gets a chance to stop
                                        * the damper motors. We want them
                                        * stopped because their min and max
                                        * opening limit percents are likely to
                                        * change when we invoke a new operating
                                        * state. */


        opStateSecondsTimer = 0u;

        startupStateTimer = 0;

        opState = WARM_START_STATE;
    }
}

void warmStartStateControl() {
    if (((postCatTemperature >= WARM_START_STATE_CAT_ESC_TEMP_C) &&
            (fireTemperature >= WARM_START_STATE_FIRE_ESC_TEMP_C) &&
            (waterOutletTemperature > WARM_START_STATE_MIN_WO_ESC_TEMP_C)) ||
            ((postCatTemperature > CAT_MULTI_STATE_ADVANCE_TEMP_C) &&
            (catTemperatureSecondsTimer >= CAT_MULTI_STATE_ADVANCE_TEMP_TIME_S))) {
        (void) StopTheMotorDamper(CAT_MOTOR_DAMPER);
        (void) StopTheMotorDamper(COMB_MOTOR_DAMPER);

        __delay_ms(500);
        __delay_ms(500); /* One second delay in order to be sure
                                        * that the ISR gets a chance to stop
                                        * the damper motors. We want them
                                        * stopped because their min and max
                                        * opening limit percents are likely to
                                        * change when we invoke a new operating
                                        * state. */

        opStateSecondsTimer = 0u;

        startupStateTimer = 0;

        opState = HOT_START_STATE;
    }
}

void hotStartStateControl() {
    if (opStateSecondsTimer >= HOT_START_STATE_MAX_TIME_S) {
        (void) FurnaceShutdown();
        m_LOCKOUT_EXT_LED_SET_ON()
        m_STANDBY_LOCKOUT_LED_SET_ON()
        opState = LOCKOUT_STATE;
    }

    if (((postCatTemperature >= HOT_START_STATE_CAT_ESC_TEMP_C) &&
            (fireTemperature >= HOT_START_STATE_FIRE_ESC_TEMP_C) &&
            (waterOutletTemperature > HOT_START_STATE_MIN_WO_ESC_TEMP_C)) ||
            ((postCatTemperature > CAT_MULTI_STATE_ADVANCE_TEMP_C) &&
            (catTemperatureSecondsTimer >= CAT_MULTI_STATE_ADVANCE_TEMP_TIME_S))) {
        (void) StopTheMotorDamper(CAT_MOTOR_DAMPER);
        (void) StopTheMotorDamper(COMB_MOTOR_DAMPER);

        __delay_ms(500);
        __delay_ms(500); /* One second delay in order to be sure
                                        * that the ISR gets a chance to stop
                                        * the damper motors. We want them
                                        * stopped because their min and max
                                        * opening limit percents are likely to
                                        * change when we invoke a new operating
                                        * state. */

        opStateSecondsTimer = 0u;

        runStateO2SecondsTimer = 0;

        catDamperO2Target = RUN_STATE_CAT_DAMPER_O2_TARGET;
        /* We initialize this variable here in order
         * to be sure that this variable is
         * initialized. Elsewhere, in the state
         * variable initialization code, there are
         * 'inbetween' conditions where this
         * variable may otherwise go
         * uninitialized. */

        opState = RUN_STATE;

    }
}

void runStateControl() {
    if ((runStateO2SecondsTimer >= RUN_STATE_ESC_O2_LEVEL_TIME_S) &&
            (opStateSecondsTimer >= RUN_STATE_ESC_MIN_CAT_TEMPERATURE_TIME_S)) {
        (void) StopTheMotorDamper(CAT_MOTOR_DAMPER);
        (void) StopTheMotorDamper(COMB_MOTOR_DAMPER);

        __delay_ms(500);
        __delay_ms(500); /* One second delay in order to be sure
                                        * that the ISR gets a chance to stop
                                        * the damper motors. We want them
                                        * stopped because their min and max
                                        * opening limit percents are likely to
                                        * change when we invoke a new operating
                                        * state. */

        opStateSecondsTimer = 0u;

        opState = RELOAD_STATE;
    }
}

void idleStateControl() {
    if ((opStateSecondsTimer >= IDLE_STATE_MIN_FIRE_TEMPERATURE_TIME_S) &&
            (postCatTemperature < IDLE_STATE_MIN_CAT_TEMPERATURE_C)) {
        (void) FurnaceShutdown();
        m_LOCKOUT_EXT_LED_SET_ON()
        m_STANDBY_LOCKOUT_LED_SET_ON()
        opState = LOCKOUT_STATE;
    }
}

void reloadStateControl() {
    if (waterOutletTemperature <= RELOAD_STATE_MIN_WO_TEMP_C) {
        (void) FurnaceShutdown();
        m_LOCKOUT_EXT_LED_SET_ON()
        m_STANDBY_LOCKOUT_LED_SET_ON()
        opState = LOCKOUT_STATE;
    }

}

void lockoutStateControl() {
    (void) SetPwmPercent(0, PWM_PORT_CN10);

    if (FurnaceHasBeenReset() == TRUE) {
        m_LOCKOUT_EXT_LED_SET_OFF()
        m_STANDBY_LOCKOUT_LED_SET_OFF()
        opState = POWERUP_STATE;
    }
}
/*----------------------------------------------------------------------------*/


/* State machine transition logic */

/*----------------------------------------------------------------------------*/
void preformStateMachine() {
    switch (opState) {
        case POWERUP_STATE:

            powerUpStateControl();
            /* To recover from FurnaceShutdown(). */

            if (OpStatusBits.CallForHeat == TRUE) {
                if ((waterOutletTemperature >= RUN_STATE_SELECTION_WATER_OUT_TEMP_C) &&
                        (postCatTemperature > COLD_START_STATE_SELECTION_MAX_CAT_TEMP_C)) {
                    catDamperO2Target = RUN_STATE_CAT_DAMPER_O2_TARGET;
                    /* We initialize this variable here in order
                     * to be sure that this variable is
                     * initialized. Elsewhere, in the state
                     * variable initialization code, there are
                     * 'inbetween' conditions where this
                     * variable may otherwise go
                     * uninitialized. */

                    opStateSecondsTimer = 0u;

                    startupStateTimer = 0;

                    runStateO2SecondsTimer = 0;

                    opState = RUN_STATE;
                } else if ((waterOutletTemperature < RUN_STATE_SELECTION_WATER_OUT_TEMP_C) &&
                        (waterOutletTemperature >= HOT_START_STATE_SELECTION_WATER_OUT_TEMP_C) &&
                        (fireTemperature >= HOT_START_STATE_SELECTION_FIRE_TEMP_C) &&
                        (postCatTemperature > COLD_START_STATE_SELECTION_MAX_CAT_TEMP_C)) {

                    opStateSecondsTimer = 0;

                    startupStateTimer = 0;

                    opState = HOT_START_STATE;
                } else if ((waterOutletTemperature < HOT_START_STATE_SELECTION_WATER_OUT_TEMP_C) &&
                        (waterOutletTemperature >= WARM_START_STATE_SELECTION_WATER_OUT_TEMP_C) &&
                        (fireTemperature >= WARM_START_STATE_SELECTION_FIRE_TEMP_C) &&
                        (postCatTemperature > COLD_START_STATE_SELECTION_MAX_CAT_TEMP_C)) {

                    opStateSecondsTimer = 0u;

                    startupStateTimer = 0;

                    opState = WARM_START_STATE;
                } else {

                    opStateSecondsTimer = 0u;

                    startupStateTimer = 0;

                    opState = COLD_START_STATE;
                }
            }

            break;
            /*----------------------------------------------------------------------------*/
        case COLD_START_STATE:

            if (postCatTemperature >= COLD_START_STATE_CAT_MIN_TEMP_C) {
                opStateSecondsTimer = 0u;
            }

            if (opStateSecondsTimer >= COLD_START_STATE_MAX_TIME_S) {
                (void) FurnaceShutdown();
                m_LOCKOUT_EXT_LED_SET_ON()
                m_STANDBY_LOCKOUT_LED_SET_ON()
                opState = LOCKOUT_STATE;
            }

            if (startupStateTimer >= COLD_START_STATE_MIN_TIME_S) {
                startupStateTimer == COLD_START_STATE_MIN_TIME_S;
            }

            coldStartStateControl();

            break;
            /*----------------------------------------------------------------------------*/
        case WARM_START_STATE:

            if (postCatTemperature >= WARM_START_STATE_CAT_MIN_TEMP_C) {
                opStateSecondsTimer = 0u;
            }

            if (opStateSecondsTimer >= WARM_START_STATE_MAX_TIME_S) {
                (void) FurnaceShutdown();
                m_LOCKOUT_EXT_LED_SET_ON()
                m_STANDBY_LOCKOUT_LED_SET_ON()
                opState = LOCKOUT_STATE;
            }

            warmStartStateControl();

            break;
            /*----------------------------------------------------------------------------*/
        case HOT_START_STATE:

            if (postCatTemperature >= HOT_START_STATE_CAT_MIN_TEMP_C) {
                opStateSecondsTimer = 0u;
            }

            hotStartStateControl();

            break;
            /*----------------------------------------------------------------------------*/
        case RUN_STATE:

            if (oxygenSensorData > RUN_STATE_ESC_O2_LEVEL) {
                runStateO2SecondsTimer = 0u;
            }
            if (runStateO2SecondsTimer >= RUN_STATE_ESC_O2_LEVEL_TIME_S) {
                runStateO2SecondsTimer == RUN_STATE_ESC_O2_LEVEL_TIME_S;
            }

            if (postCatTemperature > RUN_STATE_ESC_MIN_CAT_TEMPERATURE_C) {
                opStateSecondsTimer = 0u;
            }
            if (opStateSecondsTimer >= RUN_STATE_ESC_MIN_CAT_TEMPERATURE_TIME_S) {
                opStateSecondsTimer == RUN_STATE_ESC_MIN_CAT_TEMPERATURE_TIME_S;
            }

            runStateControl();
            break;
            /*----------------------------------------------------------------------------*/
        case IDLE_STATE:

            if (cn10FanPercentSpeedCommand != IDLE_STATE_INDUCER_FAN_SPEED_PCNT) {
                cn10FanPercentSpeedCommand = IDLE_STATE_INDUCER_FAN_SPEED_PCNT;
                (void) SetPwmPercent(cn10FanPercentSpeedCommand, PWM_PORT_CN10);
            }

            if (fireTemperature >= IDLE_STATE_MIN_FIRE_TEMPERATURE_C) {
                opStateSecondsTimer = 0u;
            }

            idleStateControl();

            break;
            /*----------------------------------------------------------------------------*/
        case RELOAD_STATE:

            if (oxygenSensorData <= RELOAD_STATE_ESC_O2_LEVEL) {
                opStateSecondsTimer = 0;
            }

            if (opStateSecondsTimer >= RELOAD_STATE_ESC_O2_LEVEL_TIME_S) {
                (void) StopTheMotorDamper(CAT_MOTOR_DAMPER);
                (void) StopTheMotorDamper(COMB_MOTOR_DAMPER);

                __delay_ms(500);
                __delay_ms(500); /* One second delay in order to be sure
                                        * that the ISR gets a chance to stop
                                        * the damper motors. We want them
                                        * stopped because their min and max
                                        * opening limit percents are likely to
                                        * change when we invoke a new operating
                                        * state. */


                opStateSecondsTimer = 0u;

                runStateO2SecondsTimer = 0;

                catDamperO2Target = RUN_STATE_CAT_DAMPER_O2_TARGET;
                /* We initialize this here in order to
                 * be sure that this variable is
                 * initialized. Elsewhere, in the state
                 * variable initialization code, there are
                 * 'inbetween' conditions where this
                 * variable may otherwise go uninitialized. */

                opState = RUN_STATE;
            }

            reloadStateControl();

            break;
            /*----------------------------------------------------------------------------*/
        case SHUTDOWN_STATE:

            ;

            break;
            /*----------------------------------------------------------------------------*/
        case LOCKOUT_STATE:

            lockoutStateControl();

            break;
            /*----------------------------------------------------------------------------*/
        case FIRE_TC_OPEN_CIRCUIT_FAULT_STATE:

            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case FIRE_TC_SHORT_TO_GND_FAULT_STATE:

            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case FIRE_TC_SHORT_TO_VCC_FAULT_STATE:

            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case POST_CAT_TC_OPEN_CIRCUIT_FAULT_STATE:

            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case POST_CAT_TC_SHORT_TO_GND_FAULT_STATE:

            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case POST_CAT_TC_SHORT_TO_VCC_FAULT_STATE:

            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case STACK_TC_OPEN_CIRCUIT_FAULT_STATE:

            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case STACK_TC_SHORT_TO_GND_FAULT_STATE:

            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case STACK_TC_SHORT_TO_VCC_FAULT_STATE:

            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_FIRE_GTODP_FUNCT_ARG_FAULT_STATE:

            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_FIRE_TC_TEMP_FUNCTION_ARG_FAULT_STATE:

            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_POST_CAT_GTODP_FUNCT_ARG_FAULT_STATE:

            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_FAULT_STATE:

            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_STACK_GTODP_FUNCT_ARG_FAULT_STATE:

            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_STACK_TC_TEMP_FUNCTION_ARG_FAULT_STATE:

            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case INLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE:

            DoErrorCadence(WATER_IN_THERMISTOR_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case INLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE:

            DoErrorCadence(WATER_IN_THERMISTOR_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case OUTLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE:

            DoErrorCadence(WATER_OUT_THERMISTOR_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case OUTLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE:

            DoErrorCadence(WATER_OUT_THERMISTOR_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_INLET_GTIDP_FUNCT_ARG_FAULT_STATE:

            DoErrorCadence(WATER_IN_THERMISTOR_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case BAD_OUTLET_GTIDP_FUNCT_ARG_FAULT_STATE:

            DoErrorCadence(WATER_OUT_THERMISTOR_FAULT_IND_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case MULTIPLE_SENSOR_FAULTS_STATE:

            DoErrorCadence(MULTIPLE_SENSOR_FAULTS_FLASH_COUNT);

            break;
            /*----------------------------------------------------------------------------*/
        case PDK_STATE:

            break;
            /*----------------------------------------------------------------------------*/
        default:

            DoErrorCadence(UNDEFINED_OP_STATE_FLASH_COUNT);

            break;

    }//end switch
}

/*----------------------------------------------------------------------------*/

/* Adaptive state-based PID control */
void updatePIDGainsAndSetPointsFromState() {
    switch (opState) {
        case POWERUP_STATE:

            break;
            /*----------------------------------------------------------------------------*/
        case COLD_START_STATE:

            break;
            /*----------------------------------------------------------------------------*/
        case HOT_START_STATE:

            break;
            /*----------------------------------------------------------------------------*/
        case RUN_STATE:
            PIDControllerChangeGains(waterOutTemperatureController,
                    WATER_OUT_TEMPERATURE_RUN_STATE_PROPORTIONAL_GAIN,
                    WATER_OUT_TEMPERATURE_RUN_STATE_INTEGRAL_GAIN,
                    WATER_OUT_TEMPERATURE_RUN_STATE_DERIVATIVE_GAIN);

            PIDControllerChangeGains(oxygenLevelController,
                    OXYGEN_TEMPERATURE_RUN_STATE_PROPORTIONAL_GAIN,
                    OXYGEN_TEMPERATURE_RUN_STATE_INTEGRAL_GAIN,
                    OXYGEN_TEMPERATURE_RUN_STATE_DERIVATIVE_GAIN);

            PIDControllerChangeGains(fireTemperatureController,
                    FIRE_TEMPERATURE_RUN_STATE_PROPORTIONAL_GAIN,
                    FIRE_TEMPERATURE_RUN_STATE_DERIVATIVE_GAIN,
                    FIRE_TEMPERATURE_RUN_STATE_INTEGRAL_GAIN);

            PIDControllerChangeSetPoint(waterOutTemperatureController,
                    WATER_OUT_TEMPERATURE_RUN_STATE_SETPOINT);

            PIDControllerChangeSetPoint(oxygenLevelController,
                    OXYGEN_RUN_STATE_SETPOINT);

            PIDControllerChangeSetPoint(fireTemperatureController,
                    COMBUSTION_TEMPERATURE_RUN_STATE_SETPOINT);

            break;
            /*----------------------------------------------------------------------------*/
        case IDLE_STATE:

            break;
            /*----------------------------------------------------------------------------*/
        case RELOAD_STATE:

            PIDControllerChangeGains(waterOutTemperatureController,
                    WATER_OUT_TEMPERATURE_RELOAD_STATE_PROPORTIONAL_GAIN,
                    WATER_OUT_TEMPERATURE_RELOAD_STATE_INTEGRAL_GAIN,
                    WATER_OUT_TEMPERATURE_RELOAD_STATE_DERIVATIVE_GAIN);

            //dynamic setpoint to follow stack temperature (assume it decays linearly))
            PIDControllerChangeSetPoint(waterOutTemperatureController,
                    stackTemperature);

            break;
        default:
            break;
    }
}


/* main loop */

/*----------------------------------------------------------------------------*/
void main(void) {

    systemSetupProcess();

    /* Initialize PID Controllers */
    /*----------------------------------------------------------------------------*/
    waterOutTemperatureController = CreatePIDController(WATER_OUT_TEMPERATURE_RUN_STATE_SETPOINT,
            WATER_OUT_TEMPERATURE_RUN_STATE_PROPORTIONAL_GAIN,
            WATER_OUT_TEMPERATURE_RUN_STATE_INTEGRAL_GAIN,
            WATER_OUT_TEMPERATURE_RUN_STATE_DERIVATIVE_GAIN,
            INDUCER_FAN_MAX_PERCENT_SPEED, INDUCER_FAN_MIN_PERCENT_SPEED);

    oxygenLevelController = CreatePIDController(OXYGEN_RUN_STATE_SETPOINT,
            OXYGEN_TEMPERATURE_RUN_STATE_PROPORTIONAL_GAIN,
            OXYGEN_TEMPERATURE_RUN_STATE_INTEGRAL_GAIN,
            OXYGEN_TEMPERATURE_RUN_STATE_DERIVATIVE_GAIN,
            PRIMARY_DAMPER_MAX_PERCENT, PRIMARY_DAMPER_MIN_PERCENT);

    fireTemperatureController = CreatePIDController(COMBUSTION_TEMPERATURE_RUN_STATE_SETPOINT,
            FIRE_TEMPERATURE_RUN_STATE_PROPORTIONAL_GAIN,
            FIRE_TEMPERATURE_RUN_STATE_INTEGRAL_GAIN,
            FIRE_TEMPERATURE_RUN_STATE_DERIVATIVE_GAIN,
            SECONDARY_DAMPER_MAX_PERCENT, SECONDARY_DAMPER_MIN_PERCENT);

    stackTemperatureController = CreatePIDController(STACK_TEMPERATURE_STARTUP_STATE_SETPOINT,
            STACK_TEMPERATURE_STARTUP_STATE_PROPORTIONAL_GAIN,
            STACK_TEMPERATURE_STARTUP_STATE_INTEGRAL_GAIN,
            STACK_TEMPERATURE_STARTUP_STATE_DERIVATIVE_GAIN,
            INDUCER_FAN_MAX_PERCENT_SPEED, INDUCER_FAN_MIN_PERCENT_SPEED);
    /*----------------------------------------------------------------------------*/

    while (1) {
        ClrWdt(); /* Once per loop. */
        /*----------------------------------------------------------------------------*/
        setLimitsAndSetPointsByState();
        /*----------------------------------------------------------------------------*/
        catalystHeaterProcess();
        /*----------------------------------------------------------------------------*/
        getCurrentValuesFromSensors();
        /*----------------------------------------------------------------------------*/

        /*----------------------------------------------------------------------------*/
        LEDProcess();
        /*----------------------------------------------------------------------------*/
        setCurrentStateAndCatchErrors();
        /*----------------------------------------------------------------------------*/

        if (opState == COLD_START_STATE || opState == WARM_START_STATE || opState == WARM_START_STATE) {
            inducerPercentFanSpeed = PIDControllerUpdate(stackTemperatureController, stackTemperature);
            primaryDamperPosition = PRIMARY_DAMPER_MAX_PERCENT;
            secondaryDamperPosition = SECONDARY_DAMPER_MAX_PERCENT;
        } else if (opState != LOCKOUT_STATE) {
            inducerPercentFanSpeed = PIDControllerUpdate(waterOutTemperatureController, waterOutletTemperature);
            primaryDamperPosition = PIDControllerUpdate(oxygenLevelController, oxygenSensorData);
            secondaryDamperPosition = PIDControllerUpdate(fireTemperatureController, fireTemperature);
        } else {
            inducerPercentFanSpeed = INDUCER_FAN_MIN_PERCENT_SPEED;
            primaryDamperPosition = PRIMARY_DAMPER_MIN_PERCENT;
            secondaryDamperPosition = SECONDARY_DAMPER_MIN_PERCENT;
        }

        /*----------------------------------------------------------------------------*/
        SetPwmPercent(inducerPercentFanSpeed, PWM_PORT_CN10); // update inducer fan position
        SetMotorDamperCmdPosition(CAT_MOTOR_DAMPER, primaryDamperPosition);
        SetMotorDamperCmdPosition(COMB_MOTOR_DAMPER, secondaryDamperPosition);
        /*----------------------------------------------------------------------------*/

        serialOutputProcess();
        /*============================================================================*/
        preformStateMachine();

        updatePIDGainsAndSetPointsFromState();

    }
}
#endif
/*----------------------------------------------------------------------------*/
