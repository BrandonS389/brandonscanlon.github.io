/*
 * File:   ClearStakSerialOutput.h
 * Author: clancyemanuel
 *
 * Created on January 12, 2016, 10:26 AM
 */

#ifndef CLEARSTAKSERIALOUTPUT_H
#define	CLEARSTAKSERIALOUTPUT_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <string.h>

#define MAX_NUMBER_OF_KEY_VALUE_PAIRS 40 //50 makes it run out of memory, increased from 30 12/21/17, increased from 35 6/6/18

    typedef struct ClearStakDataTable {
        char* keys[MAX_NUMBER_OF_KEY_VALUE_PAIRS];
        char* values[MAX_NUMBER_OF_KEY_VALUE_PAIRS];
        char* name;
        int counter;
    }ClearStakDataTable;

    void CreateDataTable(ClearStakDataTable* aTable, char* aName);
    void DataTablePutPair(ClearStakDataTable* aTable, char* aKey, char* aValue);
    void DataTableIncrementCounter(ClearStakDataTable* aTable);
    int DataTableGetKey(ClearStakDataTable* aTable, char* aKey);
    char* DataTableGetValue(ClearStakDataTable* aTable, char* aKey);



#ifdef	__cplusplus
}
#endif

#endif	 /*CLEARSTAKSERIALOUTPUT_H */

