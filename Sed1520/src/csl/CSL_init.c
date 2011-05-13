/*
 *  ======== CSL_init.c ========
 *  DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN
 */
 
/* external peripheral initialization functions */
extern void WDTplus_init(void);
extern void GPIO_init(void);
extern void BCSplus_init(void);
extern void USI_init(void);
extern void Timer_A2_init(void);
extern void System_init(void);

/*
 *  ======== CSL_init =========
 *  Initialize all configured CSL peripherals
 */
void CSL_init(void)
{
    /* initialize Config for the MSP430 WDT+ */
    WDTplus_init();

    /* initialize Config for the MSP430 GPIO */
    GPIO_init();

    /* initialize Config for the MSP430 2xx family clock systems (BCS) */
    BCSplus_init();

    /* initialize Config for the MSP430 USI */
    USI_init();

    /* initialize Config for the MSP430 A2 Timer */
    Timer_A2_init();

    /* initialize Config for the MSP430 System Registers */
    System_init();

}

/*
 *  ======== Interrupt Function Definitions ========
 */

#include <ti/mcu/msp430/include/msp430.h>

/* Interrupt Function Prototypes */



