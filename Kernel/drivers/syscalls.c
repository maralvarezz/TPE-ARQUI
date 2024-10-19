#include <stdio.h>

#define WRITE 0
#define READ 1

uint64_t sysCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){
    swith(rax){
        case WRITE:
            return syscall_write();

        case READ:
            return syscall_read();
    }
}


uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count){
    if(fd == 0){
        driver_read(buffer, count);
        return 1;
    }
    return 0;
}

uint64_t sys_write(uint64_t fd, uint64_t buffer, uint64_t count){
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