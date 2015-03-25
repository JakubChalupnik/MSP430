//---------------------------------------------------------------------------
//
// FILENAME.
//      Hw.h - include file describing the hardware details of the platform.
//
// FUNCTIONAL DESCRIPTION.
//      Define pinout of all the attached peripherals, and macros to bit bang them.
//
// PROCESSOR.
//      MSP430G family
//
// MODIFICATION HISTORY.
//      Kubik   14.5.2011       Initial release, specifying pinout of DCF77.
//
// LICENSE.
//      Copyright 2011 Jakub Chalupnik (JakubChalupnik@gmail.com). All rights reserved.
//      (see license.txt)
//
//---------------------------------------------------------------------------

#ifndef _HW_H
#define _HW_H

//
// CPU related defines
//

#define CPU_FREQUENCY   1000000UL

//
// Define bits and ports
//

#define DCF77_PORT_IN   P1IN
#define DCF77_PORT_OUT  P1OUT
#define DCF77_DATA_BIT  BIT2
#define DCF77_DATA_SHIFT 2
#define DCF77_PON_BIT   BIT3
#define DCF77_PORT_IFG  P1IFG
#define DCF77_PORT_IES  P1IES

#define LED_PORT_OUT    P1OUT
#define LED_REC_BIT     BIT0
#define LED_REC_BIT_SHIFT 0

//
// Define macros to work with the above
//

#define Dcf77DataIn()   (DCF77_PORT_IN & DCF77_DATA_BIT)
#define Dcf77PonSet()	{DCF77_PORT_OUT |= DCF77_PON_BIT;}
#define Dcf77PonClear()	{DCF77_PORT_OUT &= ~DCF77_PON_BIT;}

//
// Define other HW related macros
//

//#define TimerStop()   	{TACTL = (TACTL & ~(MC1 | MC0)) | MC_0;}
//#define TimerStart()  	{TAR = 0; TACTL = (TACTL & ~(MC1 | MC0)) | MC_2;}
#define TimerRead()   	(TAR)

#define TimerStop()   { TACTL = TASSEL_2 | ID_3 | MC_0;}
#define TimerStart()  { TAR = 0; TACTL = TASSEL_2 | ID_3 | MC_2;}


#define LedRedOn() 		{LED_PORT_OUT |= LED_REC_BIT;}
#define LedRedOff() 	{LED_PORT_OUT &= ~LED_REC_BIT;}

#endif //_HW_H
