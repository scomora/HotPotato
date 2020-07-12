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

// PORTF - buttons 
// S1 - PF2
// S2 - PF3
#define SLB_S1_bp		PIN2_bp
#define SLB_S2_bp		PIN3_bp
#define SLB_S1_bm		1 << SLB_S1_bp
#define SLB_S2_bm		1 << SLB_S2_bp

#define ALL_BITS_8		(0xFF)
#define USER_QUIT_bm		SLB_S1_bm

/************************************************************************/
/*                             TYPEDEFS									*/
/************************************************************************/


/************************************************************************/
/*                             PUBLIC APIS								*/
/************************************************************************/

void		GPIO_Init(void);
void		GPIO_InitInterrupts(void);
uint8_t	    GPIO_GetMostRecentUserInput(void);
void		GPIO_WriteValueToLeds(uint8_t value);
uint8_t		GPIO_GetUserInputAtSwitches(void);
uint8_t		GPIO_GetUserInputAtButtons(void);


#endif /* GPIO_H_ */