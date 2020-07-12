/*
 * gpio.c
 *
 * Created: 7/11/2020 5:52:02 PM
 *  Author: Spencer Comora
 */ 

#include "gpio.h"

void GPIO_Init(void)
{
	// initialize the inline SPST as input
	// PA0-7 as input
	PORTA.DIRCLR = ALL_BITS_8;
	
	// initialize LEDs as output
	// PC0-7 as output
	PORTC.DIRSET = ALL_BITS_8;
}

UserInput_e GPIO_GetMostRecentUserInput(void)
{
	return USER_QUIT;
}

void GPIO_WriteValueToLeds(uint8_t value)
{
	
}

uint8_t	GPIO_GetUserInputAtSwitches(void)
{
	return 0;
}