#include <time.h>
#include <stdint.h>
#include "../include/syscalls.h"

#define TIMER 0
#define WRITE 1
#define READ 2
#define CLEAR 3

static void timer();
uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count);
uint64_t sys_clear();

void sysCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax) {
	switch (rax) {
		case TIMER:
			return timer();
		case WRITE:
			return sys_write();
		case READ:
			return sys_read();
		case CLEAR:
			return sys_clear();
	}
	return;
}

void timer() {
	timer_handler();
}

uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count){
    if(fd == 0){
        driver_read(buffer, count);
        return 1;
    }
    return 0;
}

uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count){
    if(fd == 1){
        driver_write(buffer, count);
        return 1
    }
    return 0;
}

uint64_t sys_clear(){
    driver_clear();
    return 1;
}
