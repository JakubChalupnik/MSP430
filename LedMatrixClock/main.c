//---------------------------------------------------------------------------
//
// FILENAME.
//      Main.c - main file of the LED matrix clock.
//
// FUNCTIONAL DESCRIPTION.
//      This file implements the main function of the project, that is initialization and main program loop.
//
// PROCESSOR.
//      MSP430g family
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

//
// Local constant defines
//

//
// Macro definitions
//

//
// Local typedefs
//

//
// Global and static variables
//

//
// Following variables are used for measuring the high level and period length of the DCF77 signal pulse.
//

static volatile word DcfPeriodLength;
static volatile word DcfHighPulseLength;

//
// External function declarations
//

void InitializeCpu (void);
void DelayMs (word Ms);

//
// Local function prototypes
//

void Port1InterruptHandler (void);

//
// Interrupt handlers
//

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR_HOOK(void) {
	Port1InterruptHandler();
}

//
// Local functions
//

//---------------------------------------------------------------------------
//
// FUNCTION NAME.
//      InitializeGpio - initializes the GPIO system.
//
// FUNCTIONAL DESCRIPTION.
//      This function initializes the GPIO system - pin direction, functions, interrupts.
//      Note this is not quite aligned with Hw.h yet, wouldn't be nice to have this automatically configured as per Hw.h?
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void InitializeGpio (void) {

    P1OUT = 0;                          // Port 1 Output Register
    P1DIR = DCF77_PON_BIT;              // Port 1 Direction Register
    P1IES = 0;                          // Port 1 Interrupt Edge Select Register
    P1IFG = 0;                          // Port 1 Interrupt Flag Register

    P2OUT = 0;                          // Port 2 Output Register
    P2IES = 0;                          // Port 2 Interrupt Edge Select Register
    P2IFG = 0;                          // Port 2 Interrupt Flag Register
}

//---------------------------------------------------------------------------
//
// FUNCTION NAME.
//      InitializeTimerA - initializes timer A.
//
// FUNCTIONAL DESCRIPTION.
//      This function initializes timer A that's used for measuring the DCF77 pulses time.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void InitializeTimerA (void) {

    //
    // TACTL, Timer A Control Register
    // Set to SMCLK/2, counter stopped
    //

    TACTL = TASSEL_2 + ID_3 + MC_0;
}

//---------------------------------------------------------------------------
//
// FUNCTION NAME.
//      Port1InterruptHandler - processes the interrupt from Port1.
//
// FUNCTIONAL DESCRIPTION.
//      Process the interrupt from Port1 - that means detecting if it was falling or rising edge.
//      This is used for DCF77 pulse measurement:
//       - on rising edge, store timer value in DcfPeriodLength and restart the timer
//       - on falling edge, store timer value in DcfHighPulseLength
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void Port1InterruptHandler (void) {

  if (DCF77_PORT_IFG & DCF77_DATA_BIT) {        // Is this interrupt from DCF77?
    DCF77_PORT_IFG &= ~DCF77_DATA_BIT;          // Clear the pending interrupt

    if (Dcf77DataIn ()) {                       // DCF77 pin is high, that means rising edge
      DcfPeriodLength = TimerRead ();
      TimerStart ();
    } else {                                    // DCF77 pin is low, that is falling edge
      DcfHighPulseLength = TimerRead ();
    }
  }
}

//---------------------------------------------------------------------------
//
// FUNCTION NAME.
//      InitializeDcf77 - initializes the DCF77 receiver
//
// FUNCTIONAL DESCRIPTION.
//      This function assumes that GPIOs are defined already and only cares about the DCF77 receiver init.
//      The one being used (Pollin "DCF-Empfangsmodul DCF1", #810-054) needs one high pulse on PON.
//      Dcf77 interrupt shall be disabled yet.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void InitializeDcf77 (void) {

  //
  // Pull PON high for a while, then pull it down to start the receiver.
  //

  Dcf77PonSet ();
  DelayMs (500);
  Dcf77PonClear ();

  //
  // Wait for the rising edge - wait for low lever first, then wait while the low level lasts
  // Repeat that a couple of times to give the receiver some time to sync.
  //

  while (Dcf77DataIn ());
  while (!Dcf77DataIn ());
  while (Dcf77DataIn ());
  while (!Dcf77DataIn ());
}

//---------------------------------------------------------------------------
//
// FUNCTION NAME.
//      main - Main program.
//
// FUNCTIONAL DESCRIPTION.
//      This function initializes the hardware and then starts main program loop.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

int main (void) {

  InitializeCpu ();
  InitializeGpio ();
  InitializeTimerA ();
  InitializeDcf77 ();

  while (Dcf77DataIn ()) {}

  return 0;
}
