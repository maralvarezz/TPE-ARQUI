#ifndef LIBRARY_USER_H
#define LIBRARY_USER_H

#include <stdio.h>
#include <stdint.h>


typedef struct color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}ColorT;

typedef struct Nota{
    int frec;
    int time;
} NotaT;


void putChar(char c);
void printString(char * string, int length);
void printInt(int num);
char getChar();
void sleep(uint64_t time);
int strlen(char * str);
int strcmp(const char * str1, const char * str2);
void clearAll();
void invokeOpCode();
void invokeDivZero();
void playNota(uint64_t freq, uint64_t time);
void playMusic(NotaT * music, int duration);
int gettingSeconds();
int gettingMinutes();
int gettingHours();
void printCursor();
void printRegisters();
void drawRect(uint64_t x,uint64_t y,uint64_t x2,uint64_t y2, ColorT* colorToPaint);

#endif // LIBRARY_USER_H
