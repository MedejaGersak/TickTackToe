#ifndef __TS_BOUNDS_H__
#define __TS_BOUNDS_H__

#include "display.h"
#include <stdint.h>


typedef struct {
    uint32_t XupperBound;
    uint32_t XlowerBound;
    uint32_t YupperBound;
    uint32_t YlowerBound;

}button_play_ts_bounds;

typedef struct {
    uint32_t XupperBound;
    uint32_t XlowerBound;
    uint32_t YupperBound;
    uint32_t YlowerBound;

}button_restart_ts_bounds;

typedef struct{
    uint32_t XupperBound;
    uint32_t XlowerBound;
    uint32_t YupperBound;
    uint32_t YlowerBound;

}square_bounds;


extern button_play_ts_bounds buttonPlayTsBounds;
extern button_restart_ts_bounds buttonRestartTsBounds;
void MG_TS_bounds_Init(void);

extern square_bounds square00Bounds;
extern square_bounds square01Bounds;
extern square_bounds square02Bounds;
extern square_bounds square10Bounds;
extern square_bounds square11Bounds;
extern square_bounds square12Bounds;
extern square_bounds square20Bounds;
extern square_bounds square21Bounds;
extern square_bounds square22Bounds;


#endif