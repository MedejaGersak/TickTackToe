#include "game.h"
#include "adc.h"
#include "joystick.h"
#include "main.h"
#include "display.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h750b_discovery_ts.h"
// #include "stm32h750b_discovery_lcd.h"
// #include "stm32h7xx_hal_ltdc.h"
#include "stm32_lcd.h"


int score[] = {0,0};
TS_State_t touch;

#define BUTTON_PLAY_UPPER_MARGIN_X (BUTTON_PLAY_X - (*BUTTON_PLAY_SIZE).Height)
#define BUTTON_PLAY_LOWER_MARGIN_X BUTTON_PLAY_X

enum Homescreen MG_Homescreen(){

    MG_Backround_Homescreen();

    enum Homescreen currButton = PLAY;
    MG_Homescreen_SelectPlayButton();

    while(1){

        BSP_TS_GetState(0, &touch);

        if(touch.TouchDetected == 1){
            if(touch.TouchX >= BUTTON_PLAY_LOWER_MARGIN_X && touch.TouchX <= BUTTON_PLAY_UPPER_MARGIN_X){
                return currButton;
            }
        }


        if((joystick_button = (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_3))) == GPIO_PIN_RESET){
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

void MG_Playscreen(){

    MG_Backround_Playscreen();

    enum Playscreen currSquare = SQUARE_1_1;
}