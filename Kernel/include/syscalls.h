#include<stdint.h>
#include"videoDriver.h"

uint64_t sysCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax);
uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_clear();