/******************************************************************************
 *
 * Module: MCU1_Main
 *
 * File Name: MCU1.c
 *
 * Description: Source file for the Application
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "..\common_macros.h"
#include "../MCAL/gpio.h"
#include "../HAL/lm35_sensor.h"
#include "../MCAL/uart.h"
#include "../MCAL/internal_EEPROM.h"
#include "../HAL/button.h"
#include "../HAL/dc_motor.h"
#include "../MCAL/adc.h"
#include "../MCAL/timer1.h"
#include <avr/delay.h>
#include "../MCAL/WDT.h"

/* Definitions for various system states */
#define NORMAL_STATE 0
#define EMERGENCY_STATE 1
#define ABNORMAL_STATE 2
#define SHUTDOWN_STATE 3

/* Special codes for communication */
#define SHUTDOWN_CODE 0xFF
#define ABNORMAL_CODE 0xFE

/* Global variables */
volatile uint8 temperature;          /* Current temperature value */
volatile uint8 emergencyTIME = 0;    /* Timer counter for emergency state */
volatile uint8 state = NORMAL_STATE; /* Current system state */
volatile uint8 buttonPressed = 0;    /* Flag for button press */

/******************************************************************************
 * Service Name: INT0_vect ISR
 * Sync/Async: Asynchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Interrupt Service Routine for INT0. Sends shutdown code via UART
 *              if the temperature is in the shutdown range.
 *******************************************************************************/
ISR(INT0_vect) {
	if (temperature >= 40 && temperature <= 50) {
		UART_sendByte(SHUTDOWN_CODE);
	}
}

/******************************************************************************
 * Service Name: emergencyTick
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Increments the emergency timer if the system is in emergency state.
 *******************************************************************************/
void emergencyTick(void) {
	if (state == EMERGENCY_STATE) {
		emergencyTIME++;
	}
	else
	{
		emergencyTIME = 0;
	}
}

/******************************************************************************
 * Service Name: mapToPercentage
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): value - The input value to map
 *                  min1 - Minimum input range
 *                  max1 - Maximum input range
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: int - Mapped value as a percentage (0-100)
 * Description: Maps a given value to a percentage based on the specified range.
 *******************************************************************************/
int mapToPercentage(int value, int min1, int max1) {

	if (value < min1) value = min1;
	if (value > max1) value = max1;

	int percentage = ((value - min1) * 100) / (max1 - min1);

	return percentage;
}

/******************************************************************************
 * Service Name: main
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: int - Returns 0 upon completion (unused in embedded systems)
 * Description: Main function for MCU1 application. Handles temperature monitoring,
 *              motor control, and state transitions based on system inputs.
 *******************************************************************************/
int main(void) {
	SREG |= (1<<7);  /* Enable global interrupts */
	DcMotor_Init();  /* Initialize the DC motor */
	ADC_init();      /* Initialize ADC */

	/* UART configuration and initialization */
	UART_ConfigType uart_config;
	uart_config.baud_rate = 9600;
	uart_config.bit_data = BITS_8;
	uart_config.parity = NO_PARITY;
	uart_config.stop_bit = STOP_BIT_1;
	UART_init(&uart_config);

	/* Button configuration and initialization */
	Button_ConfigType button_config;
	button_config.pinNum = INT0_PIN_NUM;
	button_config.portNum = INT0_PORT_NUM;
	BUTTON_init(&button_config);
	MCUCR |= (1<<ISC01); /* Set interrupt on falling edge */
	GICR |= (1<<INT0);   /* Enable INT0 interrupt */
	SET_BIT(PORTD, PIN2_ID); /* Enable pull-up resistor on INT0 pin */

	/* Timer1 configuration and initialization */
	Timer1_ConfigType timer_config;
	timer_config.initial_value = 0;
	timer_config.mode = COMPARE_MODE;
	timer_config.prescaler = PRESCALER_1024;
	timer_config.compare_value = 488;
	Timer1_init(&timer_config);
	Timer1_setCallBack(emergencyTick); /* Set callback function for Timer1 */

	INTERNAL_EEPROM_writeByte(0x00, NORMAL_STATE); /* Initialize state in EEPROM */

	while(1)
	{
		state = INTERNAL_EEPROM_readByte(0x00); /* Read the current state from EEPROM */

		temperature = LM35_getTemperature(); /* Read temperature from the sensor */
		UART_sendByte(temperature); /* Send temperature value via UART */

		/* State machine handling different system states */
		switch (state) {

		case NORMAL_STATE:
			if (temperature <= 20)
			{
				INTERNAL_EEPROM_writeByte(0x00, NORMAL_STATE);
				DcMotor_Rotate(STOP,0);
				state = NORMAL_STATE;
			}
			else if (temperature >= 20 && temperature < 40) {
				INTERNAL_EEPROM_writeByte(0x00, NORMAL_STATE);
				DcMotor_Rotate(CLOCKWISE, mapToPercentage(temperature, 20, 40));
				state = NORMAL_STATE;
			}
			else if (temperature >= 40 && temperature <= 50) {
				INTERNAL_EEPROM_writeByte(0x00, NORMAL_STATE);
				DcMotor_Rotate(CLOCKWISE, 100);
				state = NORMAL_STATE;
			}
			else if (temperature > 50) {
				state = EMERGENCY_STATE;
				INTERNAL_EEPROM_writeByte(0x00, EMERGENCY_STATE);
			}
			break;

		case EMERGENCY_STATE:
			if (emergencyTIME >= 14) {
				state = ABNORMAL_STATE;
				INTERNAL_EEPROM_writeByte(0x00, ABNORMAL_STATE);
				UART_sendByte(ABNORMAL_CODE);
				break;
			} else if (temperature < 50) {
				state = NORMAL_STATE;
				INTERNAL_EEPROM_writeByte(0x00, NORMAL_STATE);
			}
			DcMotor_Rotate(CLOCKWISE, 100);
			break;

		case ABNORMAL_STATE:
			emergencyTIME = 0;
			DcMotor_Rotate(CLOCKWISE, 100);
			WDT_ON(TIME_OUT_16MS); /* Enable Watchdog Timer */
			break;

		default:
			break;
		}

		/* Handling button press for shutdown */
		if (buttonPressed) {
			if (temperature >= 40 && temperature <= 50) {
				UART_sendByte(SHUTDOWN_CODE);
			}
			buttonPressed = 0; /* Reset button press flag */
		}
	}
}



