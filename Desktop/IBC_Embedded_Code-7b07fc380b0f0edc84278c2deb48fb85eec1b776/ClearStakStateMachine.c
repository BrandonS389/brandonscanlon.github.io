/*******************************************************************************
 *  Part Number: ClearStakStateMachine
 *  File Name: ClearStakStateMachine.c
 *  Date: 3 August 2015
 *
 *  Author: Jeff Wong
 *  Company: Biomass Controls, LLC
 *  (c) 2018 Biomass Controls, LLC
 *
 * VERSION
 * 
 * THIS IS THE GI VERSION 
 * 
 * 
 *  The material contained herein is confidential and proprietary.
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
#include "ClearStakStateMachine.h"

uint8_t runCatTempAchieved209 = 0; // has Cat warmed in Run to full temp

void performMaintenance();


void doManualControl(){
     if(fuelManual)
        fuelFeedAugerPercent    = fuelFeedAugerPercentSetpoint;
    else
        fuelFeedAugerPercentSetpoint    = fuelFeedAugerPercent;
    
    if(ashManual)
        ashRemovalAugerPercent  = ashRemovalAugerPercentSetpoint;
    else
        ashRemovalAugerPercentSetpoint  = ashRemovalAugerPercent;
    
    if(combFanManual && !doorOpenMode)
        combustionFanPercent    = combustionFanPercentSetpoint;
    else
        combustionFanPercentSetpoint    = combustionFanPercent;
    
    if(IDFanManual)
        IDFanPercent = stackFanPercentSetpoint;
    else
        stackFanPercentSetpoint = IDFanPercent;
    
    if(heFanManual)
        hxFanPercent = hxFanPercentSetpoint;
    else
        hxFanPercentSetpoint = hxFanPercent;
    
    if(damperManual && !doorOpenMode)
        primaryDamperPosition= damperSetpoint;
    else
        damperSetpoint = primaryDamperPosition;
    
    if(oilPumpManual)
        oilPumpPercent = oilPumpSetpoint;
    else
        oilPumpSetpoint = oilPumpPercent;
}

/* EXECUTED BEFORE performActuation()  */
void doStateMachine() {
    switch (opState) {
//**************************************************************************
        // case STAND_BY_STATE:
        // /* Transitions */
        // /* Timer Reset Conditions */
        //     stateTimer           = CLEAR;
        //     lowTemperatureTimer  = CLEAR;
        //     highTemperatureTimer = CLEAR;

        //     if (upToTemperatureFA){
        //         opState = RUN_STATE;
        //         stateTimer           = CLEAR;
        //         lowTemperatureTimer  = CLEAR;
        //         highTemperatureTimer = CLEAR;
        //     } 
        //     break;
//**************************************************************************
        case CHECKING_SYSTEM_STATE:
            ashRemovalAugerPercent  = ZERO;
            combustionFanPercent    = ZERO;
            fuelFeedAugerPercent    = ZERO;
            IDFanPercent            = ZERO;
            damperOpenPercent       = CLOSED;
            if(hexType == 0){
                hxFanPercent        = ZERO;
            }
            break;
//**************************************************************************
        case PRIME_STATE:
            if (upToTemperatureFA){
                opState              = RUN_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            if((fireTemperature > 100) && (stateTimer > 2*MINUTES)){
                opState = START_UP_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            if(postCatTemperature > 315){
                opState              = BOOST_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            ashRemovalAugerPercent  = PRIME_ASH_AUGER_PERCENT;
            combustionFanPercent    = PRIME_COMBUSTION_FAN_PERCENT;
            fuelFeedAugerPercent    = PRIME_FUEL_FEED_AUGER_PERCENT;
            IDFanPercent            = PRIME_ID_FAN_PERCENT;
            damperOpenPercent       = PRIME_DAMPER_OPEN_PERCENT;
            if(hexType == 0){
                hxFanPercent        = PRIME_HX_FAN_PERCENT;
            }
            break;
//**************************************************************************
        case START_UP_STATE:
            if(((fireTemperature > 900) && (highTemperatureTimer > 5*MINUTES)) || (hexType == 1 && waterOutletTemperature > 90)){
                opState              = SHUTDOWN_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            if(upToTemperatureFA){
                opState              = RUN_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            if(postCatTemperature > 315){
                opState              = BOOST_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            ashRemovalAugerPercent  = START_UP_ASH_AUGER_PERCENT;
            combustionFanPercent    = START_UP_COMBUSTION_FAN_PERCENT;
            fuelFeedAugerPercent    = START_UP_FUEL_FEED_AUGER_PERCENT;
            IDFanPercent            = START_UP_ID_FAN_PERCENT;
            damperOpenPercent       = START_UP_DAMPER_OPEN_PERCENT;
            if(hexType == 0){
                hxFanPercent        = START_UP_HX_FAN_PERCENT;
            }
            break;
//**************************************************************************
        case BOOST_STATE:
            if(((fireTemperature > 900) && (highTemperatureTimer > 5*MINUTES)) || (hexType == 1 && waterOutletTemperature > 90)){
                opState = SHUTDOWN_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            if(upToTemperatureFA){
                opState = RUN_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
            if (stackTemperature < 100 || fireTemperature < 500){
                highTemperatureTimer = CLEAR;
            }
            if ((highTemperatureTimer > 5*MINUTES) && !steadyBoostReached){
                steadyBoostFuelFeedAugerPercent = fuelFeedAugerPercent;
                steadyBoostReached   = YES;
            }
            if ((highTemperatureTimer > 4*MINUTES) && (stateTimer > MAXIMUM_BOOST_TIME)) { //
                opState              = RUN_STATE;
                stateTimer           = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
                steadyBoostReached   = 0;
            }
            ashRemovalAugerPercent  = BOOST_ASH_AUGER_PERCENT;
            combustionFanPercent    = BOOST_COMBUSTION_FAN_PERCENT;
            fuelFeedAugerPercent    = BOOST_FUEL_FEED_AUGER_PERCENT;
            IDFanPercent            = BOOST_ID_FAN_PERCENT;
            damperOpenPercent       = BOOST_DAMPER_OPEN_PERCENT;
            if(hexType == 0){
                hxFanPercent        = BOOST_HX_FAN_PERCENT;
            }
            break;
//**************************************************************************
        case RUN_STATE:
        /* Transitions */
        /* Timer Reset Conditions */
            if((fireTemperature > 900 && (highTemperatureTimer > 5*MINUTES)) || (hexType == 1 && waterOutletTemperature > 90)){ //Replace with IDLE transision
                opState = SHUTDOWN_STATE;
                stateTimer = CLEAR;
            }
            if (!catIsOverheating && !stackIsOverheating && !fireIsOverheating){
                highTemperatureTimer = CLEAR;
            }
            if (fireIsLit){
                lowTemperatureTimer  = CLEAR;
            }
            if(postCatTemperature < 315 && lowTemperatureTimer > 5*MINUTES){
                opState = START_UP_STATE;
            }
             if(stackTemperature < 95 && lowTemperatureTimer > 5*MINUTES){
                opState = BOOST_STATE;
            }
            ashRemovalAugerPercent  = RUN_ASH_AUGER_PERCENT;
            combustionFanPercent    = RUN_COMBUSTION_FAN_PERCENT;
            fuelFeedAugerPercent    = RUN_FUEL_FEED_AUGER_PERCENT;
            IDFanPercent            = RUN_ID_FAN_PERCENT;
            damperOpenPercent       = RUN_DAMPER_OPEN_PERCENT;
            if(hexType == 0){
                hxFanPercent        = RUN_HX_FAN_PERCENT;
            }
            break;
//**************************************************************************
        case IDLE_STATE:
            ashRemovalAugerPercent  = IDLE_ASH_AUGER_PERCENT;
            combustionFanPercent    = IDLE_COMBUSTION_FAN_PERCENT;
            fuelFeedAugerPercent    = IDLE_FUEL_FEED_AUGER_PERCENT;
            IDFanPercent            = IDLE_ID_FAN_PERCENT;
            damperOpenPercent       = IDLE_DAMPER_OPEN_PERCENT;
            if(hexType == 0){
                hxFanPercent        = IDLE_HX_FAN_PERCENT;
            }
            break;
//**************************************************************************
        case SHUTDOWN_STATE:
            ashRemovalAugerPercent  = SHUTDOWN_ASH_AUGER_PERCENT;
            combustionFanPercent    = SHUTDOWN_COMBUSTION_FAN_PERCENT;
            fuelFeedAugerPercent    = SHUTDOWN_FUEL_FEED_AUGER_PERCENT;
            IDFanPercent            = SHUTDOWN_ID_FAN_PERCENT;
            damperOpenPercent       = SHUTDOWN_DAMPER_OPEN_PERCENT;
            if(hexType == 0){
                hxFanPercent        = SHUTDOWN_HX_FAN_PERCENT;
            }
            break;
//**************************************************************************
    /* Fault states */
        case FIRE_TC_OPEN_CIRCUIT_FAULT_STATE:
            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);
            break;

        case FIRE_TC_SHORT_TO_GND_FAULT_STATE:
            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);
            break;

        case FIRE_TC_SHORT_TO_VCC_FAULT_STATE:
            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);
            break;

        case POST_CAT_TC_OPEN_CIRCUIT_FAULT_STATE:
            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);
            break;

        case POST_CAT_TC_SHORT_TO_GND_FAULT_STATE:
            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);
            break;

        case POST_CAT_TC_SHORT_TO_VCC_FAULT_STATE:
            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);
            break;

        case STACK_TC_OPEN_CIRCUIT_FAULT_STATE:
            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);
            break;

        case STACK_TC_SHORT_TO_GND_FAULT_STATE:
            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);
            break;

        case STACK_TC_SHORT_TO_VCC_FAULT_STATE:
            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_FIRE_GTODP_FUNCT_ARG_FAULT_STATE:
            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_FIRE_TC_TEMP_FUNCTION_ARG_FAULT_STATE:
            DoErrorCadence(FIRE_TC_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_POST_CAT_GTODP_FUNCT_ARG_FAULT_STATE:
            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_FAULT_STATE:
            DoErrorCadence(POST_CAT_TC_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_STACK_GTODP_FUNCT_ARG_FAULT_STATE:
            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_STACK_TC_TEMP_FUNCTION_ARG_FAULT_STATE:
            DoErrorCadence(STACK_TC_FAULT_IND_FLASH_COUNT);
            break;

        case INLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE:
            DoErrorCadence(WATER_IN_THERMISTOR_FAULT_IND_FLASH_COUNT);
            break;

        case INLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE:
            DoErrorCadence(WATER_IN_THERMISTOR_FAULT_IND_FLASH_COUNT);
            break;

        case OUTLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE:
            DoErrorCadence(WATER_OUT_THERMISTOR_FAULT_IND_FLASH_COUNT);
            break;

        case OUTLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE:
            DoErrorCadence(WATER_OUT_THERMISTOR_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_INLET_GTIDP_FUNCT_ARG_FAULT_STATE:
            DoErrorCadence(WATER_IN_THERMISTOR_FAULT_IND_FLASH_COUNT);
            break;

        case BAD_OUTLET_GTIDP_FUNCT_ARG_FAULT_STATE:
            DoErrorCadence(WATER_OUT_THERMISTOR_FAULT_IND_FLASH_COUNT);
            break;

        case MULTIPLE_SENSOR_FAULTS_STATE:
            DoErrorCadence(MULTIPLE_SENSOR_FAULTS_FLASH_COUNT);
            break;

        case PDK_STATE:
            break;

        default:
            DoErrorCadence(UNDEFINED_OP_STATE_FLASH_COUNT);
            break;
    }
}

/* EXECTUTED AFTER doStateMachine() */
void performActuation() {
    switch (opState){
//****************************************************************************************************************************************************
        // case STAND_BY_STATE:
        //     ashRemovalAugerPercent  = STAND_BY_ASH_REMOVAL_AUGER_PERCENT;
        //     combustionFanPercent    = STAND_BY_COMBUSTION_FAN_PERCENT;
        //     fuelFeedAugerPercent    = STAND_BY_FUEL_FEED_PERCENT;
        //     IDFanPercent            = STAND_BY_ID_FAN_PERCENT;
        //     break;
//****************************************************************************************************************************************************
        case CHECKING_SYSTEM_STATE: //Each Actuator Waits For The Previous To Get To 50%
            if(ashRemovalAugerPercent < SYSTEM_CHECK_ASH_REMOVAL_AUGER_PERCENT){
                ashRemovalAugerPercent  += 0.83333333333333333333;
            }
            if(combustionFanPercent < SYSTEM_CHECK_COMBUSTION_FAN_PERCENT && ashRemovalAugerPercent == 50){
                combustionFanPercent    += 0.83333333333333333333;
            }
            if(fuelFeedAugerPercent < SYSTEM_CHECK_FUEL_FEED_PERCENT && combustionFanPercent == 50){
                fuelFeedAugerPercent    += 0.83333333333333333333;
            }
            if(IDFanPercent < SYSTEM_CHECK_ID_FAN_PERCENT && fuelFeedAugerPercent == 50){
                IDFanPercent            += 0.83333333333333333333;
            }
            if(damperOpenPercent < SYSTEM_CHECK_DAMPER_OPEN_PERCENT && IDFanPercent == 50){
                damperOpenPercent       += 0.83333333333333333333;
            }
            if(hexType == 0 && hxFanPercent < SYSTEM_CHECK_HX_FAN_PERCENT && damperOpenPercent == 50){
                hxFanPercent            += 0.83333333333333333333;
            }
            break;
//***************************************************************************************************************************************************
        case PRIME_STATE:
            if(hexType == 0 && stackTemperature > 111){
                if(hxFanPercent < 75){
                    hxFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(hexType == 0 && stackTemperature < 105){
                if(hxFanPercent > 20){
                    hxFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            break;
//***************************************************************************************************************************************************
        case START_UP_STATE:
            if(fireTemperature > 850 && stateTimer > 5*MINUTES){
               if(ashRemovalAugerPercent < 40){
                ashRemovalAugerPercent  += HALF_PERCENT_PER_MINUTE;
               }
            }
            if(hexType == 0 && stackTemperature > 111){
                if(hxFanPercent < 75){
                    hxFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(hexType == 0 && stackTemperature < 105){
                if(hxFanPercent > 20){
                    hxFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 400){
                if(IDFanPercent > 20){
                    IDFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 350){
                if(IDFanPercent < 50){
                    IDFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 800){
                damperOpenPercent = OPEN;
            }
            if(postCatTemperature > 700 || oxygenSensorData > 2500){
                if(damperOpenPercent < OPEN){
                    damperOpenPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 700 || oxygenSensorData < 100){
                if(damperOpenPercent > CLOSED){
                    damperOpenPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(fireTemperature > 750 && fireTemperature < 850){
                if(ashRemovalAugerPercent > 0){
                    ashRemovalAugerPercent  -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(fireTemperature > 800){
                if(combustionFanPercent > 20){
                    combustionFanPercent    -= HALF_PERCENT_PER_MINUTE;
                }  
            }
            if((fireTemperature > 200 && fireTemperature < 750)){
                if(combustionFanPercent < 60)
                combustionFanPercent    += HALF_PERCENT_PER_MINUTE;
            } 
            break;
//***************************************************************************************************************************************************
        case BOOST_STATE:
            if(hexType == 0 && stackTemperature > 111){
                if(hxFanPercent < 75){
                    hxFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(hexType == 0 && stackTemperature < 105){
                if(hxFanPercent > 20){
                    hxFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 400){
                if(IDFanPercent > 20){
                    IDFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 350){
                if(IDFanPercent < 75){
                    IDFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(stackTemperature > 175){
                if(combustionFanPercent > 15){
                    combustionFanPercent    -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(fireTemperature > 800){ /* TOO HOT */
                if(ashRemovalAugerPercent < 60){
                    ashRemovalAugerPercent  += HALF_PERCENT_PER_MINUTE;
                }
                if(combustionFanPercent > 15){
                    combustionFanPercent    -= HALF_PERCENT_PER_MINUTE;
                }
                if(fuelFeedAugerPercent > 12){
                    fuelFeedAugerPercent    -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(fireTemperature < 750){ /* TOO COLD */
                if(combustionFanPercent < 60){
                    combustionFanPercent    += HALF_PERCENT_PER_MINUTE;
                }
                if(fuelFeedAugerPercent < 65){
                    fuelFeedAugerPercent   += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(fireTemperature < 800){
                if(ashRemovalAugerPercent > 0){
                    ashRemovalAugerPercent  -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 800){
                damperOpenPercent = OPEN;
            }
            if((postCatTemperature > 700 && postCatTemperature < 800 )|| oxygenSensorData > 2500){
                if(damperOpenPercent < OPEN){
                    damperOpenPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 700 || oxygenSensorData < 100){
                if(damperOpenPercent > CLOSED){
                    damperOpenPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            break;
//***************************************************************************************************************************************************
        case RUN_STATE:
            if(postCatTemperature > 315){
                lowTemperatureTimer = CLEAR;
            }
            if(hexType == 0 && stackTemperature > 111){
                if(hxFanPercent < 75){
                    hxFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(hexType == 0 && stackTemperature < 105){
                if(hxFanPercent > 20){
                    hxFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 400){
                if(IDFanPercent > 20){
                    IDFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 350){
                if(IDFanPercent < 75){
                    IDFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(stackTemperature > 175){
                if(combustionFanPercent > 15){
                    combustionFanPercent    -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if (stackTemperature > 95){
                lowTemperatureTimer = CLEAR;
            }
            if(fireTemperature > 800){
                if(combustionFanPercent > 15){
                    combustionFanPercent    -= HALF_PERCENT_PER_MINUTE;
                }
                if(fuelFeedAugerPercent > 12){
                    fuelFeedAugerPercent    -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(fireTemperature < 750){
                if(combustionFanPercent < 60){
                    combustionFanPercent    += HALF_PERCENT_PER_MINUTE;
                }
                if(fuelFeedAugerPercent < 100){
                    fuelFeedAugerPercent   += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(fireTemperature > 850){
               if(ashRemovalAugerPercent < 50)
                ashRemovalAugerPercent  += HALF_PERCENT_PER_MINUTE;
            }
            if(fireTemperature < 850){
                if(ashRemovalAugerPercent > 0){
                    ashRemovalAugerPercent  -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 800){
                damperOpenPercent = OPEN;
            }
            if((postCatTemperature > 700 && postCatTemperature < 800) || oxygenSensorData > 2500){
                if(damperOpenPercent < OPEN){
                    damperOpenPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 700 || oxygenSensorData < 100){
                if(damperOpenPercent > CLOSED){
                    damperOpenPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(stateTimer > 60*MINUTES){
                if(ashRemovalAugerPercent < 50){
                    ashRemovalAugerPercent  += HALF_PERCENT_PER_MINUTE;
                }
            }
            performMaintenance();
            break;
//***************************************************************************************************************************************************
         case IDLE_STATE:
            if(postCatTemperature > 800){
                damperOpenPercent = OPEN;
            }
            if(hexType == 0 && stackTemperature > 111){
                if(hxFanPercent < 75){
                    hxFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(hexType == 0 && stackTemperature < 105){
                if(hxFanPercent > 20){
                    hxFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 400){
                if(IDFanPercent > 20){
                    IDFanPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 350){
                if(IDFanPercent < 75){
                    IDFanPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature > 700 || oxygenSensorData > 2500){
                if(damperOpenPercent < OPEN){
                    damperOpenPercent += HALF_PERCENT_PER_MINUTE;
                }
            }
            if(postCatTemperature < 700 || oxygenSensorData < 100){
                if(damperOpenPercent > CLOSED){
                    damperOpenPercent -= HALF_PERCENT_PER_MINUTE;
                }
            }
            //idleStateControl();
            break;
//***************************************************************************************************************************************************
        case SHUTDOWN_STATE:
            if(stackTemperature > 80){
                hxFanPercent += ONE_PERCENT_PER_MINUTE;
            }
            if(stackTemperature < 80){
                hxFanPercent -= ONE_PERCENT_PER_MINUTE;
            }
//-------------------------------------------------------------
            if(postCatTemperature > 315){
                IDFanPercent += ONE_PERCENT_PER_MINUTE;
            }
            if(postCatTemperature < 315){
                IDFanPercent -= ONE_PERCENT_PER_MINUTE;
            }
//-------------------------------------------------------------
            if(fireTemperature > 700){
                combustionFanPercent += ONE_PERCENT_PER_MINUTE;
            }
            if(fireTemperature < 700){
                combustionFanPercent -= ONE_PERCENT_PER_MINUTE;
            }
            break;
//***************************************************************************************************************************************************
        default:
            CONTROLLER_ENABLE = YES; 
            break;
    }
    doManualControl();  
}

void rampMotor(float* motor){  // ramp passed motor
    uint8_t sysRamp = 1.67;   // how fast to ramp
      if(*motor<FULL_SPEED)  // Fuel Ramp
         *motor += sysRamp;
        if(*motor>FULL_SPEED)
            *motor = FULL_SPEED;
}

void zeroMotors(float* motor1, float* motor2,float* motor3,float* motor4){
    *motor1=ZERO;*motor2=ZERO;*motor3=ZERO;*motor4=ZERO;
}

void doSysCheck(){
#define RUNNONE 0
#define RAMPFUEL 1
#define RAMPASH 2
#define RAMPCOMBFAN 3
#define RAMPIDFAN 4
#define OPENDAMPER 5
#define RAMPHEFAN 6
#define RUNALL  7
    
    uint8_t checkState=0;
    
            CONTROLLER_ENABLE = NO;
  
            if(stateTimer < 1*MINUTES){
                checkState=RAMPFUEL;
            }
            else if (stateTimer >= 1*MINUTES && stateTimer <2*MINUTES){
                checkState=RAMPASH;
            }
            else if (stateTimer >= 2*MINUTES && stateTimer <3*MINUTES){
                checkState=RAMPCOMBFAN;
            }
            else if (stateTimer >= 3*MINUTES && stateTimer <4*MINUTES){
                checkState=RAMPIDFAN;
            }
            else if (stateTimer >= 4*MINUTES && stateTimer <5*MINUTES){
                checkState=OPENDAMPER; 
            }
             else if (stateTimer >= 5*MINUTES && stateTimer <6*MINUTES){
                 if(hexType == 0)
                    checkState=RAMPHEFAN;
                 else
                     checkState=RUNALL;
            }
            else if (stateTimer >= 6*MINUTES && stateTimer <7*MINUTES){
                if(hexType == 0)
                    checkState=RUNALL;
                else
                    checkState=RUNNONE;
            }
            else {
                checkState=RUNNONE;
            }
                switch(checkState){
                    case RAMPFUEL:
                        primaryDamperPosition=CLOSED;
                        rampMotor(&fuelFeedAugerPercent);
                        zeroMotors(&ashRemovalAugerPercent,&combustionFanPercent,&IDFanPercent,&hxFanPercent);
                        break;
                    case RAMPASH:
                        rampMotor(&ashRemovalAugerPercent);
                        zeroMotors(&fuelFeedAugerPercent,&combustionFanPercent,&IDFanPercent,&hxFanPercent);
                        break;
                    case RAMPCOMBFAN:
                        rampMotor(&combustionFanPercent);
                        zeroMotors(&fuelFeedAugerPercent,&ashRemovalAugerPercent,&IDFanPercent,&hxFanPercent);
                        break;
                    case RAMPIDFAN:
                        rampMotor(&IDFanPercent);
                        zeroMotors(&fuelFeedAugerPercent,&ashRemovalAugerPercent,&combustionFanPercent,&hxFanPercent);
                        break;
                    case OPENDAMPER:
                        primaryDamperPosition=OPEN;
                        zeroMotors(&fuelFeedAugerPercent,&ashRemovalAugerPercent,&combustionFanPercent,&hxFanPercent);
                        IDFanPercent=ZERO;
                        break;
                    case RAMPHEFAN:
                        rampMotor(&hxFanPercent);
                        zeroMotors(&fuelFeedAugerPercent,&ashRemovalAugerPercent,&combustionFanPercent,&IDFanPercent);
                        primaryDamperPosition=CLOSED;
                        break;
                    case RUNALL:
                        hxFanPercent=FULL_SPEED;fuelFeedAugerPercent=FULL_SPEED;ashRemovalAugerPercent=FULL_SPEED;combustionFanPercent=FULL_SPEED;IDFanPercent=FULL_SPEED;
                        primaryDamperPosition=OPEN;
                        break;
                    case RUNNONE:
                        zeroMotors(&fuelFeedAugerPercent,&ashRemovalAugerPercent,&combustionFanPercent,&IDFanPercent);
                        hxFanPercent=ZERO;  primaryDamperPosition=CLOSED;
                        break;
                        }
}
    
void doSysCheckCHP(){  //ramp each motor for 60 secs, hold at 100 for 15, ramp back down 60, pause 15 secs, repeat for next motor, for CHP analysis
   
    uint8_t noAction = 15; // 15 secs of nothing between motor tests
    uint16_t endRamp = 300;  // 75 seconds, upped to 300 8/9/18
     float sysRamp = 1.67; //ramp to 100 over a minute
     
     if(stateTimer < 1*MINUTES+endRamp+noAction){
                if(fuelFeedAugerPercent<FULL_SPEED)  // Fuel Ramp
                    fuelFeedAugerPercent += sysRamp;
                combustionFanPercent    = ZERO;
                ashRemovalAugerPercent  = ZERO;
                IDFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                oilPumpPercent = ZERO;               
            }
     else if(stateTimer >= 1*MINUTES+endRamp+noAction && stateTimer < 1*MINUTES+endRamp){ // Fuel DeRamp
                    if(fuelFeedAugerPercent>ZERO)
                        fuelFeedAugerPercent -= sysRamp;
                    combustionFanPercent    = ZERO;
                    ashRemovalAugerPercent  = ZERO;
                    IDFanPercent            = ZERO;
                    primaryDamperPosition  = CLOSED;
                    hxFanPercent = ZERO;
                    oilPumpPercent = ZERO;               
                } 
     else if((stateTimer >= (1*MINUTES+endRamp+noAction)) && (stateTimer < (1*MINUTES+endRamp*2+noAction))){ //ash ramp
                if(ashRemovalAugerPercent<FULL_SPEED)
                    ashRemovalAugerPercent += sysRamp;
                combustionFanPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                IDFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                oilPumpPercent = ZERO;               
            }
     else if(stateTimer >= 1*MINUTES+endRamp*2+noAction && stateTimer < 1*MINUTES+endRamp*2+noAction+60){ // ash deramp
                if(ashRemovalAugerPercent>ZERO)
                    ashRemovalAugerPercent -= sysRamp;
                combustionFanPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                IDFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                oilPumpPercent = ZERO;               
            }
     else if(stateTimer >=1*MINUTES+endRamp*2+noAction*2+60  && stateTimer < 1*MINUTES+endRamp*3+noAction*2+60){ // comb ramp
                if(combustionFanPercent<FULL_SPEED)
                    combustionFanPercent += sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                IDFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                oilPumpPercent = ZERO;               
            }
     else if(stateTimer >=1*MINUTES+endRamp*3+noAction*2+60  && stateTimer < 1*MINUTES+endRamp*3+noAction*2+60*2){ // comb ramp down
                if(combustionFanPercent>ZERO)
                    combustionFanPercent -= sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                IDFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                oilPumpPercent = ZERO;               
            }
    else if(stateTimer >=1*MINUTES+endRamp*3+noAction*3+60*2  && stateTimer < 1*MINUTES+endRamp*4+noAction*3+60*2){ // id ramp
                if(IDFanPercent<FULL_SPEED)
                    IDFanPercent += sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                oilPumpPercent = ZERO;               
            }
     else if(stateTimer >=1*MINUTES+endRamp*4+noAction*3+60*2  && stateTimer < 1*MINUTES+endRamp*4+noAction*3+60*3){ // id ramp down
                if(IDFanPercent>ZERO)
                    IDFanPercent -= sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                oilPumpPercent = ZERO;               
            }/* not needed, GI Putnam
    else if(stateTimer >=1*MINUTES+endRamp*4+noAction*4+60*3  && stateTimer < 1*MINUTES+endRamp*5+noAction*4+60*3){ // oil ramp
                if(oilPumpPercent<FULL_SPEED)
                    oilPumpPercent += sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                IDFanPercent = ZERO;               
            }
    else if(stateTimer >=1*MINUTES+endRamp*5+noAction*4+60*3  && stateTimer < 1*MINUTES+endRamp*5+noAction*4+60*4){ // oil ramp down
                if(oilPumpPercent>ZERO)
                    oilPumpPercent -= sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                hxFanPercent = ZERO;
                IDFanPercent = ZERO;               
            }
    else if(stateTimer >=1*MINUTES+endRamp*5+noAction*5+60*4  && stateTimer < 1*MINUTES+endRamp*6+noAction*5+60*4){ // damper ramp
                if(primaryDamperPosition<OPEN)
                    primaryDamperPosition += sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                hxFanPercent  = ZERO;
                oilPumpPercent = ZERO;
                IDFanPercent = ZERO;               
            }
    else if(stateTimer >=1*MINUTES+endRamp*6+noAction*5+60*4  && stateTimer < 1*MINUTES+endRamp*6+noAction*5+60*5){ // damper ramp down
                if(primaryDamperPosition > CLOSED)
                    primaryDamperPosition -= sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                hxFanPercent  = ZERO;
                oilPumpPercent = ZERO;
                IDFanPercent = ZERO;               
            }
     else if(stateTimer >=1*MINUTES+endRamp*6+noAction*6+60*5 && stateTimer < 1*MINUTES+endRamp*7+noAction*6+60*5){ // HEX Fan ramp
                if(hxFanPercent<FULL_SPEED)
                    hxFanPercent += sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                oilPumpPercent = ZERO;
                IDFanPercent = ZERO;               
            }
     else if(stateTimer >= 1*MINUTES+endRamp*7+noAction*6+60*5 && stateTimer < 1*MINUTES+endRamp*7+noAction*6+60*6){ // HEX Fan ramp down
                if(hxFanPercent>ZERO)
                    hxFanPercent -= sysRamp;
                ashRemovalAugerPercent    = ZERO;
                fuelFeedAugerPercent  = ZERO;
                combustionFanPercent            = ZERO;
                primaryDamperPosition  = CLOSED;
                oilPumpPercent = ZERO;
                IDFanPercent = ZERO;               
            }
    else if(stateTimer >=1*MINUTES+endRamp*7+noAction*7+60*6 && stateTimer < 1*MINUTES+endRamp*8+noAction*7+60*6){ // ALL ramp
                if(hxFanPercent<FULL_SPEED){
                    hxFanPercent += sysRamp;
                    ashRemovalAugerPercent+= sysRamp;
                    fuelFeedAugerPercent+= sysRamp;
                    combustionFanPercent+= sysRamp;
                    primaryDamperPosition += sysRamp;
                    oilPumpPercent+= sysRamp;
                    IDFanPercent += sysRamp;   
                }
            }
    else if(stateTimer >= 1*MINUTES+endRamp*8+noAction*7+60*6 && stateTimer < 1*MINUTES+endRamp*8+noAction*7+60*7){ // ALL ramp down
                if(hxFanPercent>ZERO){
                    hxFanPercent -= sysRamp;
                    ashRemovalAugerPercent-= sysRamp;
                    fuelFeedAugerPercent-= sysRamp;
                    combustionFanPercent-= sysRamp;
                    primaryDamperPosition -= sysRamp;
                    oilPumpPercent-= sysRamp;
                    IDFanPercent -= sysRamp;   
                }
            } */
            else {
                fuelFeedAugerPercent    = ZERO;
                combustionFanPercent    = ZERO;
                ashRemovalAugerPercent  = ZERO;
                IDFanPercent            = ZERO;
                hxFanPercent           = ZERO;
                primaryDamperPosition = CLOSED;
                oilPumpPercent = ZERO;
            }

             
     }

void errorCheck(){
    
    if (doorOpenMode){
        combustionFanPercent = DOOR_OPEN_COMBUSTION_FAN_PERCENT;
        primaryDamperPosition = CLOSED;
    }
 /*   if fireTemperature < 537 || hadPreviousBuildup){ // build up in pot
        CONTROLLER_ENABLE       = NO;
        hadPreviousBuildup      = TRUE;
        fuelFeedAugerPercent    = 30.0;
        combustionFanPercent    = HALF_SPEED;
        oxygenController.errorIntegral = 167;

        }
    if (fireTemperature > 565) { // hysteresis for build up
        hadPreviousBuildup = FALSE;
    }
    */
    
    if (hexType == 1 && waterOutletTemperature > NEAR_BOILING){
        opState = SHUTDOWN_STATE;
        alertCode=BOIL_OVER;
    }
    
       if (catIsOverheating || stackIsOverheating || fireIsOverheating){
           if(oldFuelRate==0)
             oldFuelRate=fuelFeedAugerPercent*.75;   // remember where to resume, try 75% of rate that caused overheat 4/19
            fuelFeedAugerPercent=0;  // cut fuel
            if(averageO2 < 200)
                combustionFanPercent = DOOR_OPEN_COMBUSTION_FAN_PERCENT; //cool the fire
                
            if(opState == BOOST_STATE)
                alertCode=BOOST_OVERHEAT;
            else if(opState==RUN_STATE)
                alertCode=RUN_OVERHEAT;
        }
       else if(alertCode==BOOST_OVERHEAT || alertCode==RUN_OVERHEAT)
           alertCode=0;  //all clear
       if(fireTemperature > highestFireSoFar)
           highestFireSoFar = fireTemperature;
       
       if(alertCode != BOOST_OVERHEAT && alertCode != RUN_OVERHEAT){ // we already cut fuel for other reasons
            if(fireTemperature < FIRE_BUILD_UP_INDICATION && highestFireSoFar > (FIRE_BUILD_UP_INDICATION+50) && (opState != START_UP_STATE) && opState != SHUTDOWN_STATE && !isCow){ //probe getting buried
                if(hasDamper)
                    fuelFeedAugerPercent = 0;  // don't cut for GI2/3 this is probably a power loss
                if(!buildUpMode){
                    previousAshRemovalAugerPercent = ashRemovalAugerPercent; // remember
                    buildUpMode = 1;
                    alertCode=POT_OVERFLOW;
                    
                }
                ashRemovalAugerPercent=100;
            }
            else {
                if(buildUpMode){
                    ashRemovalAugerPercent = previousAshRemovalAugerPercent; // restore
                    buildUpMode = 0; //clear
                    if(alertCode == POT_OVERFLOW)
                        alertCode=0;
                }
            }
       }
    
    if(waterOutletTemperature > NEAR_BOILING -5){
        IDFanPercent = MINIMUM_ID_FAN_PERCENT_AIR; // cut heat to stack
        alertCode=BOIL_OVER;
    }
    else
        if(alertCode==BOIL_OVER)
            alertCode=0; //clear it
    
    if(mary){
        if(fuelFeedAugerPercent > MAXIMUM_FUEL_RATE_MARY)
            fuelFeedAugerPercent = MAXIMUM_FUEL_RATE_MARY;
        }
    else if(powerGenerator){
        if(fuelFeedAugerPercent > MAXIMUM_FUEL_RATE_POWER)
            fuelFeedAugerPercent = MAXIMUM_FUEL_RATE_POWER;
    }
    else
        if(fuelFeedAugerPercent > MAXIMUM_FUEL_RATE)
            fuelFeedAugerPercent = MAXIMUM_FUEL_RATE;
    
    if (averageO2 > NO_OXYGEN){
        m_LOW_OXY_LED_SET_ON();
        combustionFanPercent = 100;
    } else {
        m_LOW_OXY_LED_SET_OFF();
    }
    
 //   sensorFaultCheck();
   
   
    
}

//Kivalina code
void performMaintenance(){
    
    /*if (doorOpenMode){
        combustionFanPercent = DOOR_OPEN_COMBUSTION_FAN_PERCENT;
    }*/
/* 
 comment out build up code for food waste testing RIT 6/13/17
    if (fireTemperature < 593 || hadPreviousBuildup){ // build up in pot
        CONTROLLER_ENABLE       = NO;
        hadPreviousBuildup      = TRUE;
        fuelFeedAugerPercent    = 30.0;
        combustionFanPercent    = HALF_SPEED;
        oxygenController.errorIntegral = 167;

        }
    if (fireTemperature > 621) { // hysteresis for build up
        hadPreviousBuildup = FALSE;

    }
 */
    
    if (oxygenSensorData > 2500){
        IDFanPercent = FULL_SPEED;
    }
}
/*
void idFanRampDown() {
               //Lower O2 gradually upon entering run 4/11/17
            if(stateTimer <= 10 * MINUTES){
                POST_CAT_OXYGEN_SETPOINT = RUN_POST_CAT_OXYGEN_SETPOINT *.25;  // 1st ten minutes @ 25% of final A/D
                IDFanPercent = BOOST_ID_FAN_PERCENT;    // keep the same first 10 mins
            }
            else if(stateTimer > 10 * MINUTES && stateTimer <= 20*MINUTES){  // next 10 @ 50%
                POST_CAT_OXYGEN_SETPOINT = RUN_POST_CAT_OXYGEN_SETPOINT *.5;
                IDFanPercent = BOOST_ID_FAN_PERCENT * .75;    // ramp down to .75 of what we had
            }
            else if(stateTimer > 20 * MINUTES && stateTimer <= 30*MINUTES){ // next 10 @ 75%
                POST_CAT_OXYGEN_SETPOINT = RUN_POST_CAT_OXYGEN_SETPOINT *.75;
                IDFanPercent = BOOST_ID_FAN_PERCENT * .50;    // ramp down to 1/2 of what we had
            }else {
                    POST_CAT_OXYGEN_SETPOINT = RUN_POST_CAT_OXYGEN_SETPOINT;
                    IDFanPercent = BOOST_ID_FAN_PERCENT * .25;   
            }
        
}
*/

// turn everything on for UL test
/*
void ulTest() {
     fuelFeedAugerPercent     = 100; // controls fire or cat temp
 combustionFanPercent     = 100; // controls oxygen
 stackFanPercent          = 100; // controls stack temp NOT IN THIS VERSION IT DON'T
 IDFanPercent             = 100; // controls stack temp
 primaryDamperPosition = 100;
 ashRemovalAugerPercent   = 100;
 	m_LOCKOUT_EXT_LED_SET_ON();      LOCKOUT_EXT_LED = EXT_LED_ON;
//	m_LOCKOUT_EXT_LED_SET_OFF();     LOCKOUT_EXT_LED = EXT_LED_OFF;



 m_HEAT_CALL_LED_SET_ON();        //HEAT_CALL_LED = LED_ON;
// m_HEAT_CALL_LED_SET_OFF();       //HEAT_CALL_LED = LED_OFF;

	m_CAT_HEATER_LED_SET_ON();       //CAT_HEATER_LED = LED_ON;
//	m_CAT_HEATER_LED_SET_OFF();      //CAT_HEATER_LED = LED_OFF;

	m_DAMPER_FUEL_AUGER_LED_SET_ON();   // DAMPER_FUEL_AUGER_LED = LED_ON;
//	m_DAMPER_FUEL_AUGER_LED_SET_OFF();   //DAMPER_FUEL_AUGER_LED = LED_OFF;

 m_REAR_FAN_ASH_AUGER_LED_SET_ON();   //REAR_FAN_ASH_AUGER_LED = LED_ON;
// m_REAR_FAN_ASH_AUGER_LED_SET_OFF();  //REAR_FAN_ASH_AUGER_LED = LED_OFF;

	m_LOW_OXY_LED_SET_ON();          //LOW_OXY_LED = LED_ON;
//	m_LOW_OXY_LED_SET_OFF();         //LOW_OXY_LED = LED_OFF;

	m_STANDBY_LOCKOUT_LED_SET_ON();  //STANDBY_LOCKOUT_LED = LED_ON;
//	m_STANDBY_LOCKOUT_LED_SET_OFF(); //STANDBY_LOCKOUT_LED = LED_OFF;

	m_ALARM_ALERT_LED_SET_ON();      //ALARM_ALERT_LED = LED_ON;
//	m_ALARM_ALERT_LED_SET_OFF();    //ALARM_ALERT_LED = LED_OFF;
    
}
*/