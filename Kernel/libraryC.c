#include "./include/libraryC.h"

extern int getHours();
extern int getMinutes();
extern int getSeconds();
extern int getKey();

char * numToStr(int n){
    char res[3] = {0};
    for(int i = 0 ; i < 2; i++){
        res[1-i] = n % 10 + '0';
        n = n / 10;
    }
    res[2] = '\0';
    char * aux = res;
    return aux;
}

static void printT(char * vec, int time){
    char * s = numToStr(time);
    for(int i = 0; s[i] != '\0' ; i++){
        *vec++ = s[i];
        *vec++ = 0x3F;
    }
}

void printTime(char * vec){
    int h = getHours() ;
    if(h<=3){
        h+=24;
    }
    h-=3;
    int m = getMinutes();
    int s = getSeconds();

    printT(vec,  h);
    vec+=4;
    *vec++ = ':';
    *vec++ = 0x3F;
    printT(vec,  m);
    vec+=4;
    *vec++ = ':';
    *vec++ = 0x3F;
    printT(vec,  s);
}

void print(char * string, int length){
    sys_write(1,string, length); //mando 1 porque es la salida estandar
};

uint64_t strlen(char * string){
    uint64_t i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

void scanf(char * string, char * buffer, int bufferLength){
    print(string, strlen(string));
    int resp=sys_read(0, buffer, bufferLength); //mando 0 porque es la entrada estandar
    if(resp==0){
        print("Error al leer", 12);
    }
}

char getChar(){
    return sys_read(0, keyboard_handler(), 1);
}


