/* 
 * File:   ClearStakSerialHandler.h
 * Author: clancyemanuel
 *
 * Created on January 12, 2016, 10:47 PM
 */

#ifndef CLEARSTAKSERIALHANDLER_H
#define	CLEARSTAKSERIALHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct ClearStakSerialHandler ClearStakSerialHandler;

#include "ClearStakDataTable.h"
#include "cs_woodmaster_400_user.h"

#define MAX_MESSAGE_LENGTH 350   // upped from 300, 5/18/17 by JW, Buffer was overflowing

struct ClearStakSerialHandler {
    char outputMessage[MAX_MESSAGE_LENGTH];
};

void serialOutputEvent(ClearStakSerialHandler* aSerialHandler, ClearStakDataTable* aTable);
void serialSendMessage(char* aMessage);
char* serialBuildMessage(ClearStakSerialHandler* aSerialHandler, ClearStakDataTable* aTable);
void serialClearMessage(ClearStakSerialHandler* aSerialHandler);


#ifdef	__cplusplus
}
#endif

#endif	/* CLEARSTAKSERIALHANDLER_H */

