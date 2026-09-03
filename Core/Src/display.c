#include "main.h"
#include "display.h"
#include "stm32h750b_discovery_lcd.h"
#include "stm32h750b_discovery_ts.h"
#include "stm32h7xx_hal_ltdc.h"
#include "stm32h750b_discovery_sdram.h"
#include "stm32_lcd.h"
#include <stdint.h>
#include "game.h"
#include <stdio.h>
#include <stdio.h>


#define TRANSPARENT 0x00000000UL
#define CIRCLE_AND_X_MARGIN 20

//celoten display: 480 x 272
int BACKGROUND_LAYER = 0;
int FIRST_LAYER = 1;


void MG_Display_Init() {
  
  if (BSP_SDRAM_Init(0) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  if (BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  BSP_LCD_LayerConfig_t layer_1;
  layer_1.X0 = 0;
  layer_1.X1 = LCD_DEFAULT_WIDTH;
  layer_1.Y0 = 0;
  layer_1.Y1 = LCD_DEFAULT_HEIGHT;
  layer_1.PixelFormat = LCD_PIXEL_FORMAT_ARGB8888;
  layer_1.Address = LCD_LAYER_1_ADDRESS;

  if (BSP_LCD_ConfigLayer(0, FIRST_LAYER, &layer_1)  != BSP_ERROR_NONE ) {
    Error_Handler();
  }

  //nastavimo background in first layers
  if (BSP_LCD_SetLayerVisible(0, BACKGROUND_LAYER, ENABLE) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  if (BSP_LCD_SetLayerVisible(0, FIRST_LAYER, ENABLE) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  //255 = solid
  if (BSP_LCD_SetTransparency(0, BACKGROUND_LAYER, 255) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  if (BSP_LCD_SetTransparency(0, FIRST_LAYER, 255) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }


  UTIL_LCD_SetFuncDriver(&LCD_Driver);

  TS_Init_t touchscreen = {0};
  touchscreen.Width = LCD_DEFAULT_WIDTH;
  touchscreen.Height = LCD_DEFAULT_HEIGHT;
  touchscreen.Orientation = TS_SWAP_XY;
  touchscreen.Accuracy = 1; 

  if (BSP_TS_Init(0, &touchscreen) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  if (BSP_TS_EnableIT(0) != BSP_ERROR_NONE) {
    Error_Handler();
  }


  if (BSP_LCD_DisplayOn(0) != BSP_ERROR_NONE) {
    Error_Handler();
  }
}

void MG_Backround_Homescreen() {

  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
  }

  UTIL_LCD_Clear(LCD_COLOR_ARGB8888_BLACK);


  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
  }

  UTIL_LCD_Clear(0x00000000UL);
  UTIL_LCD_SetTextColor(BUTTON_PLAY_COLOR);
  UTIL_LCD_SetFont(BUTTON_PLAY_SIZE);
  UTIL_LCD_DisplayStringAt(BUTTON_PLAY_X, BUTTON_PLAY_Y, (uint8_t*) "PLAY", LEFT_MODE);//margin 10

  UTIL_LCD_SetTextColor(BUTTON_RESTART_COLOR);
  UTIL_LCD_SetFont(BUTTON_RESTART_SIZE);
  UTIL_LCD_DisplayStringAt(BUTTON_RESTART_X, BUTTON_RESTART_Y, (uint8_t*) "RESTART", LEFT_MODE); //Xpos = (460/4)*2
  UTIL_LCD_DisplayStringAt(40, 30, (uint8_t*) "PLAYER 1:", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(270,30, (uint8_t*) "PLAYER 2:", LEFT_MODE);

  unsigned char buff[20];
  snprintf(buff, sizeof(buff), "%d", score[0]);
  UTIL_LCD_DisplayStringAt(410,30,   (uint8_t*) &buff, LEFT_MODE);

}



void MG_Backround_Playscreen() {

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }
  UTIL_LCD_Clear(0x00000000UL);


  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  UTIL_LCD_Clear(LCD_COLOR_ARGB8888_BLACK);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X + SQUARE_SIZE, BOARD_TOP_LEFT_Y, LINE_THICKNESS, LINE_LENGTH, LCD_COLOR_ARGB8888_RED);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE, BOARD_TOP_LEFT_Y, LINE_THICKNESS, LINE_LENGTH, LCD_COLOR_ARGB8888_RED);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X, BOARD_TOP_LEFT_Y + SQUARE_SIZE, LINE_LENGTH, LINE_THICKNESS, LCD_COLOR_ARGB8888_RED);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X, BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE, LINE_LENGTH, LINE_THICKNESS, LCD_COLOR_ARGB8888_RED);


}

