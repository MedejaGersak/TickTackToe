#include "joystick.h"
#include "main.h"
#include "adc.h"
#include "display.h"
#include "stm32h750b_discovery_lcd.h"
#include "stm32_lcd.h"
#include <stdlib.h>


#define NEUTRAL_X (1UL << 15)
#define NEUTRAL_Y (1UL << 15)
#define LEEWAY 5000

enum Move MG_joystick_move(){

    // if (BSP_LCD_SetActiveLayer(0, FIRST_LAYER) != BSP_ERROR_NONE) {
    //     Error_Handler();
    // }

    int32_t currx = NEUTRAL_X - joystick_buffer[0];
    int32_t curry = NEUTRAL_Y - joystick_buffer[1];

    if(abs(currx) < LEEWAY && abs(curry) < LEEWAY) return NEUTRAL;

    if(abs(curry) > LEEWAY && abs(curry) > abs(currx)){

        if(curry > 0) return UP;
        else return DOWN;    
    }

    if(abs(currx) > LEEWAY){

        if(currx > 0) return RIGHT;
        else return LEFT;
    }
}