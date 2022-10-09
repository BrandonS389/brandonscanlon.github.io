
# EMBEDDED THERMO CONTROL

## CONTENTS OF THIS FILE
   
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * FAQ and Troubleshooting
 * Maintainers

## INTODUCTION

The EmbeddedThermoControl repository contains software interfaces for various hardware components and logic for system state changes and process control. The logic and control component can be separated into two processes: interrupts and main loop. The main loop covers functions that take larger amounts of time and can be re-entered after interrupts without failure. These functions are:

* Getting data readings from sensors, 
* Checking serial messages for commands,
* Setting all actuator positions and speeds,
* Building serial messages for output to the wireless hub (RaspberryPi)

The interrupts component entail tasks that are are on a strict deadline, such as reading UART buffers, or are time dependent, such as PID control calculations. The following are examples of interrupt tasks:

High Priority:
* New character available through UART comms
Low Priority:
* Timer4 interrupt flag 98Hz (used for processing pulse input for flow meter or watt node)
* CN 9-11 capture mode interrupt ~ 2Hz (increments pulse count for flow meter or watt node or fan tachometer)
* One second Timer0 tick (increment timers for PID control and state logic, perform state machine, update PID outputs, calculate RPM, GPM)

The Kivalina, GI-1, and Myron Mixon branches of this repo contain a very similar structure that can be modified for any project. 


## REQUIREMENTS

This software was developed in MPLAB IDE, but use whatever you want. Make sure you have the xc8 compiler v1.34.


## Installation

Clone the git repository to some location in your file directory. Open MPLAB and import the project files. If you need to configure the project use the following settings:

* Device: PIC18F86K22
* Hardware Tool: PICkit 3

Thats pretty much it. Go to town.


## CONFIGURATION

When starting a new project, I would first branch off the Kivalina, Myron Mixon, or Gates India branches (whichever one is most similar to your project). 

1. Start with serial output. Ask yourself which sensor values will you be exporting over serial? Fire temp, Cat temp? Auger speed? Any set points? This is available in ClearStakMain.c string declarations for serial values are found in ClearStakMain.h.

2. Next develop the state machine. This is found in ClearStakStateMachine.c. You may want to remove or add states. Just make sure you also declare them in cs_woodmaster_400_user.h. Each state should have conditions for exit. This is usually based on a a specific control input, time, or temperature value. For example, to leave standby state, a startup command must be received. To leave startup, fire temperature and stack temperature may need to meet some requirement for X minutes. The state machine logic is called from the one second timer interrupt. If there is any logic for computing actuator output, you should do this in a separate function within the state machine file. In run state actuator outputs will be determined by the PID controller. However, in start up state or shutdown state or manual mode you may want to have fixed actuator outputs or suppress them all together. If so, set the CONTROLLER_ENABLE bit to zero so your PID controller does not continue updating.

3. Last, set up the process control. PID controller can be declared in ClearStakMain.h and constructed in clearStakMain.c/createControllers(). In ClearStakMain.h set the PID parameters: controller gain, integral time, derivative time, min/max output, and initial offset. If you are unfamiliar with PID control theory, there are many resources available online and a great book called Process Control for Practitioners by Jacques Smuts. Buy in summary, the output of the controller will be your actuator position or speed. The controller gain is multiplied by error between desired and actual set points to get the proportional P controller output. This controls some temperature by increasing or decreasing an actuator position to minimize error. The integral term tries to eliminate steady state error. This term is calculated by summing the multiplication of the inverse of integral time by error and by sampling period over time. This essentially sums a small fraction of the proportional output over time. The derivative is similar but prevents overshoot by reducing rapid changes in controller output. This is usually not used though. The BiomassControlsPIDController.c file contains logic for PID calculations. All PID controllers are updated in the one second timer tick and outputs are assigned to actuators in the main loop. Again, these values may be overwritten in a function in the state machine class.

## FAQ AND TROUBLESHOOTING

Q. How do I read a Fan tachometer output?

