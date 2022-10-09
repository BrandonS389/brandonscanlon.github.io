/* 
 * File:   ClearStakMain.h
 * Author: Jeff Wong
 *
 * Created on DEC 22, 2016, 12:05 AM
 * 
 * VERSIONS
 * 
 * Covers 4018 Hydronic, Forced Air, Native Manure processors, and 209 Cold Climate
 * 
 
 */

#ifndef CLEARSTAKMAIN_H
#define	CLEARSTAKMAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
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
#include <stdlib.h>

#endif
#include "cs_woodmaster_400_system.h"
#include "cs_woodmaster_400_user.h"
#include "cs_woodmaster_400_oxy_sensor.h"
#include "cs_woodmaster_400_pwm.h"
#include "cs_woodmaster_400_serial_ports.h"
#include "cs_woodmaster_400_message.h"
#include "cs_woodmaster_400_potentiometer.h"
#include "cs_woodmaster_400_configuration.h"
#include "cs_pdk_400_sk_vfd.h"
#include "BiomassControlsPIDController.h"
#include "ClearStakStateMachine.h"
#include "ClearStakPWMInput.h"
#include "ClearStakSerialInput.h"
#include "ClearStakDataTable.h"
#include "ClearStakOutputHandler.h"
#include "ClearStakEEPROMHandler.h"

#define FIRMWARE_VERSION "10092022" //Reverted to 830202201 version
    //"830202201" //State Machine Rate Adjustments & Tweaks 
    //"812202201" //HX Fan and ID Fan Logic Rework
    //"811202201" //Therm2_Fault Bug Fixes
    //"809202201" //Lots of Tuning, Added IDLE, added damper control, added heat exchanger fan control
    //"808202202" //Debugging, Shutdown not engaging from app
    //"808202201" //Reverting all test changes and tuning state machine
    //"805202211" //Lined up opStateNameTextArray[] with #defines in user.h and fixed BOOST bug
    //"805202210" //Attempt to solve BOOST state bug
    //"805202209" //Attempt to solve BOOST state bug
    //"805202208" //Attempt to solve BOOST state bug
    //"805202207" //Attempt to solve BOOST state bug
    //"805202206" //Attempt to solve BOOST state bug
    //"805202205" //Attempt to solve BOOST state bug
    //"805202204" //State Machine Timing Test
    //"805202203" //State Machine Boost Bug Fix
    //"805202202" //State Machine Bug Fix
    //"805202201" //State Machine Bug Fix
    //"804202201" //Changed system to 60hz and commented out oil pump and hopper VFDs
    //"729202201" //Added back the feedback from the Pi.
    //"726202203" //Added actuator logic to RUN STATE. Also, deleted hybrid VFD configuration.
    //"726202202" //BOOST transition work around.
    //"726202201" //More State Machine tuning. Reduced actuator ramp speeds.
    //"725202203" //State Machine Non PID Automation and Tuning
    //"2022072305" //State Machine & Actuator Overhaul for Kalyani
    //"2022070811" //Variable name changes, State Machine cleanup and tuning
    //"2022062410" // Adjusted motor settings for Dyper system
    //"2020020711" // Comments added pertaining to PATENT US8812162B2
    //"2020012911" // boost id fan 100, to warm stack and unit as fast as possible, reduce combustion fan air in boost and run for smoke control, raise minimum run id fan to 40 from 30 for Cow
    // no slow char for first hour, to fight pot overflow Native1, shutdown char upped to 100 to empty pot
    //"2019121911" //eliminate THERM Errors--they are container temp sometimes 0 or lower., set minimum HX Fan Power to 25% to always have drying and heating
    //"2019112711" // run ash steady at .85 for first hour run, then 2x to prevent overflow, 
    // upped max fuel rate to 30% from 20%, see if ash can handle, fuel auger to run steady in shutdown (no pulse)to ensure emptying
    //"2019112611" // more fuel speed during shutdown to empty out fuel auger, start HX Fan at higher level
    //"2019112211" // pulse ash for 60 mins, rather than 20 in run, too much unburnt coming out, 
    // damper target upped to 550 (jh wants air cut) gain cut in half to operate more slowly, stack target for ID same as HX fan (115 from 145) to test HX Fan capacity
    //"2019112011" // cut ash speed .85 from 1.25, unburnt coming out
    //"2019110711" //Damper_temp_setpoint =450 dropped from 550, open earlier combat brown smoke, 
    //standby id fan stay on until room temp to protect refinery with no airlock, standby id fan reduced to 33 from 50--that's all that is needed to keep pressure positive.
    //"2019100211" //Native: cut ash pulse in half(to 10%)unburnt pellets coming out,increase steady ash to 1.25 of fuel engineering request,remain in shutdown until pot < 130 to give more time to empty ash
    //"2019092411" //Native: logic bug not opening Damper, logic bug not setting comb fan, more ash shutdown to clear pot, 
    //"2019092311" // primaryDamper wrong data type, Run Air back to O2 PI, try minimal to reduce ash, cut fuel and ash if pot is tanking (<500)
    /*"2019092011" Native:Damper PI loop Cat target 550, no run-dry, only run-wet, stack target 145: keep ID Fan Strong, 
comb fan = IDFan-20 during Run, ramp ash up slowly during Run, les air during Shutdown to fight klinkers */
    //"2019091211" //Native:start fuel after system lit for 30 mins
    //"2019091113" //Native: higher Air Boost, no fuel boost, damper open Cat > 500, ramp ash slowly, ramp fuel slowly, start later, Result: fuel trough on fire so temp drop never happened.
    //"2019091112" // pulse ash during beginning of Run
    
    //"2019091111" // Native: open damper Run to cool cat, run air at 50% to up burn rate, run ash at 100 to help empty pot, cap fuel at 20% pot,id fan min increased from 10 to 30 to keep cat cool overflow is the challenge
    //"2019090911" // stay boost longer Native,new design. higher air boost,   avoid jumping to 100% on fuel for Native (new fuel delivery) HX Fan to be run on stack, Minimum Auger speed reduced to 10 for Native
    //"2019082212"// reduce ID Fan min to 10%--enough to keep stack above 100 but not too high. At 24% HXFan could not cool to 115, and O2 was too high
    //"2019082211" // placed 209 primary air adjustments in wrong location
    //"2019082112" // ID Fan on O2 loop to help prevent smoke out, comb fan loop more responsive
    //"2019082111" // slower fuel ramp Run 209
    //"2019082013" // update correct variable fireTemperatureController.maxControllerOutput
    //"2019082012" // attempt to correct floating point error for ramping 209 fuel\
    //"2019082011" // ramp fuel slowly during run, lower O2 A/D to 1000 for 209
    //"2019081911" //bug in 209 fuel rate Run going back to cold cat setting
    // "2019081611" //run steady low rate on fuel until cat warms to prevent overfueling for 209
    //"2019081311" // allow 209 fuel to go as high as it wants for testing
    
    //"2019072312" //fix startup fuel feed cardboard kiv, escape start at 315 2 mins stack rather 389 4 mins
    //"2019072311" /*changes for Kivalina: stack target raised 115 Artic, reduce max fuel output on controller from 60 to 45,
