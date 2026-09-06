#include "main.h"
#include "display.h"
#include "stm32h750b_discovery_lcd.h"
#include "stm32h750b_discovery_ts.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_ltdc.h"
#include "stm32h750b_discovery_sdram.h"
#include "stm32_lcd.h"
#include <stdint.h>
#include "game.h"
#include <stdio.h>
#include <stdio.h>

#define TEXT_PLAYER1_X 40
#define TEXT_PLAYER1_Y 30
#define TEXT_PALYER1_SIZE &Font16
#define TEXT_PALYER1_COLOR LCD_COLOR_ARGB8888_LIGHTGRAY
#define PLAYER1_SCORE_X ((*TEXT_PALYER1_SIZE).Width * 13)


#define TEXT_PLAYER2_X 40
#define TEXT_PLAYER2_Y 80
#define TEXT_PALYER2_SIZE &Font16
#define TEXT_PALYER2_COLOR LCD_COLOR_ARGB8888_LIGHTGRAY
#define PLAYER2_SCORE_X ((*TEXT_PALYER2_SIZE).Width * 13)


#define TRANSPARENT 0x00000000UL
#define CIRCLE_AND_X_MARGIN 20
#define PLAYBOARD_COLOR LCD_COLOR_ARGB8888_LIGHTRED

#define SYMBOL_X 420
#define SYMBOL_Y 20
#define SYMBOL_DIFF 30

#define HOMESCREEN_BACKGROUND_COLOR LCD_COLOR_ARGB8888_BLACK
#define SELECT_SQUARE_COLOR LCD_COLOR_ARGB8888_WHITE
#define SELECT_BUTTON_PLAY_COLOR LCD_COLOR_ARGB8888_LIGHTRED
#define SELECT_BUTTON_RESTART_COLOR LCD_COLOR_ARGB8888_LIGHTRED
#define DRAW_COLOR LCD_COLOR_ARGB8888_LIGHTRED



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

  UTIL_LCD_Clear(HOMESCREEN_BACKGROUND_COLOR);


  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
  }
  UTIL_LCD_Clear(TRANSPARENT);

  UTIL_LCD_SetTextColor(BUTTON_PLAY_COLOR);
  UTIL_LCD_SetFont(BUTTON_PLAY_SIZE);
  UTIL_LCD_DisplayStringAt(BUTTON_PLAY_X, BUTTON_PLAY_Y, (uint8_t*) "PLAY", BUTTON_PLAY_MODE);//margin 10

  UTIL_LCD_SetTextColor(BUTTON_RESTART_COLOR);
  UTIL_LCD_SetFont(BUTTON_RESTART_SIZE);
  UTIL_LCD_DisplayStringAt(BUTTON_RESTART_X, BUTTON_RESTART_Y, (uint8_t*) "RESTART", BUTTON_RESTART_MODE); //Xpos = (460/4)*2


  UTIL_LCD_SetTextColor(TEXT_PALYER1_COLOR);
  UTIL_LCD_SetFont(TEXT_PALYER1_SIZE);
  UTIL_LCD_DisplayStringAt(TEXT_PLAYER1_X, TEXT_PLAYER1_Y, (uint8_t*) "PLAYER", LEFT_MODE);

  UTIL_LCD_SetTextColor(PLAYER0_COLOR);
  UTIL_LCD_DisplayStringAt(TEXT_PLAYER1_X + (*TEXT_PALYER1_SIZE).Width * 6, TEXT_PLAYER1_Y, (uint8_t*) " X", LEFT_MODE);

  UTIL_LCD_SetTextColor(TEXT_PALYER1_COLOR);
  UTIL_LCD_DisplayStringAt(TEXT_PLAYER1_X + (*TEXT_PALYER1_SIZE).Width * 8, TEXT_PLAYER1_Y, (uint8_t*) ":", LEFT_MODE);

  UTIL_LCD_SetTextColor(TEXT_PALYER2_COLOR);
  UTIL_LCD_SetFont(TEXT_PALYER2_SIZE);

  UTIL_LCD_DisplayStringAt(TEXT_PLAYER2_X,TEXT_PLAYER2_Y, (uint8_t*) "PLAYER", LEFT_MODE);

  UTIL_LCD_SetTextColor(PLAYER1_COLOR);
  UTIL_LCD_DisplayStringAt(TEXT_PLAYER2_X + (*TEXT_PALYER2_SIZE).Width * 6, TEXT_PLAYER2_Y, (uint8_t*) " O", LEFT_MODE);

  UTIL_LCD_SetTextColor(TEXT_PALYER2_COLOR);
  UTIL_LCD_DisplayStringAt(TEXT_PLAYER2_X + (*TEXT_PALYER2_SIZE).Width * 8, TEXT_PLAYER2_Y, (uint8_t*) ":", LEFT_MODE);



  char buff0[20];
  char buff1[20];
  snprintf(buff0, sizeof(buff0), "%d", score[0]);
  snprintf(buff1, sizeof(buff1), "%d", score[1]);
  UTIL_LCD_DisplayStringAt(PLAYER1_SCORE_X, TEXT_PLAYER1_Y,   (uint8_t*) &buff0, LEFT_MODE);
  UTIL_LCD_DisplayStringAt(PLAYER2_SCORE_X,TEXT_PLAYER2_Y,   (uint8_t*) &buff1, LEFT_MODE);


}



