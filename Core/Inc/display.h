#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>

#define BUTTON_PLAY_X 89
#define BUTTON_PLAY_Y 166
#define BUTTON_PLAY_SIZE &Font20
#define BUTTON_PLAY_COLOR LCD_COLOR_ARGB8888_LIGHTGRAY


#define BUTTON_RESTART_X 65
#define BUTTON_RESTART_Y 210
#define BUTTON_RESTART_SIZE &Font16
#define BUTTON_RESTART_COLOR LCD_COLOR_ARGB8888_LIGHTGRAY

#define LINE_THICKNESS 3
#define BOARD_TOP_LEFT_X 135
#define BOARD_TOP_LEFT_Y 31
#define LINE_LENGTH 210
#define SQUARE_SIZE 70

void MG_Display_Init(void);
void MG_Backround_Homescreen(void);
void MG_Backround_Playscreen(void);
void MG_Playscreen_SelectField(uint32_t x, uint32_t y);
void MG_Playscreen_UnselectField(uint32_t x, uint32_t y);
void MG_Homescreen_SelectPlayButton(void);
void MG_Homescreen_SelectRestartButton(void);
void MG_Homescreen_UnselectPlayButton(void);
void MG_Homescreen_UnselectRestartButton(void);
void MG_Playscreen_DrawCircle(int32_t x, int32_t y, uint32_t color);
void MG_Playscreen_DrawX(int32_t x, int32_t y, uint32_t color);
extern int BACKGROUND_LAYER;
extern int FIRST_LAYER;

#endif