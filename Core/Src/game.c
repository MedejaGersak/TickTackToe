#include "game.h"
#include "adc.h"
#include "joystick.h"
#include "legal_move.h"
#include "main.h"
#include "display.h"
#include "stm32h750b_discovery_lcd.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h750b_discovery_ts.h"
// #include "stm32h750b_discovery_lcd.h"
// #include "stm32h7xx_hal_ltdc.h"
#include "stm32_lcd.h"
#include "stm32h7xx_it.h"
#include "ts_bounds.h"

enum Playscreen gameStatus;

int score[] = {0,0};
TS_State_t touch;

square_bounds board[3][3];
int playerOnMove;

void MG_Board_Init(){

    board[0][0] = square00Bounds;
    board[0][1] = square01Bounds;
    board[0][2] = square02Bounds;
    board[1][0] = square10Bounds;
    board[1][1] = square11Bounds;
    board[1][2] = square12Bounds;
    board[2][0] = square20Bounds;
    board[2][1] = square21Bounds;
    board[2][2] = square22Bounds;
}

enum Homescreen MG_Homescreen(){

    MG_Backround_Homescreen();

    enum Homescreen currButton = PLAY;
    MG_Homescreen_SelectPlayButton();

    while(1){

        //touchscreen
        if(field_or_button_pressed == 1){

            if(INBOUNDS(touch.TouchX, buttonPlayTsBounds.XlowerBound, buttonPlayTsBounds.XupperBound)
               && 
               INBOUNDS(touch.TouchY, buttonPlayTsBounds.YlowerBound, buttonPlayTsBounds.YupperBound)) {
                return PLAY;
            }

            if (INBOUNDS(touch.TouchX, buttonRestartTsBounds.XlowerBound, buttonRestartTsBounds.XupperBound)
                &&
                INBOUNDS(touch.TouchY, buttonRestartTsBounds.YlowerBound, buttonRestartTsBounds.YupperBound)) {
                return RESTART;
            }
            field_or_button_pressed = 0;
        }

        //joystick
        if((joystick_button = MG_joystick_button()) == GPIO_PIN_RESET){
            return currButton;
        }

        enum Move mx = MG_joystick_move();
        
        if(currButton == PLAY && mx == DOWN){
            currButton = RESTART;
            MG_Homescreen_UnselectPlayButton();
            MG_Homescreen_SelectRestartButton();

        }else if(currButton == RESTART && mx == UP){
            currButton = PLAY;
            MG_Homescreen_UnselectRestartButton();
            MG_Homescreen_SelectPlayButton();
        }
    }
}
int32_t x = 0, y = 0;

void MG_Playscreen(){

    MG_Backround_Playscreen();
    gameStatus = ONGOING;
    //board[y][x] !!!!!
    MG_Playscreen_SelectField(board[y][x].XlowerBound, board[y][x].YlowerBound);

    while(1){

        //toucscreen
        MG_Playscreen_ts_board_bounds();

        //joystick:
        if((joystick_button = MG_joystick_button()) == GPIO_PIN_RESET){
            MG_empty_square(x, y);
        }

        if(gameStatus != ONGOING) return;

        enum Move mx = MG_joystick_move();

        switch (mx){

            case UP: 
                if((y-1) >= 0){
                    MG_Playscreen_UnselectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                    y--;
                    MG_Playscreen_SelectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                }
                break;

            case DOWN:
                if((y+1) <= 2){
                    MG_Playscreen_UnselectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                    y++;
                    MG_Playscreen_SelectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                } 
                break;

            case LEFT:
                if((x-1) >= 0){
                    MG_Playscreen_UnselectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                    x--;
                    MG_Playscreen_SelectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                }
                break;

            case RIGHT:
                if((x+1) <= 2){
                    MG_Playscreen_UnselectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                    x++;
                    MG_Playscreen_SelectField(board[y][x].XlowerBound, board[y][x].YlowerBound);
                }
                break;

            default:
        }
    }
}