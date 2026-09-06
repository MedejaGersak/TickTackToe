#ifndef __MG_ROTATE_H__
#define __MG_ROTATE_H__

#include <stdint.h>
#include <math.h>

typedef struct Point_t{
    int32_t x;
    int32_t y;
} Point_t;

static inline Point_t rotate(int32_t point_x, int32_t point_y, int32_t pivot_x, int32_t pivot_y, float angle) {
    float dx = (float)point_x - (float)pivot_x;
    float dy = (float)point_y - (float)pivot_y;

    float c = cosf(angle);
    float s = sinf(angle);

    int32_t x_ = (int32_t)lroundf(pivot_x + dx * c - dy * s);
    int32_t y_ = (int32_t)lroundf(pivot_y + dx * s + dy * c);

    Point_t p = {x_, y_};
    return p;
}

static inline int32_t rotate_x(int32_t point_x, int32_t point_y, int32_t pivot_x, int32_t pivot_y, float angle) {
    return rotate(point_x, point_y, pivot_x, pivot_y, angle).x;
}


static inline int32_t rotate_y(int32_t point_x, int32_t point_y, int32_t pivot_x, int32_t pivot_y, float angle) {
    return rotate(point_x, point_y, pivot_x, pivot_y, angle).y;
}

#endif