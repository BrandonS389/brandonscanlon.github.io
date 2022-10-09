/*******************************************************************************
 *  Part Number: ClearStakSerialReceive
 *  File Name: ClearStakSerialReceive.c
 *  Date: 6 January 2016
 *
 *  Author: Clancy Emanuel
 *  Guy Who Fixed Author's Mistake: Michael J Packit
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
#include <stdlib.h>

#endif

#include "ClearStakSerialInput.h"
#include "ClearStakDataTable.h"

extern volatile ClearStakDataTable keysAndValues;

volatile char receivedMessage0[MAX_RECEIVE_LENGTH],receivedMessage1[MAX_RECEIVE_LENGTH],
startMessage[START_MESSAGE_LENGTH], preparedMessage[MAX_RECEIVE_LENGTH];
volatile char* receivedMessage = receivedMessage0; // initialize to first buffer
volatile uint8_t toggleRcvBuf=0;
volatile int counter =0;
volatile int state = CHECKING_FOR_START;

void addCharToReceivedString(unsigned char aCharToAdd) {
    
    receivedMessage[counter] = aCharToAdd;
    incrementReceivedStringCounter();
    CLEAR_EUSART2_ERRORS();
}


// 6/30/17 0 out keyValue table each time since the same keys are not sent with every message
// 7/8/17 stop sending whole buffers for debugging, USART getting jammed.
// 11/13/18 add parameter to point to receive buffer
void doSerialReceiveStateMachine(uint8_t whichBuf) {
    char* processBuf;
    
    if(whichBuf==0){
        processBuf=receivedMessage0;
    }
    else {
        processBuf=receivedMessage1;
    }
        
    clearPreparedMessage();
    memset(&keysAndValues,0,sizeof(struct ClearStakDataTable));
    CreateDataTable(&keysAndValues, "KVP");
    int messageLength = strlen(processBuf) - (START_MESSAGE_LENGTH + STOP_MESSAGE_LENGTH);
    memcpy(preparedMessage, &processBuf[START_MESSAGE_LENGTH], messageLength);
//    strcat(preparedMessage,"--Received from PI\r\n");
//    serialSendMessage(preparedMessage);
    setVariablesFromInput(extractKeyValuePairs(preparedMessage));
 //   strcat(preparedMessage,"Parsed MSG:\r\n");
 //  serialSendMessage(preparedMessage);
}

void setVariablesFromInput(unsigned char*** someKeyValuePairs) {
    keyValuePairs = someKeyValuePairs;
}
/*
void clearKeyValuePairs() {
    memset(keyValuePairs, 0, 2);

}
*/
int findNumberOfKeyValuePairs(unsigned char*** someKeyValuePairs) {
    int i, validPair, numberOfKeyValuePairs;
    validPair = 1;
    i = 0;
    while (validPair) {
        validPair = someKeyValuePairs[0][i];
        i++;
    }
    numberOfKeyValuePairs = i - 1;
    return numberOfKeyValuePairs;
}

void incrementReceivedStringCounter() {
    counter++;
}

void resetReceivedStringCounter() {
    counter = 0;
}

int getReceivedStringCounter() {
    return counter;
}

void printReceivedMessage() {
    
    (receivedMessage);
}

// changed to memset 6/30 for speed: JW
void clearReceivedMessage(uint8_t buf2Clear) {
    
    if(buf2Clear==0)
        memset(receivedMessage0,0,MAX_RECEIVE_LENGTH-1);
    else
        memset(receivedMessage1,0,MAX_RECEIVE_LENGTH-1);
    resetReceivedStringCounter();
    state = CHECKING_FOR_START;
}

void clearPreparedMessage() {
    memset(preparedMessage,0,MAX_RECEIVE_LENGTH-1);
}

unsigned char*** getKeyValuePairs() {
    return keyValuePairs;
}

void CLEAR_EUSART2_ERRORS(){  // OERR = overrun error bit, CREN = continuous receiver enable bit,
    if (RCSTA2bits.OERR){    // if errors on EUART2 reception status register
        RCSTA2bits.CREN = 0; // disable continuous reception on this register (this also clears OERR)
        Nop();
        RCSTA2bits.CREN = 1; // enable continuous reception, clears OERR bit
    }

}
