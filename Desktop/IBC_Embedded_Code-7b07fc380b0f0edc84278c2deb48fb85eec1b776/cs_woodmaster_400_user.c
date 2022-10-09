/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_user.c
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
 * 3/8/17:  uncommented code for CN9 which needs DCPWM4, Bangalore Carbonizer changed to run ID Fan on either CN10 or CN9: JW
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

#endif

#include "cs_woodmaster_400_user.h"
#include "cs_woodmaster_400_thermocouple.h"
#include "cs_woodmaster_400_thermistor.h"
#include "cs_woodmaster_400_configuration.h"
#include "cs_woodmaster_400_pwm.h"
#include "cs_pdk_400_sk_vfd.h"
/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/*PC-Lint is not picking up nested compiler specific library #include <>s so
 * the following errors have been check for this file and are being suppressed.
 * If this file is modified, these error suppressions must be temporarily
 * suspended in order to re-lint the file.*/

/*lint -e10 Supresses 'Expecting a structure or a union' */
/*lint -e40 Supresses 'Undeclared identifier' */
/*lint -e63 Supresses 'Expected an lvalue' */
/*lint -e526 Supresses 'Symbol ___ not defined' */
/*lint -e628 Supresses 'No argument provided for function ___' */
/*lint -e718 Supresses 'Symbol ___ undeclared, assumed to return int' */
/*lint -e746 Supressed 'Call to function ___ not made in the presence of a prototype' */

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declaration                    */
/******************************************************************************/
volatile uint8_t oneSecondTimer;

volatile uint8_t oneSecondTimer2; /* For flashing the call for heat LED. */


volatile uint32_t runTimeSeconds = 0; /* Cumulative OWF run time in seconds. */

uint8_t flowMeterGpm;
float wattNodePower;

void init2USART();



/******************************************************************************/
/* Local Variable And Typed Constant Defining Declarations                    */
/******************************************************************************/
const uint16_t TimerZeroOneSecondPreload = 3035u;
/* Timer0 register preload provides a
 * 60 second interrupt timer tick. */

/* Fosc is 1MHz.
 * Timer0 prescaler is 1:4,
 * 16-bit timer0 register remainder is
 * 62500.
 * ((((1/1MHz)*4)*4)* 62500) = 1 second.
 * 65535 - 62500 = 3035 */

/******************************************************************************/
/* Local Macro Definitions                                                    */
/******************************************************************************/

/******************************************************************************/
/* Data Structures and Unions                                                 */
/******************************************************************************/
#if (0)
volatile SensorStatusBitsStruct_t SensorStatusBits;
#endif
volatile OpStatusBitsStruct_t OpStatusBits;
volatile RemoteDisplayStatusBitsStruct_t RemoteDisplayStatusBits;

/******************************************************************************/
/* Local Function Prototypes                                                  */
/******************************************************************************/

/******************************************************************************/
/* Function Definitions                                                       */
/******************************************************************************/

/*******************************************************************************
 * Function:        void InitializeSystem(void)
 *
 * Description:     InitializeSystem() is a centralized initialization function.
 *
 * Dependencies:    cs_pdk_400_user.h, Macros m_InitPortAOutputs(),
 *                  m_InitPortBOutputs(), m_InitPortCOutputs(),
 *                  m_InitPortDOutputs(), m_InitPortEOutputs(),
 *                  m_InitPortFOutputs(), m_InitPortGOutputs(),
 *                  m_InitPortHOutputs(), m_InitPortJOutputs(),
 *                  m_TrisInitPortA(), m_TrisInitPortB(), m_TrisInitPortC(),
 *                  m_TrisInitPortD(), m_TrisInitPortE(), m_TrisInitPortF(),
 *                  m_TrisInitPortG(), m_TrisInitPortH(), m_TrisInitPortJ()
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    None
 ******************************************************************************/
