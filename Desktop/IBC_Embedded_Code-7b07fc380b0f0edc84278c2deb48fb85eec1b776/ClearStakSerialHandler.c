/*******************************************************************************
 *  Part Number: ClearStakOutputHandler
 *  File Name: ClearStakOutputHandler.c
 *  Date: 12 January 2016
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
#include <stdio.h>

#endif
#include "ClearStakSerialHandler.h"
//#define CONTROLLER2

void 
serialOutputEvent(ClearStakSerialHandler* aSerialHandler, ClearStakDataTable* aTable) {
    serialBuildMessage(aSerialHandler, aTable);    // it sends 2/3 of the values
    serialSendMessage(aSerialHandler->outputMessage); // send what is left
    transmissionTimer = 0;  // reset upon success
    //serialClearMessage(aSerialHandler);
}

void serialSendMessage(char* aMessage) {
   
     if ((RS232DataTermRts == RS232_RTS_ASSERTED) &&
                    (RS232_DATA_TCVR_CTS == RS232_CTS_DEASSERTED)) {
                m_RS232_DATA_TCVR_CTS_ASSERT()
     }

    if ((RS232DataTermRts == RS232_RTS_DEASSERTED) &&
            (RS232_DATA_TCVR_CTS == RS232_CTS_ASSERTED)) {
        m_RS232_DATA_TCVR_CTS_DEASSERT();
    }

    if ((RS232DataTermRts == RS232_RTS_ASSERTED) &&
            (RS232_DATA_TCVR_CTS == RS232_CTS_ASSERTED)) {
        puts2USART(aMessage);
        
    }
}
/* Updated 5/19/17 to send one row at a time as there seems to be limits on string size to UART JW , 12/21/17 send 1/3, then 1/3, then return whats left*/
char* serialBuildMessage(ClearStakSerialHandler* aSerialHandler, ClearStakDataTable* aTable) {
    uint8_t chopper;
    char msg1[16],msg2[16];
    uint8_t count = aTable->counter;
    
#if defined (CONTROLLER2)
    chopper=aTable->counter/2;  // few msgs
#endif
#ifndef CONTROLLER2
    chopper=aTable->counter/3;
#endif
    
       serialClearMessage(aSerialHandler);  // reset the string
    for(int i = 0; i < aTable->counter;i++) {
        strcat(aSerialHandler->outputMessage, aTable->keys[i]);
        strcat(aSerialHandler->outputMessage, "=");
        strcat(aSerialHandler->outputMessage, aTable->values[i]);
        strcat(aSerialHandler->outputMessage, " ");
        // getting puts2USART error if string is too large, so breaking it up
        if(i==chopper || i ==chopper*2){
          /*  sprintf(msg1,"tableSize=%u ",count);
            strcat(aSerialHandler->outputMessage,msg1);
            sprintf(msg2,"rows=%u ",i);
            strcat(aSerialHandler->outputMessage,msg2);*/
            strcat(aSerialHandler->outputMessage,"\r\n");
            serialSendMessage(aSerialHandler->outputMessage);  // send the first ten
            serialClearMessage(aSerialHandler);  // reset the string
        } 
    }
    strcat(aSerialHandler->outputMessage,"\r\n");
    return aSerialHandler->outputMessage;
}

void serialClearMessage(ClearStakSerialHandler* aSerialHandler){
    memset(aSerialHandler->outputMessage,0,MAX_MESSAGE_LENGTH);
}
