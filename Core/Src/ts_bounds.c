#include "ts_bounds.h"
#include "stm32_lcd.h"
#include "display.h"

button_play_ts_bounds buttonPlayTsBounds;
button_restart_ts_bounds buttonRestartTsBounds;

square_bounds square00Bounds;
square_bounds square01Bounds;
square_bounds square02Bounds;
square_bounds square10Bounds;
square_bounds square11Bounds;
square_bounds square12Bounds;
square_bounds square20Bounds;
square_bounds square21Bounds;
square_bounds square22Bounds;


void MG_TS_bounds_Init(){

    buttonPlayTsBounds.XlowerBound = BUTTON_PLAY_X;
    buttonPlayTsBounds.XupperBound = BUTTON_PLAY_X + 4 * Font24.Width;
    buttonPlayTsBounds.YlowerBound = BUTTON_PLAY_Y;
    buttonPlayTsBounds.YupperBound = BUTTON_PLAY_Y + Font24.Height;

    buttonRestartTsBounds.XlowerBound = BUTTON_RESTART_X;
    buttonRestartTsBounds.XupperBound = BUTTON_RESTART_X + 7 * Font20.Width;
    buttonRestartTsBounds.YlowerBound = BUTTON_RESTART_Y;
    buttonRestartTsBounds.YupperBound = BUTTON_RESTART_Y + Font20.Height;

    square00Bounds.XlowerBound = BOARD_TOP_LEFT_X;
    square00Bounds.XupperBound = BOARD_TOP_LEFT_X + SQUARE_SIZE;
    square00Bounds.YlowerBound = BOARD_TOP_LEFT_Y;
    square00Bounds.YupperBound = BOARD_TOP_LEFT_Y + SQUARE_SIZE;

    square01Bounds.XlowerBound = BOARD_TOP_LEFT_X + SQUARE_SIZE;
    square01Bounds.XupperBound = BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE;
    square01Bounds.YlowerBound = BOARD_TOP_LEFT_Y;
    square01Bounds.YupperBound = BOARD_TOP_LEFT_Y + SQUARE_SIZE;

    square02Bounds.XlowerBound = BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE;
    square02Bounds.XupperBound = BOARD_TOP_LEFT_X + 3 * SQUARE_SIZE;
    square02Bounds.YlowerBound = BOARD_TOP_LEFT_Y;
    square02Bounds.YupperBound = BOARD_TOP_LEFT_Y + SQUARE_SIZE;

    square10Bounds.XlowerBound = BOARD_TOP_LEFT_X;
    square10Bounds.XupperBound = BOARD_TOP_LEFT_X + SQUARE_SIZE;
    square10Bounds.YlowerBound = BOARD_TOP_LEFT_Y + SQUARE_SIZE;
    square10Bounds.YupperBound = BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE;

    square11Bounds.XlowerBound = BOARD_TOP_LEFT_X + SQUARE_SIZE;
    square11Bounds.XupperBound = BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE;
    square11Bounds.YlowerBound = BOARD_TOP_LEFT_Y + SQUARE_SIZE;
    square11Bounds.YupperBound = BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE;

    square12Bounds.XlowerBound = BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE;
    square12Bounds.XupperBound = BOARD_TOP_LEFT_X + 3 * SQUARE_SIZE;
    square12Bounds.YlowerBound = BOARD_TOP_LEFT_Y + SQUARE_SIZE;
    square12Bounds.YupperBound = BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE;

    square20Bounds.XlowerBound = BOARD_TOP_LEFT_X;
    square20Bounds.XupperBound = BOARD_TOP_LEFT_X + SQUARE_SIZE;
    square20Bounds.YlowerBound = BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE;
    square20Bounds.YupperBound = BOARD_TOP_LEFT_Y + 3 * SQUARE_SIZE;

    square21Bounds.XlowerBound = BOARD_TOP_LEFT_X + SQUARE_SIZE;
    square21Bounds.XupperBound = BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE;
    square21Bounds.YlowerBound = BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE;
    square21Bounds.YupperBound = BOARD_TOP_LEFT_Y + 3 * SQUARE_SIZE;

    square22Bounds.XlowerBound = BOARD_TOP_LEFT_X + 2 * SQUARE_SIZE;
    square22Bounds.XupperBound = BOARD_TOP_LEFT_X + 3 * SQUARE_SIZE;
    square22Bounds.YlowerBound = BOARD_TOP_LEFT_Y + 2 * SQUARE_SIZE;
    square22Bounds.YupperBound = BOARD_TOP_LEFT_Y + 3 * SQUARE_SIZE;


}