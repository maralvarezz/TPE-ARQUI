#include <time.h>
#include <stdint.h>
#include "../include/syscalls.h"

#define READ 0
#define WRITE 1
#define CLEAR 2
#define WAIT 3
#define SOUND 4
#define SECONDS 5
#define MINUTES 6
#define HOURS 7

extern int getSeconds();
extern int getMinutes();
extern int getHours();



uint64_t sysCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax) {
	switch (rax) {
		case WRITE:
			return sys_write(rdi, (char *)rsi, rdx);
		case READ:
			return sys_read(rdi, (char *)rsi, rdx);
		case CLEAR:
			return sys_clear();
        case WAIT:
            return sys_wait(rdi);
        case SOUND:
            return sys_sound(rdi, rsi);
        case SECONDS:
            return sys_seconds();
        case MINUTES:
            return sys_minutes();
        case HOURS:
            return sys_hours();
        default:
            return 0;
	}
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
        return 1;
    }
    return 0;
}

uint64_t sys_clear(){
    driver_clear();
    return 1;
}

uint64_t sys_registers(){
    //preguntar
}

uint64_t sys_seconds(){
    return getSeconds();
}

uint64_t sys_minutes(){
    return getMinutes();
}

uint64_t sys_hours(){
    return getHours();
}

uint64_t sys_wait(uint64_t time){
    wait_time(time);
    return 1;
}

uint64_t sys_sound(uint64_t freq, uint64_t time){
    if(freq<=0 || time<=0){
        return 0;
    }
    //make_sound(freq);
    wait_time(time);
}
