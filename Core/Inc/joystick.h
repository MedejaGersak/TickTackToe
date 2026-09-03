#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

enum Move {
    LEFT, 
    RIGHT, 
    UP, 
    DOWN,
    NEUTRAL
};
enum Move MG_joystick_move(void);


#endif