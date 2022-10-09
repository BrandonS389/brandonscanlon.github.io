    /*******************************************************************************
 *  Part Number: CS_PDK_400_FWR
 *  File Name: cs_pdk_400_user.h
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
#ifndef	CS_PDK_400_USER_H_
#define	CS_PDK_400_USER_H_

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/*lint -e9026  Supresses 'Function-like macro, '___, defined [BARR10 Rule #9]'.
 * These function-like macros are not parameterized and so should be reasonably
 * safe. */

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
typedef struct
{
    unsigned Usart1IsConfigured:1;

    unsigned Usart2IsConfigured:1;

    unsigned Spi1IsConfigured:1;

    unsigned CallForHeat:1;
    
    unsigned BdhIsEnforced:1;

}OpStatusBitsStruct_t;

extern volatile OpStatusBitsStruct_t OpStatusBits;

typedef struct
{
    unsigned DisplayDecimalPointIsOn:1;

    unsigned FlashTheDisplay:1;

    unsigned DisplayIsBlanked:1;

}RemoteDisplayStatusBitsStruct_t;

extern volatile RemoteDisplayStatusBitsStruct_t RemoteDisplayStatusBits;

/******************************************************************************/
/* Global Variable And Typed Constant Referencing Declaration                 */
/******************************************************************************/
extern volatile uint8_t oneSecondTimer;

volatile int16_t PIDTimer = 21;
volatile int16_t catalystHeaterTimer = 0;
volatile int32_t stateTimer = 0;
volatile int32_t shutdownTimer = 0;
volatile uint16_t transmissionTimer=0;
volatile uint16_t timeSinceStartup=0;

volatile int16_t augerTimer = 0;
//volatile int16_t fanTimer = 0; // not currently used
//volatile int16_t lowFuelTimer =0;
volatile int16_t lowTemperatureTimer = 0;
volatile int16_t highTemperatureTimer = 0;
volatile uint16_t CN10Counter = 0;
volatile uint16_t CN9Counter = 0;

volatile uint16_t tachoMinuteReg = 0;

volatile int16_t oxygenLevelCounter = 0;
volatile int16_t lockOutTimer = 0;


extern volatile uint8_t oneSecondTimer2;    /* For flashing the call for
                                             * heat LED. */
extern volatile uint32_t runTimeSeconds;    /* Cumulative OWF run time */

extern uint8_t flowMeterGpm;
extern float wattNodePower;

extern const uint16_t TimerZeroOneSecondPreload;

/******************************************************************************/
/* Global Function Prototypes (Declarations)                                  */
/******************************************************************************/
void InitializeSystem(void);
                                    /* Initializes uC I/O, and peripherals */

uint24_t PowerOnSelfTest (volatile int16_t * const OperationalState,
                          const int16_t InitialState);

uint32_t ReadTemperatureSensors (volatile uint16_t * const FireTemperature,
                                 volatile uint16_t * const FireCjTemperature,
                                 volatile uint16_t * const PostCatTemperature,
                                 volatile uint16_t * const PostCatCjTemperature,
                                 volatile uint16_t * const StackTemperature,
                                 volatile uint16_t * StackCjTemperature,
                                 volatile uint16_t * const WaterInletTemperature,
                                 volatile uint16_t * const WaterOutletTemperature);

uint32_t SensorFaultBitsToOpStateIndex (const uint32_t SensorFltBitWord);

void FurnaceShutdown (void);

void DoErrorCadence (const int8_t ErrorType);

int8_t FurnaceHasBeenReset (void);

/******************************************************************************/
/* Global enums                                                               */
/******************************************************************************/

/******************************************************************************/
/* Global #define Macros                                                      */
/******************************************************************************/

/* Cannot use LOW, MEDIUM, HIGH, ON, OFF. They conflict with the
 * microcontroller
 * configuration bit settings. */

#define _XTAL_FREQ  1000000         /* For xc8 compiler __delay_ms() macros. */

#if (0)
#define	VCC_VOLTAGE 5
#endif

#if 0
#define	SET         1               /* These four constants are defined in the*/
#define	CLEAR       0                * xc8 compiler GenericTypeDefs.h file.

#define TRUE        1
#define FALSE       0
#endif

#define	YES         1
#define	NO          0
#define ZERO        0
#define OFF         0
#define DONT        0
#define STOP        0
#define DOIT        1
#define ON          1
#define FULL_SPEED  100
#define HALF_SPEED  50
#define FIFTH_SPEED 24  // upped from 18 on 5/17 for ID fan change

#define JUMPER_OUT  1               /* Jumper is not present. */
#define JUMPER_IN   0               /* Jumper is present. */

#if (0)
#define NORMAL      0               /* For shutdown type. */
#define	ABNORMAL    1
#define FAULT       2
#endif
/*----------------------------------------------------------------------------*/
#define CELSIUS     1
#define FAHRENHEIT  2               /* Temperature degree scale
                                     * specifiers. */
/*----------------------------------------------------------------------------*/
#define FAN_MOTOR 1                 /* Motor definitions*/