//startup fuel feed Kiv reduced to 0, startup air reduced to 20 from 43, boost fuel only fire < 400,
// Boost Combustion fan reduced 20 from 50, escape Boost when stack >100 for 4 minutes, escape shutdown when Pot < 300 rather than Cat */
    // "2019071813" // full ash
    //"2019071711" // fix Kivalina bug, not updating stackController,add some ID Fan to Run to vent smoke kivalina, report "RUN" for kivalina, no ash during PRIME
    //"2019071511" // test cow ash .60, 50% increase
    //"2019071011" // lower ash for Tide to minimum
    //"2019070811" // actually slow ash(bigash=0), open damper in RUN WET, to help fire
    //"2019070312"  //handle entering run from overheat, crank combustion fan in smoke mode, lower RUN STACK for COW to 110, to lower ID Fan, try to retain more heat, slower ash to hold heat, no pot overflow mode for Cow (running low temps anyway)
    //"2019070311" // faster Run Wet, no ash first 30 mins of RUN, or if fire < 400
    //"2019070213"  // don't use slow fuelRateIncrease for Cow--get to Run Wet Sooner
    //"2019070212" // turn K7 on for RTT (unit "10")
    //"2019070211" // ramp up fuel for Cow in run wet, clean old code out of RUN
    //"2019070111"  // fixed logic relative to Native, some 'No Damper' logic assumes GI 2/3
    //"2019062812" // fire probe reintalled Native 1, fix dry run
    //"2019062611" //lack of oil pump reporting causing HMI to crash, oops
    //"2019062511" // stop reporting oil pump and hopper auger as we may be overloading serial bufs: getting unstable manual controls
    //"2019062411" // Go right to RUN Wet for Cow as soon as boost fueling starts, and use fixed settings
    //"2019060412" // set watt node voltage from config file
    //"2019060411" // do not crank fuel in Run Wet when in manual mode, or when fuel should be 0
    //"2019060311" // only run fuel at  100% in RUN WET, otherwise hopper/fuel are the same, report hopper speed correctly
    //"2019053111" // only run hopper as fuel in boost/run/shutdown
    /* "2019053011"  O2 reporting bug, restore low pass filter,drive system off of transport auger (setActuators modified), run fire target 650 for native units, report hopper
auger speed to kelvin, native1 to be configured as Unit "9" */
    //"2019052912" // take raw O2 readings for troubleshooting
    //"2019052911" // target fire set to 650, hopper to 25Hz
    //"2019052411" // fixed fuel rate of 40 Hz Boost and Run for GI2, don't cut fuel in 'Pot Overflow' (really power outage), no ash boost, wattnode 230
    //"2019052211" // discard readings above MAXIMUM_READING (2000), fuel aug amps to .57 from .48 to push manure, no low pass filter(harder to troubleshoot TC's)
    //"2019051711" //throw out readings more than double previous reading, more time for vfd setup due to addition of hopper vfd
    //"2019051611"  // put low-pass filter in TC readings to smooth out noisy electrical interference
    //"2019050911" // add Hopper Auger VFD, set speed to 40hz during Prime/Startup/Boost/Run, 0 otherwise, wattnode to 120
    //"2019050111" // restore original project VFD settings, fix min fuel level boost (and start)
    //"2019043011" // per BL: The Ash Auger and Fuel Auger motors should be limited to 50 Hz max speed, and use the parameters for that speed. The combustion fan should have a max speed at 60 Hz and use those parameters for that motor.
    //"2019042611" // reset fuel restart rate between Boost and Run
    // "2019042511" // new VFD Params from Brendon, 230 watt node for release
    //"2019042312" // back to 120v for watt node
    //"2019042311"  // recompile for 230v for watt node
    //"2019040911" //fix fuel rate resume after RUN overheat, fix Run Wet Detector, don't trigger LOW_FUEL in Door Open Mode
    //"2019040511" // After overheat in Wet Run, resume fuel at 75% of the rate, when ramps 20% in Run Dry go automatically to Run Wet!
    //"2019040411" // remove increased ash auger speed GI2/3 NO_DAMP, hope India can leave it on Auto
    // "201904021" // when cat rises RUN_ESCAPE_LOW_FUEL (10) low fuel alert ends
    //"201904011" // try reseting highestCatTempSoFar when wet fuel starts to avoid false LOW_FUEL alerts
    //"201903291" // wait for decline in CAT temp before sending dry fuel in BOOST
    //"201903281"  // restore old logic in boost after yesterday's smoke out
    //"201903271" //boost fuel to run off of CAT instead of fire.  Cat is too hot for NO_DAMP, back to fixed AIR for NO_DAMP 
    //"201903261"  // Cat drop of 45 instead of 75 in boost to start fuel, taking too long if startup is not super hot
    //"201903191"  // Max Cat set to 700, separate Max Fire of 900 implemented
    //"201903133"  //back to new O2 algo
    //"201903122"  // add power to O2 sensor
    // "201903121" // try old O2 algo for comparison 
    //"201903111"  // dryfuel mode incorrectly shut off on start
    //"2019030812"  // min fuel level fixed, restore old ID Fan settings when fuel starts boost, go to O2 PI loop in run for NO_DAMP
    // "201903072"  // bug where going into run too soon,2: removed max fuel rate of 40Hz, guess when to add fuel in Boost off of drop in Cat
    //"201903061"  // PI Control on primary air and fuel off of fire temp and id fan off of waterOut in BOOST
    //"201903051"  // O2 readings smoothed by Low Pass Filter algorithm
    //"201902281"  // restarting boost fuel after overheat bug
    //"201902041"  // new VFD nums for 50HZ and 60HZ from Jimmy, put a #define is cs_woodmaster_400_configuration.h
    //"201901291"  //fixes related to smart sys check
    
    //"201812202" // report manual mode as sensor readings+
    //"201812201"  // add Prime Mode to Kivalina
  //  "201812191" // Echo Manual mode state back
 //   "201812061"  // debugging manual mode for offline PI mode
    //"201811271"   // manual control bug, values not always sticking, stop echoing manual settings back for testing, enable HxFan Boost kivalina, update manual control Kivalina
    
 //   "201811261" //bug handling start up and shutdown msg's from PI
 //   "201811131"  // add additional serial receive buffer and toggle between the two
    
 //   "201810261" // incorporate Kivaline logic
    
 //   "201810164"// 03281, back to 650 CAT, 02281 newest code, with CAT TARGET 800 for Ajay GI3 (2), 05161, receive target fire from Pi
    
