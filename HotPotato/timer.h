/*
 * timer.h
 *
 * Created: 7/11/2020 3:12:54 PM
 *  Author: Spencer Comora, Matthew Gerstel
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

#define FRAME_EXPIRATION_TIME	(0xF)	// defined in ms
#define TCC0_PRESCALER_gc		(TC_CLKSEL_DIV1024_gc)
#define TCC0_PRESCALER			(1024)
#define TCC0_PERIOD				(0xFF)

void TC_Init(void);
void TC_Start(void);
void Delay_1s(void);
void TC_poll_overflow(void);
void TC_clear_ovfif(void);

#endif /* TIMER_H_ */