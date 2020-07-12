/*
 * game.c
 *
 * Created: 7/11/2020 5:07:01 PM
 *  Author: Spencer Comora
 */ 

#include "game.h"
#include "rand.h"
#include "timer.h"
#include "gpio.h"
 
Game_t game;

void Game_InitGame(void)
{
	Rand_Init();
	game.gameState = ROUND_LOSS;
	game.scoreInfo.all = 0;
}

GameState_e	Game_PlayRound(void)
{
	uint8_t prevUserInput = PORTA.IN;
	Bool_e userGuessedCorrectly = FALSE;
	uint8_t valueToSwitchOn = Rand_GetRandomPowerOfTwoU8();
	GPIO_WriteValueToLeds(valueToSwitchOn);
	PORTC.OUT = ~valueToSwitchOn;
	TC_Start();
	while ((TCC0.INTFLAGS & TC0_OVFIF_bm) != TC0_OVFIF_bm)
	{
		if ((PORTA.IN ^ prevUserInput) == valueToSwitchOn)
		{
			userGuessedCorrectly = TRUE;
		}
	}
	if (userGuessedCorrectly == TRUE)
	{
		return ROUND_WIN;
	}
	return ROUND_LOSS;
}

void Game_IncrementCurrentScore(void)
{
	game.scoreInfo.currScore++;
}

void Game_FlashCurrentScoreOnLeds(void)
{
	
}

GameState_e Game_GetGameState(void)
{
	return ROUND_LOSS;
}