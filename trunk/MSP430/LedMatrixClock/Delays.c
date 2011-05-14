//---------------------------------------------------------------------------
//
// FILENAME.
//      Delays.c - software generated delays.
//
// FUNCTIONAL DESCRIPTION.
//      This file implements various software generated delays. 
//      Those are inacurate and as interrupt can kick in, they can end up being much longer.
//
// PROCESSOR.
//      MSP430g family
//
// MODIFICATION HISTORY.
//      Kubik   14.5.2011       Initial version, using __delay_cycles and CPU_FREQUENCY.
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
// Local functions
//

//---------------------------------------------------------------------------
//
// FUNCTION NAME.
//      DelayMs - software loop based delay.
//
// FUNCTIONAL DESCRIPTION.
//      This function delays for specified number of milliseconds.
//      __delay_cycles is intrinsic function, that is compiler generated one.
//
// ENTRY PARAMETERS.
//      Ms      - Number of milliseconds to wait.
//
// EXIT PARAMETERS.
//      None.
//

void DelayMs (word Ms) {

  while (Ms--) {
    __delay_cycles (CPU_FREQUENCY / 1000);
  }
}  
