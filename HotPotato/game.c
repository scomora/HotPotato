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
 
static Game_t game = {0};
#define CLEAR_SCREEN	(0x00)
 
void Game_InitGame(void)
{
	Rand_Init();
	game.gameState = ROUND_LOSS;
	game.scoreInfo.all = 0;
}

// never returns
void Game_RunGame(void)
{
	GameState_e roundResult;
	while (!Game_DoesUserWantToQuit())
	{
		roundResult = Game_PlayRound();
		switch(roundResult)
		{
			case ROUND_LOSS:
			{
				break;
			}
			case ROUND_WIN:
			{
				Game_IncrementCurrentScore();
				Game_DisplayCurrentScoreOnLeds();
				break;
			}
		}
	}
	// never return
	while(TRUE);
}

Bool_e Game_DoesUserWantToQuit(void)
{
	volatile uint8_t mostRecentInput = GPIO_GetMostRecentUserInput();
	if ((mostRecentInput & USER_QUIT_bm) == USER_QUIT_bm)
	{
		return TRUE;
	}
	return FALSE;
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
	
	while ((TCD0.INTFLAGS & TC0_OVFIF_bm) == 0)
	{
		currUserInput = GPIO_GetUserInputAtSwitches();
		changeInUserInput = currUserInput ^ initialUserInput;
		if (valueToSwitchOn == changeInUserInput)
		{
			userGuessedCorrectly = TRUE;
			break;
		}
	}
	TC_clear_ovfif();
	
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
	asm("nop");
}

GameState_e Game_GetGameState(void)
{
	return game.gameState;
}

uint8_t	Game_GetCurrentScore(void)
{
	return game.scoreInfo.currScore;
}

uint8_t	Game_GetHighScore(void)
{
	return game.scoreInfo.highScore;	
}

void Game_SetCurrentScore(uint8_t newCurrentScore)
{
	game.scoreInfo.currScore = newCurrentScore;
}

void Game_SetHighScore(uint8_t newHighScore)
{
	game.scoreInfo.highScore = newHighScore;
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