void InitializeSystem(void) { /* The configuration bits set the clock
                                     * oscillator to use the internal clock
                                     * oscillator. */

    /* Upon power-up the internal clock
     * oscillator post-scaler is set to provide
     * a system Fosc of 1.0 MHz. */

    /* Eventually we will change this to use
     * the external 3.6864 MHz clock oscillator
     * that is on the 4.0.0 controller
     * board */
    m_InitPortAOutputs() /* Port I/O pin state initialization. */
    m_InitPortBOutputs()
    m_InitPortCOutputs()
    m_InitPortDOutputs()
    m_InitPortEOutputs()
    m_InitPortFOutputs()
    m_InitPortGOutputs()
    m_InitPortHOutputs()
    m_InitPortJOutputs()
    /* Set the I/O pins to input, output or
     * analog as required. The output pins that
     * are used by the USARTs are automatically
     * switched from inputs to outputs,
     * as required. */
    m_TrisInitPortA()
    m_TrisInitPortB()
    m_TrisInitPortC()
    m_TrisInitPortD()
    m_TrisInitPortE()
    m_TrisInitPortF()
    m_TrisInitPortG()
    m_TrisInitPortH()
    m_TrisInitPortJ()

    m_VFD_ENABLE_DEASSERT()

    if (USE_5VDC_POWER == YES) {
        m_5VDC_PWR_SUPPLY_SET_ON() /* This power supply is used to power the
                                     * local simple HMI, the cellular gateway
                                     * module and the USB power port. */
    } else {
        m_5VDC_PWR_SUPPLY_SET_OFF()
    }

    m_EXT_CLK_OSC_DISABLED() /* For now, we use the microcontroller's
                                     * internal RC clock oscillator. */

    /*Initialize certain status bit flags. */
    OpStatusBits.Usart1IsConfigured = (bool) FALSE;
    OpStatusBits.Usart2IsConfigured = (bool) FALSE;

    OpStatusBits.Spi1IsConfigured = (bool) FALSE;

    OpStatusBits.BdhIsEnforced = (bool) FALSE;

    /*----------------------------------------------------------------------------*/
    ANCON0 = 0x03; /* RA0:AN0 and RA1:AN1 are configured as
                                     * analog inputs. RA2:AN2, RA3:AN3, RA5:AN4,
                                     * RF7:AN5, RF1:AN6 and RF2:AN7 are
                                     * configured as digital I/O. */

    ANCON1 = 0x00; /* RF3:AN8, RF4:AN9, RF5:AN10, RF6:AN11,
                                     * RH4:AN12, RH5:AN13, RH6:AN14 and RH7:AN15
                                     * are configured as digital I/O. */

    ANCON2 = 0x00; /* RG4:AN16, RG3:AN17, RG2:AN18, RG1:AN19,
                                     * RH3:AN20 and RH2:AN21, RH1:AN22 and
                                     * RH0:AN23 are configured as digital
                                     * I/O. */

    MEMCONbits.EBDIS = 1; /* External memory bus is enabled when the
                                     * microcontroller accesses external memory;
                                     * otherwise, all external bus drivers are
                                     * mapped as I/O ports. */
    /*---------------------------------------------------------------------------*/
    /* Open and configure the SPI serial port
     * and flush the SPI buffer, if required. */
    CloseSPI1();

    OpenSPI1(SPI_FOSC_4, MODE_00, SMPMID);

    if (SSP1STATbits.BF) {
        (void) ReadSPI1();
    }//end if()

    OpStatusBits.Spi1IsConfigured = TRUE;
    /*----------------------------------------------------------------------------*/
    Close1USART(); /* RS485 bus is driven by USART1. */

    Open1USART((USART_TX_INT_OFF & USART_RX_INT_OFF &
            USART_ASYNCH_MODE & USART_EIGHT_BIT &
            USART_BRGH_HIGH & USART_ADDEN_OFF), 12);
    /* 19.2K Baud with 1.00MHz
     * oscillator. (8-bit and no CREN). */

    baud1USART(BAUD_IDLE_RX_PIN_STATE_HIGH &
            BAUD_IDLE_TX_PIN_STATE_HIGH &
            BAUD_16_BIT_RATE & BAUD_WAKEUP_OFF &
            BAUD_AUTO_OFF);

    OpStatusBits.Usart1IsConfigured = TRUE;
    /*----------------------------------------------------------------------------*/
    /* Data logging or the the local or remote
     * HMI is on the RS232 bus that is driven
     * by USART2. */
    init2USART();
    /*----------------------------------------------------------------------------*/
    (void) OpenADC((ADC_FOSC_2 & ADC_RIGHT_JUST & ADC_12_TAD),
            (ADC_CH0 & ADC_INT_OFF),
            (ADC_NEG_CH0 & ADC_REF_VDD_VDD & ADC_REF_VDD_VSS));
    /* TAD = 2.0 uS.
     * Acquisition time = 12 * TAD = 24uS.
     * Later in this firmware we need only to
     * select the appropriate A/D channel. */
    //------------------------------------------------------------------------------
    (void) OpenTimer0(TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_4);
    /* Timer0 will be a 60 second interrupt
     * timer tick. Timer clock frequency is
     * the internal Fosc/4 instruction cycle,
     * the timer0 prescaler is set to 1:4 and
     * the timer is set to operate in 16-bit
     * timer0 register mode. */

    INTCON2bits.TMR0IP = CLEAR; /* Assign low interrupt priority to timer0.
                                     * (NOT Default) */

    WriteTimer0(TimerZeroOneSecondPreload);
    /* Timer0 is a one second timer. */

    /* Initialize the timing registers that are
     * associated with the Timer0 interrupt. */
    //    oneMinuteReg = (uint16_t)0;
    oneSecondTimer = (uint8_t) 0;
    oneSecondTimer2 = (uint8_t) 0;
    runTimeSeconds = (uint32_t) 0;
    /*----------------------------------------------------------------------------*/

    PR4 = 255;
    WriteTimer4(0);
    PIR5bits.TMR4IF = CLEAR;
    OpenTimer4(TIMER_INT_ON & T4_PS_1_1 & T4_POST_1_10);
                //m_HEAT_CALL_LED_SET_OFF()
    IPR5bits.TMR4IP = CLEAR;
    /* With an FOSC/4 frequency of 250kHz and
     * a timer4 prescaler ratio of 1:1 and a
     * timer4 postscaler ratio of 1:10 and a
     * timer4 period register value of 255,
     * timer4 generates interrupt at a rate
     * of 98 Hz. These interrupts will call
     * an integration function that will be
     * used to debounce the flowmeter reed
     * switch output. */
    /*----------------------------------------------------------------------------*/
    //    PR2 = 0;
    //    WriteTimer2 (0);
    OpenTimer2(TIMER_INT_OFF & T2_PS_1_1 & T2_POST_1_1);
    /* Timer2 is used with the PWM6 module. */
    /*----------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------*/
    OpenTimer1 (TIMER_INT_OFF & T1_16BIT_RW & T1_SOURCE_FOSC & T1_PS_1_1 &
                T1_OSC1EN_OFF & T1_SYNC_EXT_OFF, TIMER_GATE_OFF);  
                                    /* Timer1 is used with the capture5 module
                                     * and CN9. */
/*----------------------------------------------------------------------------*/
   OpenTimer5 (TIMER_INT_OFF & T5_16BIT_RW & T5_SOURCE_FOSC & T5_OSC1EN_OFF &
                T5_PS_1_1 & T5_SYNC_EXT_OFF, TIMER_GATE_OFF);
                                    /* Timer5 is used with the capture7 module
                                     * and CN10. */
/*----------------------------------------------------------------------------*/
/*    OpenTimer7 (TIMER_INT_OFF & T7_16BIT_RW & T7_SOURCE_FOSC & T7_OSC1EN_OFF &
                T7_PS_1_1 & T7_SYNC_EXT_OFF, TIMER_GATE_OFF);
                                    /* Timer7 is used with the capture9 module
                                     * and CN11. */
/*----------------------------------------------------------------------------*/
    OpenCapture5 (CAPTURE_INT_ON & CAP_EVERY_16_RISE_EDGE & CCP_5_SEL_TMR12);
                                    /* Timer1 and CN9. */
    IPR4bits.CCP5IP = CLEAR; 

/*----------------------------------------------------------------------------*/
    OpenCapture7 (CAPTURE_INT_ON & CAP_EVERY_16_RISE_EDGE & CCP_7_SEL_TMR58);
                                    //Timer5 and CN10. 
    IPR4bits.CCP7IP = CLEAR;

/*----------------------------------------------------------------------------*/
    //OpenCapture9 (CAPTURE_INT_ON & CAP_EVERY_RISE_EDGE & CCP_9_SEL_TMR74);
                                    /* Timer7 and CN11. */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    SetDCPWM4(0);
    OpenPWM4(250, CCP_4_SEL_TMR34);
    /* Open PWM4 for fan control on controller
     * connector CN9. Period = 0.001004 seconds
     * (976.0 Hz) base on Timer4. The duty cycle
     * is initialized to zero.
     * PWMPeriod = (250 + 1) x 4 x Tosc x TMR4prescaler */
    /*----------------------------------------------------------------------------*/
    SetDCPWM6(0);
    OpenPWM6(250, CCP_6_SEL_TMR12);
    /* Open PWM6 for fan control on controller
     * connector CN10. Period = 0.001004 seconds
     * (976.0 Hz) base on Timer2. The duty cycle
     * is initialized to zero.
     * PWMPeriod = (250 + 1) x 4 x Tosc x TMR2prescaler */
    /*----------------------------------------------------------------------------*/
    SetDCPWM8(0);
    OpenPWM8(250, CCP_8_SEL_TMR76);
    /* Open PWM8 for fan control on controller
     * connector CN11. Period = 0.001004 seconds
     * (976.0 Hz) base on Timer6. The duty cycle
     * is initialized to zero.
     * PWMPeriod = (250 + 1) x 4 x Tosc x TMR6prescaler */
    /*----------------------------------------------------------------------------*/
#if (0)
    OpenTimer3((TIMER_INT_OFF & T3_16BIT_RW & T3_SOURCE_FOSC_4 & T3_OSC1EN_ON &
            T3_PS_1_4 & T3_SYNC_EXT_OFF), TIMER_GATE_OFF);
#endif
    /*----------------------------------------------------------------------------*/
    INTCONbits.TMR0IF = CLEAR;

    INTCONbits.TMR0IE = SET; /* Enable the timer0 interrupt. */

    RCONbits.IPEN = SET; /* Enable the interrupt priority feature. */
    INTCONbits.GIEH = CLEAR; /* Enable all high priority interrupts. */
    INTCONbits.GIEL = CLEAR; /* Enable all low priority interrupts. */
    
    m_VFD_ENABLE_ASSERT()

    return;

}/* end InitializeSystem() */

