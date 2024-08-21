/******************************************************************************
 *
 * Module: Button
 *
 * File Name: button.c
 *
 * Description: Source file for the Button driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#include "button.h"
#include "../MCAL/gpio.h"
#include  "..\common_macros.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/******************************************************************************
 * Service Name: BUTTON_init
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Config_Ptr - Pointer to a configuration structure containing
 *                               the pin and port number to be initialized
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the specified button's pin as an input pin.
 *              The configuration is based on the provided Button_ConfigType structure,
 *              which includes the port number and pin number.
 *******************************************************************************/
void BUTTON_init(const Button_ConfigType* Config_Ptr) {
	/* Set up the pin as an input pin using the provided configuration */
	GPIO_setupPinDirection(Config_Ptr->portNum, Config_Ptr->pinNum, PIN_INPUT);

}

/******************************************************************************
 * Service Name: BUTTON_getStates
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): PortNum - The port number where the button is connected
 *                  PinNum - The pin number where the button is connected
 * Parameters (inout): None
 * Parameters (out): uint8 - The state of the button (0 if not pressed, 1 if pressed)
 * Return value: uint8 - The current state of the button
 * Description: Reads the current logic level of the button pin to determine
 *              if the button is pressed (logic high) or not pressed (logic low).
 *******************************************************************************/
uint8 BUTTON_getStates(uint8 PortNum, uint8 PinNum) {
	/* Read and return the state of the button (pressed or not pressed) */
	uint8 state = GPIO_readPin(PortNum, PinNum);
	return state;
}


