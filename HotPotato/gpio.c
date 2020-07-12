/*
 * gpio.c
 *
 * Created: 7/11/2020 5:52:02 PM
 *  Author: Spencer Comora
 */ 

#include "gpio.h"
#include <avr/interrupt.h>

static uint8_t mostRecentUserInput = 0;

void GPIO_Init(void)
{
	// initialize the inline SPST as input
	// PA0-7 as input
	PORTA.DIRCLR = ALL_BITS_8;
	
	// initialize LEDs as output
	// PC0-7 as output
	PORTC.DIRSET = ALL_BITS_8;
	
	// initialize buttons as input
	PORTF.DIRCLR = SLB_S1_bm | SLB_S2_bm;
	
	GPIO_InitInterrupts();
}

void GPIO_InitInterrupts(void)
{
	// enable lo-level interrupts in in interrupt controller
	PMIC.CTRL = PMIC_LOLVLEN_bm;
	
	// enable lo-level, rising interrupts on S1 (PF2)
	PORTF.PIN2CTRL = PORT_ISC_RISING_gc;
	PORTF.INTCTRL = PORT_INT0LVL_LO_gc;
	
	PORTF.INT0MASK = SLB_S1_bm;
	sei();
}

UserInput_e GPIO_GetMostRecentUserInput(void)
{
	return mostRecentUserInput;
}

void GPIO_WriteValueToLeds(uint8_t value)
{
	// LEDs are active-low. Complement the logical value to
	// eliminate mismatch between uC port and LED configuration
	PORTC.OUT = ~value;
}

uint8_t	GPIO_GetUserInputAtSwitches(void)
{
	return PORTA.IN;
}

uint8_t GPIO_GetUserInputAtButtons(void)
{
	return PORTF.IN;
}

ISR(PORTF_INT0_vect)
{
	mostRecentUserInput = GPIO_GetUserInputAtButtons();
}