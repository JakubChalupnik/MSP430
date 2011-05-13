/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

#include "typedefs.h"
#include "sed1520.h"
 
//void Nop (void) {
//} 

void DelaySecond (unsigned int Seconds) {
	volatile unsigned int i;
	
	while (Seconds > 0) {
		for (i = 0; i < 65000; i++) {
		}
		for (i = 0; i < 65000; i++) {
		}
		Seconds--;
	}
}

void LcdSetDataBus (byte Data) {
   	USISRL = Data;
   	USICNT = 8;
   	while (!(USICTL1 & USIIFG)) {}; 
}


#define DcfHigh() (P1IN & BIT4)	
#define DcfLow() (!(P1IN & BIT4))	

#define TimerStop()   { TACTL = TASSEL_2 | ID_3 | MC_0;}
#define TimerStart()  { TAR = 0; TACTL = TASSEL_2 | ID_3 | MC_2;}
#define TimerRead()   ( TAR )

void LcdPutString (byte x, byte y, char *String) {
	
	while (*String != '\0') {
		LcdPutc (x, y, *String);
		String++;
		if (x < 120) {
			x += 6;
		} else {
			x = 0;
			y++;
		}
	}
}

byte ConvertHexToAscii (byte Hex) {
	
	if (Hex < 10) {
		return Hex + '0';
	} else {
		return Hex - 10 + 'A';
	}
}
	
void LcdPutHex (byte x, byte y, word Hex) {
	
	LcdPutc (x + 0,  y, ConvertHexToAscii ((Hex >> 12) & 0x000F)); 	
	LcdPutc (x + 6,  y, ConvertHexToAscii ((Hex >>  8) & 0x000F)); 	
	LcdPutc (x + 12, y, ConvertHexToAscii ((Hex >>  4) & 0x000F)); 	
	LcdPutc (x + 18, y, ConvertHexToAscii ((Hex >>  0) & 0x000F)); 	
}
	
	 
/*
 *  ======== main ========
 */
