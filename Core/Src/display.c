#include "main.h"
#include "display.h"
#include "stm32h750b_discovery_lcd.h"
#include "stm32h750b_discovery_ts.h"
#include "stm32h7xx_hal_ltdc.h"
#include "stm32h750b_discovery_sdram.h"
#include "stm32_lcd.h"
#include <stdint.h>

#define LINE_THICKNESS 3
#define BOARD_TOP_LEFT_X 135
#define BOARD_TOP_LEFT_Y 31
#define LINE_LENGTH 210
#define CUBE_SIZE 70


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
  touchscreen.Orientation = LCD_ORIENTATION_LANDSCAPE;
  touchscreen.Accuracy = 5; //TODO

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

void MG_Backround_Start() {

  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
  }

  UTIL_LCD_Clear(LCD_COLOR_ARGB8888_BLACK);


  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
      Error_Handler();
  }

  UTIL_LCD_Clear(0x00000000UL);
  UTIL_LCD_SetTextColor(LCD_COLOR_ARGB8888_LIGHTGRAY);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_DisplayStringAt(7, 200, (uint8_t*) "PLAY", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(40, 30, (uint8_t*) "PLAYER 1:", LEFT_MODE);
  UTIL_LCD_DisplayStringAt(270,30, (uint8_t*) "PLAYER 2:", LEFT_MODE);

  //score = Xpos + 160
  UTIL_LCD_DisplayStringAt(430,30, (uint8_t*) "5", LEFT_MODE);

}



void MG_Backround_Play() {

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }
  UTIL_LCD_Clear(0x00000000UL);


  if (BSP_LCD_SetActiveLayer(0, BACKGROUND_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  UTIL_LCD_Clear(LCD_COLOR_ARGB8888_BLACK);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X + CUBE_SIZE, BOARD_TOP_LEFT_Y, LINE_THICKNESS, LINE_LENGTH, LCD_COLOR_ARGB8888_RED);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X + 2 * CUBE_SIZE, BOARD_TOP_LEFT_Y, LINE_THICKNESS, LINE_LENGTH, LCD_COLOR_ARGB8888_RED);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X, BOARD_TOP_LEFT_Y + CUBE_SIZE, LINE_LENGTH, LINE_THICKNESS, LCD_COLOR_ARGB8888_RED);
  UTIL_LCD_FillRect(BOARD_TOP_LEFT_X, BOARD_TOP_LEFT_Y + 2 * CUBE_SIZE, LINE_LENGTH, LINE_THICKNESS, LCD_COLOR_ARGB8888_RED);

  MG_SelectField(0, 0, LCD_COLOR_ARGB8888_BLUE);

}

void MG_SelectField(uint32_t x, uint32_t y, uint32_t color){

  if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    Error_Handler();
  }

  UTIL_LCD_DrawRect(BOARD_TOP_LEFT_X + x + 1, BOARD_TOP_LEFT_Y + y + 1, CUBE_SIZE - 1, CUBE_SIZE - 1, color);
}