void MG_Playscreen_SelectField(uint32_t x, uint32_t y){

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  UTIL_LCD_DrawRect( x + 1, y + 1, SQUARE_SIZE - 1, SQUARE_SIZE - 1, LCD_COLOR_ARGB8888_WHITE);
}

void MG_Playscreen_UnselectField(uint32_t x, uint32_t y){
  
  UTIL_LCD_DrawRect( x + 1, y + 1, SQUARE_SIZE - 1, SQUARE_SIZE - 1, TRANSPARENT);


}

void MG_Homescreen_SelectPlayButton(){

  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_ClearStringLine( BUTTON_PLAY_Y / Font20.Height);
  UTIL_LCD_ClearStringLine( BUTTON_PLAY_Y / Font20.Height + 1);

  // UTIL_LCD_SetFont(&Font16);
  // UTIL_LCD_SetTextColor(BUTTON_RESTART_COLOR);
  // UTIL_LCD_DisplayStringAt(BUTTON_RESTART_X, BUTTON_RESTART_Y, (uint8_t*)"RESTART", LEFT_MODE);


  UTIL_LCD_SetTextColor(LCD_COLOR_ARGB8888_ORANGE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_DisplayStringAt(BUTTON_PLAY_X, BUTTON_PLAY_Y, (uint8_t*)"PLAY", LEFT_MODE);

}

void MG_Homescreen_UnselectPlayButton(){

  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_ClearStringLine(BUTTON_PLAY_Y / Font24.Height + 1);
  UTIL_LCD_ClearStringLine(BUTTON_PLAY_Y / Font24.Height);


  UTIL_LCD_SetTextColor(BUTTON_PLAY_COLOR);
  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_DisplayStringAt(BUTTON_PLAY_X, BUTTON_PLAY_Y, (uint8_t*)"PLAY", LEFT_MODE);

}

void MG_Homescreen_SelectRestartButton(){
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font16.Height);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font16.Height + 1);

  UTIL_LCD_SetTextColor(LCD_COLOR_ARGB8888_ORANGE);
  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_DisplayStringAt(BUTTON_RESTART_X, BUTTON_RESTART_Y, (uint8_t*)"RESTART", LEFT_MODE);

}

void MG_Homescreen_UnselectRestartButton(){

  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font20.Height);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font20.Height + 1);

  UTIL_LCD_SetTextColor(BUTTON_RESTART_COLOR);
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_DisplayStringAt(BUTTON_RESTART_X, BUTTON_RESTART_Y, (uint8_t*)"RESTART", LEFT_MODE);

}

void MG_Playscreen_DrawCircle(int32_t x, int32_t y, uint32_t color){

  UTIL_LCD_DrawCircle((board[y][x].XupperBound + board[y][x].XlowerBound) / 2, (board[y][x].YupperBound + board[y][x].YlowerBound) / 2,  (board[y][x].YupperBound - board[y][x].YlowerBound) / 2 - CIRCLE_AND_X_MARGIN, color);

}

void MG_Playscreen_DrawX(int32_t x, int32_t y, uint32_t color){
  // \ line
  UTIL_LCD_DrawLine(board[y][x].XlowerBound + CIRCLE_AND_X_MARGIN, board[y][x].YlowerBound + CIRCLE_AND_X_MARGIN, board[y][x].XupperBound - CIRCLE_AND_X_MARGIN, board[y][x].YupperBound - CIRCLE_AND_X_MARGIN, color);
  // / line
  UTIL_LCD_DrawLine(board[y][x].XlowerBound + CIRCLE_AND_X_MARGIN, board[y][x].YupperBound - CIRCLE_AND_X_MARGIN, board[y][x].XupperBound - CIRCLE_AND_X_MARGIN, board[y][x].YlowerBound + CIRCLE_AND_X_MARGIN, color);

}


