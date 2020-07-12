/*
 * rand.c
 *
 * Created: 7/11/2020 6:21:09 PM
 *  Author: Spencer Comora, Matthew Gerstel
 */ 

#include "rand.h"
#include "timer.h"

void Rand_Init(void)
{
	TCC0.PER = 0xFF;
	TCC0.CTRLA = TC_CLKSEL_DIV4_gc;
}

uint8_t	Rand_GetRandomU8(void)
{
	return (uint8_t) TCC0.CNT;
}

uint8_t Rand_GetRandomPowerOfTwoU8(void)
{
	return Rand_RoundUpToNearestPowerOfTwoU8(Rand_GetRandomU8());
}

uint8_t Rand_RoundUpToNearestPowerOfTwoU8(uint8_t valuetoRound)
{
	valuetoRound--;
	valuetoRound |= valuetoRound >> 1;
	valuetoRound |= valuetoRound >> 2;
	valuetoRound |= valuetoRound >> 4;
	valuetoRound |= valuetoRound >> 8;
	valuetoRound++;
	return valuetoRound;
}