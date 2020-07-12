/*
 * game.c
 *
 * Created: 7/11/2020 5:07:01 PM
 *  Author: Spencer Comora, Matthew Gerstel
 */ 

#include "game.h"
#include "rand.h"
#include "timer.h"
#include "gpio.h"
 
#define CLEAR_SCREEN	(0x00)
 
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
			GPIO_WriteValueToLeds(CLEAR_SCREEN);
			break;
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

void Game_DisplayCurrentScoreOnLeds(void)
{

}

GameState_e Game_GetGameState(void)
{
	return ROUND_LOSS;
}

void Game_HandleLoss(void)
{
	// TODO: Play loss animation
	if (game.scoreInfo.currScore > game.scoreInfo.highScore)
	{
		game.scoreInfo.highScore = game.scoreInfo.currScore;
		game.scoreInfo.currScore = 0;
		//TODO: Blink High Score
	}
	else
	{
		//TODO: Display Score
		game.scoreInfo.currScore = 0;
	}
	//TODO: GOTO Main Menu
}