// 05171: ability to compile controller2 and deliver sensors Thermocouple4-6, Thermistor 3-4
// 05301: Receive unit number 7 or 8 from, OIL_PUMP_VFD defined as #6
// 06041: Controller2 must send extra sensor readings, nothing more!
    // 06051: No manual control info from Controller2 for now
    // 06071/2: controller2 chop transmissions into 2, controller1 3, PI app updated to wait for 5 transmissions before sending, receive buffer getting corrupted
    //060721/2:  serial buffs chopped to 250, from 700
    //060811/2:  program vfd 6 (Oil Pump)
    //061211: more air, more ash, less boost fuel for mary
    //061221: remove 40 htz fuel feed cap, mary's wood chips are wet, 50 htz max fuel, 20% min run air, ash 1.2 * fuel to maximize ash production
    //061511: isolate Mary's code to GI 44, don't override alert state with DRY/WET FUEL, fix missing highestCat temp resets on all fuel cuts, was getting low fuel conditions incorrectly in run-wet
    //061911: RIT converted to GI 55, big ash!
    //062111: not so agressive about pot overflow in BOOST, report pot overflow in status!
    //062611: When GI 7 cat > 500, go Run, water taking too long to heat, implement 'powerGenerator' flag
    //062622: new thermistor code for controller 2
    //062711: oldFuelRate lost in RUN START
    //062811: combine code for old and new thermistors, and use compiler directive for controller 1 and 2
    //070311: reset dryfuel code in a restart, rewrite RUN_WET Logic to be more like working RUN_DRY.
    //070511/2:  add oil pump to system check, move oil pump to controller 1, restore old thermistors to controller 2 since new ones not installed yet
    //070611  : fancy system check that ramps each motor up to 100% over a minute, holds for 15, ramps down over a minute
    //070911 : sys check bug, not ramping damper individually, restore traditional boost criteria for GI7
    //072311/2: enable new thermistor drivers Controller 2 GI 7, see compiler directive thermistor.c
    // 080711 : GI7 Hard Coded RUN: fuel 100, air 50, id 100, ash 20, using powergenerator flag
    //080811:  add MAXIMUM_FUEL_RATE_POWER to allow GI7 to get to 100%
    //080812: break transmission into 3 like C1, getting errors
    // 080912: 0 our serial string for proper strcat in serialhandler
    // 080911: ditto for controler 1
    // 080921/2: syscheck up to 6 mins, new state PRIME_STATE
    // 081411  : respect door open in Manual Mode, GI 7 Primary Fan 60, ID Fan 70
    // 081711  : set voltage value to 120 for the wattnode (has been 240v)
    // 082111  : exit state machine properly from Prime State
    // 090611  : 230v
    // 10011   : shortened sys check, 120v
    // 10111   : fake run motors for demo
    // 10151   : demo mode to compiler directive
    // 10164-8    : RUN-FIRE 4-800 for GI '55' (RIT)
    
