/******************************************************************************
 *
 * Module: LED Driver
 *
 * File Name: led.c
 *
 * Description: Source file for the LED Driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#include "led.h"
#include "..\MCAL\gpio.h"
#include "..\std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
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
void LED_init(void) {
	GPIO_setupPinDirection(RED_LED_PORT, RED_LED_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(YELLOW_LED_PORT, YELLOW_LED_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, PIN_OUTPUT);
}

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
void LED_turnLedOn(colorType Color) {

	switch (Color) {
		case RED:
			GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_HIGH);
			break;
		case YELLOW:
			GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOGIC_HIGH);
			break;
		case GREEN:
			GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_HIGH);
			break;
		default:
			break;
	}

}

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
void LED_turnLedOff(colorType Color) {

	switch (Color) {
		case RED:
			GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_LOW);
			break;
		case YELLOW:
			GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOGIC_LOW);
			break;
		case GREEN:
			GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_LOW);
			break;
		default:
			break;
	}

}

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
void LED_turnAllOn(void) {

	GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_HIGH);
	GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOGIC_HIGH);
	GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_HIGH);

}

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
void LED_turnAllOff(void) {

	GPIO_writePin(RED_LED_PORT, RED_LED_PIN, LOGIC_LOW);
	GPIO_writePin(YELLOW_LED_PORT, YELLOW_LED_PIN, LOGIC_LOW);
	GPIO_writePin(GREEN_LED_PORT, GREEN_LED_PIN, LOGIC_LOW);
}




