#include <stdint.h>
#include "fuente.h"

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void driver_clear();
void driver_read(char * buffer, uint64_t count);
void driver_write(char * buffer, uint64_t count);
void driver_newLine();
void driver_backspace();
void driver_width();
void driver_sound();