//#define CONTROLLER2
//#define DEMO

   
   
#define CAT_ON 1u
#define CAT_OFF 0u
#define MINUTES                                 60      // its a minute. got it?
#define HYDRONIC                                1
#define AIR                                     2
volatile uint8_t mary=0;   // is it Mary's woodchip eater?    
    
#define MINIMUM_FIRE_TEMP                       150     // 300F
#define MAXIMUM_CATALYST_TEMP                   700     // The temp which CAT starts to degrade, cut fuel
#define MAXIMUM_STACK_TEMP                      190     // Increased from 177 on 10/3, still below the fan melt zone. triggers a shutdown
#define MAXIMUM_FIRE_TEMP                       900     // temp to cut fuel
#define MAXIMUM_READING                         2000   // throw out TC readings above this
#define HIGH_CAT_TEMP                           650     //  temp to trigger ID fan to ramp in an attempt to cool the Cat.
#define FIRE_BUILD_UP_INDICATION                350   // Below this the probe is getting covered
#define ACTUATOR_PERCENT_CHANGE               0.0166667  // 1 percent per minute (upped from .01 on 10/25/17)
volatile float MAXIMUM_FUEL_RATE   =                100;  // up from 67 Ajay says, lets keep it under 40 htz, up from 67 for Mary: wet wood chips
#define MAXIMUM_FUEL_RATE_MARY              83
#define MAXIMUM_FUEL_RATE_POWER             100
#define HOPPER_AUGER_SPEED                  42  // fuel hopper speed 25hz

#define NO_OXYGEN                                   3000  
#define AMBIENT_OXYGEN                              300
#define NEAR_BOILING                                99  // intervenes NEAR_BOILING -5, upped to 99 12/10 as they want to run 90c water
#define ROOM_TEMPERATURE                            25
#define CLOSED                                      0
#define OPEN                                        100

#define NO_DAMP_FUEL_AUGER_PERCENT                  66.67  // requested Ajay 5-24-19

volatile float MINIMUM_AUGER_SPEED_PERCENT      =   16.67;  // raised from 10 6/16
volatile float MINIMUM_ASH_AUGER_PERCENT       =    20;   //per ajay 8/8/17--doesn't reliably turn below 18.3333 , 11/20 raise to 30 for Pulsing,12/10 try 20, pot too empty, back to 30 12/20, back to 20 on 1/19
#define MINIMUM_ID_FAN_PERCENT_HYDRONIC             30
volatile float MINIMUM_ID_FAN_PERCENT_AIR =         30; // raised from 10 9/11/19 to keep cat cool


/* ACCELERATION AND DECELLERATION RATES */
#define HALF_PERCENT_PER_MINUTE                     0.0083333333333333  //  0.5/60
#define ONE_PERCENT_PER_MINUTE                      0.0166666666666667  //  1/60
#define ONE_AND_HALF_PERCENT_PER_MINUTE             0.025               //  1.5/60
#define TWO_PERCENT_PER_MINUTE                      0.0333333333333333  //  2/60
    
/* STAND BY STATE VARIABLES */
#define STAND_BY_COMBUSTION_FAN_PERCENT             15.0 // 7.5Hz - raised from 0.0 7/22/22
#define STAND_BY_ASH_REMOVAL_AUGER_PERCENT          0.0        
#define STAND_BY_ID_FAN_PERCENT                     25.0  // lowered from 33% 7/22/22
#define STAND_BY_FUEL_FEED_PERCENT                  15.0  
#define STAND_BY_DAMPER_OPEN_PERCENT                0 
#define STAND_BY_HX_FAN_PERCENT                     0

