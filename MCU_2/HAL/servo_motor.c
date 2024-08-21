/******************************************************************************
 *
 * Module: Servo Motor Driver
 *
 * File Name: servo_motor.c
 *
 * Description: Source file for the Servo Motor Driver
 *
 * Author: Mohamed Hisham
 *
 *
 *******************************************************************************/


#include "servo_motor.h"
#include "..\MCAL\timer1.h"
#include "..\MCAL\gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/******************************************************************************
 * Service Name: ServoMotor_init
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the servo motor by setting up the control pin direction.
 *******************************************************************************/
void ServoMotor_init(void) {
	GPIO_setupPinDirection(PORTD_ID,PIN5_ID, PIN_OUTPUT);
}

/******************************************************************************
 * Service Name: ServoMotor_rotate
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): degree - The angle to rotate the servo motor to (0 to 180 degrees)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Rotates the servo motor to a specific angle by generating the corresponding PWM signal.
 *******************************************************************************/
void ServoMotor_rotate(uint16 degree) {
	Timer1_Fast_PWM_Init(degree);
}
