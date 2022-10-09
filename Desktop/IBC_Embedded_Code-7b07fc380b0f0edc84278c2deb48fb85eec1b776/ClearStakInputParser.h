/* 
 * File:   ClearStakInputParser.h
 * Author: clancyemanuel
 *
 * Created on January 8, 2016, 3:48 PM
 */

#ifndef CLEARSTAKINPUTPARSER_H
#define	CLEARSTAKINPUTPARSER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "string.h"
    
#define MAX_NUMBER_OF_ADJUSTABLE_KEY_VALUE_PAIRS 15
    
extern volatile int numberOfEditableVariables;
unsigned char*** extractKeyValuePairs(unsigned char* aStringToParse);



#ifdef	__cplusplus
}
#endif

#endif	/* CLEARSTAKINPUTPARSER_H */

