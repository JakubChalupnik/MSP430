//---------------------------------------------------------------------------
//
// FILENAME.
//      LedMatrix.c - implements support for the HT1632 based LED matrix displey from Sure El.
//
// FUNCTIONAL DESCRIPTION.
//      This file implements the support for DP14112 display from Sure Electronics (32x16 bi-color 3mm).
//      The communication with the display is bit banged due to rather odd protocol.
//
// PROCESSOR.
//      MSP430g family
//
// MODIFICATION HISTORY.
//      Kubik   15.5.2011       Based on separate sources, reformatted and cleaned.
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
#include <string.h>
#include "typedefs.h"
#include "Hw.h"

//
// LED matrix specific defines - commands used by HT1632
//

#define SLAVE_MODE 0x820
#define RC_MASTER_MODE 0x830
#define EXT_CLK_MASTER_MODE 0x838

#define SYS_EN 0x802
#define LED_ON 0x806

#define NMOS_COM8 0x840

#define PWM_01 0x940
#define PWM_02 0x942
#define PWM_03 0x944
#define PWM_04 0x946
#define PWM_05 0x948
#define PWM_06 0x94A
#define PWM_07 0x94C
#define PWM_08 0x94E
#define PWM_09 0x950
#define PWM_10 0x952
#define PWM_11 0x954
#define PWM_12 0x956
#define PWM_13 0x958
#define PWM_14 0x95A
#define PWM_15 0x95C
#define PWM_16 0x95E

//
// Pin definitions - all is on P1, those are corresponding bit masks
//

#define BitCs BIT4
#define BitClk BIT7
#define BitSpiClk BIT5
#define BitSpiDat BIT6

//
// Font parameters - width specifies how many columns, height how many bytes per one column
//

#define FONT_WIDTH 8
#define FONT_HEIGHT 2

//
// Macro definitions
//

#define ClkDelay() IoDelay()

#define BitSet(BitMask) {P1OUT = P1OUT | (BitMask); ClkDelay();}
#define BitClear(BitMask) {P1OUT = P1OUT & ~(BitMask); ClkDelay();}

#define CLK0 {P1OUT = P1OUT & ~(BitSpiClk); ClkDelay();}
#define CLK1 {P1OUT = P1OUT | (BitSpiClk); ClkDelay();}

#define DAT0 {P1OUT = P1OUT & ~(BitSpiDat); ClkDelay();}
#define DAT1 {P1OUT = P1OUT | (BitSpiDat); ClkDelay();}

//
// Static variables
//

const byte FontTable [] = {
#include "font.h"
};

const byte FontTable3 [] = {
#include "font3.h"
};

//
// Screen buffer.
// Due to chip RAM limitations, we only can have one buffer of 64 bytes, that's enough for one colour only.
//

byte ScreenBuffer [64];

//
// External function declarations
//

//
// Local functions
//

//
// FUNCTION NAME.
//      IoDelay - short delay for the LED display.
//
// FUNCTIONAL DESCRIPTION.
//      This function generates a short delay (microseconds) for the LED display.
//      The delay is necessary for giving the HT1632 time to read the data.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void IoDelay (void) {
  volatile int i;

  for (i = 0; i < 6; i++) {
  }
}

//
// FUNCTION NAME.
//      OutputClkPulse - Pulses the 74164 clock input.
//
// FUNCTIONAL DESCRIPTION.
//      This function pulses the 74164 clock input. Short (IoDelay) high pulse is created.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void OutputClkPulse (void) {

    BitSet (BitClk);
    BitClear (BitClk);
}

//
// FUNCTION NAME.
//      OutputA74164 - Controls the 74164 A input.
//
// FUNCTIONAL DESCRIPTION.
//      This function sets the 74164 A input based on the function parameter.
//
// ENTRY PARAMETERS.
//      Value           - Either 0 (input A low) or something else (input A high).
//
// EXIT PARAMETERS.
//      None.
//

void OutputA74164 (int Value) {

  if (Value != 0) {
    BitSet (BitCs);
  } else {
    BitClear (BitCs);
  }
}

//
// FUNCTION NAME.
//      Ht1632ChipSelect - Controls the chip select inputs of HT1632 chips.
//
// FUNCTIONAL DESCRIPTION.
//      This function controls the chip select inputs of HT1632 chips.
//      See below for details.
//
// ENTRY PARAMETERS.
//      Select          - 0 means disable all four HT1632 chips, -1 means enable them all,
//                        positive number means enable just one chip (1 is first HT1632 etc.)
//
// EXIT PARAMETERS.
//      None.
//

