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
 
void Nop (void) {
} 

void Delay (void) {
	volatile unsigned int i;
	
	for (i = 0; i < 65000; i++) {}
	for (i = 0; i < 65000; i++) {}
	for (i = 0; i < 65000; i++) {}
	for (i = 0; i < 65000; i++) {}
}

void LcdSetDataBus (byte Data) {
   	USISRL = Data;
   	USICNT = 8;
   	while (!(USICTL1 & USIIFG)) {}; 
}

	

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    CSL_init();                     // Activate Grace-generated configuration
    __enable_interrupt();           // Set global interrupt enable

	LcdInit ();    
    // >>>>> Fill-in user code here <<<<<
	LcdPutc (0, 0, 'A');    
    while (1) {
//    	USISRL = 0xAA;
//    	USICNT = 8;
//    	while (!(USICTL1 & USIIFG)) {}; 
//    	Delay ();
    }
    return (0);
}
