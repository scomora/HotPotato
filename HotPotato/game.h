/*
 * game.h
 *
 * Created: 7/11/2020 4:55:19 PM
 *  Author: Spencer Comora
 */ 


#ifndef GAME_H_
#define GAME_H_

#include "types.h"

typedef enum
{
	ROUND_LOSS,
	ROUND_WIN
} GameState_e;

typedef union
{
	struct
	{
		uint8_t currScore;
		uint8_t highScore;
	};
	uint16_t all;
} ScoreInfo_t;

typedef struct  
{
	GameState_e gameState;
	ScoreInfo_t scoreInfo;
} Game_t;

void		Game_InitGame(void);
GameState_e	Game_PlayRound(void);
void		Game_IncrementCurrentScore(void);
void		Game_FlashCurrentScoreOnLeds(void);
GameState_e Game_GetGameState(void);

#endif /* GAME_H_ */