#include <stdio.h>

#define WRITE 0
#define READ 1



uint64_t syscallsCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax){
    swith(rax){
        case WRITE:
            return syscall_write();

        case READ:
            return syscall_read();
    }
}


void syscall_read(uint64_t fd, uint64_t buffer, uint64_t count){

}

void syscall_write(uint64_t fd, uint64_t buffer, uint64_t count){

}