/* SYSTEM CHECK VARIABLES */
#define SYSTEM_CHECK_COMBUSTION_FAN_PERCENT         50   //ALL HALF TO RAMP UP TO
#define SYSTEM_CHECK_ASH_REMOVAL_AUGER_PERCENT      50       
#define SYSTEM_CHECK_ID_FAN_PERCENT                 50
#define SYSTEM_CHECK_FUEL_FEED_PERCENT              50
#define SYSTEM_CHECK_DAMPER_OPEN_PERCENT            50
#define SYSTEM_CHECK_HX_FAN_PERCENT                 50

/* PRIME STATE VARIABLES */
#define PRIME_DRAG_CHAIN_PERCENT                    100.0  // Set to 100% for the drag chain on Dyper system
#define PRIME_COMBUSTION_FAN_PERCENT                37.6
#define PRIME_ID_FAN_PERCENT                        50.0
#define PRIME_ASH_AUGER_PERCENT                     0.0
#define PRIME_FUEL_FEED_AUGER_PERCENT               24.0
#define PRIME_HX_FAN_PERCENT                        20
#define PRIME_DAMPER_OPEN_PERCENT                   0.0

/* START UP STATE VARIABLES */
#define START_UP_FUEL_FEED_DAMP                     22   // per Ajay 8/3/17 13.11, raised to 22 for testing on 10/2
volatile float START_UP_FUEL_FEED_NO_DAMP     =     16.67;//                 13.11 raised 5/1/19 problems turning at 13.11  
#define START_UP_COMBUSTION_FAN_PERCENT_DAMP        70.0  // upped from 50 on 9/20 per team's request
#define START_UP_COMBUSTION_FAN_PERCENT_NODAMP      100
#define START_UP_ID_FAN_PERCENT                     50.0
#define START_UP_FUEL_FEED_AUGER_PERCENT            24.0
#define START_UP_FUEL_FEED_CARDBOARD                0.0 //dropped from 25 7/23/19 for Kiv
#define START_UP_FUEL_FEED                          0.0  // reduced to 0 7/23/19 for Kiv
#define START_UP_COMBUSTION_FAN_PERCENT             37.6 // raised from 20.0 7/22/22  
#define START_UP_ASH_AUGER_PERCENT                  0     
#define START_UP_DAMPER_POSITION                    0    // closed
#define ESC_START_UP_TRANSITION_CAT_TEMPERATURE     315 // raised from 315 7/22/22
#define ESC_START_UP_TRANSITION_STACK_TEMPERATURE   100     // raised from 50 7/22/2022
#define MAXIMUM_STARTUP_TIME                        7200   // 60 Min, increased to 2 hours
#define START_UP_HX_FAN_PERCENT                     20.0
#define START_UP_DAMPER_OPEN_PERCENT                0.0

/* BOOST STATE VARIABLES */
#define BOOST_CAT_DROP_FUEL_START               25 // When cat drops by 25, start fuel in Boost, data shows this is safe to assume initial startup fuel is burning out.
#define BOOST_ASH_AUGER_PERCENT                 0 
#define BOOST_ASH_AUGER_PERCENT                 0 
#define BOOST_ASH_AUGER_PULSE                   16.67  // pulse at the minimum     
#define BOOST_FUEL_FEED_START_PERCENT           20.0
#define BOOST_FUEL_FEED_MAX_PERCENT             24.166  // 14.5 hZ
#define BOOST_COMBUSTION_FAN_PERCENT_HYDRO      44.0   // same as start up 5/10/17
#define BOOST_COMBUSTION_FAN_PERCENT_AIR        13.0   // try the min 1/23/18
#define BOOST_ID_FAN_PERCENT                    50.0   // dropped from 100 7/22/22
#define BOOST_ASH_AUGER_PERCENT                 0     
#define BOOST_ASH_REMOVAL_AUGER_PERCENT         0.0  // reduced from 33.3 7/23/19 for Kiv          
#define BOOST_FUEL_FEED_PERCENT_INCREASE        0.005
#define BOOST_FUEL_FEED_AUGER_PERCENT           24.0
#define BOOST_COMBUSTION_FAN_PERCENT            37.6
#define BOOST_ASH_AUGER_PERCENT                 0 
#define BOOST_HX_FAN_PERCENT                    20
#define ESC_BOOST_FIRE_TEMPERATURE              650  // 1200 lowered from 1350, target fire is 1300 JW:  , not being used currently
#define ESC_BOOST_WATER_OUT_TEMP                80
#define MAXIMUM_BOOST_TIME                      7200   // 120 Min  JW: 2/1/17, give plenty of time to heat water.
#define BOOST_DAMPER_OPEN_PERCENT               0.0
#define MINIMUM_BOOST_TIME                      1800   // 30 Min  -- Kivalina

