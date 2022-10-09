/* 
 * File:   ClearStakOutputHandler.h
 * Author: clancyemanuel
 *
 * Created on January 12, 2016, 10:47 PM
 */

#ifndef CLEARSTAKOUTPUTHANDLER_H
#define	CLEARSTAKOUTPUTHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "ClearStakDataTable.h"
#include "ClearStakSerialHandler.h"

typedef struct ClearStakOutputHandler {
    ClearStakSerialHandler serialHandler;
    char* name;
}ClearStakOutputHandler;

void CreateOutputHandler(ClearStakOutputHandler* anOutputHandler, char* aName);
void outputEvent(ClearStakOutputHandler* anOutputHandler, ClearStakDataTable* aTable);


#ifdef	__cplusplus
}
#endif

#endif	/* CLEARSTAKOUTPUTHANDLER_H */

