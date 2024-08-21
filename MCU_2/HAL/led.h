/******************************************************************************
 *
 * Module: LED Driver
 *
 * File Name: led.h
 *
 * Description: Header file for the LED Driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "..\std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define RED_LED_PORT	 	PORTA_ID
#define YELLOW_LED_PORT		PORTA_ID
#define GREEN_LED_PORT		PORTA_ID

#define RED_LED_PIN			PIN7_ID
#define YELLOW_LED_PIN		PIN6_ID
#define GREEN_LED_PIN		PIN5_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum {
	RED,
	YELLOW,
	GREEN
} colorType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/******************************************************************************
 * Service Name: LED_init
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the LED pins by setting up their direction as output.
 *******************************************************************************/
void LED_init(void);

/******************************************************************************
 * Service Name: LED_turnLedOn
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Color - The color of the LED to turn on (RED, YELLOW, GREEN)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Turns on the specified LED by setting the corresponding pin to HIGH.
 *******************************************************************************/
void LED_turnLedOn(colorType Color);

/******************************************************************************
 * Service Name: LED_turnLedOff
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Color - The color of the LED to turn off (RED, YELLOW, GREEN)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Turns off the specified LED by setting the corresponding pin to LOW.
 *******************************************************************************/
void LED_turnLedOff(colorType Color);

/******************************************************************************
 * Service Name: LED_turnAllOn
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Turns on all LEDs by setting their corresponding pins to HIGH.
 *******************************************************************************/
void LED_turnAllOn(void);

/******************************************************************************
 * Service Name: LED_turnAllOff
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Turns off all LEDs by setting their corresponding pins to LOW.
 *******************************************************************************/
void LED_turnAllOff(void);

#endif /* LED_H_ */