#define AUGER_MOTOR 0
/*----------------------------------------------------------------------------*/
#define FIRE_TC_FAULT_IND_FLASH_COUNT       1
#define POST_CAT_TC_FAULT_IND_FLASH_COUNT   2
#define STACK_TC_FAULT_IND_FLASH_COUNT      3

#define WATER_IN_THERMISTOR_FAULT_IND_FLASH_COUNT   4
#define WATER_OUT_THERMISTOR_FAULT_IND_FLASH_COUNT  5
                                    /* These manifest constants represent the
                                     * number of times that the Alarm/Alert LED
                                     * flashes in order to indicate which sensor
                                     * is experiencing an error. */
/*----------------------------------------------------------------------------*/
#define MULTIPLE_SENSOR_FAULTS_FLASH_COUNT  6
/*----------------------------------------------------------------------------*/
#define UNDEFINED_OP_STATE_FLASH_COUNT  7
                                    /* This manifest constants represent the
                                     * number of times that the Alarm/Alert LED
                                     * flashes in order to indicate that the
                                     * default case of the state machine switch
                                     * statement was asserted. */
/*----------------------------------------------------------------------------*/
                                    /* Controller operational state indices. */

#define STAND_BY_STATE 0
#define CHECKING_SYSTEM_STATE 1
#define PRIME_STATE 2
#define START_UP_STATE 3
#define BOOST_STATE 4
#define RUN_STATE 5
#define IDLE_STATE 6
#define SHUTDOWN_STATE 7
#define LOCKOUT_STATE 8
#define MAX_OPERATION_STATE 9

#define PELLET_FUEL 2
#define CARDBOARD_FUEL 1
#define WASTE_FUEL 3
#define WOODCHIPS_FUEL 4

#define FIRE_TC_OPEN_CIRCUIT_FAULT_STATE 16
#define FIRE_TC_SHORT_TO_GND_FAULT_STATE 17
#define FIRE_TC_SHORT_TO_VCC_FAULT_STATE 19

#define POST_CAT_TC_OPEN_CIRCUIT_FAULT_STATE 23
#define POST_CAT_TC_SHORT_TO_GND_FAULT_STATE 31
#define POST_CAT_TC_SHORT_TO_VCC_FAULT_STATE 32

#define STACK_TC_OPEN_CIRCUIT_FAULT_STATE 34
#define STACK_TC_SHORT_TO_GND_FAULT_STATE 38
#define STACK_TC_SHORT_TO_VCC_FAULT_STATE 46

#define BAD_FIRE_GTODP_FUNCT_ARG_FAULT_STATE 47
#define BAD_FIRE_TC_TEMP_FUNCTION_ARG_FAULT_STATE 49

#define BAD_POST_CAT_GTODP_FUNCT_ARG_FAULT_STATE 53
#define BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_FAULT_STATE 61

#define BAD_STACK_GTODP_FUNCT_ARG_FAULT_STATE 62
#define BAD_STACK_TC_TEMP_FUNCTION_ARG_FAULT_STATE 64

#define INLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE 68
#define INLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE 76

#define OUTLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE 77
#define OUTLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE 79

#define BAD_INLET_GTIDP_FUNCT_ARG_FAULT_STATE 83

#define BAD_OUTLET_GTIDP_FUNCT_ARG_FAULT_STATE 91

#define MULTIPLE_SENSOR_FAULTS_STATE  95

#define PDK_STATE 96
/*----------------------------------------------------------------------------*/

#define NO_SENSOR_FAULT_BITS                    0x000000

#define FIRE_TC_OPEN_CIRCUIT_BIT                0x000001
#define FIRE_TC_SHORT_TO_GND_BIT                0x000002
#define FIRE_TC_SHORT_TO_VCC_BIT                0x000004

#define	POST_CAT_TC_OPEN_CIRCUIT_BIT            0x000008
#define POST_CAT_TC_SHORT_TO_GND_BIT            0x000010
#define POST_CAT_TC_SHORT_TO_VCC_BIT            0x000020

#define	STACK_TC_OPEN_CIRCUIT_BIT               0x000040
#define STACK_TC_SHORT_TO_GND_BIT               0x000080
#define STACK_TC_SHORT_TO_VCC_BIT               0x000100

#define BAD_FIRE_GTODP_FUNCT_ARG_BIT            0x000200
#define BAD_FIRE_TC_TEMP_FUNCTION_ARG_BIT       0x000400

#define BAD_POST_CAT_GTODP_FUNCT_ARG_BIT        0x000800
#define BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_BIT   0x001000

#define BAD_STACK_GTODP_FUNCT_ARG_BIT           0x002000
#define BAD_STACK_TC_TEMP_FUNCTION_ARG_BIT      0x004000

#define INLET_THERMISTOR_OPEN_CIRCUIT_BIT       0x008000
#define INLET_THERMISTOR_SHORT_CIRCUIT_BIT      0x010000

