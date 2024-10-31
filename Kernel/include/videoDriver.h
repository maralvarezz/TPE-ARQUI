#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>
#include "color.h"
#include "fuente.h"
#include "keyboard.h"
#include "libraryC.h"

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void driver_clear();
void driver_read(char * buffer);
void driver_lineBelow();
void driver_backspace();
uint32_t colorToHexa(ColorT color);
void driver_putCursor();
void driver_print_color(char * buffer, uint64_t count,ColorT colorFte,ColorT colorFdo);
void driver_drawRect(uint64_t x,uint64_t y ,uint64_t x2 , uint64_t y2 ,ColorT colorToPaint);
uint16_t driver_width();
uint16_t driver_height();
uint64_t driver_reduceSize();
uint64_t driver_increaseSize();
void driver_setCursorX(uint64_t x);
void driver_setCursorY(uint64_t y);

#endif