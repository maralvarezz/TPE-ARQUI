#include "./include/libraryC.h"

char * numToStr(uint64_t n, uint64_t c){
    uint64_t i = 0;
    char res[c+1];
    for(i = 0 ; i < c; i++){
        res[c-i] = n % 10 + '0';
        n = n / 10;
    }
    res[i] = '\0';
    char * aux = res;
    return aux;
}

static void printT(char * vec, int time){
    char * s = numToStr(time, 2);
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
}

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
    //no imprime back
    if(resp==0){
        print("Error al leer", 12);
    }
}

char getChar(){
    char buffer[2]={0};
    buffer[0]=getKeyboard();
    return sys_read(0, buffer, 1);
}