#define OUTLET_THERMISTOR_OPEN_CIRCUIT_BIT      0x020000
#define OUTLET_THERMISTOR_SHORT_CIRCUIT_BIT     0x040000

#define BAD_INLET_GTIDP_FUNCT_ARG_BIT           0x080000
#define BAD_OUTLET_GTIDP_FUNCT_ARG_BIT          0x100000
                                        /* Sensor and sensor related function
                                         * status word bits. These bit
                                         * definitions can be bit-wise
                                         * inclusive ORed in order to construct
                                         * the related status word.*/
/*----------------------------------------------------------------------------*/
#define	TMR0_01_SEC_MSBYTE              0x0B
#define	TMR0_01_SEC_LSBYTE              0xDB
#define TMR0_01_SEC_PRELOAD_VALUE       0x0BDB
                                        /* Timer0 register preload provides a
                                         * 60 second interrupt timer tick.
                                         * Fosc is 1MHz if the external clock
                                         * oscillator is disabled. Timer0
                                         * prescaler is 1:4, 16-bit timer0
                                         * register remainder is 62500.
                                         * ((((1/1MHz)*4)*4)* 62500) = 1 second.
                                         * 65535 - 62500 = 3035 = 0x0BDB */
/*----------------------------------------------------------------------------*/
#define EXT_CLK_OSC_ENABLED     1
#define EXT_CLK_OSC_DISABLED    0       /* For the external clock oscillator
                                         * IC */
#define FIVE_VDC_PWR_ENABLED    0
#define FIVE_VDC_PWR_DISABLED   1       /* For the internal +5 VDC high current
                                         * power supply.*/

#define	LED_ON                  0       /* For the LED outputs. */
#define LED_OFF                 1

#define	EXT_LED_ON              1
#define	EXT_LED_OFF             0       /* For the external indicators 'run'
                                         * and 'alert'. */

#define RELAY_ON                1       /* For the relay coil outputs. */
#define	RELAY_OFF               0

#define	RS232_RTS_ASSERTED      1       
#define	RS232_RTS_DEASSERTED    0       /* For the RS-232 data tranceiver RTS
                                         * signal. */
#define RS232_CTS_ASSERTED      0
#define RS232_CTS_DEASSERTED    1       /* For the RS-232 data tranceiver CTS
                                         * signal. */

#define	VFD_ENABLED             1
#define	VFD_DISABLED            0       /* For the variable frequency motor
                                         * drives. */
#define MOTOR_STOP                  1u
#define MOTOR_RUN                   2u
#define RAMP_MOTOR_SPEED_UPWARD     3u
#define RAMP_MOTOR_SPEED_DOWNWARD   4u
#define HOLD_MOTOR_SPEED            5u
#define SET_MOTOR_SPEED             6u

#define	RS232_IC_SHUTDOWN       0       /* For the RS232 tranceiver IC. */
#define	RS232_IC_ACTIVE         1

#define RS232_RCV_EN_ENABLED    0       /* For the RS232 tranceiver IC. */
#define RS232_RCV_EN_DISABLED   1

#define	RS485_RE_ASSERTED       0
#define	RS485_RE_DEASSERTED     1       /*  For the RS-485 tranceiver IC
                                         * RE signal. */

#define	RS485_DE_ASSERTED       1
#define	RS485_DE_DEASSERTED     0       /* For the RS-485 tranceiver IC
                                         * DE signal. */

#define SWITCH_ACTUATED         1       /* For the Sw1 and Sw2 switch states. */
#define	SWITCH_RELEASED         0

#define EXT_RESET_SW_RELEASED   1       /* For the external reset switch. */
#define EXT_RESET_SW_ACTUATED   0

#define SPI_SELECTED            0       /* For the SPI slave selects. */
#define SPI_DESELECTED          1

#define SET_MOTORIZED_DAMPER_DIR_TO_OPEN    1   /* For the motorized dampers. */
#define SET_MOTORIZED_DAMPER_DIR_TO_CLOSE   0

#define RUN_MOTORIZED_DAMPER    1       /* For the motorized dampers. */
#define STOP_MOTORIZED_DAMPER   0

/*===== I/O Pin Type Constants ===============================================*/

#if (0)
#define INPUT_PIN               1
#define OUTPUT_PIN              0       /* Input and output pin types are from
                                         * the  perspective of the
                                         * microcontroller */
#endif

/*===== Analog Input Pins ====================================================*/

#define	WT_HIGH_LIMIT_POT   ADC_CH0     /* AN0 is the water temperature
                                         * high limit control voltage
                                         * input which is obtained from
                                         * the high limit potentiometer.
                                         * (PORTA.RA0) */

#define	WT_DIFF_POT         ADC_CH1     /* AN1 is the water temperature
                                         * differential control voltage
                                         * input which is obtained from
                                         * the differential potentiometer.
                                         * (PORTA.RA1) */

#define	LSM11_O2_SENSOR     ADC_CH12    /* AN12 is the post-catalyst
                                         * oxygen sensor voltage input
                                         * which is obtained from the
                                         * LSM-11 oxygen sensor voltage
                                         * amplifer.
                                         * (PORTH.RH4) */

