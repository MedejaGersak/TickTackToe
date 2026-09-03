#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define BUTTON_PLAY_X 60
#define BUTTON_PLAY_Y 230
#define BUTTON_PLAY_SIZE &Font20
#define BUTTON_PLAY_COLOR LCD_COLOR_ARGB8888_LIGHTGRAY


#define BUTTON_RESTART_X 300
#define BUTTON_RESTART_Y 230
#define BUTTON_RESTART_SIZE &Font16
#define BUTTON_RESTART_COLOR LCD_COLOR_ARGB8888_LIGHTGRAY

void MG_Display_Init(void);
void MG_Backround_Homescreen(void);
void MG_Backround_Playscreen(void);
void MG_Playscreen_SelectField(uint32_t x, uint32_t y);
void MG_Homescreen_SelectPlayButton(void);
void MG_Homescreen_SelectRestartButton(void);
void MG_Homescreen_UnselectPlayButton(void);
void MG_Homescreen_UnselectRestartButton(void);
extern int BACKGROUND_LAYER;
extern int FIRST_LAYER;

#endif