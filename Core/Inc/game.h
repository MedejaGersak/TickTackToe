#ifndef __GAME_H__
#define __GAME_H__

#include "stm32h750b_discovery_ts.h"
#include "ts_bounds.h"

#define INBOUNDS(val, min, max) ((val) < (min) ? 0 : ((val) > (max) ? 0 : 1))

enum Homescreen{
  PLAY,
  RESTART
};

enum Playscreen{
  ONGOING,
  DRAW,
  PLAYER1_WIN,
  PLAYER2_WIN
};

extern int score[];
extern TS_State_t touch;
extern int playerOnMove;
extern square_bounds board[3][3];
extern enum Playscreen gameStatus;

enum Homescreen MG_Homescreen(void);
void MG_Playscreen(void);
void MG_Board_Init(void);
#endif