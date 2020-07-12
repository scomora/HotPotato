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
void		Game_RunGame(void);
Bool_e		Game_DoesUserWantToQuit(void);
GameState_e	Game_PlayRound(void);
void		Game_IncrementCurrentScore(void);
void		Game_DisplayCurrentScoreOnLeds(void);
GameState_e Game_GetGameState(void);
uint8_t		Game_GetCurrentScore(void);
uint8_t		Game_GetHighScore(void);
void		Game_SetCurrentScore(uint8_t newCurrentScore);
void		Game_SetHighScore(uint8_t newHighScore);
void		Game_HandleLoss(void);
#endif /* GAME_H_ */