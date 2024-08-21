 /******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.c
 *
 * Description: Source file for Timer1
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#include "timer1.h"
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */\


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = ((void*)0);

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != ((void*)0))
	{
		/* Call the Call Back function in the application after overflow*/
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != ((void*)0))
	{
		/* Call the Call Back function in the application after reaching the compare value*/
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description
 	 * Function to initialize the Timer driver
* Inputs: pointer to the configuration structure with type Timer1_ConfigType.
* Return: None
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	TCCR1A = (1<<FOC1A);
	TCCR1B = (Config_Ptr->mode<<WGM12);
	TCCR1B |= (Config_Ptr->prescaler);
	TCNT1 = Config_Ptr->initial_value;

	if(Config_Ptr->mode)
	{
		OCR1A = Config_Ptr->compare_value;
		TIMSK = (1<<OCIE1A);
	}
	else
	{
		TIMSK = (1<<TOIE1);
	}
}

void Timer1_Fast_PWM_Init(unsigned short duty_cycle)
{
	TCNT1 = 0;		/* Set timer1 initial count to zero */
	ICR1 = 2499;	/* Set TOP count for timer1 in ICR1 register */

	OCR1A = duty_cycle; /* Set the compare value */

	/* Configure timer control register TCCR1A
     * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
     * 2. Disconnect OC1B  COM1B0=0 COM1B1=0
     * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
     * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
	 */
	TCCR1A = (1<<WGM11) | (1<<COM1A1);

	/* Configure timer control register TCCR1B
	 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
	 * 2. Prescaler = F_CPU/8
     */
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS11);
}

/*
 * Description
 	 * Function to disable the Timer1.
* Inputs: None
* Return: None
 */
void Timer1_deInit(void){
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	TIMSK = 0;
}

/*
 * Description
 	 *Function to set the Call Back function address.
* Inputs: pointer to Call Back function.
* Return: None
 */
void Timer1_setCallBack(void(*a_ptr)(void)){

	/* Save the address of the Call back function in a global variable */
		g_callBackPtr = a_ptr;
}
