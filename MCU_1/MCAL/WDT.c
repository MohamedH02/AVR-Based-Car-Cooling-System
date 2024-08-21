/******************************************************************************
 *
 * Module: Watchdog Timer (WDT)
 *
 * File Name: WDT.c
 *
 * Description: Source file for the Watchdog Timer (WDT) driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#include "WDT.h"
#include <avr/io.h>
#include <avr/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/******************************************************************************
 * Service Name: WDT_ON
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): timeOut - The desired timeout period for the WDT
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Enables the Watchdog Timer (WDT) by setting the WDE bit and
 *              configuring the timeout period based on the timeOut parameter.
 *******************************************************************************/
void WDT_ON(uint8 timeOut)
{
	/* Enable WDT with the specified timeout period */
	WDTCR |= (1 << WDE);


    /* Set the timeout period */
	WDTCR = (WDTCR & 0xF8) | (timeOut & 0x07);
}

/******************************************************************************
 * Service Name: WDT_OFF
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Disables the Watchdog Timer (WDT) by following the correct
 *              sequence to prevent accidental disabling.
 *******************************************************************************/
void WDT_OFF(void)
{
	/* Write logical one to WDTOE and WDE to start the timed sequence */
	/* Within four clock cycles, clear the WDE bit to disable the WDT */
	WDTCR = (1 << WDTOE) | (1 << WDE);
	WDTCR = 0x00;
}
