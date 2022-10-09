/* 
 * File:   ClearStakEEPROMHandler.h
 * Author: clancyemanuel
 *
 * Created on January 13, 2016, 11:14 PM
 */

#ifndef CLEARSTAKEEPROMHANDLER_H
#define	CLEARSTAKEEPROMHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#if defined(__XC) || defined(HI_TECH_C)

#include <stdbool.h>        /* For true/false definition */

#endif
#define EEPROM_SET 0
#define EEPROM_CLEAR 0xff
    
// 20 chars are allocated for each setpoint in EEPROM
#define WATER_OUT_TEMP_SETPOINT_WRITTEN_EEPROM_ADDRESS 0x0001
#define O2_LEVEL_RUN_STATE_SETPOINT_WRITTEN_EEPROM_ADDRESS 0x0002
#define WATER_OUT_TEMP_SETPOINT_EEPROM_ADDRESS 0x000a //10
#define O2_LEVEL_RUN_STATE_SETPOINT_EEPROM_ADDRESS 0x001e //30

void writeSetpointToEEPROM(char* aSetpointKey, char* aSetpointValue);
char* readSetpointFromEEPROM(char* aSetpointKey);
bool setpointExists(char* aKey);

#ifdef	__cplusplus
}
#endif

#endif	/* CLEARSTAKEEPROMHANDLER_H */

