/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_interrupts.c
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
#include <string.h>
#include "cs_woodmaster_400_system.h"
#include "cs_woodmaster_400_user.h"
#include "cs_woodmaster_400_message.h"
#include "cs_woodmaster_400_flowmeter.h"
#include "cs_woodmaster_400_wattnode.h"
#include "cs_woodmaster_400_configuration.h"
#include "cs_woodmaster_400_oxy_sensor.h"
#include "cs_woodmaster_400_serial_ports.h"
#include "ClearStakPWMInput.h"
#include "ClearStakSerialInput.h"
#include "ClearStakActuation.h"

extern volatile char msgString[];
extern volatile uint8_t isArtic;
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************/
/* High-priority interrupt service                                            */
/******************************************************************************/
#if defined(__XC) || defined(HI_TECH_C)
void interrupt high_isr(void)
#elif defined (__18CXX)
#pragma code high_isr=0x08
#pragma interrupt high_isr
void high_isr(void)
#else
#error "Invalid compiler selection for implemented ISR routines"
#endif
{
    ClrWdt(); // Once per interrupt cycle. 
    if (DataRdy2USART()) {
        m_RS232_DATA_TCVR_CTS_ASSERT()
        addCharToReceivedString(RCREG2);
    }
    if(transmissionTimer > 30){
            // nothing sent in last 30 secs, must be jammed
            init2USART(); // clear it
            transmissionTimer = 0;
            strcpy(msgString,"SerialCleared!");
        }
   
}

/******************************************************************************/
/* Low-priority interrupt service                                             */
/******************************************************************************/
#if defined(__XC) || defined(HI_TECH_C)
void low_priority interrupt low_isr(void)
#elif defined (__18CXX)
#pragma code low_isr=0x18
#pragma interruptlow low_isr
void low_isr(void)
#else
#error "Invalid compiler selection for implemented ISR routines"
#endif
{

    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 separate if blocks.
    Do not use a separate if block for each interrupt flag to avoid run
    time errors. */

    
    if (PIR4bits.CCP5IF)
     {
         PIR4bits.CCP5IF = CLEAR;
 
         CN9Counter ++;
     } 
    else if (PIR4bits.CCP7IF)
    {
        PIR4bits.CCP7IF = CLEAR;

        CN10Counter ++;
    } 

    else if (INTCONbits.TMR0IF) /* Test for the one second
                                         * timer tick. */ {
        WriteTimer0(TimerZeroOneSecondPreload);
 //       ++lowFuelTimer;
        ++augerTimer;
        ++lowTemperatureTimer;
        ++highTemperatureTimer;
        ++PIDTimer;
        ++stateTimer;
        ++oxygenLevelCounter;
        ++oneSecondTimer;
        ++oneSecondTimer2;
        ++runTimeSeconds;
        ++serialDataXmitIntervalTimer;
        ++flowMeterMinuteReg;
        ++wattNodeMinuteReg; //added another counter fir wattnode AB 5/12/17
        ++tachoMinuteReg;
        ++transmissionTimer;
        
        LimitSecondsToOneYear(&runTimeSeconds);
        doStateMachine();
        updatePIDControllers();
        performActuation();
        INTCONbits.TMR0IF = CLEAR;

        if (tachoMinuteReg >= 10u)
        {
            cn10RpmBuffer = (uint16_t)(SECONDS_PER_MINUTE) * CN10Counter * PULES_PER_INT / tachoMinuteReg;      // capture interrupts every 16 pos edges
            cn9RpmBuffer = (uint16_t)(SECONDS_PER_MINUTE) * CN9Counter * PULES_PER_INT / tachoMinuteReg;
            CN10Counter = CLEAR;
            CN9Counter = CLEAR;

            tachoMinuteReg = 0u;
        }
        if (flowMeterMinuteReg >= 120u)  
        {
            //wattNodePower = CalculateEnergy ();  //seperated the wattnode timer from the flowmeter timer
            flowMeterGpm = CalculateFlowmeterGpm(&flowMeterPulseAccumulator);
            

            flowMeterMinuteReg = 0u;
        }
        if (wattNodeMinuteReg >= 60u)  
        {
            wattNodePower = CalculateEnergy ();
           // flowMeterGpm = CalculateFlowmeterGpm(&flowMeterPulseAccumulator);  //seperated the flowmeter timer from the wattnode timer
            

            wattNodeMinuteReg = 0u;
        }
    }
    
    else if ((PIR5bits.TMR4IF) && (PIE5bits.TMR4IE))
    {                                       /* Test for debounce timer tick. */
        PIR5bits.TMR4IF = CLEAR;

        ProcessWattNodeInput ((bool)SwitchInputOne);
        ProcessFlowmeterInput (&flowMeterPulseAccumulator,(bool)SwitchInputTwo);

    }
    
    ClrWdt(); /* Once per interrupt cycle. */

}

/***** EOF for cs_pdk_400_interrupts.c ****************************************/