void init2USART() {
/* Data logging or the the local or remote
     * HMI is on the RS232 bus that is driven
     * by USART2. */
    Close2USART();
    PIR3bits.RC2IF = CLEAR;//Clear the flag before enabling the interrupt
    Open2USART((USART_TX_INT_OFF & USART_RX_INT_ON &//CHANGED THIS TO USART_RX_INT_ON!!!
            USART_ASYNCH_MODE & USART_EIGHT_BIT &
            USART_BRGH_HIGH & USART_ADDEN_OFF), 25);
    /* 9600 Baud with 1MHz oscillator. */
    IPR3bits.RC2IP = 1;//high priority
    baud2USART(BAUD_IDLE_RX_PIN_STATE_HIGH &
            BAUD_IDLE_TX_PIN_STATE_HIGH &
            BAUD_16_BIT_RATE & BAUD_WAKEUP_OFF &
            BAUD_AUTO_OFF);

    //m_RS232_DISPLAY_TCVR_SET_ACTIVE()
    m_RS232_DATA_TCVR_SET_ACTIVE() /* Activate both the terminal serial
                                     * tranceiver IC and the local display
                                     * serial transceiver IC. */
    __delay_ms(5); /* Wait a little for the charge pump
                                     * to ramp up. */
    //m_RS232_DISPLAY_TCVR_EN_SET_ENABLED()
    m_RS232_DATA_TCVR_EN_SET_ENABLED() /* Enable both the terminal serial
                                         * tranceiver and the local display
                                         * serial transceiver. */

    OpStatusBits.Usart2IsConfigured = TRUE;
}


