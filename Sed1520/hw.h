#ifndef _DEFINES_H
#define _DEFINES_H

#include <msp430.h>

//
// LCD pin and communication defines
//

#define LCD_A0_0() P1OUT &= ~BIT1
#define LCD_A0_1() P1OUT |=  BIT1
#define LCD_E1_1() P1OUT |=  BIT2
#define LCD_E1_0() P1OUT &= ~BIT2
#define LCD_E2_1() P1OUT |=  BIT3
#define LCD_E2_0() P1OUT &= ~BIT3

void LcdSetDataBus (byte);

//
// Architectural specific defines
//

#define __progmem_const__ const
//#define Nop()
void Nop (void);

#endif
