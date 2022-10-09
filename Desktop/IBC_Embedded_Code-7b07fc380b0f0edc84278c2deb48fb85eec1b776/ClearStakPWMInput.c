/* 
 * File:   ClearStakMain.h
 * Author: David
 *
 * Created on August 5, 2015, 8:51 PM
 */



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

#include "ClearStakPWMInput.h"


/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global Variable And Typed Constant Defining Declarations   
 * The below are not used as far as I can tell: JW 8-2-17                */
/******************************************************************************
volatile uint16_t CN9CaptureIntervalValue;
volatile uint16_t CN9T1Value = 0;
volatile uint16_t CN9T2RawValueBuffer;
volatile uint24_t CN9T2Value = 0; /* CN9 CCP5 stored capture value (T1)
                                         * and current capture value (T2). We
                                         * need 17 bits here in order to account
                                         * for the timer overflow (TMR1IF)
                                         * bit. 

volatile uint16_t CN10CaptureIntervalValue;
volatile uint16_t CN10T1Value = 0;
volatile uint16_t CN10T2RawValueBuffer;
volatile uint24_t CN10T2Value = 0; /* CN10 CCP7 stored capture value (T1)
                                         * and current capture value (T2). We
                                         * need 17 bits here in order to account
                                         * for the timer overflow (TMR5IF)
                                         * bit. 

volatile uint16_t CN11CaptureIntervalValue;
volatile uint16_t CN11T1Value = 0;
volatile uint16_t CN11T2RawValueBuffer;
volatile uint24_t CN11T2Value = 0; /* CN11 CCP9 stored capture value (T1)
                                         * and current capture value (T2). We
                                         * need 17 bits here in order to account
                                         * for the timer overflow (TMR7IF)
                                         * bit. 
volatile uint16_t cn9NewCapturedValue;  /* CN9, CCP5 and TMR1. 
volatile uint16_t cn10NewCapturedValue; /* CN10, CCP7 and TMR5. 
volatile uint16_t cn11NewCapturedValue; /* CN11, CCP9 and TMR7. 
                                        /* The most recent (new) value captured
                                         * by the CCP module. 

volatile uint16_t cn9OldCapturedValue = 0;
volatile uint16_t cn10OldCapturedValue = 0;
volatile uint16_t cn11OldCapturedValue = 0;
                                    /* Used to hold the (old) value that was
                                     * previously captured by the CCP module.
                                     * The old captured value is subtracted
                                     * from the new captured value in order to
                                     * calculate the number of timer counts in
                                     * the tachometer pulse period. */

volatile uint16_t cn9RpmBuffer;
volatile uint16_t cn10RpmBuffer;
volatile uint16_t cn11RpmBuffer;

/*uint16_t cn9Rpm;
uint16_t cn10Rpm;
uint16_t cn11Rpm;                   /* The cnXRpmBuffer registers and the
                                     * cnXRpm registers are used to double
                                     * buffer the tachometer RPM values in order
                                     * to compensate for potentially non-atomic
                                     * register operations in the event of
                                     * ISR operations. */

volatile uint8_t cn9TachPulseTimer;
volatile uint8_t cn10TachPulseTimer;
volatile uint8_t cn11TachPulseTimer;
                                    /* If a tachometer pulse is not generated
                                     * at least once each second, then the fan
                                     * speed will be assumed to be zero. */
uint24_t pwmDutyCycleToPercent(uint24_t dutyCycle) {
    //return dutyCycle / 1023;
    return dutyCycle;
}
/*
uint24_t GetCN9Feedback() {
    return pwmDutyCycleToPercent(CN9T2Value);
}

uint24_t GetCN10Feedback() {
    return pwmDutyCycleToPercent(CN10T2Value);
}

uint24_t GetCN11Feedback() {
    return pwmDutyCycleToPercent(CN11T2Value);
}
*/