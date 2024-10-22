#include <stdio.h>
#include "libraryUser.h"


void playNota(uint64_t freq, uint64_t time){
    sys_sound(freq, time);
}

void playMusic(NotaT * music, int duration){
    for(int i = 0; i < duration; i++){
        playNota(music[i].frec, music[i].time);
    }
}

void printString(char * string, int length){
    sys_write(1,string, length); //mando 1 porque es la salida estandar
}

void printChar(char c){
    sys_write(1,(char*)c, 1);
}

char getChar(){
    char c;
    sys_read(0,&c, 1); //mando 0 porque es la entrada estandar
    return c;
}

void clearAll(){
    sys_clear();
}

void sleep(){
    sys_wait();
}

int strcmp(char * str1, char * str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return 0;
        }
        i++;
    }
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 1;
    }
    return 0;
}

int strlen(char * str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

void invokeOpCode(){
    exc_invalidopcode();
}

void invokeDivZero(){
    exc_divzero();
}

int gettingSeconds(){
    return sys_seconds();
}

int gettingMinutes(){
    return sys_minutes();
}

int gettingHours(){
    return sys_hours();
}

void printInt(int num){
    char buffer[10];
    int i = 0;
    while(num > 0){
        buffer[i] = num%10 + '0';
        num = num/10;
        i++;
    }
    i--;
    while(i >= 0){
        printChar(buffer[i]);
        i--;
    }
}