A. Assuming you have the pulse output from the fan attached to the appropriate CN9-11 connector, look at the cs_woodmaster_400_user.c file. Arround line 300 or so are the timer and interrupt configurations. There are 3 important parts to look for that may be commented out (open timer, open capture, and open PWM)
```
    OpenTimer5 (TIMER_INT_OFF & T5_16BIT_RW & T5_SOURCE_FOSC & T5_OSC1EN_OFF & T5_PS_1_1 & T5_SYNC_EXT_OFF, TIMER_GATE_OFF);
                                    /* Timer5 is used with the capture7 module and CN10. */
```
```
    OpenCapture7 (CAPTURE_INT_ON & CAP_EVERY_16_RISE_EDGE & CCP_7_SEL_TMR58);
                                    /* Timer5 and CN10. */
```
```
    IPR4bits.CCP7IP = CLEAR;
```
```
    SetDCPWM6(0);
    OpenPWM6(250, CCP_6_SEL_TMR12);
    /* Open PWM6 for fan control on controller
     * connector CN10. Period = 0.001004 seconds
     * (976.0 Hz) base on Timer2. The duty cycle
     * is initialized to zero.
     * PWMPeriod = (250 + 1) x 4 x Tosc x TMR2prescaler */
    /*----------------------------------------------------------------------------*/
```
In this example, timer 5 is assigned to the capture7 module and CN10. Leave the arguments for this timer as is.
Capture7 is set to produce interrupts in every 16 rising edges of the input. This can be changed to every base 2 number less than 32 to increase or decrease the frequency of interrupts.
The interrupt priority is set to CLEAR (zero) so interrupts are low priority. These should not be high priority as the relative deadline is much greater than serial input.
Last, the PWM module is configured. This doesn’t have anything to do with the tac output, but is used to control the fan.

Next add to the cs_woodmaster_400_.c file. Whenever a tach pulse occurs the capture7 interrupt flag will be high. within the low priority ISR add a condition like:

```
    if (PIR4bits.CCP7IF)
    {
        PIR4bits.CCP7IF = CLEAR;

        CN10Counter ++;
    } 
```

This will increment a pulse count whenever X number of interrupts occur (X being whatever base2 number of pulses/interrupt you chose). Next in the one second timer interrupt, add a calculation for RPM based on the pulse count such as:

```
    if (tachoMinuteReg >= 10u)
    {
        cn10RpmBuffer = (uint16_t)(SECONDS_PER_MINUTE) * CN10Counter * PULES_PER_INT / tachoMinuteReg;      // capture interrupts every 16 pos edges
        CN10Counter = CLEAR;

        tachoMinuteReg = 0u;
    }
```



Q. Nothing is working at all. It seems like the program halts at some random point.

A. Make sure the watch dog timer is cleared. You may have deleted this line in the one second interrupt or while loop. 
   If you are using a PWM motor and don’t care about RPM data, make sure you either have the tachometer wire unplugged from the board or have the interrupts disabled for that tachometer. If you do want PWM data and have the interrupts configured, make sure you are clearing the interrupt flag in the interrupt service routine (ISR). This might freeze the program or make time run slower.



Q. How many thermocouples, thermistors, PWM modules, relays, other sensors do I have to work with?

A. There are 3 thermocouples, 2 thermistors, 3 PWM modules, 4 relays, an oxygen sensor input, and 2 additional switch inputs.


Q. One or more of my PID controllers is not updating.

A. Make sure you are actually calling the update function AND assigning these outputs to the actuator AND updating the actuator. Also make sure you set CONTROLLER_ENABLE to true in states where you want PID control. and make sure you do not have manual_control set to 1.

Q. My PID controller is always saturated.

A. Check your lower and upper PID limits. they may not be suitable for the type of actuator you are controlling. Also, if your process variable is not responding well to the PID control, the controller may saturate with no hope of affecting the process variable. Make sure you have the appropriate sign on you controller gain. Make sure your controller gain is not too small or two large. Make sure your integral time is not too small or too large.

Q. Where do I go to change constants and variable declarations?

A. Most of these are in the ClearStakMain.h file. Some are in the cs_woodmaster400_config or users files. You can do a search in you IDE for any variables you see.


## MAINTAINERS

For any questions please contact jeffw@biomasscontrols.com