/*===== Digital I/O Pin Constants ============================================*/

                                        /* RA0 is configured above as
                                         * an analog input. */

                                        /* RA1 is configured above as
                                         * an analog input. */

                                        /* RA2 is not used. It will be
                                         * configured as an output and
                                         * driven logic low. */

                                        /* RA3 is not used. It will be
                                         * configured as an output and
                                         * driven logic low. */

#define	SwitchInputTwo  PORTAbits.RA4   /* RA4 is the active high input
                                         * obtained from the Sw.In 2 input
                                         * level shifter circuit. */

                                        /* RA5 is not used. It will be
                                         * configured as an output and
                                         * driven logic low. */

#define WATER_IN_TEMP_SLAVE_SEL   LATAbits.LATA6
                                        /* RA6 is the active low SPI slave
                                         * select output for the water inlet
                                         * temperature sensor interface IC. */

                                        /* RA7 is the input from the external
                                         * clock oscillator IC. */
/*----------------------------------------------------------------------------*/
#define HEAT_CALL_LED  LATBbits.LATB0   /* RB0 is the active low 'call for
                                         * heat' indicator LED driver
                                         * output. */

#define CAT_HEATER_LED LATBbits.LATB1   /* RB1 is the active low
                                         * 'catalyst heater' indicator
                                         * LED driver output. */

#define DAMPER_FUEL_AUGER_LED  LATBbits.LATB2
					/* RB2 is the active low combustion
                                         * damper or fuel auger energized
                                         * indicator LED driver output. */

#define	REAR_FAN_ASH_AUGER_LED  LATBbits.LATB3
                                        /* RB3 is the active low rear fan or ash
                                         * auger energized indicator LED driver
                                         * output. */

#define	LOW_OXY_LED    LATBbits.LATB4   /* RB4 is the active low, 'low oxygen
                                         * level' indicator LED driver
                                         * output. */

#define	ALARM_ALERT_LED    LATBbits.LATB5
                                        /* RB5 is the active low 'alarm/alert'
                                         * indicator LED driver output. */

                                        /* RB6 is not used. It will be
                                         * configured as an output and driven
                                         * logic low. This pin also appears on
                                         * CN19 as ICSP PGC. */

                                        /* RB7 is not used. It will be
                                         * configured as an output and driven
                                         * logic low. This pin also appears on
                                         * CN19 as ICSP PGD. */
/*----------------------------------------------------------------------------*/
#define	VFD_ENABLE LATCbits.LATC0       /* RC0 is the active high variable
                                         * frequency drive enable output. */

#define	SwitchInputOne  PORTCbits.RC1   /* RC1 is the active high input obtained
                                         * from the Sw.In 1 input level shifter
                                         * circuit. This is an ECCP2 capable
                                         * input and it may be used with a pulse
                                         * type flow meter. */

#define FIRE_TEMP_SLAVE_SEL    LATCbits.LATC2
                                        /* RC2 is the active low SPI slave
                                         * select output for the fire
                                         * temperature sensor interface IC. */

                                        /* RC3 is the MSSP SCK1 output
                                         * that is used for the SPI
                                         * clock output line. It will be
                                         * configured as an output and
                                         * driven logic low. */

                                        /* RC4 is the MSSP SDI1 input
                                         * that is used for the SPI-MISO
                                         * data input line. It will be
                                         * configured as an input. */

                                        /* RC5 is SPI SDO signal output and
                                         * it is not connected to anything. It
                                         * will be configured as an output and
                                         * driven logic low. */

                                        /* RC6 is the RS-485 TxD output.
                                         * This pin is configured as an
                                         * input. The microcontroller
                                         * EUSART module will
                                         * re-configure it as an output
                                         * as needed. */

                                        /* RC7 is the RS-485 RxD input.
                                         * This pin is configured as an
                                         * input. */
/*----------------------------------------------------------------------------*/
                                        /* RD0 is not used. It will be
                                         * configured as an output and
                                         * driven logic low. */

#define RELAY1 LATDbits.LATD1           /* RD1 is the active high output
                                         * that energizes relay number 3.
                                         * (CN21-Pin2) */

#define RELAY2 LATDbits.LATD2           /* RD2 is the active high output
                                         * that energizes relay number 3.
                                         * (CN21-Pin1) */

#define RELAY3 LATDbits.LATD3           /* RD3 is the active high output
                                         * that energizes relay number 3.
                                         * (CN22-Pin2) */

#define RELAY4 LATDbits.LATD4           /* RD4 is the active high output
                                         * that energizes relay number 4.
                                         * (CN22-Pin1) */

                                        /* RD5 is not used. It will be
                                         * configured as an output and
                                         * driven logic low. */

#define RS232_DATA_TERM_DTR LATDbits.LATD6
                                        /* RD6 is the RS-232 data terminal
                                         * active high data terminal ready
                                         * signal output. */

#define RS232DataTermDcd    PORTDbits.RD7
                                        /* RD7 is the RS-232 data terminal
                                         * active high data carrier detect
                                         * signal input. */
