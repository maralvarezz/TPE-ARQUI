#include "fuente.h"
#include "../include/keyboard.h"
typedef struct color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}ColorT;


void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void driver_clear();
void driver_read(char * buffer);
void driver_lineBelow();
void driver_backspace();
uint32_t colorToHexa(ColorT color);
void driver_putCursor();
void driver_print(char * buffer, uint64_t count);
