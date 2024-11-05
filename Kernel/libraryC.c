#include "./include/libraryC.h"

char * numToStr(uint64_t n, uint64_t c){
    uint64_t i = 0;
    char * res = {0};
    for(i = 0 ; i < c; i++){
        res[c-i-1] = n % 10 + '0';
        n = n / 10;
    }
    res[c] = '\0';
    return res;
}

void print(char * string, int length){
    sys_write(1,string, length,WHITE,BLACK);
}

uint64_t strleng(char * string){
    uint64_t i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

char getChar(){
    char buffer[1]={0};
    return sys_read(0, buffer);
}



