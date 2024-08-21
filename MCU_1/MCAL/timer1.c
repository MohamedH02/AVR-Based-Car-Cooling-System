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
#include <avr/interrupt.h> /* For ICU ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variable to hold the address of the callback function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Callback function in the application after overflow */
		(*g_callBackPtr)(); /* Another method to call the function using pointer to function: g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Callback function in the application after reaching the compare value */
		(*g_callBackPtr)(); /* Another method to call the function using pointer to function: g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/* Null pointer check */
	if (Config_Ptr == NULL_PTR)
	{
		return;
	}

	/* Configure Timer1 Control Registers */
	TCCR1A = (1<<FOC1A);
	TCCR1B = (Config_Ptr->mode << WGM12);
	TCCR1B |= (Config_Ptr->prescaler);

	/* Set Timer1 initial value */
	TCNT1 = Config_Ptr->initial_value;

	if (Config_Ptr->mode == COMPARE_MODE)
	{
		/* Set compare value */
		OCR1A = Config_Ptr->compare_value;

		/* Enable Compare Match Interrupt */
		TIMSK = (1<<OCIE1A);
	}
	else
	{
		/* Enable Overflow Interrupt */
		TIMSK = (1<<TOIE1);
	}

	/* Clear any pending interrupts */
	TIFR = (1<<OCF1A) | (1<<TOV1);
}

void Timer1_deInit(void)
{
	/* Disable Timer1 and clear all its registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;

	/* Disable Timer1 Interrupts */
	TIMSK = 0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Callback function in a global variable */
	g_callBackPtr = a_ptr;
}
