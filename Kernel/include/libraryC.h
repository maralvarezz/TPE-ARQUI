#ifndef LIBRARYC_H
#define LIBRARYC_H

#include <stdint.h>
#include "syscalls.h"
#include "keyboard.h"

extern uint64_t getHours();
extern uint64_t getMinutes();
extern uint64_t getSeconds();
extern void sound(int freq);
extern void stopSound();

//función que retorna la longitud de un string
uint64_t strleng(char * string);

//pasa de numero a string
char* numToStr(uint64_t n, uint64_t c);

//printea en pantalla
void print(char * string, int length);

//hace un read de un caracter
char getChar();

#endif