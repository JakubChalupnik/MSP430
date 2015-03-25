//---------------------------------------------------------------------------
//
// FILENAME.
//      Cpu.c - CPU specific initialization.
//
// FUNCTIONAL DESCRIPTION.
//      This file implements the CPU specific initialization, that is clock sourcing, watchdog etc.
//
// PROCESSOR.
//      MSP430G family
//
// MODIFICATION HISTORY.
//      Kubik   13.5.2011       Initial version, just dummy file.
//
// LICENSE.
//      Copyright 2011 Jakub Chalupnik (JakubChalupnik@gmail.com). All rights reserved.
//      (see license.txt)
//
//---------------------------------------------------------------------------

//
// Include files, first common includes, then project specific includes
//

#include <msp430.h>
#include "typedefs.h"
#include "hw.h"

//---------------------------------------------------------------------------
//
// FUNCTION NAME.
//      InitializeCpu - initializes the CPU.
//
// FUNCTIONAL DESCRIPTION.
//      This function initializes the CPU clocks and watchdog.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void InitializeCpu (void) {
// 
//   //
//   // Disable watchdog
//   //
// 
//   WDTCTL = WDTPW + WDTHOLD;
// 
//   //
//   // Initialize CPU clock:
//   // - MCLK  - internal 1MHz oscillator without any calibration, no divider
//   // - SMCLK - internal 1MHz with /8 divider
//   // - XT2 off
//   //
// 
//   BCSCTL2 = SELM_0 + DIVM_0 + DIVS_3;
//   DCOCTL = 0x00;
//   __delay_cycles(100000);               // Adjust this accordingly to your VCC rise time
// 
//   DCOCTL = MOD1 + MOD3 + MOD4 + DCO1;
//   BCSCTL1 = XT2OFF + DIVA_0 + RSEL0 + RSEL1 + RSEL2 + RSEL3;
//   BCSCTL3 = XT2S_0 + LFXT1S_0 + XCAP_1;
// 
//     /*
//      * Basic Clock System Control 2
//      *
//      * SELM_0 -- DCOCLK
//      * DIVM_0 -- Divide by 1
//      * ~SELS -- DCOCLK
//      * DIVS_3 -- Divide by 8
//      * ~DCOR -- DCO uses internal resistor
//      *
//      * Note: ~<BIT> indicates that <BIT> has value zero
//      */
//     BCSCTL2 = SELM_0 + DIVM_0 + DIVS_3;
// 
//     if (CALBC1_1MHZ != 0xFF) {
//         /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
//          * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
//          */
//         DCOCTL = 0x00;
//         BCSCTL1 = CALBC1_1MHZ;      /* Set DCO to 1MHz */
//         DCOCTL = CALDCO_1MHZ;
//     }
// 
//     /* 
//      * Basic Clock System Control 1
//      * 
//      * XT2OFF -- Disable XT2CLK
//      * ~XTS -- Low Frequency
//      * DIVA_0 -- Divide by 1
//      * 
//      * Note: ~XTS indicates that XTS has value zero
//      */
//     BCSCTL1 |= XT2OFF + DIVA_0;
// 
//     /* 
//      * Basic Clock System Control 3
//      * 
//      * XT2S_0 -- 0.4 - 1 MHz
//      * LFXT1S_0 -- If XTS = 0, XT1 = 32768kHz Crystal ; If XTS = 1, XT1 = 0.4 - 1-MHz crystal or resonator
//      * XCAP_1 -- ~6 pF
//      */
//     BCSCTL3 = XT2S_0 + LFXT1S_0 + XCAP_1;

//         DCOCTL = 0xE0;
//         BCSCTL1 = 0x0F;
//         BCSCTL2 = 0x06;
//         BCSCTL3 = 0x00;










    WDTCTL = WDTPW + WDTHOLD;   




    /*
     * Basic Clock System Control 2
     *
     * SELM_0 -- DCOCLK
     * DIVM_0 -- Divide by 1
     * ~SELS -- DCOCLK
     * DIVS_3 -- Divide by 8
     * ~DCOR -- DCO uses internal resistor
     *
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    BCSCTL2 = SELM_0 + DIVM_0 + DIVS_3;

    if (CALBC1_1MHZ != 0xFF) {
        /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
         * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
         */
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_1MHZ;      /* Set DCO to 1MHz */
        DCOCTL = CALDCO_1MHZ;
    }

    /*
     * Basic Clock System Control 1
     *
     * XT2OFF -- Disable XT2CLK
     * ~XTS -- Low Frequency
     * DIVA_0 -- Divide by 1
     *
     * Note: ~XTS indicates that XTS has value zero
     */
    BCSCTL1 |= XT2OFF + DIVA_0;

    /*
     * Basic Clock System Control 3
     *
     * XT2S_0 -- 0.4 - 1 MHz
     * LFXT1S_0 -- If XTS = 0, XT1 = 32768kHz Crystal ; If XTS = 1, XT1 = 0.4 - 1-MHz crystal or resonator
     * XCAP_1 -- ~6 pF
     */
    BCSCTL3 = XT2S_0 + LFXT1S_0 + XCAP_1;
















}



