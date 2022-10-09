/*******************************************************************************
 *  Part Number: ClearStakEEPROMHandler
 *  File Name: ClearStakEEPROMHandler.c
 *  Date: 13 January 2016
 *
 *  Author: Clancy Emanuel
 *  Company: Biomass Controls, LLC
 *  (c) 2015 Biomass Controls, LLC
 *
 *  Licensee: ClearStak, LLC
 *
 *  The material contained herein is confidential and proprietary.
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
#include <stdbool.h>        /* For true/false definition */
#include <string.h>

#endif

#include "ClearStakEEPROMHandler.h"


void writeSetpointToEEPROM(char* aSetpointKey, char* aSetpointValue) {
    char null_character = '\0';
    if(!strcmp(aSetpointKey, "WaterOutTempSetpoint")) {
        Write_b_eep(WATER_OUT_TEMP_SETPOINT_WRITTEN_EEPROM_ADDRESS, EEPROM_SET);
        int i = 0;
        while(aSetpointValue[i] != null_character) {
            Write_b_eep(WATER_OUT_TEMP_SETPOINT_EEPROM_ADDRESS+i,aSetpointValue[i]);
            i++;
        }
        Write_b_eep(WATER_OUT_TEMP_SETPOINT_EEPROM_ADDRESS+i,null_character);
    } else if(!strcmp(aSetpointKey, "O2LevelSetpoint")) {
        Write_b_eep(O2_LEVEL_RUN_STATE_SETPOINT_WRITTEN_EEPROM_ADDRESS,EEPROM_SET);
        int i = 0;
        while(aSetpointValue[i] != null_character) {
            Write_b_eep(O2_LEVEL_RUN_STATE_SETPOINT_EEPROM_ADDRESS+i,aSetpointValue[i]);
            i++;
        }
        Write_b_eep(O2_LEVEL_RUN_STATE_SETPOINT_EEPROM_ADDRESS+i,null_character);
    }
}
char* readSetpointFromEEPROM(char* aSetpointKey) {
    char returnValue[20]; 
    returnValue[0] = '\0';
    int i = 0;
    if(!strcmp(aSetpointKey, "WaterOutTempSetpoint")) {
        char temp = Read_b_eep(WATER_OUT_TEMP_SETPOINT_WRITTEN_EEPROM_ADDRESS);
        if(temp != EEPROM_CLEAR) {
            temp = Read_b_eep(WATER_OUT_TEMP_SETPOINT_EEPROM_ADDRESS + i);
            while(temp != '\0') {
                returnValue[i] = temp;
                i++;
                temp = Read_b_eep(WATER_OUT_TEMP_SETPOINT_EEPROM_ADDRESS + i);
            }
            returnValue[i] = '\0';
        }
    } else if(!strcmp(aSetpointKey, "O2LevelSetpoint")) {
        char temp = Read_b_eep(O2_LEVEL_RUN_STATE_SETPOINT_WRITTEN_EEPROM_ADDRESS);
        if(temp != EEPROM_CLEAR) {
            temp = Read_b_eep(O2_LEVEL_RUN_STATE_SETPOINT_EEPROM_ADDRESS + i);
            while(temp != '\0') {
                returnValue[i] = temp;
                i++;
                temp = Read_b_eep(O2_LEVEL_RUN_STATE_SETPOINT_EEPROM_ADDRESS + i);
            }
            returnValue[i] = '\0';
        }
    }
    return returnValue;
}

bool setpointExists(char* aKey) {
    bool existence = false;
    if(!strcmp(aKey, "WaterOutTempSetpoint")) {
        if (Read_b_eep(WATER_OUT_TEMP_SETPOINT_WRITTEN_EEPROM_ADDRESS) == EEPROM_SET) {
            existence = true;
        }
    } else if(!strcmp(aKey, "O2LevelSetpoint")) {
        if (Read_b_eep(O2_LEVEL_RUN_STATE_SETPOINT_WRITTEN_EEPROM_ADDRESS) == EEPROM_SET) {
            existence = true;
        }
    }
    return existence;
}