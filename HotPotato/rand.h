/*
 * rand.h
 *
 * Created: 7/11/2020 6:08:19 PM
 *  Author: Spencer Comora
 */ 


#ifndef RAND_H_
#define RAND_H_

#include "types.h"

void	Rand_Init(void);
uint8_t	Rand_GetRandomU8(void);
uint8_t Rand_GetRandomPowerOfTwoU8(void);
uint8_t Rand_RoundUpToNearestPowerOfTwoU8(uint8_t valuetoRound);

#endif /* RAND_H_ */