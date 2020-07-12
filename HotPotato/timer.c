/*
 * timer.c
 *
 * Created: 7/11/2020 3:13:25 PM
 *  Author: Spencer Comora
 */ 

#include <avr/io.h>
#include "timer.h"

void TC_Init(void)
{
	TCC0.PER = TCC0_PERIOD;
}

void TC_Start(void)
{
	TCC0.CNT = 0;
	TCC0.CTRLA = TCC0_PRESCALER_gc;
}

void TC_poll_overflow(void)
{
	while ((TCC0.INTFLAGS & TC0_OVFIF_bm) == 0);
}

inline void TC_clear_ovfif(void)
{
	TCC0.INTFLAGS |= TC0_OVFIF_bm;
}

void Delay_1s(void)
{
	// set count to 0
	TC_Start();
	// wait for overflow flag to be set
	TC_poll_overflow();
	// clear overflow flag
	// by writing a 1 to it
	TC_clear_ovfif();
}