#include "joystick.h"
#include "main.h"
#include "adc.h"
#include "display.h"
#include "stm32h750b_discovery_lcd.h"
#include "stm32_lcd.h"
#include <stdlib.h>
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"


#define NEUTRAL_X (1UL << 15)
#define NEUTRAL_Y (1UL << 15)
#define LEEWAY 5000

GPIO_PinState lastButtonState = GPIO_PIN_SET;
uint32_t lastButtonPress = 0;

uint32_t lastJoystickMove = 0;

enum Move MG_joystick_move(){

    if(HAL_GetTick() - lastJoystickMove < 210) return NEUTRAL;

    lastJoystickMove = HAL_GetTick();

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



uint16_t MG_joystick_button(){

    GPIO_PinState currentState = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_3);

    if(currentState == GPIO_PIN_RESET && lastButtonState == GPIO_PIN_SET){
        if(HAL_GetTick() - lastButtonPress > 225){
            lastButtonPress = HAL_GetTick();
            lastButtonState = currentState;
            return GPIO_PIN_RESET;
        }
    }

    if(currentState == GPIO_PIN_SET) lastButtonState = GPIO_PIN_SET;
    return GPIO_PIN_SET;
}