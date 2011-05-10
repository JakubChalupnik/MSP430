#ifndef _SED1520_H
#define _SED1520_H

//
// Do _not_ define both BIG (8x16) and BIG_BIG (16x16)
//

// #define USE_BIG_FONT
// #define USE_BIG_BIG_FONT

//
// Define if you want the logo to be displayed in init procedure
//

// #define USE_LOGO

//
// Function prototypes
//

void LcdCmd (byte Command);
void LcdData (byte Data);
void LcdFill (byte Pattern);
void LcdInit (void);
void LcdPutc (byte x, byte y, byte Char);

// #define glcd_putbyte(x, y, data) {glcd_set_cursor(x, y); sed1520_data(data);}
// 
// #if defined USE_BIG_FONT || defined USE_BIG_BIG_FONT
// void glcd_putc(byte x, byte y, byte c);
// #endif
// 
// 
// void SetDb (byte Data);
// 
// 
// void Nop (void);

#endif