/*******************************************************************************
 * Function:        uint24_t PowerOnSelfTest (volatile int16_t * const OperationalState,
                          const int16_t InitialState)
 *
 * Description:     PowerOnSelfTest() is a place holder for now, wherein
 *                  sophisticated firmware and hardware error checking will be
 *                  implimented. At present, this function tests for a stuck
 *                  reset switch.
 *
 * Dependencies:    cs_pdk_400_user.h, Macros m_HEAT_CALL_LED_SET_ON(),
 *                  m_CAT_HEATER_LED_SET_ON(), m_DAMPER_FUEL_AUGER_LED_SET_ON(),
 *                  m_REAR_FAN_ASH_AUGER_LED_SET_ON(), m_LOW_OXY_LED_SET_ON(),
 *                  m_LOCKOUT_EXT_LED_SET_ON(), m_ALARM_ALERT_LED_SET_ON(),
 *                  m_HEAT_CALL_LED_SET_OFF(), m_CAT_HEATER_LED_SET_OFF(),
 *                  m_DAMPER_FUEL_AUGER_LED_SET_OFF(),
 *                  m_REAR_FAN_ASH_AUGER_LED_SET_OFF(), m_LOW_OXY_LED_SET_OFF(),
 *                  m_LOCKOUT_EXT_LED_SET_OFF(), m_ALARM_ALERT_LED_SET_OFF(),
 *
 * PreConditions:   None
 *
 * Inputs:          The address of a register in which a operational state
 *                  index will be stored.
 *
 * Output:          A fault status word.
 *
 * Side Effects:    If no errors, OperationalState will contain InitialState.
 ******************************************************************************/
