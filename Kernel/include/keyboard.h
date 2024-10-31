#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

extern void _hlt();
char getKeyboard();
void keyboard_handler();
int isLetter(char key);
void addBuffer();
char getBuffer();
uint64_t getCtrlFlag();

#endif