void MG_Backround_Playscreen() {


  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  UTIL_LCD_Clear(HOMESCREEN_BACKGROUND_COLOR);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X + SQUARE_SIZE, BOARD_TOP_LEFT_Y, LINE_THICKNESS, LINE_LENGTH, PLAYBOARD_COLOR);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE, BOARD_TOP_LEFT_Y, LINE_THICKNESS, LINE_LENGTH, PLAYBOARD_COLOR);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X, BOARD_TOP_LEFT_Y + SQUARE_SIZE, LINE_LENGTH, LINE_THICKNESS, PLAYBOARD_COLOR);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X, BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE, LINE_LENGTH, LINE_THICKNESS, PLAYBOARD_COLOR);

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }
  UTIL_LCD_Clear(TRANSPARENT);

  MG_DrawPlayerOnMoveSymbol();
}


void MG_DrawPlayerOnMoveSymbol(){

  UTIL_LCD_FillRect(SYMBOL_X, SYMBOL_Y,SYMBOL_DIFF + CIRCLE_AND_X_MARGIN , SYMBOL_DIFF + CIRCLE_AND_X_MARGIN, TRANSPARENT);

  if(playerOnMove == 0){
    UTIL_LCD_DrawLine(SYMBOL_X,SYMBOL_Y,SYMBOL_X + SYMBOL_DIFF,SYMBOL_Y + SYMBOL_DIFF, PLAYER0_COLOR);
    UTIL_LCD_DrawLine(SYMBOL_X, SYMBOL_Y + SYMBOL_DIFF, SYMBOL_X + SYMBOL_DIFF, SYMBOL_Y, PLAYER0_COLOR);
  }else{

    UTIL_LCD_DrawCircle((SYMBOL_X + SYMBOL_X + SYMBOL_DIFF) / 2, (SYMBOL_Y + SYMBOL_Y + SYMBOL_DIFF) / 2, SYMBOL_DIFF / 2, PLAYER1_COLOR);
  }
}

void MG_Playscreen_SelectField(uint32_t x, uint32_t y){

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  UTIL_LCD_DrawRect( x + 1, y + 1, SQUARE_SIZE - 1, SQUARE_SIZE - 1, SELECT_SQUARE_COLOR);
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


  UTIL_LCD_SetTextColor(SELECT_BUTTON_PLAY_COLOR);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_DisplayStringAt(BUTTON_PLAY_X, BUTTON_PLAY_Y, (uint8_t*)"PLAY", BUTTON_PLAY_MODE);

}

void MG_Homescreen_UnselectPlayButton(){

  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_ClearStringLine(BUTTON_PLAY_Y / Font24.Height + 1);
  UTIL_LCD_ClearStringLine(BUTTON_PLAY_Y / Font24.Height);


  UTIL_LCD_SetTextColor(BUTTON_PLAY_COLOR);
  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_DisplayStringAt(BUTTON_PLAY_X, BUTTON_PLAY_Y, (uint8_t*)"PLAY", BUTTON_PLAY_MODE);

}