uint24_t PowerOnSelfTest(volatile int16_t * const OperationalState, const int16_t InitialState) {
    uint24_t postStatus = (uint24_t) NO_SENSOR_FAULT_BITS;
#if (0)
    m_HEAT_CALL_LED_SET_ON() /* Is  flow meter indicator in PDK code. */
#endif
            m_CAT_HEATER_LED_SET_ON()
            m_DAMPER_FUEL_AUGER_LED_SET_ON()
            m_REAR_FAN_ASH_AUGER_LED_SET_ON()
            m_LOW_OXY_LED_SET_ON()

#if 0
            m_STANDBY_LOCKOUT_LED_SET_ON() /* There is a SPI bus conflict  with this
                                     * LED on the 4.0.0 controller board. */
#endif

            m_LOCKOUT_EXT_LED_SET_ON()
            m_ALARM_ALERT_LED_SET_ON()

            __delay_ms(250); // 250ms.

#if (0)
    m_HEAT_CALL_LED_SET_OFF() /* Is  flow meter indicator in PDK code. */
#endif
            m_CAT_HEATER_LED_SET_OFF()
            m_DAMPER_FUEL_AUGER_LED_SET_OFF()
            m_REAR_FAN_ASH_AUGER_LED_SET_OFF()
            m_LOW_OXY_LED_SET_OFF()
#if 0
            mSTANDBY_LOCKOUT_LED_SET_OFF() /* There is a SPI bus conflict with this LED
                                     * on the 4.0.0 controller board. */
#endif

            m_LOCKOUT_EXT_LED_SET_OFF()
            m_ALARM_ALERT_LED_SET_OFF()

    if (ResetSwitch == EXT_RESET_SW_ACTUATED) /* Test for stuck reset switch. */ {
        for (;;) /* Reset switch is stuck closed. */ {
            m_CAT_HEATER_LED_SET_ON()
            m_DAMPER_FUEL_AUGER_LED_SET_ON()
            m_REAR_FAN_ASH_AUGER_LED_SET_ON()
            m_LOW_OXY_LED_SET_ON()
            m_LOCKOUT_EXT_LED_SET_ON()

            m_ALARM_ALERT_LED_SET_ON()
            __delay_ms(500); /* On for 1.0 second. */
            __delay_ms(500);
            m_CAT_HEATER_LED_SET_OFF()
            m_DAMPER_FUEL_AUGER_LED_SET_OFF()

            m_REAR_FAN_ASH_AUGER_LED_SET_OFF()
            m_LOW_OXY_LED_SET_OFF()
            m_LOCKOUT_EXT_LED_SET_OFF()
            m_ALARM_ALERT_LED_SET_OFF()

            __delay_ms(250); /* Off for 0.250ms. */
        }//end for()
        /* In order to recover from this state
         * the power to the controller must be
         * cycled. */
    } else {
        *OperationalState = InitialState; /* The reset switch is not stuck. */
    }//end if else()

    return postStatus;

}/* end PowerOnSelfTest() */

/*******************************************************************************
 * Function:        uint32_t ReadTemperatureSensors
 *                              (volatile uint16_t * const FireTemperature,
 *                               volatile uint16_t * const FireCjTemperature,
 *                               volatile uint16_t * const PostCatTemperature,
 *                               volatile uint16_t * const PostCatCjTemperature,
 *                               volatile uint16_t * const StackTemperature,
 *                               volatile uint16_t * StackCjTemperature,
 *                               volatile uint16_t * const WaterInletTemperature,
 *                               volatile uint16_t * const WaterOutletTemperature)
 *
 * Description:     ReadTemperatureSensors() is a wrapper function that reads
 *                  the temperature sensors and reports on their health status.
 *
 * Dependencies:    cs_pdk_400_thermocouple.h, cs_pdk_400_thermistor.h
 *
 * PreConditions:   None
 *
 * Inputs:          The addresses of the locations in which to store the
 *                  temperatures that are read from the various temperature
 *                  sensors.
 *
 * Output:          A status word whose bits reflect the health of the various
 *                  temperature sensors.
 *
 * Side Effects:    The locations addressed by the input arguments will be
 *                  written with the obtained temperature values. Note that
 *                  the helper functions that this function calls are designed
 *                  to not provide a temperature update from a given sensor if
 *                  that sensor is is found to be in poor health and, in this
 *                  case, the corresponding addressed location will not be
 *                  altered.
 ******************************************************************************/
