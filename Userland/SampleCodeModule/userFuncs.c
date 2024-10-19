#include "shell.h"

void print(char * string, int length){
    syscall_write(1,string, length); //mando 1 porque es la salida estandar
};

void printTime(){
    syscall_time();
};

void strlen(char * string){
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

void scanf(char * string, char * buffer, int bufferLength){
    print(string, strlen(string));
    syscall_read(0, buffer, bufferLength); //mando 0 porque es la entrada estandar
}