void MG_Homescreen_SelectRestartButton(){
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font16.Height);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font16.Height + 1);

  UTIL_LCD_SetTextColor(SELECT_BUTTON_RESTART_COLOR);
  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_DisplayStringAt(BUTTON_RESTART_X, BUTTON_RESTART_Y, (uint8_t*)"RESTART", BUTTON_RESTART_MODE);

}

void MG_Homescreen_UnselectRestartButton(){

  UTIL_LCD_SetFont(&Font20);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font20.Height);
  UTIL_LCD_ClearStringLine(BUTTON_RESTART_Y / Font20.Height + 1);

  UTIL_LCD_SetTextColor(BUTTON_RESTART_COLOR);
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_DisplayStringAt(BUTTON_RESTART_X, BUTTON_RESTART_Y, (uint8_t*)"RESTART", BUTTON_RESTART_MODE);

}

void MG_Playscreen_DrawCircle(int32_t x, int32_t y, uint32_t color){

  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  UTIL_LCD_DrawCircle((board[y][x].XupperBound + board[y][x].XlowerBound) / 2, (board[y][x].YupperBound + board[y][x].YlowerBound) / 2,  (board[y][x].YupperBound - board[y][x].YlowerBound) / 2 - CIRCLE_AND_X_MARGIN, color);

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }
}

void MG_Playscreen_DrawX(int32_t x, int32_t y, uint32_t color){

  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }
  // \ line
  UTIL_LCD_DrawLine(board[y][x].XlowerBound + CIRCLE_AND_X_MARGIN, board[y][x].YlowerBound + CIRCLE_AND_X_MARGIN, board[y][x].XupperBound - CIRCLE_AND_X_MARGIN, board[y][x].YupperBound - CIRCLE_AND_X_MARGIN, color);
  // / line
  UTIL_LCD_DrawLine(board[y][x].XlowerBound + CIRCLE_AND_X_MARGIN, board[y][x].YupperBound - CIRCLE_AND_X_MARGIN, board[y][x].XupperBound - CIRCLE_AND_X_MARGIN, board[y][x].YlowerBound + CIRCLE_AND_X_MARGIN, color);

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }
}

void MG_End_of_game_screen(int32_t x1, int32_t y1, int32_t x2, int32_t y2){

  if(gameStatus != DRAW){

    UTIL_LCD_DrawLine(x1, y1, x2, y2, PLAYBOARD_COLOR);

    HAL_Delay(800);

    UTIL_LCD_DrawLine(x1, y1, x2, y2, TRANSPARENT);

    HAL_Delay(800);

    UTIL_LCD_DrawLine(x1, y1, x2, y2, PLAYBOARD_COLOR);

    HAL_Delay(300);
  }

  HAL_Delay(500);

  for(int i = 0; i <= 272; i++){

    if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
    }
    UTIL_LCD_DrawHLine(0, i, 480, HOMESCREEN_BACKGROUND_COLOR);

    if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
    }
    UTIL_LCD_DrawHLine(0, i, 480, TRANSPARENT);

    HAL_Delay(5);
  }

  if(gameStatus == DRAW){
    if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
    }

    UTIL_LCD_SetTextColor(DRAW_COLOR);
    UTIL_LCD_SetFont(&Font24);

    UTIL_LCD_DisplayStringAt(0, 136, (uint8_t*)"DRAW", CENTER_MODE);

    HAL_Delay(800);

    UTIL_LCD_Clear(TRANSPARENT);

    HAL_Delay(800);

    UTIL_LCD_DisplayStringAt(0, 136, (uint8_t*)"DRAW", CENTER_MODE);

    HAL_Delay(800);
  }



  // char player1_win[] = "PLAYER1 WINS";
  // char player2_win[] = "PLAYER2 WINS";
  // char draw[] = "DRAW";

  // uint8_t* p;

  // if(gameStatus == PLAYER1_WIN) p = (uint8_t*)player1_win;
  // else if(gameStatus == PLAYER2_WIN) p = (uint8_t*)player2_win;
  // else p = (uint8_t*)draw;

  // UTIL_LCD_Clear(0x00000000UL);

  // UTIL_LCD_SetTextColor(BUTTON_RESTART_COLOR);
  // UTIL_LCD_SetFont(&Font24);
  // UTIL_LCD_DisplayStringAt(240, 136, p, LEFT_MODE);

  




}


