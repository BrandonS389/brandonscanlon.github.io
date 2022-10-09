/*******************************************************************************
 *  Part Number: ClearStakSerialReceive
 *  File Name: ClearStakSerialReceive.c
 *  Date: 6 January 2016
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

#endif

#include "ClearStakDataTable.h"

void CreateDataTable(ClearStakDataTable* aTable, char* aName) {
    aTable->counter = 0;
    aTable->name = aName;
}

void DataTablePutPair(ClearStakDataTable* aTable, char* aKey, char* aValue) {
    int keyIndex = DataTableGetKey(aTable, aKey); // check if key already exists
    if (keyIndex == -1) {// if it doesn't create a new key value pair
        aTable->keys[aTable->counter] = aKey;
        aTable->values[aTable->counter] = aValue;
        DataTableIncrementCounter(aTable);
    } else {
        aTable->values[keyIndex] = aValue; // if it does exist replace the value
    }
}

void DataTableIncrementCounter(ClearStakDataTable* aTable) {
    aTable->counter++;
}

char* DataTableGetValue(ClearStakDataTable* aTable, char* aKey) {
    int keyIndex = DataTableGetKey(aTable, aKey); // check if the key exists
    if (keyIndex == -1) {
        return "Key does not exist.";
    } else {
        return aTable->values[keyIndex];
    }
}

int DataTableGetKey(ClearStakDataTable* aTable, char* aKey) {
    int key = -1;
    int i = 0;
    while((key == -1) && (i < aTable->counter)) {
        if (!strcmp(aKey, aTable->keys[i])) {
            key = i;
        }
        i++;
    }
    return key;
}