/*----------------------------------------------------------------------------*/
#define RS232DataTermRts    PORTEbits.RE0
                                        /* RE0 is the RS-232 data terminal
                                         * port transceiver IC active high
                                         * request-to-send signal input. */

#define RS232_DATA_TCVR_CTS LATEbits.LATE1
                                        /* RE1 is the RS-232 data terminal
                                         * active high clear-to-send signal
                                         * output. */

#define	STANDBY_LOCKOUT_LED    LATEbits.LATE2
                                        /* RE2 is the active low
                                         * 'standby/lockout' indicator LED
                                         * driver output. */

#define motor3Tachometer    PORTEbits.RE3
                                        /* RE3 is the active low CCP9
                                         * tachometer input signal from
                                         * motor 3.
                                         * (CN11) */

#define	MOTOR_3_PWM_OUT    LATEbits.LATE4
                                        /* RE4 is the active high CCP8 PWM
                                         * output signal for motor 3.
                                         * (CN11) */

#define motor2Tachometer    PORTEbits.RE5
                                        /* RE5 is the active low CCP7
                                         * tachometer input signal from
                                         * motor 2.
                                         * (CN10) */

#define	MOTOR_2_PWM_OUT    LATEbits.LATE6
                                        /* RE6 is the active high CCP6 PWM
                                         * output signal for motor 2.
                                         * (CN10). */

                                        /* RE7 is not used. It will be
                                         * configured as an output and
                                         * driven logic low. */
/*----------------------------------------------------------------------------*/
                                        /* RF0 does not exist on this
                                         * microcontroller. */

#define PWR_SUPPLY_5VDC_ENABLE  LATFbits.LATF1
                                        /* RF1 is the active high output that
                                         * enables the on-board +5VDC power
                                         * supply. */

#define COMB_DAMPER_MOTOR_CTRL  LATFbits.LATF2
                                        /* RF2 is the active high output
                                         * that causes the combustion air
                                         * damper motor to run. (CN7) */

#define COMB_DAMPER_DIRECTION   LATFbits.LATF3
                                        /* RF3 is the active high output
                                         * that sets the combustion air damper
                                         * motor direction so that, when the
                                         * motor is energized, it will open
                                         * the combustion damper if set to
                                         * high or close the combustion damper
                                         * if set to low.(CN7) */

#define CAT_DAMPER_MOTOR_CTRL  LATFbits.LATF4
                                        /* RF4 is the active high output
                                         * that causes the catalyst air damper
                                         * motor to run. (CN8) */

#define CAT_DAMPER_DIRECTION  LATFbits.LATF5
                                        /* RF5 is the active high output
                                         * that sets the catalyst air damper
                                         * motor direction so that, when the
                                         * motor is energized, it will open
                                         * the catalyst damperif set to high
                                         * or close the catalyst damper if
                                         * set to low. (CN8) */

#define RS232_DATA_TCVR_EN  LATFbits.LATF6
                                        /* RF6 is the RS-232 data terminal
                                         * port transceiver IC active low
                                         * enable signal output. */

#define RS232_DATA_TCVR_SHDN    LATFbits.LATF7
                                        /* RF7 is the RS-232 data terminal port
                                         * transceiver IC active low shutdown
                                         * signal output. */
/*----------------------------------------------------------------------------*/
                                        /* RG0 is not used. It will be
                                         * configured as an output and
                                         * driven logic low. */

                                        /* RG1 is the RS-232 TxD output. This
                                         * pin is configured as an input. The
                                         * microcontroller EUSART module will
                                         * re-configure it as an output as
                                         * needed. */

                                        /* RG2 is the RS-232 data terminal port
                                         * RxD input. This pin is configured
                                         * as an input. */

#define	MOTOR_1_PWM_OUT    LATGbits.LATG3
                                        /* RG3 is the active high CCP4 PWM
                                         * output signal for motor 1.
                                         * (CN9). */

#define motor1Tachometer    PORTGbits.RG4
                                        /* RG4 is the active low CCP5
                                         * tachometer input signal from
                                         * motor 1. (CN9) */

                                        /* RG5 is the MCLR input. */
/*----------------------------------------------------------------------------*/
#define CAT_HEATER LATHbits.LATH0       /* RH0 is the active high output
                                         * that energizes the electric
                                         * heater that pre-heats the
                                         * catalyst. (Relay) */

#define HighLimitMon    PORTHbits.RH1   /* RH1 is the active high monitor for
                                         * the high voltage external high limit
                                         * control. This input goes high if the
                                         * high if the external high limit
                                         * control trips. */

#define RS232_DISPLAY_TCVR_EN  LATHbits.LATH2
                                        /* RH2 is the RS-232 display terminal
                                         * port transceiver IC active low
                                         * enable signal output. */

#define RS232_DISPLAY_TCVR_SHDN LATHbits.LATH3
                                        /* RH3 is the RS-232 display terminal
                                         * port transceiver IC active low
                                         * shutdown signal output. */

                                        /* RH4 is configured above as
                                         * an analog input. */