uint32_t ReadTemperatureSensors(volatile uint16_t * const FireTemperature,
        volatile uint16_t * const FireCjTemperature,
        volatile uint16_t * const PostCatTemperature,
        volatile uint16_t * const PostCatCjTemperature,
        volatile uint16_t * const StackTemperature,
        volatile uint16_t * StackCjTemperature,
        volatile uint16_t * const WaterInletTemperature,
        volatile uint16_t * const WaterOutletTemperature) {
    uint32_t statusWord = (uint32_t) NO_SENSOR_FAULT_BITS;

    int16_t tempStatusWord;

  // (void) GetTcTemperature_C(FIRE_THERMOCOUPLE_ID,
  //          COLD_JUNCTION_DATA,
  //          FireCjTemperature);

    tempStatusWord = GetTcTemperature_C(FIRE_THERMOCOUPLE_ID,
            THERMOCOUPLE_DATA,
            FireTemperature);

 /*   switch ((uint16_t) tempStatusWord) {
        case (uint16_t) TC_OPEN_CIRCUIT_FAULT_IND:
            statusWord = statusWord | (uint32_t) FIRE_TC_OPEN_CIRCUIT_BIT;
            break;

        case (uint16_t) TC_SHORT_TO_GND_FAULT_IND:
            statusWord = statusWord | (uint32_t) FIRE_TC_SHORT_TO_GND_BIT;
            break;

        case (uint16_t) TC_SHORT_TO_VCC_FAULT_IND:
            statusWord = statusWord | (uint32_t) FIRE_TC_SHORT_TO_VCC_BIT;
            break;

        case (uint16_t) GTODP_FUNCT_ARG_RELATED_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_FIRE_GTODP_FUNCT_ARG_BIT;
            break;

        case (uint16_t) BAD_EXTRACT_TC_TEMP_FUNCTION_ARG_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_FIRE_TC_TEMP_FUNCTION_ARG_BIT;
            break;

        default:
            break;

    } */
 
    /*----------------------------------------------------------------------------*/
   // (void) GetTcTemperature_C(POST_CAT_THERMOCOUPLE_ID,
    //        COLD_JUNCTION_DATA,
     //       PostCatCjTemperature);

    tempStatusWord = GetTcTemperature_C(POST_CAT_THERMOCOUPLE_ID,
            THERMOCOUPLE_DATA,
            PostCatTemperature);
/*
    switch ((uint16_t) tempStatusWord) {
        case (uint16_t) TC_OPEN_CIRCUIT_FAULT_IND:
            statusWord = statusWord | (uint32_t) POST_CAT_TC_OPEN_CIRCUIT_BIT;
            break;

        case (uint16_t) TC_SHORT_TO_GND_FAULT_IND:
            statusWord = statusWord | (uint32_t) POST_CAT_TC_SHORT_TO_GND_BIT;
            break;

        case (uint16_t) TC_SHORT_TO_VCC_FAULT_IND:
            statusWord = statusWord | (uint32_t) POST_CAT_TC_SHORT_TO_VCC_BIT;
            break;

        case (uint16_t) GTODP_FUNCT_ARG_RELATED_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_POST_CAT_GTODP_FUNCT_ARG_BIT;
            break;

        case (uint16_t) BAD_EXTRACT_TC_TEMP_FUNCTION_ARG_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_BIT;
            break;

        default:

            break;

    }*/
    /*----------------------------------------------------------------------------*/
 //   (void) GetTcTemperature_C(STACK_THERMOCOUPLE_ID,
 //           COLD_JUNCTION_DATA,
 //           StackCjTemperature);

    tempStatusWord = GetTcTemperature_C(STACK_THERMOCOUPLE_ID,
            THERMOCOUPLE_DATA,
            StackTemperature);
/*
    switch ((uint16_t) tempStatusWord) {
        case (uint16_t) TC_OPEN_CIRCUIT_FAULT_IND:
            statusWord = statusWord | (uint32_t) STACK_TC_OPEN_CIRCUIT_BIT;
            break;

        case (uint16_t) TC_SHORT_TO_GND_FAULT_IND:
            statusWord = statusWord | (uint32_t) STACK_TC_SHORT_TO_GND_BIT;
            break;

        case (uint16_t) TC_SHORT_TO_VCC_FAULT_IND:
            statusWord = statusWord | (uint32_t) STACK_TC_SHORT_TO_VCC_BIT;
            break;

        case (uint16_t) GTODP_FUNCT_ARG_RELATED_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_STACK_GTODP_FUNCT_ARG_BIT;
            break;

        case (uint16_t) BAD_EXTRACT_TC_TEMP_FUNCTION_ARG_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_STACK_TC_TEMP_FUNCTION_ARG_BIT;
            break;

        default:

            break;

    }*/
    /*----------------------------------------------------------------------------*/
    tempStatusWord = GetThermistorTemperature_C(INLET_WT_THERMISTOR_ID,
            WaterInletTemperature);
/*
    switch ((uint16_t) tempStatusWord) {
        case (uint16_t) THERMISTOR_SHORT_CIRCUIT_FAULT_IND:
            statusWord = statusWord | (uint32_t) INLET_THERMISTOR_SHORT_CIRCUIT_BIT;
            break;

        case (uint16_t) THERMISTOR_OPEN_CIRCUIT_FAULT_IND:
            statusWord = statusWord | (uint32_t) INLET_THERMISTOR_OPEN_CIRCUIT_BIT;
            break;

        case (uint16_t) GTIDP_FUNCT_ARG_RELATED_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_INLET_GTIDP_FUNCT_ARG_BIT;
            break;

        default:

            break;
    }
    /*----------------------------------------------------------------------------*/
    tempStatusWord = GetThermistorTemperature_C(OUTLET_WT_THERMISTOR_ID,
            WaterOutletTemperature);
/*
    switch ((uint16_t) tempStatusWord) {
        case (uint16_t) THERMISTOR_SHORT_CIRCUIT_FAULT_IND:
            statusWord = statusWord | (uint32_t) OUTLET_THERMISTOR_SHORT_CIRCUIT_BIT;
            break;

        case (uint16_t) THERMISTOR_OPEN_CIRCUIT_FAULT_IND:
            statusWord = statusWord | (uint32_t) OUTLET_THERMISTOR_OPEN_CIRCUIT_BIT;
            break;

        case (uint16_t) GTIDP_FUNCT_ARG_RELATED_FAULT_IND:
            statusWord = statusWord | (uint32_t) BAD_OUTLET_GTIDP_FUNCT_ARG_BIT;
            break;

        default:

            break;
    }*/
    return statusWord;
}
/*******************************************************************************
 * Function:        uint32_t SensorFaultBitsToOpStateIndex (const uint32_t SensorFltBitWord)
 *
 * Description:     ConvertSensorFaultBitsToOpStateIndex() converts the argumant
 *                  passed in SensorFltBitWord to a valid operational state
 *                  index.
 *
 * Dependencies:    cs_pdk_400_thermocouple.h, cs_pdk_400_thermistor.h
 *
 * PreConditions:   SensorFltBitWord must indicate a valid sensor, or sensors,
 *                  fault condition.
 *
 * Inputs:          An argument that indicates a valid sensor, or sensors, fault
 *                  condition.
 *
 * Output:          The index of a firmware operational state that is
 *                  appropriate for the sensor, or sensors, fault.
 *
 * Side Effects:    None
 ******************************************************************************/
