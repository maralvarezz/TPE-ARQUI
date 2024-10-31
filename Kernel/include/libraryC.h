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


uint64_t strleng(char * string);
void printTime(char * vec); // no se deberia de borrar?
char* numToStr(uint64_t n, uint64_t c);
void keyboard(char * vec);
void print(char * string, int length);

#endif