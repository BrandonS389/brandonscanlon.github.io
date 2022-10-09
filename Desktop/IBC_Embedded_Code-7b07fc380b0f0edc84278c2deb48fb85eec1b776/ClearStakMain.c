/*
 * File:   ClearStakMain.c
 * Author: Jeff W
 *
 * THIS VERSION IS FOR Biomass Controls Bio Refineries--all types
 * 
 * 
 * 
 */


//TEST
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
#include <math.h>
#include "ClearStakMain.h"
#include "cs_woodmaster_400_wattnode.h"
#include "cs_woodmaster_400_user.h"

#define TURN_ON 1
#define TURN_OFF 0
#define CONFIG_ALL 1
#define CONFIG_ASH 2
#define CONFIG_FUEL 3
#define CONFIG_FAN 4
#define CONFIG_OPUMP 6

// command codes from PI
#define MANUALCONTROLSETPOINT       47 //"ManualControlSetpoint"   //47
#define FUELAUGERCMDSETPOINT        41
#define COMBFANCMDSETPOINT          40
#define STACKFANSETPOINT            66
#define ASHREMOVALAUGERSETPOINT     67
#define FIRETEMPSETPOINT            78
#define SHUTDOWN                    73
#define STARTUP                     74 //Not in use
#define FUELTYPE                    79
#define DOOROPEN                    80
#define PRIMEMODE                   75 //"PrimeMode"       //75
#define SYSTEMCHECK                 76 //"SystemCheck"   //76
#define FIRETEMPSETPOINT            78
#define ASHVFD                      81
#define FUELVFD                     82
#define FANVFD                      83
#define REBOOT                      84
#define FUELMANUAL                  85
#define ASHMANUAL                   86
#define COMBFANMANUAL               87
#define IDFANMANUAL                 88
#define IDFANSETPOINT               89
#define HEFANMANUAL                 93
#define HEFANPOWER                  94
#define HEFANSETPOINT               92
#define DAMPERMANUAL                95
#define DAMPERPOWER                 90
#define HEX                         91   // heat exchanger 1=hydronic, 2=forced air
#define DRYFUEL                     96
#define UNITNUM                     101   // which GI it is
#define THERMO4                     102
#define THERMO5                     103
#define THERMO6                     104
#define THERMI3                     105
#define THERMI4                     106
#define OILPUMPSETPOINT             110
#define OILPUMPMANUAL               111
#define OILPUMPVFD                  112

volatile ClearStakDataTable keysAndValues; //from what I can tell, this points to the received serial string to make the key/value pair table.
volatile ClearStakOutputHandler outputHandler;
volatile uint8_t temp=0;
volatile uint8_t fuelReported=0,ashReported=0,combFanReported=0,idFanReported=0,heFanReported=0,damperReported=0;     
float filterReading(float filteredReading,float newReading);
void ledLights(uint8_t onOff);
extern void doSerialReceiveStateMachine(uint8_t which);
extern void clearReceivedMessage(uint8_t which);