/* RUN STATE VARIABLES */
#define RUN_ASH_AUGER_PERCENT                   0                      
#define RUN_ID_FAN_PERCENT                      50       // requested Ajay 8/3/17             
#define RUN_FUEL_FEED_AUGER_PERCENT             24.0  // GI7 8/7/18 100%, 25 for Kivalina 8/16/19
#define RUN_DAMPER_OPEN_PERCENT                 0
#define RUN_HX_FAN_PERCENT                      20
#define RUN_COMBUSTION_FAN_PERCENT              37.6    // requested Ajay 8/3/17, requested Ajay 12/11 up from 91.667
#define RUN_ASH_PULSE_INTERVAL                  60    // how many tics to stir pot in RUN
#define RUN_LOW_FUEL_DETECTOR                   75   // how far the CAT cools in RUN before triggering LOW_FUEL alert
#define RUN_ESCAPE_LOW_FUEL                     10   // how far Cat has to rise to escape LOW_FUEL

/* IDLE STATE VARIABLES */
#define IDLE_ASH_AUGER_PERCENT                  33.33333333
#define IDLE_COMBUSTION_FAN_PERCENT             36.7
#define IDLE_FUEL_FEED_AUGER_PERCENT            24
#define IDLE_ID_FAN_PERCENT                     50
#define IDLE_DAMPER_OPEN_PERCENT                0
#define IDLE_HX_FAN_PERCENT                     20

/* SHUTDOWN STATE VARIABLES */
#define SHUTDOWN_ASH_AUGER_PERCENT              50.0
#define SHUTDOWN_COMBUSTION_FAN_PERCENT         20
#define SHUTDOWN_FUEL_FEED_AUGER_PERCENT        41.66666667
#define SHUTDOWN_ID_FAN_PERCENT                 50
#define SHUTDOWN_DAMPER_OPEN_PERCENT            0
#define SHUTDOWN_HX_FAN_PERCENT                 20

/* DOOR OPEN */
#define DOOR_OPEN_COMBUSTION_FAN_PERCENT        16.67
    
//uint16_t messagelength = 0;

volatile int16_t opState;
volatile int16_t fuelType = 1;
volatile int16_t doorOpenMode = FALSE;
volatile int16_t primeMode = 0;
volatile uint8_t hadPreviousBuildup = FALSE;
//volatile uint8_t REBOOT = CLEAR;
volatile uint8_t manualControl = FALSE;
volatile uint8_t CONTROLLER_ENABLE = FALSE;
volatile uint8_t fuelManual = 0;
volatile uint8_t ashManual = 0;    
volatile uint8_t combFanManual = 0;
volatile uint8_t IDFanManual = 0;
volatile uint8_t heFanManual=0;
volatile uint8_t hasDamper=0;  // secondary air or no secondary air?
volatile uint8_t damperManual=0;
volatile uint8_t oilPumpManual=0;
volatile uint8_t dryFuel=1;    // assume Fuel is dry until operator presses button
volatile uint8_t hexType=0;   // heat exchanger type [ForcedAir = 0 & Hydronic = 1]
volatile uint8_t bigAsh=0;   // whether max ash is desired.
volatile uint8_t powerGenerator=0; // whether we are generating power
volatile float   runFuelIncrease=0.0;  // the rate to increase fuel in RUN (differs AIR v. HYDRONIC 1/12/18)
volatile uint8_t isArtic=0;
volatile uint8_t boostFuel=0;   // is it time to add fuel to Boost?
volatile uint8_t hasHopper=0;   // driving Hopper off of VFD
volatile uint8_t maxFuelMode=0;
volatile uint8_t isCow=0;       // is it a cow manure unit?

#define LOW_FUEL 1
#define BOIL_OVER 2
#define LOW_O2    3
#define BOOST_OVERHEAT 4
#define FIRE_OUT        5
#define RUN_OVERHEAT    6
#define TC1_FAULT       7
#define TC2_FAULT       8
#define TC3_FAULT       9
#define THERM1_FAULT    10
#define THERM2_FAULT    11
#define O2SENSOR_FAULT  12
#define POT_OVERFLOW    13
#define BAD_CODE        99
volatile uint8_t alertCode=0;      // what alert to send 
volatile uint8_t badTC1=0,badTC2=0,badTC3=0,badTHERM1=0,badTHERM2=0,badO2=0;
#define BAD_SENSOR_COUNT 12   // how many bad readings before reporting trouble.


//PI controller settings
PIDController fireTemperatureController; 
//PIDController boostFuelTemperatureController; 
//PIDController boostAirTemperatureController; 
PIDController oxygenController; 
PIDController idOxygenController;
PIDController stackTemperatureController;
PIDController damperTemperatureController;
//PIDController boostIDController;   // drive off of water temp, don't raise until crossing 60c

//PIDController waterOutTemperatureController;
//PIDController waterInTemperatureController;
                          

