/*******************************************************************************
 *  Part Number: CS_WOODMASTER_400_FWR
 *  File Name: cs_pdk_400_configuration_bits.c
 *  Date: 2 January 2015
 *
 *  Author: Peter J. D'Aloisio
 *  Company: Amaranthine, LLC
 *  (c) 2015 Amaranthine, LLC
 *
 *  Licensee: ClearStak, LLC
 *
 *  The material contained herein is confidential and proprietary.
 *******************************************************************************
 *  Revision History: See the cs_pdk_400_main.c source file.
 *******************************************************************************
 *  Microcontroller: PIC18F86K22    Internal Oscillator == 1MHz.
 *******************************************************************************
 *  Notes:  Coding for a source file for an Outdoor Wood Furnace Low Emission
 *          Controller model number IBC 4.0.0
 *
 *          The XC8 compiler contains documentation on the configuration
 *          bit macros within the compiler installation /docs folder in a file
 *          called pic18_chipinfo.html.
 *
 *          For additional information about what the hardware configurations
 *          mean in terms of device operation, refer to the device datasheet.
 *
 *          General C18/XC8 syntax for configuration macros:
 *          #pragma config <Macro Name>=<Setting>, <Macro Name>=<Setting>
 *
 *          A feature of MPLAB X is the 'Generate Source Code to Output'
 *          utility in the Configuration Bits window.  Under Window >
 *          PIC Memory Views > Configuration Bits, a user controllable
 *          configuration bits window is available to Generate Configuration
 *          Bits source code which the user can paste into this project.
 *******************************************************************************
 *  THIS SOFTWARE/FIRMWARE IS PROVIDED IN AN "AS IS" CONDITION. NO
 *  WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 *  LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *  PARTICULAR PURPOSE APPLY TO THIS SOFTWARE/FIRMWARE. THE COMPANY
 *  SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL
 *  OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER. ACCEPTANCE AND/OR
 *  USE OF THIS SOFTWARE/FIRMWARE SHALL CONSTITUTE ACCEPTANCE OF THESE TERMS
 *  AND CONDITIONS.
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

/******************************************************************************/
/* PC-Lint Options                                                            */
/******************************************************************************/

/******************************************************************************/
/* PIC18F86K22 Configuration Bit Settings                                     */
/******************************************************************************/

/* CONFIG1L */
#pragma config RETEN = ON       /* VREG Sleep Enable bit (Enabled) */

#pragma config INTOSCSEL = HIGH /* LF-INTOSC Low-power Enable bit (LF-INTOSC in
                                 * High-power mode during Sleep) */

#pragma config SOSCSEL = DIG    /* SOSC Power Selection and mode Configuration
                                 * bits (Digital (SCLKI) mode) */

#pragma config XINST = OFF      /* Extended Instruction Set Enabled */

/* CONFIG1H */
#pragma config FOSC = INTIO2    /* Oscillator (Internal RC oscillator) */
#pragma config PLLCFG = OFF     /* PLL x4 Enable bit (Disabled) */
#pragma config FCMEN = OFF      /* Fail-Safe Clock Monitor (Disabled) */

#pragma config IESO = OFF       /* Internal External Oscillator Switch Over Mode
                                 * (Disabled) */

/* CONFIG2L */
#pragma config PWRTEN = ON      /* Power Up Timer (Enabled) */

#pragma config BOREN = SBORDIS  /* Brown Out Detect (Enabled in hardware, SBOREN
                                 * disabled) */

#pragma config BORV = 2         /* Brown-out Reset Voltage bits (2.0V) */

#pragma config BORPWR = ZPBORMV /* BORMV Power level (ZPBORMV instead of BORMV
                                 * is selected) */

/* CONFIG2H */
#pragma config WDTEN = SWDTDIS  /* Watchdog Timer (WDT enabled in hardware;
                                   SWDTEN bit disabled) */
#pragma config WDTPS = 16384    /* Watchdog Postscaler (1:8192)
                                /* t = (0.004s x WDTPS) = 32.8s*/

/* CONFIG3L */
#pragma config RTCOSC = INTOSCREF   /* RTCC Clock Select (RTCC uses INTRC) */

#pragma config EASHFT = ON      /* External Address Shift bit (Address shifting
                                 * enabled) */

#pragma config ABW = MM         /* Address Bus Width Select bits (8-bit address
                                 * bus) */

#pragma config BW = 16          /* Data Bus Width (16-bit external bus mode) */
#pragma config WAIT = OFF       /* External Bus Wait (Disabled) */

/* CONFIG3H */
#pragma config CCP2MX = PORTC   /* CCP2 Mux (RC1) */

#pragma config ECCPMX = PORTE   /* ECCP Mux (Enhanced CCP1/3 [P1B/P1C/P3B/P3C]
                                 * muxed with RE6/RE5/RE4/RE3) */

#pragma config MSSPMSK = MSK7   /* MSSP address masking (7 Bit address masking
                                 * mode) */

#pragma config MCLRE = ON       /* Master Clear Enable (MCLR Enabled, RG5
                                 * Disabled) */

/* CONFIG4L */
#pragma config STVREN = ON      /* Stack Overflow Reset (Enabled) */
#pragma config BBSIZ = BB1K     /*  Boot Block Size (1K word Boot Block size) */

/* CONFIG5L */
#pragma config CP0 = ON         /* Code Protect 00800-03FFF (Enabled) */
#pragma config CP1 = ON         /* Code Protect 04000-07FFF (Enabled) */
#pragma config CP2 = ON         /* Code Protect 08000-0BFFF (Enabled) */
#pragma config CP3 = ON         /* Code Protect 0C000-0FFFF (Enabled) */

/* CONFIG5H */
#pragma config CPB = ON         /* Code Protect Boot (Enabled) */
#pragma config CPD = OFF        /* Data EE Read Protect (Disabled) */

/* CONFIG6L */
#pragma config WRT0 = ON        /* Table Write Protect 00800-03FFF (Enabled) */
#pragma config WRT1 = ON        /* Table Write Protect 04000-07FFF (Enabled) */
#pragma config WRT2 = ON        /* Table Write Protect 08000-0BFFF (Enabled) */
#pragma config WRT3 = ON        /* Table Write Protect 0C000-0FFFF (Enabled) */

/* CONFIG6H */
#pragma config WRTC = ON        /* Config. Write Protect (Enabled) */
#pragma config WRTB = ON        /* Table Write Protect Boot (Enabled) */
#pragma config WRTD = OFF       /* Data EE Write Protect (Disabled) */

/* CONFIG7L */
#pragma config EBRT0 = OFF      /* Table Read Protect 00800-03FFF (Disabled) */
#pragma config EBRT1 = OFF      /* Table Read Protect 04000-07FFF (Disabled) */
#pragma config EBRT2 = OFF      /* Table Read Protect 08000-0BFFF (Disabled) */
#pragma config EBRT3 = OFF      /* Table Read Protect 0C000-0FFFF (Disabled) */

/* CONFIG7H */
#pragma config EBRTB = OFF      /* Table Read Protect Boot (Disabled) */

/***** EOF for cs_pdk_400_configuration_bits.c ********************************/
