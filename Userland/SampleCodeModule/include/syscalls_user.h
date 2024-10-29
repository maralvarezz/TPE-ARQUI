#include <stdint.h>
#include "libraryUser.h"

extern uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count);
extern uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count);
extern uint64_t sys_clear();
extern uint64_t sys_exit();
extern uint64_t sys_wait(uint64_t time);
extern uint64_t sys_sound(uint64_t freq, uint64_t time);
extern uint64_t sys_seconds();
extern uint64_t sys_minutes();
extern uint64_t sys_hours();
extern uint64_t sys_cursor();
uint64_t sys_registers(uint64_t vec[17], uint64_t * flag);
extern uint64_t sys_drawRectangle(uint64_t x, uint64_t y, uint64_t x2,uint64_t y2,ColorT* colorToPaint);
