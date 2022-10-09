/* 
 * File:   ClearStakSerialReceive.h
 * Author: Clancy Emanuel
 *
 * Created on January 6, 2016, 4:29 PM
 */

#ifndef CLEARSTAKSERIALRECEIVE_H
#define	CLEARSTAKSERIALRECEIVE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "string.h"    
#include "stdio.h"
#include "ClearStakInputParser.h"
#include "ClearStakSerialHandler.h"

/*String definitions*/
#define MAX_RECEIVE_LENGTH 250   // chopped from 700 6/7/18, we believe it sends less than 200    
#define CLEAR_CHARACTER '~'
#define START_MESSAGE "STARTMESSAGE" /* The Pi should start every message with this*/
#define START_MESSAGE_LENGTH  12
#define STOP_MESSAGE "STOPMESSAGE" /* The Pi should end every message with this*/
#define STOP_MESSAGE_LENGTH 11
/*States for the serial state machine*/
#define CHECKING_FOR_START 0
#define RECEIVING_KEY_VALUE_PAIRS 1

volatile bool newMessage = false;
volatile bool newMessageParsed = false;
volatile bool doit = false;

extern volatile uint8_t toggleRcvBuf; // toggle the receive buffer
extern volatile uint8_t toggleProcessBuf;

unsigned char*** keyValuePairs;
extern volatile char* receivedMessage;
extern volatile char receivedMessage0[],receivedMessage1[],
startMessage[START_MESSAGE_LENGTH], preparedMessage[];
void addCharToReceivedString(unsigned char aCharToAdd);
void setVariablesFromInput(unsigned char*** someKeyValuePairs);
void incrementReceivedStringCounter();
int getReceivedStringCounter();
void resetReceivedStringCounter();
void printReceivedMessage();
void clearReceivedMessage(uint8_t whichBuf);
void clearPreparedMessage(); 

//void clearKeyValuePairs();
unsigned char*** getKeyValuePairs();
int findNumberOfKeyValuePairs(unsigned char*** someKeyValuePairs);
void CLEAR_EUSART2_ERRORS();

#ifdef	__cplusplus
}
#endif

#endif	/* CLEARSTAKSERIALRECEIVE_H */