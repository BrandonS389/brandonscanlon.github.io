/*******************************************************************************
 *  Part Number: ClearStakInputParser
 *  File Name: ClearStakInputParser.c
 *  Date: 8 January 2016
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

#endif

#include "ClearStakInputParser.h"

unsigned char* keyPointers[MAX_NUMBER_OF_ADJUSTABLE_KEY_VALUE_PAIRS];
unsigned char* valuePointers[MAX_NUMBER_OF_ADJUSTABLE_KEY_VALUE_PAIRS];
unsigned char** InputParserKeysAndValues[2];
volatile int numberOfEditableVariables = 0;

// He seems to point the key/value pair pointers to the input string itself
unsigned char*** extractKeyValuePairs(unsigned char* aStringToParse) {
    char* pch;
    pch = strtok(aStringToParse,"=");  // the key is on left side of = sign
    int i = 0;
    while(pch != NULL) {
        keyPointers[i] = pch;
        valuePointers[i] = strtok(NULL," ");//value is up to the blank space
        pch = strtok(NULL,"=");
        i++;
    }
    numberOfEditableVariables = i;
    InputParserKeysAndValues[0] = keyPointers;
    InputParserKeysAndValues[1] = valuePointers;
    return InputParserKeysAndValues;
}