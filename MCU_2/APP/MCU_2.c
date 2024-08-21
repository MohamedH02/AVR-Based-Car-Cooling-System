/******************************************************************************
 *
 * Module: MCU2_Main
 *
 * File Name: MCU2.c
 *
 * Description: Source file for the Application
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/delay.h>
#include "..\common_macros.h"
#include "..\MCAL\gpio.h"
#include "..\MCAL\uart.h"
#include "..\HAL\dc_motor.h"
#include "..\MCAL\adc.h"
#include "..\HAL\led.h"
#include "..\HAL\buzzer.h"
#include "..\HAL\servo_motor.h"
#include "..\MCAL\timer1.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Define the various system states */
#define NORMAL_STATE 0
#define EMERGENCY_STATE 1
#define ABNORMAL_STATE 2
#define SHUTDOWN_STATE 3

/* Define codes for specific actions */
#define SHUTDOWN_CODE 0xFF
#define ABNORMAL_CODE 0xFE

/*******************************************************************************
 *                                    Main                                     *
 *******************************************************************************/

int main(void) {
	/* Enable global interrupts */
	SREG |= (1<<7);

	/* Initialize various hardware modules */
	Buzzer_init();
	DcMotor_Init();
	ServoMotor_init();
	LED_init();
	ADC_init();

	/* Configure UART settings */
	UART_ConfigType uart_config;
	uart_config.baud_rate = 9600;
	uart_config.bit_data = BITS_8;
	uart_config.parity = NO_PARITY;
	uart_config.stop_bit = STOP_BIT_1;
	UART_init(&uart_config);

	/* Declare variables for temperature,
	 * ADC output, motor speed, and system
	 * state
	 *  */
	uint8 temperature;
	uint32 mvop;
	uint8 motorSpeed;
	uint8 state = NORMAL_STATE;

	while(1) {
		/* Receive the temperature value via UART */
		temperature = UART_recieveByte();

		/* Handle different states based on the received temperature value */
		switch (temperature) {
		case SHUTDOWN_CODE:
			/* Transition to SHUTDOWN state */
			state = SHUTDOWN_STATE;
			break;

		case ABNORMAL_CODE:
			/* Handle abnormal state with specific actions */
			ServoMotor_rotate(ROTATE_TO_90_POSTION);
			LED_turnAllOff();
			LED_turnLedOn(RED);
			Buzzer_on();
			DcMotor_Rotate(STOP, 0);
			_delay_ms(5000);
			Buzzer_off();
			ServoMotor_rotate(ROTATE_TO_0_POSTION);
			state = NORMAL_STATE;
			break;

		default:
			/* Normal State: set LEDs and buzzer based on temperature thresholds */
			if (temperature < 20) {
				LED_turnLedOff(RED);
				LED_turnLedOff(YELLOW);
				LED_turnLedOn(GREEN);
				Buzzer_off();
			}
			else if (temperature >= 20 && temperature < 40) {
				LED_turnLedOff(RED);
				LED_turnLedOff(GREEN);
				LED_turnLedOn(YELLOW);
				Buzzer_off();
			}
			else if (temperature >= 40 && temperature <= 50) {
				LED_turnLedOff(YELLOW);
				LED_turnLedOff(GREEN);
				LED_turnLedOn(RED);
				Buzzer_off();
			}
			else if (temperature > 50) {
				LED_turnLedOff(YELLOW);
				LED_turnLedOff(GREEN);
				LED_turnLedOn(RED);
				Buzzer_on();
			}
			break;
		}

		/* Read the potentiometer value using ADC from channel and calculate motor speed */
		mvop = ADC_readChannel(PIN4_ID);
		motorSpeed = (mvop * 100) / 1023;

		/* Control motor based on the current state */
		if (state == SHUTDOWN_STATE) {
			DcMotor_Rotate(STOP, 0);
		}
		else if (state == NORMAL_STATE) {
			DcMotor_Rotate(CLOCKWISE, motorSpeed);
		}
	}
}
