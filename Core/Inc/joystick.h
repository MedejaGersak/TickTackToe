#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <stdint.h>

enum Move {
    LEFT, 
    RIGHT, 
    UP, 
    DOWN,
    NEUTRAL
};
enum Move MG_joystick_move(void);

uint16_t MG_joystick_button(void);


#endif