#include <stdint.h>

uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_clear();
uint64_t sys_exit();
uint64_t sys_wait(uint64_t time);
uint64_t sys_sound(uint64_t freq, uint64_t time);
uint64_t sys_seconds();
uint64_t sys_minutes();
uint64_t sys_hours();
uint64_t sys_cursor();