//Fire Temperature controller parameters
volatile float CATALYST_CONTROLLER_GAIN             = 0.15; 
volatile float CATALYST_CONTROLLER_INTEGRAL_TIME    = 300.0; 
volatile float CATALYST_CONTROLLER_DERIVATIVE_TIME  = 0.0; 
volatile float CATALYST_CONTROLLER_MIN_OUTPUT       = 16.0;
volatile float CATALYST_CONTROLLER_MAX_OUTPUT       = 25.0; // down from 60 for Kivalina 7/23/2019, raised from 45 for testing 209 8/9/19, down to 50 8/13/19(100 overflows), start 25 then raise
volatile float CATALYST_CONTROLLER_INITIAL_OFFSET   = 166.67; // 25% 

//Oxygen controller parameters
volatile float OXYGEN_CONTROLLER_GAIN               = -0.004333;  //back to original .008 from .004 as it is not reacting fast enough 5/4/17, back to .004, 5/9 as swings were too wild.
volatile float OXYGEN_CONTROLLER_INTEGRAL_TIME      = 150.0; 
volatile float OXYGEN_CONTROLLER_DERIVATIVE_TIME    = 0.0; 
volatile float OXYGEN_CONTROLLER_MIN_OUTPUT         = 12.0;  // dropping to 20 % JW: 2/2; dropped to 12% 2/13, O2 too high., 6-12-18 up to 20 for mary
volatile float OXYGEN_CONTROLLER_MIN_OUTPUT_MARY    = 20.0;  // dropping to 20 % JW: 2/2; dropped to 12% 2/13, O2 too high., 6-12-18 up to 20 for mary
volatile float OXYGEN_CONTROLLER_MAX_OUTPUT         = 100.0;  
volatile float OXYGEN_CONTROLLER_INITIAL_OFFSET     = -5020.0; // 30%

//Oxygen controller parameters for ID FAN on 209
volatile float ID_OXYGEN_CONTROLLER_GAIN               = -0.008333;  
volatile float ID_OXYGEN_CONTROLLER_INTEGRAL_TIME      = 150.0; 
volatile float ID_OXYGEN_CONTROLLER_DERIVATIVE_TIME    = 0.0; 
volatile float ID_OXYGEN_CONTROLLER_MIN_OUTPUT         = 10.0;  // 10 seems enough to keep stack warm
volatile float ID_OXYGEN_CONTROLLER_MAX_OUTPUT         = 100.0;  
volatile float ID_OXYGEN_CONTROLLER_INITIAL_OFFSET     = -5020.0; // 30%

//stack controller parameters
volatile float STACK_CONTROLLER_GAIN               = -2; 
volatile float STACK_CONTROLLER_INTEGRAL_TIME      = 1000.0; 
volatile float STACK_CONTROLLER_DERIVATIVE_TIME    = 0.0; 
volatile float STACK_CONTROLLER_MIN_OUTPUT         = 0.0;
volatile float STACK_CONTROLLER_MAX_OUTPUT         = 100.0;  
volatile float STACK_CONTROLLER_INITIAL_OFFSET     = -4000.0;  //try starting HX Fan at higher speed and adjust from there (40% power)

//damper controller parameters
volatile float DAMPER_CONTROLLER_GAIN               = -1; //-2 was moving too fast 11/22/1 
volatile float DAMPER_CONTROLLER_INTEGRAL_TIME      = 1000.0; 
volatile float DAMPER_CONTROLLER_DERIVATIVE_TIME    = 0.0; 
volatile float DAMPER_CONTROLLER_MIN_OUTPUT         = 0.0; 
volatile float DAMPER_CONTROLLER_MAX_OUTPUT         = 50.0;  // 50 seems to be wide open
volatile float DAMPER_CONTROLLER_INITIAL_OFFSET     = 0.0; 

//water out controller parameters
volatile float WATER_OUT_CONTROLLER_GAIN               = 5;            // drop fire by 5 deg for every water deg over setpoint
volatile float WATER_OUT_CONTROLLER_INTEGRAL_TIME      = 1000.0;       
volatile float WATER_OUT_CONTROLLER_DERIVATIVE_TIME    = 0.0; 
volatile float WATER_OUT_CONTROLLER_MIN_OUTPUT         = 593.0;       // min desired fire = 1100F
volatile float WATER_OUT_CONTROLLER_MAX_OUTPUT         = 815.0;       // max desired fire = 1500F
volatile float WATER_OUT_CONTROLLER_INITIAL_OFFSET     = 621.0; // begin desired fire temp at 1150F + proportional offset

//water in controller parameters
volatile float WATER_IN_CONTROLLER_GAIN               = 5;            // drop fire by 5 deg for every water deg over setpoint
volatile float WATER_IN_CONTROLLER_INTEGRAL_TIME      = 0.0;       
volatile float WATER_IN_CONTROLLER_DERIVATIVE_TIME    = 0.0; 
volatile float WATER_IN_CONTROLLER_MIN_OUTPUT         = -55.55;       // reduces fire by 100 degreesF
volatile float WATER_IN_CONTROLLER_MAX_OUTPUT         = 55.55;       // increases fire by 100 degF
volatile float WATER_IN_CONTROLLER_INITIAL_OFFSET     = 0.0; 

//Sampling period
volatile float CONTROLLER_SAMPLING_PERIOD = 5.0;

