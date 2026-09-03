#ifndef __GAME_H__
#define __GAME_H__

#include "stm32h750b_discovery_ts.h"

enum Homescreen{
  PLAY,
  RESTART
};

enum Playscreen{
  SQUARE_1_1,
  SQUARE_1_2,
  SQUARE_1_3,
  SQUARE_2_1,
  SQUARE_2_2,
  SQUARE_2_3,
  SQUARE_3_1,
  SQUARE_3_2,
  SQUARE_3_3
};
extern int score[];
extern TS_State_t touch;;
enum Homescreen MG_Homescreen(void);
#endif