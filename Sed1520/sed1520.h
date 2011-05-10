#ifndef _SED1520_H
#define _SED1520_H

//
// Function prototypes
//

void LcdCmd (byte Command);
void LcdData (byte Data);
void LcdFill (byte Pattern);
void LcdInit (void);
void LcdPutc (byte x, byte y, byte Char);

#endif
