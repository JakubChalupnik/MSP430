//****************************************************************
// TITLE:   SED1520LCD.C
// DATE:    04 DEC 05
// BY:      JV
// DESCRIPTION: SED1520 code for DrawFns.C
// COMPILER:    MPLAB C18
//----------------------------------------------------------------
// Revision:    V1.1
//----------------------------------------------------------------
// Modified by Jakub Chalupnik
// As the EW12A03GLY does not support reading.
// all the RMW functions were removed, including bit graphics
//****************************************************************

#include "typedefs.h"
#include "hw.h"
#include "sed1520.h"
#include "font.h"

//
// Locally used defines
//

#define LEFT    0x01
#define RIGHT   0x02

//
// Local variables
//

static int Side;                        // Left or Right side of LCD

//===============================================================
// command_write (Cdata)
// Write command data to the LCD
// See SED1520 datasheet for more info
//===============================================================
void LcdCmd (byte Command) {

    LCD_A0_0 ();
    LcdSetDataBus (Command);
    if (Side == LEFT) {
        LCD_E1_1 ();
        Nop ();
        LCD_E1_0 ();
    } else {
        LCD_E2_1 ();
        Nop ();
        LCD_E2_0 ();
    }
}

//===============================================================
// Data write (DData)
// Writes display data to the LCD
//===============================================================
void LcdData (byte Data) {

    LCD_A0_1 ();
    LcdSetDataBus (Data);
    if (Side == LEFT) {
        LCD_E1_1 ();
        Nop ();
        LCD_E1_0 ();
    } else {
        LCD_E2_1 ();
        Nop ();
        LCD_E2_0 ();
    }
}

//===================================================================
// Fills the whole display with a specified pattern (clear etc.)
//===================================================================
void LcdFill (byte Pattern) {
    byte displ, page, column;

    for (displ = 0; displ < 2; displ++) {       // Clear both controlers data
        Side = displ;
        for (page = 0; page < 4; page++) {      // Now go through all pages and clear the LCD RAM
            LcdCmd (0xB8 | page);               // so that the display is cleared
            LcdCmd (0x00);
            for(column = 0; column < 61; column++) {
                LcdData (Pattern);
            }
        }
    }
}

//===================================================================
// Set cursor position
//===================================================================
void LcdSetCursorPos (byte x, byte y) {

    if (x <= 60) {                      // Left side
        Side = LEFT;
    } else if (x <= 121) {              // Right side
        x -= 61;
        Side = RIGHT;
    } else {
        return;
    }

    LcdCmd (0xB8 | (y & 0x03));         // Select row
    LcdCmd (60 - x);
}

//===================================================================
// Put a character to a specified row/column
//===================================================================
void LcdPutc (byte x, byte y, byte Char) {
    byte i;
    __progmem_const__ byte *ptr;

    Char -= 0x20;                       // Adjust to the fact the font starts at 0x20
    ptr = Font5x7[Char];
    i = 5;
    while(i--) {
        LcdSetCursorPos (x++, y);
        LcdData (*ptr++);
    }
    LcdSetCursorPos (x, y);
    LcdData (0x00);
}

//===================================================================
// Initialise the SED11520 controllers
// for the display type we are using
//===================================================================
void LcdInit (void) {
    byte page;

    LCD_E1_0 ();                                  // De-select each side to start
    LCD_E2_0 ();

    // Setup both SED1520 controllers
    for(page = 0; page < 2; page++) {
        Side = page;
        LcdCmd (0xaf);                       // Turn on the display
        LcdCmd (0xa4);                       // Static drive is off
        LcdCmd (0xa9);                       // Duty cycle is set to 1/32
        LcdCmd (0xe2);                       // Reset the chip
        LcdCmd (0xa0);                       // Set ADC
        LcdCmd (0xee);                       // Read modify write disabled
        LcdCmd (0xc0);                       // Set the start position to
        LcdCmd (0xb8);                       // the top left of the display
        LcdCmd (0x00);                       // in column 0
    }

    LcdFill (0x00);
}