#define	O2_HEATER_PWR  LATHbits.LATH5   /* RH5 is the active high LSM11 oxygen
                                         * sensor heater power control
                                         * output. */

#define ResetSwitch PORTHbits.RH6       /* RH6 is the active high 'reset'
                                         * input obtained from the reset
                                         * switch input level shifter
                                         * circuit. */

#define LOCKOUT_EXT_LED LATHbits.LATH7
                                        /* RH7 is the active high external
                                         * lockout indicator LED output. The
                                         * external LED is driven through a
                                         * power driver circuit. */
/*----------------------------------------------------------------------------*/
#define SpareJumper  PORTJbits.RJ0      /* RJ0 is the spare jumper input. */

#define DegCDegFJumper  PORTJbits.RJ1   /* RJ1 is the active high degree C,
                                         * active low degree F display mode
                                         * jumper input. */

#define WATER_OUT_TEMP_SLAVE_SEL   LATJbits.LATJ2
                                        /* RJ2 is the active low SPI slave
                                         * select output for the water outlet
                                         * temperature sensor interface IC. */

#define EXT_CLK_OSC_TRI_STATE  LATJbits.LATJ3
                                        /* RJ3 is the active low external
                                         * clock oscillator IC tri-state signal
                                         * output. */

#define	RS485_DE   LATJbits.LATJ4       /* RJ4 is the active high RS-485 IC
                                         * driver enable signal output. */

#define RS485_RE LATJbits.LATJ5         /* RJ5 is the active low RS-485 IC
                                         * receiver output enable signal
                                         * output. */

#define STACK_TEMP_SLAVE_SEL   LATJbits.LATJ6
                                        /* RJ6 is the active low SPI slave
                                         * select output for the stack
                                         * temperature sensor interface IC. */

#define CAT_TEMP_SLAVE_SEL LATJbits.LATJ7
                                        /* RJ7 is the active low SPI slave
                                         * select output for the catalyst
                                         * temperature sensor interface IC. */

/******************************************************************************/
/* Global Macro Definitions                                                   */
/******************************************************************************/

/*----- Port Pin Configuration Macro Definitions -----------------------------*/

#define m_TrisInitPortA()       TRISA =	0x93;   /* Was 0x92*/
#define m_TrisInitPortB()       TRISB = 0x00;

#if (0)
#define m_TrisInitPortC()        TRISC = 0xD2;  /* PORTC pin 6 is set to input.
                                                 * The USART will automatically
                                                 * switch it to an output,
                                                 * as needed. */
#endif

#define m_TrisInitPortC()       TRISC = 0xD2;
#define m_TrisInitPortD()       TRISD = 0x80;
#define m_TrisInitPortE()       TRISE = 0x29;
#define m_TrisInitPortF()       TRISF = 0x00;
#define m_TrisInitPortG()       TRISG = 0x36;   /* PORTG pin 1 is set to input.
                                                 * The USART will automatically
                                                 * switch it to an output,
                                                 * as needed. */


#define m_TrisInitPortH()       TRISH = 0x52;
#define m_TrisInitPortJ()       TRISJ = 0x02;
/*----------------------------------------------------------------------------*/
#define	m_InitPortAOutputs()    PORTA = 0x40;
#define	m_InitPortBOutputs()    PORTB = 0x3F;
#define	m_InitPortCOutputs()    PORTC = 0x04;
#define m_InitPortDOutputs()    PORTD = 0x00;
#define	m_InitPortEOutputs()    PORTE = 0x04;

#define m_InitPortFOutputs()    PORTF = 0x40;
#define m_InitPortGOutputs()    PORTG = 0x00;
#define m_InitPortHOutputs()    PORTH = 0x04;

#define m_InitPortJOutputs()    PORTJ = 0xE4;

/*----- External Clock Oscillator Macro Definitions --------------------------*/

#define m_EXT_CLK_OSC_ENABLED()     EXT_CLK_OSC_TRI_STATE = EXT_CLK_OSC_ENABLED;
#define m_EXT_CLK_OSC_DISABLED()    EXT_CLK_OSC_TRI_STATE = EXT_CLK_OSC_DISABLED;

/*----- Serial Communications Macro Definitions ------------------------------*/

#define m_RS232_DISPLAY_TCVR_SET_ACTIVE()       RS232_DISPLAY_TCVR_SHDN = RS232_IC_ACTIVE;
#define m_RS232_DISPLAY_TCVR_SET_SHUTDOWN()     RS232_DISPLAY_TCVR_SHDN = RS232_IC_SHUTDOWN;

#define m_RS232_DISPLAY_TCVR_EN_SET_ENABLED()   RS232_DISPLAY_TCVR_EN = RS232_RCV_EN_ENABLED;
#define m_RS232_DISPLAY_TCVR_EN_SET_DISABLED()  RS232_DISPLAY_TCVR_EN = RS232_RCV_EN_DISABLED;
/*----------------------------------------------------------------------------*/
#define m_RS232_DATA_TCVR_SET_ACTIVE()          RS232_DATA_TCVR_SHDN = RS232_IC_ACTIVE;
#define m_RS232_DATA_TCVR_SET_SHUTDOWN()        RS232_DATA_TCVR_SHDN = RS232_IC_SHUTDOWN;

