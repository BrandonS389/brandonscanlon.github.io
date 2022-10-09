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

#endif

#include "ClearStakOutputHandler.h"

void CreateOutputHandler(ClearStakOutputHandler* anOutputHandler, char* aName) {
    anOutputHandler->name = aName;
}

void outputEvent(ClearStakOutputHandler* anOutputHandler, ClearStakDataTable* aTable) {
    serialOutputEvent(&(anOutputHandler->serialHandler), aTable);
}


