#include <stdint.h>
#include "./include/libraryUser.h"
#include "./include/syscalls_user.h"
#include "./include/exceptions_user.h"


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

void putChar(char c){
    char * c1 = &c;
    sys_write(1,c1, 1);
}

char getChar(){
    char c;
    printCursor();
    sys_read(0,&c, 1); //mando 0 porque es la entrada estandar
    //sleep(2); // no esta definido
    
    return c;
}

void clearAll(){
    sys_clear();
}

void sleep(uint64_t time){
    sys_wait(time);
}

int strcmp(const char * str1, const char * str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return -1;
        }
        i++;
    }
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 0;
    }
    return 1;
}

int strlen(char * str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

void printCursor(){
    sys_cursor();
    return;
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

void printInt(int num) {
    char buffer[12]; // Suficiente para almacenar int de 32 bits con signo
    int i = 0;
    if (num == 0) {
        putChar('0');
        return;
    }
    if (num < 0) {   // Maneja el signo
        putChar('-');
        num = -num;
    }
    while (num > 0) { // Convierte el número a caracteres
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    // Imprime el número en el orden correcto
    for (int j = i - 1; j >= 0; j--) {
        putChar(buffer[j]);
    }
}



