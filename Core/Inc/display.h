#ifndef __DISPLAY_H__
#define __DISPLAY_H__

void MG_Display_Init(void);
void MG_Backround_Start(void);
void MG_Backround_Play(void);
void MG_SelectField(uint32_t x, uint32_t y, uint32_t color);
extern int BACKGROUND_LAYER;
extern int FIRST_LAYER;

#endif