int main(int argc, char *argv[]) {
	word DcfHighLevelLength, DcfPeriod;
	int Poisoned, PoisonedCounter;
	int SecondCounter;
//	dword FirstSample, SecondSample;
	word CurrentBit;
	word Minute, Hour, Day;
	
    CSL_init();                     // Activate Grace-generated configuration
    __enable_interrupt();           // Set global interrupt enable

    // >>>>> Fill-in user code here <<<<<
	LcdInit ();    
//	LcdPutc (16, 0, 'A');
//	LcdData (0xAA);    
//	LcdPutc (100, 0, 'A');
//	LcdData (0xAA);    
   
//	LcdPutString (0, 0, "HELLO WORLD!");
	
	P1OUT &= ~BIT7;
	
	//
	// Delay some second, then pull the PON high and low again
	//
	
	DelaySecond (3);
	P1OUT ^= BIT7;
	DelaySecond (1);
	P1OUT ^= BIT7;

	//
	// Wait for the rising edge - wait for low lever first, then wait while the low level lasts
	//
	
	DcfHighLevelLength = DcfPeriod = 0;
	SecondCounter = 0;
	Poisoned = 1;
	PoisonedCounter = 0;
//	x = y = 0;
	 
	while (DcfHigh ());
	while (DcfLow ());
	while (DcfHigh ());
	while (DcfLow ());
	while (DcfHigh ());
	while (DcfLow ());

	while (1) {
		//
		// Start the timer to measure the length of the HIGH signal
		//
		 	
		TimerStart ();
		
		//
		// Find out what happened in previous cycle:
		// - either the times we measured are regular 1 sec pulse
		// - the previous cycle was 2sec one
		// - the times are wrong, mark the cycle as Poisoned
		//
		
		if ((DcfPeriod > 0x3800) &&
		    (DcfPeriod < 0x4000) 
		    ) {												// The whole period is around 1sec, that's the correct DCF77 pulse
			if ((DcfHighLevelLength > 0x300) && 
				(DcfHighLevelLength < 0x680) 
				) {											// Short pulse - logical 0
				CurrentBit = 0;
			} else if ((DcfHighLevelLength > 0x900) && 
				(DcfHighLevelLength < 0xD00) 
				) {											// Short pulse - logical 0
				CurrentBit = 1;
			} else {
				Poisoned = 1;
			}
			if (SecondCounter < 21) {	
				// Do nothing, meteo and other info bits
			} else if (SecondCounter < 28) {
				// Minutes
				Minute <<= 1;
				Minute |= CurrentBit;
			} else if (SecondCounter < 29) {
				// Do nothing, parity for 21-28
			} else if (SecondCounter < 35) {
				// Hours
				Hour <<= 1;
				Hour |= CurrentBit;
			} else if (SecondCounter < 36) {
				// Parity for 29 - 35
			} else if (SecondCounter < 42) {
				// Day in month
				Day <<= 1;
				Day |= CurrentBit;
			} else {
				// Do nothing
			}   						
			SecondCounter++;
		} else if ((DcfPeriod > 0x7000) && 
				   (DcfPeriod < 0x9000)
				   ) {
			if (!Poisoned) {
				// process the sample

				LcdPutHex (60, 2, Minute);
				LcdPutHex (90, 2, Hour);
				LcdPutHex (60, 3, Day);
//				LcdPutHex (84, 3, SecondSample & 0xFFFF);
			} else {
				PoisonedCounter++;
			}				   	
			Poisoned = 0;
			SecondCounter = 0;
			Minute = Hour = Day = 0;
		} else {
			Poisoned = 1;
		}
							    	

//		if ((DcfPeriod > 0x3800) &&
//		    (DcfPeriod < 0x4000) 
//		    ) {												// The whole period is around 1sec, that's the correct DCF77 pulse
//			if ((DcfHighLevelLength > 0x300) && 
//				(DcfHighLevelLength < 0x680) 
//				) {											// Short pulse - logical 0
//				LcdPutc (x, y, '0');
//			} else if ((DcfHighLevelLength > 0x900) && 
//				(DcfHighLevelLength < 0xD00) 
//				) {											// Short pulse - logical 0
//				LcdPutc (x, y, '1');
//			} else {
//				LcdPutc (x, y, 'P');
//			}
//			
//			if (x < 115) {
//				x += 6;
//			} else {
//				x = 0; y++;
//			}
//		} else if ((DcfPeriod > 0x7000) && 
//				   (DcfPeriod < 0x9000)
//				   ) {
//			LcdFill (0x00);
//			x = y = 0;
//		} else {
//			LcdPutc (x, y, 'P');
//			if (x < 115) {
//				x += 6;
//			} else {
//				x = 0; y++;
//			}
//		}
//							    	
		
		P1OUT |= BIT0;
		while (DcfHigh ());
		DcfHighLevelLength = TimerRead ();

		LcdPutHex (28, 0, DcfPeriod);
//		LcdPutHex (0, 2, (FirstSample >> 16) & 0xFFFF);
//		LcdPutHex (24, 2, FirstSample & 0xFFFF);
//		LcdPutHex (0, 3, (SecondSample >> 16) & 0xFFFF);
//		LcdPutHex (24, 3, SecondSample & 0xFFFF);

		LcdPutHex (12, 1, PoisonedCounter);
		
		if (Poisoned) {
			LcdPutc (0, 1, 'P');
		} else {
			LcdPutc (0, 1, ' ');
		}
	
		P1OUT &= ~BIT0;
		while (DcfLow ());
		DcfPeriod = TimerRead ();
	}
	
	//
	// The receiver should be reset, now just copy the DATA signal to LED
	//
	
	while (1) {
		if (P1IN & BIT4) {		// Data bit set
			P1OUT |= BIT0;
		} else {
			P1OUT &= ~BIT0;
		}
	} 
	   
//    while (1) {
////    	USISRL = 0xAA;
////    	USICNT = 8;
////    	while (!(USICTL1 & USIIFG)) {}; 
////    	Delay ();
//    }
//    return (0);
}
