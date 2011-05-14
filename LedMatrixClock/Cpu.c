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
  // Disable watchdog
  //

  WDTCTL = WDTPW + WDTHOLD;
  
  //
  // Initialize CPU clock:
  // - MCLK  - internal 1MHz oscillator without any calibration, no divider
  // - SMCLK - internal 1MHz with /8 divider
  // - XT2 off
  //

  BCSCTL2 = SELM_0 + DIVM_0 + DIVS_3;
  DCOCTL = 0x00;
  __delay_cycles(100000);               // Adjust this accordingly to your VCC rise time

  DCOCTL = MOD1 + MOD3 + MOD4 + DCO1;
  BCSCTL1 = XT2OFF + DIVA_0 + RSEL0 + RSEL1 + RSEL2 + RSEL3;
  BCSCTL3 = XT2S_0 + LFXT1S_0 + XCAP_1;
}
