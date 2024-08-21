/******************************************************************************
 *
 * Module: Servo Motor Driver
 *
 * File Name: servo_motor.h
 *
 * Description: Header file for the Servo Motor Driver
 *
 * Author: Mohamed Hisham
 *
 *
 *******************************************************************************/

#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

#include "..\std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ROTATE_TO_0_POSTION		 124
#define ROTATE_TO_90_POSTION	 187
#define ROTATE_TO_180_POSTION	 250

/*******************************************************************************
 *                              Functions Prototypes                           *
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
void ServoMotor_init(void);

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
void ServoMotor_rotate(uint16 degree);


#endif /* SERVO_MOTOR_H_ */