void Ht1632ChipSelect (int Select) {
  int i;

  if (Select < 0) {	                // Enable all chips
    OutputA74164 (0);
    OutputClkPulse();
    OutputClkPulse();
    OutputClkPulse();
    OutputClkPulse();
  } else if (Select == 0) {             // Disable all chips
    OutputA74164 (1);
    OutputClkPulse();
    OutputClkPulse();
    OutputClkPulse();
    OutputClkPulse();
  } else {                              // Enable just one chip
    OutputA74164 (1);
    OutputClkPulse();
    OutputClkPulse();
    OutputClkPulse();
    OutputClkPulse();

    OutputA74164 (0);
    OutputClkPulse();
    OutputA74164 (1);
    for (i = 1; i < Select; i++) {
      OutputClkPulse();
    }
  }
}

//
// FUNCTION NAME.
//      AddressWrite - Sends address to HT1632.
//
// FUNCTIONAL DESCRIPTION.
//      This function sends write command and then address to HT1632.
//      The corresponding chip(s) have to be enabled prior calling this function.
//      See below for details.
//
// ENTRY PARAMETERS.
//      Address         - Value to be written into the address register of HT1632.
//
// EXIT PARAMETERS.
//      None.
//

void AddressWrite (byte Address) {
  byte i;

  //
  // The address is 7 bits only. Mask unused bits and send "Write" command (101).
  //

  Address &= 0x7f;

  CLK0;
  DAT1;
  CLK1;
  CLK0;
  DAT0;
  CLK1;
  CLK0;
  DAT1;
  CLK1;

  //
  // Now send the address to HT1632C, MSB first.
  //

  for (i = 0; i < 7; i++) {
    CLK0;
    if (Address & 0x40) {
      DAT1;
    } else {
      DAT0;
    }
    Address <<= 1;
    CLK1;
  }
}

//
// FUNCTION NAME.
//      CommandWrite - Sends command to all HT1632.
//
// FUNCTIONAL DESCRIPTION.
//      This function sends command to all HT1632. This is used for things like initialization.
//
// ENTRY PARAMETERS.
//      Command         - Command to be sent to HT1632.
//
// EXIT PARAMETERS.
//      None.
//

void CommandWrite (word Command) {
  int i;

  //
  // First, mask out all unused command bits (commands are 12 bits only),
  // then select all HT1632.
  //

  Command &= 0x0FFF;

  Ht1632ChipSelect (0);
  Ht1632ChipSelect (-1);

  //
  // Send the command bit by bit, MSB first.
  //

  for (i = 0; i < 12; i++) {
    CLK0;
    if (Command & 0x0800) {
      DAT1;
    } else {
      DAT0;
    }
    Command <<= 1;
    CLK1;
  }

  //
  // Now deselect all HT1632 and leave.
  //

  Ht1632ChipSelect (0);
}

//
// FUNCTION NAME.
//      InitializeHt1632 - Initialize all HT1632.
//
// FUNCTIONAL DESCRIPTION.
//      This function initializes all HT1632 chips - enables them, enables LEDs, sets clocking, output drivers,
//      and last but not least, sets the LED PWM.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void InitializeHt1632 (void) {

  CommandWrite (SYS_EN);
  CommandWrite (LED_ON);
  CommandWrite (RC_MASTER_MODE);
  CommandWrite (NMOS_COM8);
  CommandWrite (PWM_10);
}

//
// FUNCTION NAME.
//      SpiSend - Bit bangs one byte to HT1632.
//
// FUNCTIONAL DESCRIPTION.
//      This function bit bangs one byte to HT1632.
//      We are emulating SPI communication here as the HT1632 is slow and switching from SPI for data communication
//      to bit bang for commands could be a little tricky.
//      We can't use SPI for commands as we need to send 10 or 12 bits, while MSP430 can only do multiples of 8.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void SpiSend (byte Data) {
  int i;

  //
  // Make sure CLK is high, then set the data output accordingly and pulse clock.
  // Do that 8 times to send all 8 bits.
  //

  CLK1;
  for (i = 0; i < 8; i++) {
    if (Data & 0x80) {
      DAT1;
    } else {
      DAT0;
    }
    CLK0;
    CLK1;
    Data <<= 1;
  }
}