//Process controller outputs
volatile float fuelFeedAugerPercent             = 0;    // controls fire or cat temp
volatile float combustionFanPercent             = 0;    // controls oxygen
volatile float hxFanPercent                     = 0;    // heat exchanger fan on CN10
volatile float IDFanPercent                     = 0;    // controls stack temp
volatile float oldIDPercent;                            // remember what it used to be when things get back to normal
volatile float oldFuelRate                      = 0;    // remember what rate caused overHeat
volatile float previousFuelRate                 = 0;    // used to detect if fuel ramping (go to wet mode)
volatile uint8_t smokeMode                      = 0;    // smoke emergency (no O2)
volatile float primaryDamperPosition            = 0;
volatile float ashRemovalAugerPercent           = 0;
volatile float previousAshRemovalAugerPercent   = 0;
volatile float oilPumpPercent                   = 0;
volatile uint8_t buildUpMode                    = 0;
volatile float steadyBoostReached               = 0;
volatile float steadyBoostFuelFeedAugerPercent  = 0;
volatile float damperOpenPercent                = 0;

// controller setpoints
volatile float CATALYST_TEMPERATURE_SETPOINT        = 650; // per manufacturer, CAT should stay under 700 during operations, normal 650, Ajay 800
volatile float BOOST_FIRE_TEMPERATURE_SETPOINT      = 800;  // target fire temp for BOOST (dry fuel)
volatile float BOOST_WATER_ID_SETPOINT              = 60;    // warm enough to crank ID Fan

// Oxygen controller setpoints.  removed 'temperature' from the var names and changed to 'POST_CAT'.  
// these are O2 A/D values that reflect levels. nothing to do with temps.  JW 1/26/17
volatile float POST_CAT_OXYGEN_SETPOINT             = 2000.0;   // upped the target to 2000 from 1000 to lower 02 levels per Jeff H., JW. Implements PATENT US8812162B2, Claim 8
volatile float BOOST_POST_CAT_OXYGEN_SETPOINT       = 300.0;
volatile float RUN_POST_CAT_OXYGEN_SETPOINT         = 1500.0;
volatile float SHUTDOWN_POST_CAT_OXYGEN_SETPOINT    = 2000.0; 
volatile float WATER_OUT_TEMPERATURE_SETPOINT       = 82.0;  //180F
volatile float WATER_IN_TEMPERATURE_SETPOINT        = 65.5; //150F
volatile float SHUTDOWN_OXYGEN_TEMPERAURE_SETPOINT  = 600.0;
volatile float STACK_TEMPERATURE_SETPOINT           = 115.0; //raised from 100 7/23/19 for Kiv
volatile float DAMPER_TEMPERATURE_SETPOINT          = 550.0; //dropped from 550, open earlier combat brown smoke, upped to 550 from 450 11/22/19 per JH

//kivalina values
volatile float OXYGEN_TEMPERATURE_SETPOINT          = 1000.0; 
volatile float RUN_OXYGEN_TEMPERAURE_SETPOINT       = 1000.0;
volatile float ID_POST_CAT_OXYGEN_SETPOINT          = 1000.0;   // upped the target to 2000 from 1000 to lower 02 levels per Jeff H., JW.


//Manual setpoints
volatile float fuelFeedAugerPercentSetpoint = 0; // controls cat temp
volatile float combustionFanPercentSetpoint = 0;  
volatile float stackFanPercentSetpoint = 0;       // we now have heFanSetpoing
volatile float ashRemovalAugerPercentSetpoint = 0;
volatile float IDFanPercentSetpoint=0;
volatile uint8_t hxFanPercentSetpoint=0;
volatile uint8_t damperSetpoint=0;
volatile uint8_t oilPumpSetpoint;
volatile float rcvSetpoint=200;

static volatile uint32_t sensorFaultBitWord;
volatile float fireTemperature;
volatile uint16_t fireColdJctTemperature;    
volatile float postCatTemperature;
volatile float highestCatSoFar=0;            // keep track of how hot Mr Cat has gotten
volatile float coolestCatSoFar=0;           // keep track of how cool Mr. Cat has gotten (also used for low fuel alerts)
volatile float highestFireSoFar=0;
volatile uint16_t postCatColdJctTemperature;
volatile float stackTemperature;
volatile uint16_t stackColdJctTemperature;
volatile uint16_t waterInletTemperature;
volatile uint16_t waterOutletTemperature;
//volatile uint16_t highLimitSettingToWaterOutDifferential;
volatile float oxygenSensorData;
volatile float averageO2 = 0;
volatile float thermo4Temperature;
volatile float thermo5Temperature;
volatile float thermo6Temperature;
volatile uint16_t thermi3Temperature;
volatile uint16_t thermi4Temperature;



volatile float controllerGainMultipliedByAHundred = 83; //remember to update this or fix it or something // the guy who wrote this quit. I don't know whats wrong with it
volatile float oxygenPercentDepleted;
volatile char msgString[32]="";
//volatile char msg2String[32]="";



#ifdef	__cplusplus
}
#endif

#endif	/* CLEARSTAKMAIN_H */
