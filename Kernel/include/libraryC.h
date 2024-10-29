#include <stdint.h>
#include "syscalls.h"
#include "keyboard.h"

extern uint64_t getHours();
extern uint64_t getMinutes();
extern uint64_t getSeconds();
extern void sound(int freq);
extern void stopSound();


void printTime(char * vec);
char * numToStr(uint64_t n, uint64_t c);
void keyboard(char * vec);
void print(char * string, int length);
