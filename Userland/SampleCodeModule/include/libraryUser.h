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

static ColorT RED = {0xFF, 0,0};
static ColorT GREEN = {0,0xFF,0};
static ColorT BLUE = {0,0,0xFF};
static ColorT ORANGE = {0xFF,0x80,0};
static ColorT YELLOW = {0xFF,0xE8,0};
static ColorT LIGHT_GREEN = {0,0xE0,0x03};
static ColorT DARK_GREEN = {0,0x9C,0x02};
static ColorT LIGHT_BLUE={0,0xC1,0xFF};
static ColorT DARK_BLUE={0,0,0xD2};
static ColorT VIOLET = {0x93,0,0xFF};
static ColorT DARK_PINK={0xDA,0,0xEC};
static ColorT PINK={0xFF,0,0xFF};
static ColorT WINE={0xB4,0,0x57};


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
void getWidth(uint64_t* w);
void getHeight(uint64_t* h);

#endif // LIBRARY_USER_H