#define m_RS232_DATA_TCVR_EN_SET_ENABLED()      RS232_DATA_TCVR_EN = RS232_RCV_EN_ENABLED;
#define m_RS232_DATA_TCVR_EN_SET_DISABLED()     RS232_DATA_TCVR_EN = RS232_RCV_EN_DISABLED;

#define	m_RS232_DATA_TCVR_CTS_ASSERT()      RS232_DATA_TCVR_CTS = RS232_CTS_ASSERTED;
#define	m_RS232_DATA_TCVR_CTS_DEASSERT()    RS232_DATA_TCVR_CTS = RS232_CTS_DEASSERTED;
/*----------------------------------------------------------------------------*/
#define m_RS485_RE_ASSERT()             RS485_RE = RS485_RE_ASSERTED;
#define m_RS485_RE_DEASSERT()           RS485_RE = RS485_RE_DEASSERTED;

#define	m_RS485_DE_ASSERT()             RS485_DE = RS485_DE_ASSERTED;
#define	m_RS485_DE_DEASSERT()           RS485_DE = RS485_DE_DEASSERTED;

/*----- SPI Slave Select Macro Definitions -----------------------------------*/

#define m_WATER_IN_TEMP_SLAVE_SEL_TRUE()    WATER_IN_TEMP_SLAVE_SEL = SPI_SELECTED;
#define m_WATER_IN_TEMP_SLAVE_SEL_FALSE()   WATER_IN_TEMP_SLAVE_SEL = SPI_DESELECTED;

#define m_FIRE_TEMP_SLAVE_SEL_TRUE()    FIRE_TEMP_SLAVE_SEL = SPI_SELECTED;
#define m_FIRE_TEMP_SLAVE_SEL_FALSE()   FIRE_TEMP_SLAVE_SEL = SPI_DESELECTED;

#define m_WATER_OUT_TEMP_SLAVE_SEL_TRUE()   WATER_OUT_TEMP_SLAVE_SEL = SPI_SELECTED;
#define m_WATER_OUT_TEMP_SLAVE_SEL_FALSE()  WATER_OUT_TEMP_SLAVE_SEL = SPI_DESELECTED;

#define m_STACK_TEMP_SLAVE_SEL_TRUE()   STACK_TEMP_SLAVE_SEL = SPI_SELECTED;
#define m_STACK_TEMP_SLAVE_SEL_FALSE()  STACK_TEMP_SLAVE_SEL = SPI_DESELECTED;

#define m_CAT_TEMP_SLAVE_SEL_TRUE()     CAT_TEMP_SLAVE_SEL = SPI_SELECTED;
#define m_CAT_TEMP_SLAVE_SEL_FALSE()    CAT_TEMP_SLAVE_SEL = SPI_DESELECTED;

/*----- External Indicator Control Macro Definitions -------------------------*/

#define	m_LOCKOUT_EXT_LED_SET_ON()      LOCKOUT_EXT_LED = EXT_LED_ON;
#define	m_LOCKOUT_EXT_LED_SET_OFF()     LOCKOUT_EXT_LED = EXT_LED_OFF;

/*----- VFD Enable Control Macro Definitions ---------------------------------*/

#define m_VFD_ENABLE_ASSERT()           VFD_ENABLE = VFD_ENABLED;
#define m_VFD_ENABLE_DEASSERT()         VFD_ENABLE = VFD_DISABLED;

/*----- LED Indicator Control Macro Definitions ------------------------------*/

#define m_HEAT_CALL_LED_SET_ON()        HEAT_CALL_LED = LED_ON;
#define m_HEAT_CALL_LED_SET_OFF()       HEAT_CALL_LED = LED_OFF;

#define	m_CAT_HEATER_LED_SET_ON()       CAT_HEATER_LED = LED_ON;
#define	m_CAT_HEATER_LED_SET_OFF()      CAT_HEATER_LED = LED_OFF;

#define	m_DAMPER_FUEL_AUGER_LED_SET_ON()    DAMPER_FUEL_AUGER_LED = LED_ON;
#define	m_DAMPER_FUEL_AUGER_LED_SET_OFF()   DAMPER_FUEL_AUGER_LED = LED_OFF;

#define m_REAR_FAN_ASH_AUGER_LED_SET_ON()   REAR_FAN_ASH_AUGER_LED = LED_ON;
#define m_REAR_FAN_ASH_AUGER_LED_SET_OFF()  REAR_FAN_ASH_AUGER_LED = LED_OFF;

#define	m_LOW_OXY_LED_SET_ON()          LOW_OXY_LED = LED_ON;
#define	m_LOW_OXY_LED_SET_OFF()         LOW_OXY_LED = LED_OFF;

