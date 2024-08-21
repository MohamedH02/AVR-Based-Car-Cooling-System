/******************************************************************************
 *
 * Module: Watchdog Timer (WDT)
 *
 * File Name: WDT.h
 *
 * Description: Header file for the Watchdog Timer (WDT) driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/


#ifndef WDT_H_
#define WDT_H_

#include "..\std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TIME_OUT_16MS		0x00
#define TIME_OUT_32MS		0x01
#define TIME_OUT_65MS		0x02
#define TIME_OUT_130MS		0x03
#define TIME_OUT_260MS		0x04
#define TIME_OUT_520MS		0x05
#define TIME_OUT_1S			0x06
#define TIME_OUT_2S			0x07

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/******************************************************************************
 * Service Name: WDT_ON
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): timeOut - The desired timeout period for the WDT
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Enables the Watchdog Timer (WDT) with the specified timeout period.
 *******************************************************************************/
void WDT_ON(uint8 timeOut);

/******************************************************************************
 * Service Name: WDT_OFF
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Disables the Watchdog Timer (WDT).
 *******************************************************************************/
void WDT_OFF(void);

#endif /* WDT_H_ */
