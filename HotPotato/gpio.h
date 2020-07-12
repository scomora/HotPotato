/*
 * gpio.h
 *
 * Created: 7/11/2020 5:48:14 PM
 *  Author: Spencer Comora
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

/************************************************************************/
/*                             DEFINES									*/
/************************************************************************/

#define ALL_BITS_8		(0xFF)

/************************************************************************/
/*                             TYPEDEFS									*/
/************************************************************************/

typedef enum
{
	USER_QUIT	=	PIN0_bm
} UserInput_e;

/************************************************************************/
/*                             PUBLIC APIS								*/
/************************************************************************/

void		GPIO_Init(void);
UserInput_e GPIO_GetMostRecentUserInput(void);
void		GPIO_WriteValueToLeds(uint8_t value);
uint8_t		GPIO_GetUserInputAtSwitches(void);


#endif /* GPIO_H_ */