void checkForChangedSetpoints() {
    unsigned char*** keyValuePairs = getKeyValuePairs();
    for (int i = 0; i < numberOfEditableVariables; i++) {
        if (!strncmp(keyValuePairs[0][i], "ManualControlSetpoint", 21)) {
            uint8_t manualControlCheck = atoi(keyValuePairs[1][i]);
            if (manualControlCheck == 1) {
                manualControl = 1;
            } else if (manualControlCheck == 0) {
                manualControl = 0;
            }
        } else if (!strncmp(keyValuePairs[0][i], "FuelAugerCmdSetpoint", 20)) {
            fuelFeedAugerPercentSetpoint = (float) atoi(keyValuePairs[1][i]);
        } else if (!strncmp(keyValuePairs[0][i], "CombFanCmdSetpoint", 18)) {
            combustionFanPercentSetpoint = (float) atoi(keyValuePairs[1][i]);
        } else if (!strncmp(keyValuePairs[0][i], "StackFanSetpoint", 16)) {
            stackFanPercentSetpoint = (float) atoi(keyValuePairs[1][i]);
        } else if (!strncmp(keyValuePairs[0][i], "AshRemovalAugerSetpoint", 23)) {
            ashRemovalAugerPercentSetpoint = (float) atoi(keyValuePairs[1][i]);
        } else if (!strncmp(keyValuePairs[0][i], "FireTempSetpoint", 16)) {
            CATALYST_TEMPERATURE_SETPOINT = (float) atoi(keyValuePairs[1][i]);
        }
        else if (!strncmp(keyValuePairs[0][i], "Shutdown", 8)) {
            uint8_t shutdownStatus = atoi(keyValuePairs[1][i]);
            if (shutdownStatus == 1){
                opState = SHUTDOWN_STATE;
                stateTimer = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
        } else if (!strncmp(keyValuePairs[0][i], "SystemCheck", 11)) {
            uint8_t systemCheckStatus = atoi(keyValuePairs[1][i]);
            if (systemCheckStatus == 1){
                opState = CHECKING_SYSTEM_STATE;  
                stateTimer = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
        } else if (!strncmp(keyValuePairs[0][i], "StartUp", 7)) {
            uint8_t startUpStatus = atoi(keyValuePairs[1][i]);
            if (startUpStatus == 1){
                opState = START_UP_STATE;  
                stateTimer = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
        } else if (!strncmp(keyValuePairs[0][i], "FuelType", 8)) {
            fuelType = atoi(keyValuePairs[1][i]);
            
        } else if (!strncmp(keyValuePairs[0][i], "DoorOpen", 8)) {
            uint8_t doorStatus = atoi(keyValuePairs[1][i]);
            if (doorStatus == 1){
                doorOpenMode = 1;  
            } else {
                doorOpenMode = 0;
            }
        } else if (!strncmp(keyValuePairs[0][i], "PrimeMode", 9)) {
            uint8_t primeStatus = atoi(keyValuePairs[1][i]);
            if (primeStatus == 1){
                opState = PRIME_STATE;
                stateTimer = CLEAR;
                lowTemperatureTimer  = CLEAR;
                highTemperatureTimer = CLEAR;
            }
        } else if (!strncmp(keyValuePairs[0][i], "Reboot", 6)) {
            uint8_t rebootStatus = atoi(keyValuePairs[1][i]);
            if (rebootStatus == 1) {
                opState = STAND_BY_STATE;
                runTimeSeconds = 0;
                fuelFeedAugerPercent = 0;
                combustionFanPercent = 0;
                ashRemovalAugerPercent = 0;
                IDFanPercent = 0;
                fuelFeedAugerPercentSetpoint = 0;
                combustionFanPercentSetpoint = 0;
                ashRemovalAugerPercentSetpoint = 0;
                stackFanPercentSetpoint = 0;
                manualControl = 0;
                m_LOCKOUT_EXT_LED_SET_OFF()
                m_STANDBY_LOCKOUT_LED_SET_OFF()
                augerTimer = CLEAR;
                lowTemperatureTimer = CLEAR;
                highTemperatureTimer = CLEAR;
                PIDTimer = CLEAR;
                stateTimer = CLEAR;
                catalystHeaterTimer = CLEAR;
                oxygenLevelCounter = CLEAR;
                oneSecondTimer = CLEAR;
                oneSecondTimer2 = CLEAR;
                runTimeSeconds = CLEAR;
                serialDataXmitIntervalTimer = CLEAR;
                lockOutTimer = CLEAR;
                //systemStartupProcess();
            }
        }
    }
}

void getDataReadingFromSensors() {
    
    uint16_t tempWaterInletTemperature=0, tempWaterOutletTemperature=0;
    float tempFireTemperature=0.0,tempPostCatTemperature=0.0, tempStackTemperature=0.0,tempOxygenSensorData=0.0;
    
    sensorFaultBitWord = ReadTemperatureSensors(&tempFireTemperature,
            &fireColdJctTemperature,
            &tempPostCatTemperature,
            &postCatColdJctTemperature,
            &tempStackTemperature,
            &stackColdJctTemperature,
            &tempWaterInletTemperature,
            &tempWaterOutletTemperature);
    
           tempOxygenSensorData  = (float) GetOxySensorData();
            
          
           // if multiple sensors are bad, this code will report the last in the sensor order
            if(tempFireTemperature<1){
                badTC1++;  // another bad reading
                if(badTC1 > BAD_SENSOR_COUNT){
                    alertCode=TC1_FAULT;
                fireTemperature = tempFireTemperature;  // tell 'em the bad news
                }
            }
            else {
                if(tempFireTemperature<MAXIMUM_READING) // ignore noise from shorts if double the previous reading
  //                  fireTemperature = filterReading(fireTemperature,tempFireTemperature); // record the reading
                    fireTemperature=tempFireTemperature;
                badTC1=CLEAR;
            }
           
           if(tempPostCatTemperature<1){
                badTC2++;  // another bad reading
                if(badTC2 > BAD_SENSOR_COUNT){
                    alertCode=TC2_FAULT;
                    postCatTemperature = tempPostCatTemperature;
                }
            }
            else {
               if(tempPostCatTemperature<MAXIMUM_READING) // ignore noise from shorts if double the previous reading
   //                postCatTemperature = filterReading(postCatTemperature,tempPostCatTemperature); // record the reading
                   postCatTemperature=tempPostCatTemperature;
                badTC2=CLEAR;
            }
           
           if(tempStackTemperature<1){
                badTC3++;  // another bad reading
                if(badTC3 > BAD_SENSOR_COUNT){
                    alertCode=TC3_FAULT;
                    stackTemperature = tempStackTemperature;
                }
            }
            else {
               if(tempStackTemperature<MAXIMUM_READING) // ignore noise from shorts if double the previous reading
  //                stackTemperature = filterReading(stackTemperature,tempStackTemperature); // record the reading
                   stackTemperature=tempStackTemperature;
                badTC3=CLEAR;
            }
          
           if(hexType == 1){
                    if(tempWaterInletTemperature<1){
                         badTHERM1++;  // another bad reading
                         if(badTHERM1 > BAD_SENSOR_COUNT){
                             alertCode=THERM1_FAULT;
                             waterInletTemperature = tempWaterInletTemperature;
                         }
                     }
                     else {
                         waterInletTemperature = tempWaterInletTemperature; // record the reading
                         badTHERM1=CLEAR;
                     }

                    if(tempWaterOutletTemperature<1){
                         badTHERM2++;  // another bad reading
                         if(badTHERM2 > BAD_SENSOR_COUNT){
                             alertCode=THERM2_FAULT;
                             waterOutletTemperature = tempWaterOutletTemperature;
                         }
                     }
                     else {
                         waterOutletTemperature = tempWaterOutletTemperature; // record the reading
                         badTHERM2=CLEAR;
                     }
           }
           else {
               waterInletTemperature = tempWaterInletTemperature; // could be using therms for something
               waterOutletTemperature = tempWaterOutletTemperature;
           }
           
           if(tempOxygenSensorData<1){
                badO2++;  // another bad reading
                if(badO2 > BAD_SENSOR_COUNT){
                    alertCode=O2SENSOR_FAULT;
                    oxygenSensorData = tempOxygenSensorData;
                }
            }
            else {
                averageO2 = filterReading(oxygenSensorData,tempOxygenSensorData); // record the reading
                badO2=CLEAR;
            }
           
       
}

void createControllers() {
    
        
    oxygenController = PIDControllerCreate(POST_CAT_OXYGEN_SETPOINT,
            OXYGEN_CONTROLLER_GAIN, OXYGEN_CONTROLLER_INTEGRAL_TIME, OXYGEN_CONTROLLER_DERIVATIVE_TIME, 
            OXYGEN_CONTROLLER_MIN_OUTPUT, OXYGEN_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            OXYGEN_CONTROLLER_INITIAL_OFFSET);
    
 /*       oxygenController = PIDControllerCreate(POST_CAT_OXYGEN_SETPOINT,
            OXYGEN_CONTROLLER_GAIN, OXYGEN_CONTROLLER_INTEGRAL_TIME, OXYGEN_CONTROLLER_DERIVATIVE_TIME, 
            OXYGEN_CONTROLLER_MIN_OUTPUT_MARY, OXYGEN_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            OXYGEN_CONTROLLER_INITIAL_OFFSET); */
        
       idOxygenController = PIDControllerCreate(ID_POST_CAT_OXYGEN_SETPOINT,
            ID_OXYGEN_CONTROLLER_GAIN, ID_OXYGEN_CONTROLLER_INTEGRAL_TIME, ID_OXYGEN_CONTROLLER_DERIVATIVE_TIME, 
            ID_OXYGEN_CONTROLLER_MIN_OUTPUT, ID_OXYGEN_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            ID_OXYGEN_CONTROLLER_INITIAL_OFFSET);
        
    // this is actually for the catalyst temp. I realize it says fire everywhere. UPDATE: fixed most of it
    fireTemperatureController = PIDControllerCreate(CATALYST_TEMPERATURE_SETPOINT,
            CATALYST_CONTROLLER_GAIN, CATALYST_CONTROLLER_INTEGRAL_TIME, CATALYST_CONTROLLER_DERIVATIVE_TIME, 
            CATALYST_CONTROLLER_MIN_OUTPUT, CATALYST_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            CATALYST_CONTROLLER_INITIAL_OFFSET);
    
/*    boostFuelTemperatureController = PIDControllerCreate(CATALYST_TEMPERATURE_SETPOINT,
            CATALYST_CONTROLLER_GAIN, CATALYST_CONTROLLER_INTEGRAL_TIME, CATALYST_CONTROLLER_DERIVATIVE_TIME, 
            START_UP_FUEL_FEED_NO_DAMP, OXYGEN_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            CATALYST_CONTROLLER_INITIAL_OFFSET); // HACK: O2 controller max is 100, so using it.  JW 3/19
    
    boostAirTemperatureController = PIDControllerCreate(BOOST_FIRE_TEMPERATURE_SETPOINT,
            CATALYST_CONTROLLER_GAIN, CATALYST_CONTROLLER_INTEGRAL_TIME, CATALYST_CONTROLLER_DERIVATIVE_TIME, 
            OXYGEN_CONTROLLER_MIN_OUTPUT, OXYGEN_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            CATALYST_CONTROLLER_INITIAL_OFFSET);
    
    boostIDController = PIDControllerCreate(BOOST_WATER_ID_SETPOINT,
            OXYGEN_CONTROLLER_GAIN, OXYGEN_CONTROLLER_INTEGRAL_TIME, OXYGEN_CONTROLLER_DERIVATIVE_TIME, 
            OXYGEN_CONTROLLER_MIN_OUTPUT, OXYGEN_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            OXYGEN_CONTROLLER_INITIAL_OFFSET);  // steal values from O2 controller higher water = higher fan */
    
    stackTemperatureController = PIDControllerCreate(STACK_TEMPERATURE_SETPOINT,
            STACK_CONTROLLER_GAIN, STACK_CONTROLLER_INTEGRAL_TIME, STACK_CONTROLLER_DERIVATIVE_TIME, 
            STACK_CONTROLLER_MIN_OUTPUT, STACK_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            STACK_CONTROLLER_INITIAL_OFFSET);
    
    damperTemperatureController = PIDControllerCreate(DAMPER_TEMPERATURE_SETPOINT,
            DAMPER_CONTROLLER_GAIN, DAMPER_CONTROLLER_INTEGRAL_TIME, DAMPER_CONTROLLER_DERIVATIVE_TIME, 
            DAMPER_CONTROLLER_MIN_OUTPUT, DAMPER_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            DAMPER_CONTROLLER_INITIAL_OFFSET);
    
  /*  waterOutTemperatureController = PIDControllerCreate(WATER_OUT_TEMPERATURE_SETPOINT,
            WATER_OUT_CONTROLLER_GAIN, WATER_OUT_CONTROLLER_INTEGRAL_TIME, WATER_OUT_CONTROLLER_DERIVATIVE_TIME, 
            WATER_OUT_CONTROLLER_MIN_OUTPUT, WATER_OUT_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            WATER_OUT_CONTROLLER_INITIAL_OFFSET);
    waterInTemperatureController = PIDControllerCreate(WATER_IN_TEMPERATURE_SETPOINT,
            WATER_IN_CONTROLLER_GAIN, WATER_IN_CONTROLLER_INTEGRAL_TIME, WATER_IN_CONTROLLER_DERIVATIVE_TIME, 
            WATER_IN_CONTROLLER_MIN_OUTPUT, WATER_IN_CONTROLLER_MAX_OUTPUT, CONTROLLER_SAMPLING_PERIOD, 
            WATER_IN_CONTROLLER_INITIAL_OFFSET); */
}


void dataReadingToSerialOutput() {
    
 
    
char   scaledFireTempValueString[MAX_OUTPUT_VALUE_LENGTH], 
    oxygenSensorDataString[MAX_OUTPUT_VALUE_LENGTH], 
    scaledCatTempValueString[MAX_OUTPUT_VALUE_LENGTH],
    scaledStackTempValueString[MAX_OUTPUT_VALUE_LENGTH],
    scaledWaterOutValueString[MAX_OUTPUT_VALUE_LENGTH],
    scaledWaterInValueString[MAX_OUTPUT_VALUE_LENGTH],
//    REBOOTString[MAX_OUTPUT_VALUE_LENGTH], 
    manualControlString[MAX_OUTPUT_VALUE_LENGTH],
    runtimeOutputString[MAX_OUTPUT_VALUE_LENGTH],  
    //catStatusString[MAX_OUTPUT_VALUE_LENGTH],
    //controllerDutyCycleOutputString[MAX_OUTPUT_VALUE_LENGTH], 
    //integralErrorString[MAX_OUTPUT_VALUE_LENGTH],
    //controllerGainString[MAX_OUTPUT_VALUE_LENGTH],integralTimeString[MAX_OUTPUT_VALUE_LENGTH],
    fuelAugerCmdSetpointString[MAX_OUTPUT_VALUE_LENGTH],
    combFanCmdSetpointString[MAX_OUTPUT_VALUE_LENGTH],
    ashRemovalAugerSetpointString[MAX_OUTPUT_VALUE_LENGTH],
    fuelAugerPctString[MAX_OUTPUT_VALUE_LENGTH],
    combFanPctString[MAX_OUTPUT_VALUE_LENGTH],
    ashRemovalAugerPctString[MAX_OUTPUT_VALUE_LENGTH],
    flowMeterGPMString[MAX_OUTPUT_VALUE_LENGTH],
 //   stackTempSetpointString[MAX_OUTPUT_VALUE_LENGTH],
//    fireTempSetpointString[MAX_OUTPUT_VALUE_LENGTH],    
    energyUsageString[MAX_OUTPUT_VALUE_LENGTH],
    CN10RPMString[MAX_OUTPUT_VALUE_LENGTH],
    hexFanPowerString[MAX_OUTPUT_VALUE_LENGTH],
    IdFanPowerString[MAX_OUTPUT_VALUE_LENGTH],
    CN9RPMString[MAX_OUTPUT_VALUE_LENGTH],
    primaryDamperString[MAX_OUTPUT_VALUE_LENGTH],
    oilPumpPctString[MAX_OUTPUT_VALUE_LENGTH];
    // hopperAugerPercentString[MAX_OUTPUT_VALUE_LENGTH];
    // oxygenPercentSetpointString[MAX_OUTPUT_VALUE_LENGTH];

 char ashManualString[3]=" ",fuelManualString[3]=" ",combFanManualString[3]=" ",IDFanManualString[3]=" ",HeFanManualString[3]=" ",damperManualString[3]=" ",oilPumpManualString[3]=" ";

        if (serialDataXmitIntervalTimer >= (uint8_t) DATA_XMIT_INTERVAL_TIME_S) {
        serialDataXmitIntervalTimer = 0u;
        uint16_t hours;
        uint16_t minutes;
        uint16_t seconds;
        
        if(alertCode==0){
            if ((strlen(opStateNameTextArray[opState])) < (sizeof (unitsString))) {
                strcpy(unitsString, opStateNameTextArray[opState]);
            } else {
                strcpy(unitsString, "szER");
            }
             strncat(unitsString, "_C", (sizeof (unitsString) - (strlen(unitsString) - 1)));
            ledLights(TURN_OFF);
            if(opState == RUN_STATE)
                if(isArtic)
                    strcpy(unitsString,"Run");                   
                else if(dryFuel)
                    strcpy(unitsString,"Run-Dry");
                else
                    strcpy(unitsString,"Run-Wet");
        }
        else{
            switch(alertCode){
                case LOW_FUEL:
                    strcpy(unitsString,"LOW_FUEL");  // fire temp dropped quickly
                    break;
                case BOIL_OVER:
                    strcpy(unitsString,"BOIL_OVER");
                    break;
                case LOW_O2:
                    strcpy(unitsString,"LOW_O2");   // smoking alert
                    break;
                case BOOST_OVERHEAT:
                    strcpy(unitsString,"BOOST_OVERHEAT");
                    break;
                case FIRE_OUT:
                    strcpy(unitsString,"FIRE_OUT");  // fire went out
                    break;
                case RUN_OVERHEAT:
                    strcpy(unitsString,"RUN_OVERHEAT");
                    break;
                case TC1_FAULT:
                    strcpy(unitsString,"TC1_FAULT");
                    break;
                case TC2_FAULT:
                    strcpy(unitsString,"TC2_FAULT");
                    break;  
                case TC3_FAULT:
                    strcpy(unitsString,"TC3_FAULT");
                    break;
                case THERM1_FAULT:
                    strcpy(unitsString,"THERM1_FAULT");
                    break;
                case THERM2_FAULT:
                    strcpy(unitsString,"THERM2_FAULT");
                    break;
                case O2SENSOR_FAULT:
                    strcpy(unitsString,"O2SENSOR_FAULT");
                    break;
                case POT_OVERFLOW:
                    strcpy(unitsString,"POT_OVERFLOW");
                    break;
                default:
                    strcpy(unitsString,"UNKNOWN");
                    break;
            }
            ledLights(TURN_ON);
            alertCode=0;        // reset after reporting, controller must keep raising the code if the condition still exists
        }
        
        
            
        SecondsToHrMinSec(runTimeSeconds, &hours, &minutes, &seconds);

        if (DegCDegFJumper == JUMPER_OUT) /* Jumper is not present. */ {
            scaledWaterInTempValue = waterInletTemperature;
            scaledWaterOutTempValue = waterOutletTemperature;
            scaledFireTempValue = fireTemperature;
//            scaledFireCjTempValue = fireColdJctTemperature;
            scaledCatTempValue = postCatTemperature;
   //         scaledCatCjTempValue = postCatColdJctTemperature;
            scaledStackTempValue = stackTemperature;
    //        scaledStackCjTempValue = stackColdJctTemperature;
   
        }

        sensorStatusMSByte = (uint16_t) (sensorFaultBitWord >> 16);
        sensorStatusLSByte = (uint16_t) sensorFaultBitWord;
        
        sprintf(runtimeOutputString, "%04u:%02u:%02u", hours, minutes, seconds);
 
        sprintf(oxygenSensorDataString, "%.0f", averageO2);
 
        sprintf(scaledFireTempValueString, "%.2f", scaledFireTempValue);
        sprintf(scaledCatTempValueString, "%.2f", scaledCatTempValue);
        sprintf(scaledWaterInValueString, "%03u", scaledWaterInTempValue);
        sprintf(scaledWaterOutValueString, "%03u", scaledWaterOutTempValue);
        sprintf(scaledStackTempValueString, "%.2f", scaledStackTempValue);
 //       sprintf(REBOOTString, "%01u", REBOOT);
        sprintf(manualControlString, "%u", manualControl);
        sprintf(fuelAugerCmdSetpointString, "%.1f", fuelFeedAugerPercentSetpoint);
        sprintf(combFanCmdSetpointString, "%.1f", combustionFanPercentSetpoint);
        sprintf(ashRemovalAugerSetpointString, "%.1f", ashRemovalAugerPercentSetpoint);
        if(maxFuelMode)
            strcpy(fuelAugerPctString,"100.0");
        else
            sprintf(fuelAugerPctString, "%03.1f", fuelFeedAugerPercent);
        sprintf(combFanPctString, "%03.1f", combustionFanPercent);
        sprintf(ashRemovalAugerPctString, "%03.1f", ashRemovalAugerPercent);
        sprintf(CN10RPMString, "%u", cn10RpmBuffer);
        sprintf(CN9RPMString, "%u", cn9RpmBuffer);
        sprintf(energyUsageString, "%.0f", wattNodePower);
        sprintf(flowMeterGPMString, "%u", flowMeterGpm);
       sprintf(primaryDamperString, "%0f", primaryDamperPosition);
       sprintf(IdFanPowerString,"%.1f",IDFanPercent);
       sprintf(hexFanPowerString,"%.1f",hxFanPercent);
    //    sprintf(hopperAugerPercentString,"%03.1f",hopperAugerPercent);
       
       
#if defined (CONTROLLER2)
       
        DataTablePutPair(&keysAndValues, "Thermocouple6", scaledFireTempValueString);
        DataTablePutPair(&keysAndValues, "Thermocouple5", scaledCatTempValueString);
        DataTablePutPair(&keysAndValues, "Thermocouple4", scaledStackTempValueString);
        DataTablePutPair(&keysAndValues, "Thermistor3", scaledWaterInValueString);
        DataTablePutPair(&keysAndValues, "Thermistor4", scaledWaterOutValueString);
        DataTablePutPair(&keysAndValues,"Controller","2");
        DataTablePutPair(&keysAndValues, "Status2", unitsString);
        DataTablePutPair(&keysAndValues, "RunTime2", runtimeOutputString);
        DataTablePutPair(&keysAndValues, "Firmware2", FIRMWARE_VERSION);
 
        oilPumpManualString[0] = OILPUMPMANUAL;
       if(oilPumpManual)
           DataTablePutPair(&keysAndValues,oilPumpManualString,"1");
       else
           DataTablePutPair(&keysAndValues,oilPumpManualString,"0");
        
        if(strlen(msgString)>1){
             DataTablePutPair(&keysAndValues, "ErrorCode2", msgString);
        
#endif
#ifndef CONTROLLER2
        DataTablePutPair(&keysAndValues, "FireTemp", scaledFireTempValueString);
        DataTablePutPair(&keysAndValues, "CatalystTemp", scaledCatTempValueString);
        DataTablePutPair(&keysAndValues, "StackTemp", scaledStackTempValueString);
        DataTablePutPair(&keysAndValues, "WaterInTemp", scaledWaterInValueString);
        DataTablePutPair(&keysAndValues, "WaterOutTemp", scaledWaterOutValueString);
        DataTablePutPair(&keysAndValues,"Controller","1");
        DataTablePutPair(&keysAndValues, "Status", unitsString);
        DataTablePutPair(&keysAndValues, "RunTime", runtimeOutputString);
         DataTablePutPair(&keysAndValues, "O2Level", oxygenSensorDataString);
        
        DataTablePutPair(&keysAndValues, "CN10Rpm", CN10RPMString);
        DataTablePutPair(&keysAndValues, "CN9Rpm", CN9RPMString);
        DataTablePutPair(&keysAndValues, "Watt-hours", energyUsageString);
        DataTablePutPair(&keysAndValues, "FlowRate", flowMeterGPMString);
        sprintf(oilPumpPctString,"%.1f",oilPumpPercent);
       DataTablePutPair(&keysAndValues, "OilPump", oilPumpPctString);
 
 //       DataTablePutPair(&keysAndValues, "Reboot", REBOOTString);
        DataTablePutPair(&keysAndValues, "FirmwareVersion", FIRMWARE_VERSION);
       

        DataTablePutPair(&keysAndValues, "ManualControlSetpoint", manualControlString); //obsolete will have individual control now
        DataTablePutPair(&keysAndValues, "FuelAugerCmdSetpoint", fuelAugerCmdSetpointString);          
        DataTablePutPair(&keysAndValues, "CombFanCmdSetpoint", combFanCmdSetpointString);       
        DataTablePutPair(&keysAndValues, "AshRemovalAugerSetpoint", ashRemovalAugerSetpointString);

       DataTablePutPair(&keysAndValues, "CombFanCmd", combFanPctString);
       DataTablePutPair(&keysAndValues, "FuelAugerCmd", fuelAugerPctString);  // this is the current operational percentage, 'cmd' is confusing but key is already in DB 
       DataTablePutPair(&keysAndValues, "AshRemovalAuger", ashRemovalAugerPctString);
       DataTablePutPair(&keysAndValues, "IdFanPower", IdFanPowerString); 

       DataTablePutPair(&keysAndValues, "CombDamper", primaryDamperString); 
       DataTablePutPair(&keysAndValues, "HEFanPower", hexFanPowerString); 
//       DataTablePutPair(&keysAndValues,"HopperAugerCmd",hopperAugerPercentString);
           
//       sprintf(msg2String,"ManualMode_%u",manualControl);
//      sprintf(msg2String,"Current_Fuel_%s",fuelAugerPctString); 
       
        if(!ashReported){  
            ashManualString[0] = ASHMANUAL; 
            if(ashManual){   
               DataTablePutPair(&keysAndValues,ashManualString,"1"); 
               DataTablePutPair(&keysAndValues,"AshManual","1");     
            }
            else {
                  DataTablePutPair(&keysAndValues,ashManualString,"0");   
                  DataTablePutPair(&keysAndValues,"AshManual","0"); 
            }
            ashReported=1;  // we told 'em
        }
       
       if(!fuelReported){
        fuelManualString[0] = FUELMANUAL;      
        if(fuelManual){
             DataTablePutPair(&keysAndValues,fuelManualString,"1");
             DataTablePutPair(&keysAndValues,"FuelManual","1");
        }
        else{
             DataTablePutPair(&keysAndValues,fuelManualString,"0");
             DataTablePutPair(&keysAndValues,"FuelManual","0");
        }
        fuelReported=1;
       }
        
       if(!combFanReported){
            combFanManualString[0] = COMBFANMANUAL;
            if(combFanManual){
                DataTablePutPair(&keysAndValues,combFanManualString,"1");
                DataTablePutPair(&keysAndValues,"CombFanManual","1");
            }
            else{
                DataTablePutPair(&keysAndValues,combFanManualString,"0");
                DataTablePutPair(&keysAndValues,"CombFanManual","0");
            }
            combFanReported=1;
       }
 
       if(!idFanReported){
            IDFanManualString[0] = IDFANMANUAL;
            if(IDFanManual){
                DataTablePutPair(&keysAndValues,IDFanManualString,"1");
                DataTablePutPair(&keysAndValues,"IDFanManual","1");
            }
            else{
                DataTablePutPair(&keysAndValues,IDFanManualString,"0");
                DataTablePutPair(&keysAndValues,"IDFanManual","0");
            }
            idFanReported=1;
        }
       
       if(!heFanReported){
            HeFanManualString[0] = HEFANMANUAL;
            if(heFanManual){
                DataTablePutPair(&keysAndValues,HeFanManualString,"1");
                DataTablePutPair(&keysAndValues,"HEFanManual","1");
            }
            else{
                DataTablePutPair(&keysAndValues,HeFanManualString,"0");
                DataTablePutPair(&keysAndValues,"HEFanManual","0");
            }
            heFanReported=1;
       }
       
       if(!damperReported){
            damperManualString[0] = DAMPERMANUAL;
            if(damperManual){
                DataTablePutPair(&keysAndValues,damperManualString,"1");
                DataTablePutPair(&keysAndValues,"DamperManual","1");
            }
            else{
                DataTablePutPair(&keysAndValues,damperManualString,"0");
                DataTablePutPair(&keysAndValues,"DamperManual","0");
            }
            damperReported=1;
       }
        
       if(strlen(msgString)>1){
             DataTablePutPair(&keysAndValues, "ErrorCode", msgString);
       
#endif
       
       }
    
//      DataTablePutPair(&keysAndValues, "ErrorCode2", msg2String);
    
        outputEvent(&outputHandler, &keysAndValues);
        strcpy(msgString,"");  //reset string after reporting

    }
}
/*
void sensorFaultCheck() {
    if (sensorFaultBitWord == (uint32_t) NO_SENSOR_FAULT_BITS) {
        if (!(opState <= MAX_OPERATION_STATE)) { //before this was garbage. its better now
            opState = STAND_BY_STATE;
        }
    } else {
        opState = SensorFaultBitsToOpStateIndex(sensorFaultBitWord);
    }
}
*/
void configureVFDs(uint8_t which){
    //wait for drives to turn on
    if(which==CONFIG_ALL)
        for(int i = 0; i < 12; i++)
            __delay_ms(255);

    //configure a drive
    // CHANGED TO SPECIFIC MOTOR TYPES JW 1/20/17
    switch(which){
        case CONFIG_ALL:
            ConfigureVfd (FUEL_FEED_AUGER_VFD,
                             FUEL_MOTOR_RATED_CURRENT,
                             FUEL_MOTOR_RATED_FULL_LOAD_RPM,
                             FUEL_MOTOR_RATED_VOLTAGE,
                             FUEL_MOTOR_RATED_FULL_SPEED_FREQ,
                             FUEL_MOTOR_RATED_POWER_FACTOR); //Add Min Hz & param 44 - VFD address
            ConfigureVfd (COMBUSTION_FAN_VFD,
                             COMB_FAN_MOTOR_RATED_CURRENT,
                             COMB_FAN_MOTOR_RATED_FULL_LOAD_RPM,
                             COMB_FAN_MOTOR_RATED_VOLTAGE,
                             COMB_FAN_MOTOR_RATED_FULL_SPEED_FREQ,
                             COMB_FAN_MOTOR_RATED_POWER_FACTOR);
            ConfigureVfd (ASH_REMOVAL_AUGER_VFD,      
                             ASH_MOTOR_RATED_CURRENT,
                             ASH_MOTOR_RATED_FULL_LOAD_RPM, 
                             ASH_MOTOR_RATED_VOLTAGE,     
                             ASH_MOTOR_RATED_FULL_SPEED_FREQ,
                             ASH_MOTOR_RATED_POWER_FACTOR);
 /*           ConfigureVfd (OIL_PUMP_VFD,
                             OIL_PUMP_MOTOR_RATED_CURRENT,
                             OIL_PUMP_MOTOR_RATED_FULL_LOAD_RPM,
                             OIL_PUMP_MOTOR_RATED_VOLTAGE,
                             OIL_PUMP_MOTOR_RATED_FULL_SPEED_FREQ,
                             OIL_PUMP_MOTOR_RATED_POWER_FACTOR);
            ConfigureVfd (HOPPER_AUGER_VFD,
                             HOPPER_MOTOR_RATED_CURRENT,
                             HOPPER_MOTOR_RATED_FULL_LOAD_RPM,
                             HOPPER_MOTOR_RATED_VOLTAGE,
                             HOPPER_MOTOR_RATED_FULL_SPEED_FREQ,
                             HOPPER_MOTOR_RATED_POWER_FACTOR); */
            break;
            
        case CONFIG_ASH:
            ConfigureVfd (ASH_REMOVAL_AUGER_VFD,             
                             ASH_MOTOR_RATED_CURRENT,       
                             ASH_MOTOR_RATED_FULL_LOAD_RPM,   
                             ASH_MOTOR_RATED_VOLTAGE,         
                             ASH_MOTOR_RATED_FULL_SPEED_FREQ,
                             ASH_MOTOR_RATED_POWER_FACTOR);  
            break;
            
        case CONFIG_FUEL:
            ConfigureVfd (FUEL_FEED_AUGER_VFD,
                             FUEL_MOTOR_RATED_CURRENT,
                             FUEL_MOTOR_RATED_FULL_LOAD_RPM,
                             FUEL_MOTOR_RATED_VOLTAGE,
                             FUEL_MOTOR_RATED_FULL_SPEED_FREQ,
                             FUEL_MOTOR_RATED_POWER_FACTOR);
            break;
            
        case CONFIG_FAN:
             ConfigureVfd (COMBUSTION_FAN_VFD,
                             COMB_FAN_MOTOR_RATED_CURRENT,
                             COMB_FAN_MOTOR_RATED_FULL_LOAD_RPM,
                             COMB_FAN_MOTOR_RATED_VOLTAGE,
                             COMB_FAN_MOTOR_RATED_FULL_SPEED_FREQ,
                             COMB_FAN_MOTOR_RATED_POWER_FACTOR);
        // case CONFIG_OPUMP:
        //      ConfigureVfd (OIL_PUMP_VFD,
        //                      OIL_PUMP_MOTOR_RATED_CURRENT,
        //                      OIL_PUMP_MOTOR_RATED_FULL_LOAD_RPM,
        //                      OIL_PUMP_MOTOR_RATED_VOLTAGE,
        //                      OIL_PUMP_MOTOR_RATED_FULL_SPEED_FREQ,
        //                      OIL_PUMP_MOTOR_RATED_POWER_FACTOR);
             break;       
    }
}

void systemStartupProcess() {
    ClrWdt();
    CONTROLLER_ENABLE = NO;
    ConfigureOscillator();
    InitializeSystem();
    (void) PowerOnSelfTest(&opState, PRIME_STATE);
   m_O2_HEATER_PWR_SET_ON(); // needed to power O2 sensor
    WRITETIMER0(TMR0_01_SEC_PRELOAD_VALUE);
    oneSecondTimer = CLEAR;
    CreateDataTable(&keysAndValues, "KVP");
    CreateOutputHandler(&outputHandler, "OH");
    createControllers();
    clearReceivedMessage(0);
    clearReceivedMessage(1);  // clear both
    CLEAR_EUSART2_ERRORS();
    m_VFD_ENABLE_ASSERT()

    configureVFDs(CONFIG_ALL);
    INTCONbits.GIEH = SET; /* Enable all high priority interrupts. */
    INTCONbits.GIEL = SET; /* Enable all low priority interrupts. */
    
   
}

void getSerialInput() {
    uint8_t buf2Process;
    
    if ((strstr(receivedMessage, STOP_MESSAGE) != NULL)&&(strstr(receivedMessage, START_MESSAGE) != NULL) && !DataRdy2USART()) {
        // If there is a FULL message available and we are done sending over USART...
        // change receive buffers
        if(toggleRcvBuf==0){ //if receiving in buf 0
            receivedMessage=receivedMessage1; // receive future bytes in buf 1
            toggleRcvBuf=1;  // indicate receiving in buf 1
            buf2Process=0; // process data in buf 0
        }
        else {
             //if receiving in buf 1
            receivedMessage=receivedMessage0; // receive future bytes in buf 0
            toggleRcvBuf=0;  // indicate receiving in buf 0
            buf2Process=1;  // process buf 1
        }
        
        doSerialReceiveStateMachine(buf2Process);
        checkForChangedSetpoints();
        clearReceivedMessage(buf2Process);
    } else {
        // In the case of overrun errors we need to clear this bit. The ISR has been optimized to prevent these
        // but if it happens we don't want communication to halt
        CLEAR_EUSART2_ERRORS();
    }
}

// void idleStateControl() {
//     if ((opStateSecondsTimer >= IDLE_STATE_MIN_FIRE_TEMPERATURE_TIME_S) &&
//             (postCatTemperature < IDLE_STATE_MIN_CAT_TEMPERATURE_C)) {
//         (void) FurnaceShutdown();
//         m_LOCKOUT_EXT_LED_SET_ON()
//         m_STANDBY_LOCKOUT_LED_SET_ON()
//         opState = LOCKOUT_STATE;
//     }
// }

// void FurnaceShutdown(void) {
//     if (O2_HEATER_PWR == RELAY_ON) {
//         m_O2_HEATER_PWR_SET_OFF()
//     }
//     return;

void setActuators(){

    float fuelSpeed;
    if(hasHopper && opState == RUN_STATE && dryFuel==00 && fuelManual==00 && fuelFeedAugerPercent >0) // crank it during wet run, but not in manual mode, or when fuel should be 0
    {
        fuelSpeed=MAXIMUM_FUEL_RATE; // run it wide open if vfd on the hopper
        maxFuelMode=1;  // remember for reporting purposes
    }
    else
    {
        fuelSpeed=fuelFeedAugerPercent;
        maxFuelMode=0;
    }

    // set combustion fan speed
    (void) AdjustVfdMotorOperation (COMBUSTION_FAN_VFD, SET_MOTOR_SPEED,
                                    (const uint8_t) combustionFanPercent, COMB_FAN_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
    (void) AdjustVfdMotorOperation (COMBUSTION_FAN_VFD, MOTOR_RUN,
                                    (const uint8_t) combustionFanPercent, COMB_FAN_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
    // set fuel auger speed
    (void) AdjustVfdMotorOperation (FUEL_FEED_AUGER_VFD, SET_MOTOR_SPEED,
                                    (const uint8_t) fuelSpeed, FUEL_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
    (void) AdjustVfdMotorOperation (FUEL_FEED_AUGER_VFD, MOTOR_RUN,
                                    (const uint8_t) fuelSpeed, FUEL_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
    // set ash removal auger speed
    (void) AdjustVfdMotorOperation (ASH_REMOVAL_AUGER_VFD, SET_MOTOR_SPEED,
                                    (const uint8_t)ashRemovalAugerPercent, ASH_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
    (void) AdjustVfdMotorOperation (ASH_REMOVAL_AUGER_VFD, MOTOR_RUN,
                                    (const uint8_t)ashRemovalAugerPercent, ASH_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);

//    // oil pump 
//     (void) AdjustVfdMotorOperation (OIL_PUMP_VFD, SET_MOTOR_SPEED,
//                                     (const uint8_t)oilPumpPercent, OIL_PUMP_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
//     (void) AdjustVfdMotorOperation (OIL_PUMP_VFD, MOTOR_RUN,
//                                     (const uint8_t)oilPumpPercent, OIL_PUMP_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
    
//     // fuel hopper
//     if(hasHopper && (opState==BOOST_STATE || opState==RUN_STATE|| opState==SHUTDOWN_STATE))
//         hopperAugerPercent=fuelFeedAugerPercent;   // drive system off of transport auger
//     (void) AdjustVfdMotorOperation (HOPPER_AUGER_VFD, SET_MOTOR_SPEED,
//                                     (const uint8_t)hopperAugerPercent, HOPPER_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
//     (void) AdjustVfdMotorOperation (HOPPER_AUGER_VFD, MOTOR_RUN,
//                                     (const uint8_t)hopperAugerPercent, HOPPER_MOTOR_RATED_FULL_SPEED_FREQ, 0, 100);
    // set ID fan motor speed
    SetPwmPercent((uint8_t)hxFanPercent,PWM_PORT_CN10);
     SetPwmPercent((uint8_t)IDFanPercent,PWM_PORT_CN9); // set botSetPwmPercenth 9 & 10, so we can use either....
     SetPwmPercent((uint8_t)primaryDamperPosition,PWM_PORT_CN11);

    /* no longer using global manual mode, manual is for each individual actuator
    if (!manualControl){
        fuelFeedAugerPercentSetpoint = fuelFeedAugerPercent;
        ashRemovalAugerPercentSetpoint = ashRemovalAugerPercent;
        combustionFanPercentSetpoint = combustionFanPercent;
        IDFanPercentSetpoint = IDFanPercent;
        hxFanPercentSetpoint = hxFanPercent;
    }
    */
}


void updatePIDControllers(){
    // If it is appropriate to compute the new controller output for our PID controllers, do it!
    if (PIDTimer >= CONTROLLER_SAMPLING_PERIOD){

        if (CONTROLLER_ENABLE) 
        {
            // compute output
            if(isArtic)
                PIDControllerComputeOutput(&fireTemperatureController, postCatTemperature);  //driving fuel off of Cat temp 10/10/17
  
                PIDControllerComputeOutput(&oxygenController, averageO2);
            if(isArtic)
                PIDControllerComputeOutput(&idOxygenController, averageO2);
            if(hexType == 0)
             PIDControllerComputeOutput(&stackTemperatureController, stackTemperature);
            if(isCow)
                PIDControllerComputeOutput(&damperTemperatureController,postCatTemperature);
            
 /*           if(opState == BOOST_STATE){
                if(boostFuel)
                    PIDControllerComputeOutput(&boostFuelTemperatureController, postCatTemperature); //start computing when fueling begins, experiment 3/19
            PIDControllerComputeOutput(&boostAirTemperatureController, fireTemperature);
            PIDControllerComputeOutput(&boostIDController, waterOutletTemperature); 
            }*/
      //      PIDControllerComputeOutput(&waterOutTemperatureController, waterOutletTemperature);
      //      PIDControllerComputeOutput(&waterInTemperatureController, waterInletTemperature);

            // clear the PID timer
        }
        PIDTimer = CLEAR;

    }
  //  CATALYST_TEMPERATURE_SETPOINT = waterOutTemperatureController.controllerOutput + waterInTemperatureController.controllerOutput;
   // CATALYST_TEMPERATURE_SETPOINT = (CATALYST_TEMPERATURE_SETPOINT > WATER_OUT_CONTROLLER_MAX_OUTPUT)? WATER_OUT_CONTROLLER_MAX_OUTPUT : (CATALYST_TEMPERATURE_SETPOINT < WATER_OUT_CONTROLLER_MIN_OUTPUT)? WATER_OUT_CONTROLLER_MIN_OUTPUT : CATALYST_TEMPERATURE_SETPOINT;
            
    oxygenController.processVariableSetPoint = POST_CAT_OXYGEN_SETPOINT; // it might change
   /* fireTemperatureController.processVariableSetPoint = CATALYST_TEMPERATURE_SETPOINT;
    boostIDController.processVariableSetPoint = BOOST_WATER_ID_SETPOINT;
    boostAirTemperatureController.processVariableSetPoint=BOOST_FIRE_TEMPERATURE_SETPOINT;
    boostFuelTemperatureController.processVariableSetPoint=CATALYST_TEMPERATURE_SETPOINT;*/


}


float filterReading(float filteredReading,float newReading){
    float LPF_Beta = 0.025; // 0<ß<1
    
    if (filteredReading == 0){
        filteredReading = newReading;
    }
      
    // low pass filter algorithm 
    //https://kiritchatterjee.wordpress.com/2014/11/10/a-simple-digital-low-pass-filter-in-c/#more-116
    // LPF: Y(n) = (1-ß)*Y(n-1) + (ß*X(n))) = Y(n-1) - (ß*(Y(n-1)-X(n)));
    filteredReading = filteredReading - (LPF_Beta * (filteredReading - newReading));
   return(filteredReading); 
   
}


void main(void) {
    ClrWdt();
    opState = PRIME_STATE;
    systemStartupProcess();

    while (1) {
        ClrWdt();
        // Read thermocouples and oxygen sensor
        getDataReadingFromSensors();
        // Check for setpoint changes, remote reboots, or manual control
        getSerialInput();
        // Set VFDs and PWM fan percent
        setActuators();
        // Put it all together and tell someone
       
        dataReadingToSerialOutput();
        
    }
}

void ledLights(uint8_t turnOn){
 
    if(turnOn){
            m_LOCKOUT_EXT_LED_SET_ON();      //LOCKOUT_EXT_LED = EXT_LED_ON;
         m_HEAT_CALL_LED_SET_ON();        //HEAT_CALL_LED = LED_ON;
            m_CAT_HEATER_LED_SET_ON();       //CAT_HEATER_LED = LED_ON;
            m_DAMPER_FUEL_AUGER_LED_SET_ON();   // DAMPER_FUEL_AUGER_LED = LED_ON;
         m_REAR_FAN_ASH_AUGER_LED_SET_ON();   //REAR_FAN_ASH_AUGER_LED = LED_ON;
            m_LOW_OXY_LED_SET_ON();          //LOW_OXY_LED = LED_ON;
            m_STANDBY_LOCKOUT_LED_SET_ON();  //STANDBY_LOCKOUT_LED = LED_ON;
            m_ALARM_ALERT_LED_SET_ON();      //ALARM_ALERT_LED = LED_ON;
    }
    else {
        m_ALARM_ALERT_LED_SET_OFF();    //ALARM_ALERT_LED = LED_OFF;
            m_LOCKOUT_EXT_LED_SET_OFF();     LOCKOUT_EXT_LED = EXT_LED_OFF;
         m_HEAT_CALL_LED_SET_OFF();       //HEAT_CALL_LED = LED_OFF;
            m_CAT_HEATER_LED_SET_OFF();      //CAT_HEATER_LED = LED_OFF;
            m_DAMPER_FUEL_AUGER_LED_SET_OFF();   //DAMPER_FUEL_AUGER_LED = LED_OFF;
         m_REAR_FAN_ASH_AUGER_LED_SET_OFF();  //REAR_FAN_ASH_AUGER_LED = LED_OFF;
            m_LOW_OXY_LED_SET_OFF();         //LOW_OXY_LED = LED_OFF;
            m_STANDBY_LOCKOUT_LED_SET_OFF(); //STANDBY_LOCKOUT_LED = LED_OFF;
    }

}

