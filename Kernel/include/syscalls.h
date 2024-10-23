#include <stdint.h>
#include"videoDriver.h"
#include "time.h"


uint64_t sysCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax);
uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_clear();
uint64_t sys_sound(uint64_t freq, uint64_t time);
uint64_t sys_wait(uint64_t time);
uint64_t sys_seconds();
uint64_t sys_minutes();
uint64_t sys_hours();
uint64_t sys_cursor();

