/*
 * messyhouse.cpp
 *
 * Created: 7/5/2020 9:27:38 PM
 * Author : Spencer Comora
 */ 

#include <avr/io.h>
#include "types.h"
#include "game.h"
#include "timer.h"
#include "gpio.h"

#define DEFAULT_HIGH_SCORE		(10)

int main(void)
{
	GPIO_Init();
	TC_Init();
	Game_InitGame();
	
	GameState_e roundResult;
    while (TRUE)
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
				Game_FlashCurrentScoreOnLeds();
				break;
			}
		}
	}
	while (1);
}

