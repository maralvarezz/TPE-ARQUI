#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

extern void _hlt();

//con el códigode teclado, dependiendo si es mayuscula o minúscula devuelve el caracter correspondiente
char getKeyboard();

//handler de teclado
void keyboard_handler();

//función para adicionar el buffer circular
void addBuffer();

//función para obtener del buffer circular
char getBuffer();

//función para obtener el flag de control
uint64_t getCtrlFlag();

#endif
