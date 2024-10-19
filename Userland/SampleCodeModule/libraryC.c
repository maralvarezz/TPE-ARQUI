#include "libraryC.h"
#include <stdio.h>

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

void print(char * vec, int time){
    char * s = numToStr(time);

    for(int i = 0; s[i] != '\0' ; i++){
        *vec++ = s[i];
        *vec++ = 0x3F;
    }
}

void printTime(char * vec){
    //Las horas estan desfazadas por 3 --> arreglar
    int h = getHours() ;
    if(h<=3){
        h+=24;
    }
    h-=3;
    int m = getMinutes();
    int s = getSeconds();

    print(vec,  h);
    vec+=4;
    *vec++ = ':';
    *vec++ = 0x3F;
     print(vec,  m);
    vec+=4;
    *vec++ = ':';
    *vec++ = 0x3F;
     print(vec,  s);
}


void keyboard(char * vec){
    //me va a devolver el codigo de scaneo
    int code = getKey();

    *vec++ = keyboard_handler(code);
    *vec++ = 0x3F;

    /*
    //vector que mapea el teclado
char key [128] =
{0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b','\t','q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',0,'a', 's', 'd', 'f', 'g', 'h', 'j','k','l',';', '\'', '`',0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,'+',0,0,0,0,0,0,0,0,0,0,0};
    if(code < 128 && key[code] != 0){
        *vec++ = key[code];
        *vec++ = 0x3F;
    }*/
}