uint32_t SensorFaultBitsToOpStateIndex(const uint32_t SensorFltBitWord) {
    uint32_t opStateIndex;

    switch (SensorFltBitWord) {
        case FIRE_TC_OPEN_CIRCUIT_BIT:

            opStateIndex = (uint16_t) FIRE_TC_OPEN_CIRCUIT_FAULT_STATE;

            break;

        case FIRE_TC_SHORT_TO_GND_BIT:

            opStateIndex = (uint16_t) FIRE_TC_SHORT_TO_GND_FAULT_STATE;

            break;

        case FIRE_TC_SHORT_TO_VCC_BIT:

            opStateIndex = (uint16_t) FIRE_TC_SHORT_TO_VCC_FAULT_STATE;

            break;

        case POST_CAT_TC_OPEN_CIRCUIT_BIT:

            opStateIndex = (uint16_t) POST_CAT_TC_OPEN_CIRCUIT_FAULT_STATE;

            break;

        case POST_CAT_TC_SHORT_TO_GND_BIT:

            opStateIndex = (uint16_t) POST_CAT_TC_SHORT_TO_GND_FAULT_STATE;

            break;

        case POST_CAT_TC_SHORT_TO_VCC_BIT:

            opStateIndex = (uint16_t) POST_CAT_TC_SHORT_TO_VCC_FAULT_STATE;

            break;

        case STACK_TC_OPEN_CIRCUIT_BIT:

            opStateIndex = (uint16_t) STACK_TC_OPEN_CIRCUIT_FAULT_STATE;

            break;

        case STACK_TC_SHORT_TO_GND_BIT:

            opStateIndex = (uint16_t) STACK_TC_SHORT_TO_GND_FAULT_STATE;

            break;

        case STACK_TC_SHORT_TO_VCC_BIT:

            opStateIndex = (uint16_t) STACK_TC_SHORT_TO_VCC_FAULT_STATE;

            break;

        case BAD_FIRE_GTODP_FUNCT_ARG_BIT:

            opStateIndex = (uint16_t) BAD_FIRE_GTODP_FUNCT_ARG_FAULT_STATE;

            break;

        case BAD_FIRE_TC_TEMP_FUNCTION_ARG_BIT:

            opStateIndex = (uint16_t) BAD_FIRE_TC_TEMP_FUNCTION_ARG_FAULT_STATE;

            break;

        case BAD_POST_CAT_GTODP_FUNCT_ARG_BIT:

            opStateIndex = (uint16_t) BAD_POST_CAT_GTODP_FUNCT_ARG_FAULT_STATE;

            break;

        case BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_BIT:

            opStateIndex = (uint16_t) BAD_POST_CAT_TC_TEMP_FUNCTION_ARG_FAULT_STATE;

            break;

        case BAD_STACK_GTODP_FUNCT_ARG_BIT:

            opStateIndex = (uint16_t) BAD_STACK_GTODP_FUNCT_ARG_FAULT_STATE;

            break;

        case BAD_STACK_TC_TEMP_FUNCTION_ARG_BIT:

            opStateIndex = (uint16_t) BAD_STACK_TC_TEMP_FUNCTION_ARG_FAULT_STATE;

            break;

        case INLET_THERMISTOR_OPEN_CIRCUIT_BIT:

            opStateIndex = (uint16_t) INLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE;

            break;

        case INLET_THERMISTOR_SHORT_CIRCUIT_BIT:

            opStateIndex = (uint16_t) INLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE;

            break;

        case OUTLET_THERMISTOR_OPEN_CIRCUIT_BIT:

            opStateIndex = (uint16_t) OUTLET_THERMISTOR_OPEN_CIRCUIT_FAULT_STATE;

            break;

        case OUTLET_THERMISTOR_SHORT_CIRCUIT_BIT:

            opStateIndex = (uint16_t) OUTLET_THERMISTOR_SHORT_CIRCUIT_FAULT_STATE;

            break;

        case BAD_INLET_GTIDP_FUNCT_ARG_BIT:

            opStateIndex = (uint16_t) BAD_INLET_GTIDP_FUNCT_ARG_FAULT_STATE;

            break;

        case BAD_OUTLET_GTIDP_FUNCT_ARG_BIT:

            opStateIndex = (uint16_t) BAD_OUTLET_GTIDP_FUNCT_ARG_FAULT_STATE;

            break;

        default:

            opStateIndex = (uint16_t) MULTIPLE_SENSOR_FAULTS_STATE;

            break;
    }

    return opStateIndex;
}

