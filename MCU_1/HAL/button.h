/******************************************************************************
 *
 * Module: Button
 *
 * File Name: button.h
 *
 * Description: Header file for the Button driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

#include "..\std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define INT0_PORT_NUM	PORTD_ID
#define INT1_PORT_NUM	PORTD_ID
#define INT2_PORT_NUM	PORTB_ID

#define INT0_PIN_NUM	PIN2_ID
#define INT1_PIN_NUM	PIN3_ID
#define INT2_PIN_NUM	PIN2_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef struct {
	uint8 pinNum;
	uint8 portNum;
} Button_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
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
 * Description: Initializes the specified button's pin as an input pin,
 *              based on the provided configuration structure.
 *******************************************************************************/
void BUTTON_init(const Button_ConfigType* Config_Ptr);

/******************************************************************************
 * Service Name: BUTTON_getStates
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): PortNum - The port number where the button is connected
 *                  PinNum - The pin number where the button is connected
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: uint8 - The state of the button (0 if not pressed, 1 if pressed)
 * Description: Reads and returns the current state of the button
 *              (pressed or not pressed) by reading the logic level on the specified pin.
 *******************************************************************************/
uint8 BUTTON_getStates(uint8 PortNum, uint8 PinNum);



#endif /* BUTTON_H_ */
