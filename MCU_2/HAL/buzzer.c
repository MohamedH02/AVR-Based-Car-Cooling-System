 /********************************************************************************
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Description: source file for the Buzzer
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#include "buzzer.h"
#include "..\MCAL\gpio.h"  /* to use the gpio functions */


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 *  Description
	* Setup the direction for the buzzer pin as output pin through the GPIO driver.
 	*Turn off the buzzer through the GPIO.
* Inputs: None
* Return: None
 */
void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

/*
 * Description
 	 * Function to enable the Buzzer through the GPIO.
* Inputs: None
* Return: None
 */
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

/*
 * Description
 	 *Function to disable the Buzzer through the GPIO.
* Inputs: None
* Return: No
 */
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