/*******************************************************************************
 * Function:        void FurnaceShutdown(void)
 *
 * Description:     None
 *
 * Dependencies:    cs_pdk_400_user.h, Macros m_O2_HEATER_PWR_SET_OFF(),
 *                  m_CAT_HEATER_SET_OFF(), m_CAT_HEATER_LED_SET_OFF()
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    None
 ******************************************************************************/
void FurnaceShutdown(void) {
    if (O2_HEATER_PWR == RELAY_ON) {
        m_O2_HEATER_PWR_SET_OFF()
    }
    return;
}/* end FurnaceShutdown() */

/*******************************************************************************
 * Function:        void DoErrorCadence (const int8_t ErrorType)
 *
 * Description:     None
 *
 * Dependencies:    cs_pdk_400_user.h, Macros m_ALARM_ALERT_LED_SET_ON(),
 *                  m_ALARM_ALERT_LED_SET_OFF()
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    None
 ******************************************************************************/
void DoErrorCadence(const int8_t ErrorType) {
    int8_t flashes;

    for (flashes = (int8_t) 0; flashes < ErrorType; ++flashes) {
        ClrWdt();
        m_ALARM_ALERT_LED_SET_ON() /* Short on for 0.10 second. */
        __delay_ms(100);

        m_ALARM_ALERT_LED_SET_OFF() /* Short off for 0.10 second. */
        __delay_ms(250);
    }//end for()

    m_ALARM_ALERT_LED_SET_OFF() /* Long off for 1.0 second. */
    ClrWdt();
    __delay_ms(500);
    ClrWdt();
    __delay_ms(500);
    ClrWdt();

    return;

}/* end DoErrorCadence() */

/*******************************************************************************
 * Function:        int8_t FurnaceHasBeenReset (void)
 *
 * Description:     None
 *
 * Dependencies:    cs_pdk_400_user.h, Macros m_O2_HEATER_PWR_SET_ON(),
 *
 * PreConditions:   None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Side Effects:    None
 ******************************************************************************/
int8_t FurnaceHasBeenReset(void) {
    int8_t resetStatus = FALSE;

    if (ResetSwitch != SWITCH_ACTUATED) {
        __delay_ms(250); /* 0.25 seconds. */
        if (ResetSwitch != SWITCH_ACTUATED) {
            while (ResetSwitch != SWITCH_ACTUATED) {
                ClrWdt();
            } /* Wait for the user to
                                                 * release the reset button. */

            if (O2_HEATER_PWR == RELAY_OFF) {
                m_O2_HEATER_PWR_SET_ON()
            } /* Energize the O2 sensor
                                                 * heater. */

            resetStatus = (int8_t) TRUE; /* Accept the reset command. */
        }//end if()
        else {
            resetStatus = (int8_t) FALSE;
        } /* The switch was not actuated
                                                 * for a long enough time or
                                                 * else the switch is still
                                                 * bouncing. */
    }//end else if()
    else {
        resetStatus = (int8_t) FALSE;
    }

    return resetStatus;
}/* end CheckForReset() */

/***** EOF for cs_pdk_400_user.c **********************************************/