#define	m_STANDBY_LOCKOUT_LED_SET_ON()  STANDBY_LOCKOUT_LED = LED_ON;
#define	m_STANDBY_LOCKOUT_LED_SET_OFF() STANDBY_LOCKOUT_LED = LED_OFF;

#define	m_ALARM_ALERT_LED_SET_ON()      ALARM_ALERT_LED = LED_ON;
#define	m_ALARM_ALERT_LED_SET_OFF()     ALARM_ALERT_LED = LED_OFF;

/*----- Control Output Macro Definitions -------------------------------------*/

#define	m_RELAY1_SET_ON()   RELAY1 = RELAY_ON;     /* CN21-Pin 2. */ //K7
#define	m_RELAY1_SET_OFF()  RELAY1 = RELAY_OFF;

#define	K7_RELAY_SET_ON()   RELAY1 = RELAY_ON;     /* CN21-Pin 2. */ //K7
#define	K7_RELAY_SET_OFF()  RELAY1 = RELAY_OFF;

#define	m_RELAY2_SET_ON()   RELAY2 = RELAY_ON;     /* CN21-Pin 1. */ //K8
#define m_RELAY2_SET_OFF()  RELAY2 = RELAY_OFF;

#define	K8_RELAY_SET_ON()   RELAY2 = RELAY_ON;     /* CN21-Pin 1. */ //K8
#define K8_RELAY_SET_OFF()  RELAY2 = RELAY_OFF;

#define	m_RELAY3_SET_ON()   RELAY3 = RELAY_ON;     /* CN22-Pin 2. */ //K9
#define	m_RELAY3_SET_OFF()  RELAY3 = RELAY_OFF;

#define	K9_RELAY_SET_ON()   RELAY3 = RELAY_ON;     /* CN22-Pin 2. */ //K9
#define	K9_RELAY_SET_OFF()  RELAY3 = RELAY_OFF;

#define	m_RELAY4_SET_ON()   RELAY4 = RELAY_ON;     /* CN22-Pin 1. */ //K10
#define m_RELAY4_SET_OFF()  RELAY4 = RELAY_OFF;

#define	K10_RELAY_SET_ON()   RELAY4 = RELAY_ON;     /* CN22-Pin 1. */ //K10
#define K10_RELAY_SET_OFF()  RELAY4 = RELAY_OFF;
/*----------------------------------------------------------------------------*/
#define	m_CAT_HEATER_SET_ON()       CAT_HEATER = RELAY_ON; // K5
#define	m_CAT_HEATER_SET_OFF()      CAT_HEATER = RELAY_OFF;

#define	K5_RELAY_SET_ON()       CAT_HEATER = RELAY_ON; // K5
#define	K5_RELAY_SET_OFF()      CAT_HEATER = RELAY_OFF;

#define	m_O2_HEATER_PWR_SET_ON()    O2_HEATER_PWR = RELAY_ON;
#define	m_O2_HEATER_PWR_SET_OFF()   O2_HEATER_PWR = RELAY_OFF;
/*----------------------------------------------------------------------------*/
#define m_5VDC_PWR_SUPPLY_SET_ON()  PWR_SUPPLY_5VDC_ENABLE = FIVE_VDC_PWR_ENABLED;
#define m_5VDC_PWR_SUPPLY_SET_OFF() PWR_SUPPLY_5VDC_ENABLE = FIVE_VDC_PWR_DISABLED;
/*----------------------------------------------------------------------------*/
#define m_SET_COMB_DAMPER_MOTOR_CTRL_RUN()  COMB_DAMPER_MOTOR_CTRL = RUN_MOTORIZED_DAMPER;
#define m_SET_COMB_DAMPER_MOTOR_CTRL_STOP() COMB_DAMPER_MOTOR_CTRL = STOP_MOTORIZED_DAMPER;

#define m_SET_COMB_DAMPER_DIRECTION_OPEN()  COMB_DAMPER_DIRECTION = SET_MOTORIZED_DAMPER_DIR_TO_OPEN;
#define m_SET_COMB_DAMPER_DIRECTION_CLOSE() COMB_DAMPER_DIRECTION = SET_MOTORIZED_DAMPER_DIR_TO_CLOSE;

#define m_SET_CAT_DAMPER_MOTOR_CTRL_RUN()   CAT_DAMPER_MOTOR_CTRL = RUN_MOTORIZED_DAMPER;
#define m_SET_CAT_DAMPER_MOTOR_CTRL_STOP()  CAT_DAMPER_MOTOR_CTRL = STOP_MOTORIZED_DAMPER;

#define m_SET_CAT_DAMPER_DIRECTION_OPEN()   CAT_DAMPER_DIRECTION = SET_MOTORIZED_DAMPER_DIR_TO_OPEN;
#define m_SET_CAT_DAMPER_DIRECTION_CLOSE()  CAT_DAMPER_DIRECTION = SET_MOTORIZED_DAMPER_DIR_TO_CLOSE;



#endif /*CS_PDK_400_USER_H_*/

/***** EOF for cs_pdk_400_user.h **********************************************/
