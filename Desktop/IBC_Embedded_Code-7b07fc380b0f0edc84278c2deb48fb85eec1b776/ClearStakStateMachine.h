/* 
 * File:   ClearStakStateMachine.h
 * Author: David
 *
 * Created on August 3, 2015, 10:40 PM
 * Updated 2017: Jeff W.
 */

#ifndef CLEARSTAKSTATEMACHINE_H
#define	CLEARSTAKSTATEMACHINE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void doStateMachine();
void performActuation();

#ifdef	__cplusplus
}
#endif

#endif	/* CLEARSTAKSTATEMACHINE_H */

#define fireIsLit (fireTemperature >= MINIMUM_FIRE_TEMP)
#define fireIsNotLit (fireTemperature < MINIMUM_FIRE_TEMP)
#define SMOKING (oxygenSensorData > NO_OXYGEN)
#define AMBIENT (oxygenSensorData < AMBIENT_OXYGEN)
#define catIsOverheating (postCatTemperature > MAXIMUM_CATALYST_TEMP)
#define stackIsOverheating (stackTemperature > MAXIMUM_STACK_TEMP)
#define fireIsOverheating (fireTemperature > MAXIMUM_FIRE_TEMP)
//kivalina
#define upToTemperatureFA (stackTemperature > ESC_START_UP_TRANSITION_STACK_TEMPERATURE && postCatTemperature > ESC_START_UP_TRANSITION_CAT_TEMPERATURE)
#define upToTemperatureHydro (stackTemperature >= ESC_START_UP_TRANSITION_STACK_TEMPERATURE && postCatTemperature >= ESC_START_UP_TRANSITION_CAT_TEMPERATURE && waterOutletTemperature >= ESC_BOOST_WATER_OUT_TEMP)  
#define waterUpToTemperature (waterOutletTemperature > ESC_BOOST_WATER_OUT_TEMP) // ready for Run
#define airUpToTemperature (stackTemperature > MINIMUM_RUN_STACK)
#define catUpToTemperature (postCatTemperature > MINIMUM_RUN_CAT)
#define fireGettingTooHot (fireTemperature > RUN_FIRE_TARGET+25)  // back the fuel off 

float fuelFeedAugerPercentToFanSpeed();
void errorCheck();
void setIdFan();   // set Id fan by stack temp
void doRun();
void sensorFaultCheck();
uint8_t analyzeTemps(uint8_t dryFuel);
void doSysCheckCHP();
void doSysCheck();
//void ulTest();
// uint8_t doUlTest=1;


#define STARTUP_COLD                          40
#define STARTUP_WARM                          41
#define STARTUP_END                           49
#define STANDBY_IDLE                          50
#define STANDBY_PRIME                         51
#define BOOST_START                           30
#define BOOSTING                              31
#define BOOST_TOO_HOT                         32
#define BOOST_GOOD                            33
#define RUN_START                             10
#define RUN_NORMAL                            11
#define RUN_HOT                               12
#define RUN_COLD                              13
#define RUN_DRY                               14
#define RUN_HOT_CAT                             15
#define RUN_GI7                                 16
#define RUN_WET                               19
#define SHUTDOWN_START                        100
#define SHUTDOWN_DECREASE_FUEL                101
#define SHUTDOWN_PULSE_FUEL                   102
#define SHUTDOWN_STEADY_FUEL                  103

#define GOOD    1 // TEMPS ARE GOOD
#define HOT     2
#define COLD    3
#define TANKING 4  //fire getting put out

#define WET   0
#define DRY   1