//
// FUNCTION NAME.
//      ClearScreen - Clears the screen completely.
//
// FUNCTIONAL DESCRIPTION.
//      This function clears the screen completely, that is switches off all the LEDs in the matrix.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void ClearScreen (void) {
  int j;

  //
  // Select all HT1632, write 0 to address register and then send 32 zeros.
  //

  Ht1632ChipSelect (-1);
  AddressWrite (0);

  for (j = 0; j < 32; j++) {
    SpiSend (0);
  }
}

//
// FUNCTION NAME.
//      SendBuffer - sends the whole buffer to the display.
//
// FUNCTIONAL DESCRIPTION.
//      This function sends the whole buffer (64 bytes) to the display. Offset specifies colour, 0 is green, 16 is red.
//
// ENTRY PARAMETERS.
//      Buffer          - Buffer containing 64 bytes to be sent to display
//      Offset          - Offset (starting address in HT1632) where to write the first byte to
//						  (green LEDs start at 0, red LEDs at 32)
//
// EXIT PARAMETERS.
//      None.
//

void SendBuffer (byte *Buffer, byte Offset) {
  int Display, i;

  //
  // For all four displays, send 16 corresponding bytes to it.
  //

  for (Display = 1; Display <= 4; Display++) {
    Ht1632ChipSelect (Display);
    AddressWrite (Offset);
    for (i = 0; i < 16; i++) {
      SpiSend (*(Buffer++));
    }
  }
}

//
// FUNCTION NAME.
//      DisplayCharacter - displays one character at specified column.
//
// FUNCTIONAL DESCRIPTION.
//      This function displays (puts into the screen buffer) one character from the font table.
//
// ENTRY PARAMETERS.
//      Character	- Character to display (ASCII)
//      Column          - Column on the screen where the character should start
//      Row             - Row on the screen where the character should start
//      Font            - Pointer to the font table
//
// EXIT PARAMETERS.
//      None.
//

void DisplayCharacter (byte Character, byte Column, byte Row, const byte *Font) {
  int i;
  byte *Ptr;
  int FontColumns, RowBytes, FirstCharacter, LastCharacter;
  unsigned long int ColumnPattern;

  FontColumns = *(Font++);
  RowBytes = *(Font++);
  FirstCharacter = *(Font++);
  LastCharacter = *(Font++);
  
  if ((Character < FirstCharacter) ||
      (Character > LastCharacter)
      ) {
    return;
  }
  
  Character -= FirstCharacter;
  Ptr = ((byte *) Font) + (Character * FontColumns * RowBytes);

  for (i = 0; i < FontColumns; i++) {
  	ColumnPattern = (unsigned long int) *Ptr;
  	ColumnPattern <<= 8;
  	if (RowBytes == 2) {
  		ColumnPattern |= *(Ptr + FontColumns);
  	}
  	ColumnPattern >>= Row;
  	ScreenBuffer [Column + i] |= (ColumnPattern >> 8) & 0xFF;
  	ScreenBuffer [Column + i + 32] |= ColumnPattern & 0xFF;
  	Ptr++;
  }
}

// void _delay(void) {
// 	volatile int i;
// 
// 	for (i = 0; i < 32000; i++) {
// 	  ClkDelay();
// 	}
// }

//
// FUNCTION NAME.
//      InitLedMatrix - Initializes the LED matrix display.
//
// FUNCTIONAL DESCRIPTION.
//      This function initializes the GPIOs used to talk to the LED matrix display, 
//      and then the display hardware itself, including clearing the RAM.
//
// ENTRY PARAMETERS.
//      None.
//
// EXIT PARAMETERS.
//      None.
//

void InitLedMatrix (void) {

  //
  // Init GPIO to values we want - that is CLK low, rest is high.
  // Initialize the screen.
  // Clear the screen buffer.
  //

//   P1OUT = 0xFF;
  P1DIR |= BitCs | BitClk | BitSpiClk | BitSpiDat;

  BitClear (BitClk);

  InitializeHt1632 ();
  ClearScreen ();

  memset (ScreenBuffer, 0, sizeof (ScreenBuffer));

  DisplayCharacter ('1', 0, 0, FontTable);
  SendBuffer ((byte *) ScreenBuffer, 32);
}
