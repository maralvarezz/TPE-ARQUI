#include "driverVideo.h"
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

//Arreglar repeticion de codigo
void printTime(char * vec){
    //Las horas estan desfazadas por 3 --> arreglar
    int h = getHours();
    int m = getMinutes();
    int s = getSeconds();

    char * hS = numToStr(h);

    for(int i = 0; hS[i] != '\0' ; i++){
        *vec++ = hS[i];
        *vec++ = 0x3F;
    }

    char * mS = numToStr(m);

    for(int i = 0; mS[i] != '\0' ; i++){
        *vec++ = mS[i];
        *vec++ = 0x3F;
    }

    char * sS = numToStr(s);
    
    for(int i = 0; sS[i] != '\0' ; i++){
        *vec++ = sS[i];
        *vec++ = 0x3F;
    }
}

void keyboard(char * vec){
    //me va a devolver el codigo de scaneo
    int code = getKey();
    
    //vector que mapea el teclado
    char key[128] = {0, 27, '1', '2', '3', '4','5','6','7','8','9','0','-','=','\b','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    if(code < 128 && key[code] != 0){
        *vec++ = key[code];
        *vec++ = 0x3F;
    }
}
