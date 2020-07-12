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
	volatile uint8_t initialUserInput;
	volatile uint8_t currUserInput;
	volatile uint8_t changeInUserInput;
	Bool_e userGuessedCorrectly;
	uint8_t valueToSwitchOn;
	
	initialUserInput = PORTA.IN;
	userGuessedCorrectly = FALSE;
	valueToSwitchOn = Rand_GetRandomPowerOfTwoU8();
	
	GPIO_WriteValueToLeds(valueToSwitchOn);
	TC_Start();
	
	while ((TCC0.INTFLAGS & TC0_OVFIF_bm) != TC0_OVFIF_bm)
	{
		currUserInput = GPIO_GetUserInputAtSwitches();
		changeInUserInput = currUserInput ^ initialUserInput;
		if (valueToSwitchOn == changeInUserInput)
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
	return game.gameState;
}