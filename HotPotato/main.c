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

int main(void)
{
	GPIO_Init();
	TC_Init();
	Game_InitGame();
	
	// game entrypoint. never returns
	Game_RunGame();
}

