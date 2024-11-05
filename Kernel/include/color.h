#ifndef COLOR_H
#define COLOR_H
#include<stdint.h>

typedef struct color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}ColorT;

static const ColorT WHITE = {255,255,255};
static const ColorT BLACK = {0,0,0};

#endif