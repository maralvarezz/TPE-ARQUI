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

static const ColorT BLACK ={0,0,0};
static const ColorT WHITE = {0xFF,0xFF,0xFF};
static const ColorT RED = {0xFF, 0,0};
static const ColorT GREEN = {0,0xFF,0};
static const ColorT BLUE = {0,0,0xFF};
static const ColorT ORANGE = {0xFF,0x80,0};
static const ColorT YELLOW = {0xFF,0xE8,0};
static const ColorT LIGHT_GREEN = {0,0xE0,0x03};
static const ColorT DARK_GREEN = {0,0x9C,0x02};
static const ColorT LIGHT_BLUE={0,0xC1,0xFF};
static const ColorT DARK_BLUE={0,0,0xD2};
static const ColorT VIOLET = {0x93,0,0xFF};
static const ColorT DARK_PINK={0xDA,0,0xEC};
static const ColorT PINK={0xFF,0,0xFF};
static const ColorT WINE={0xB4,0,0x57};


void putChar(char c);
void printString(char * string, int length);
void printStringColor(char * string, int length,const ColorT* colorFte,const ColorT* colorFdo);
void printInt(int num);
void printIntColor(int num,const ColorT* c1,const ColorT* c2);
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
void drawRect(uint64_t x,uint64_t y,uint64_t x2,uint64_t y2, const ColorT* colorToPaint);
void getWidth(uint64_t* w);
void getHeight(uint64_t* h);
void increaseSize();
void reduceSize();
char peekChar();
char toLower(char c);
void setCursorX(uint64_t x);
void setCursorY(uint64_t y);
void moveCursor(uint64_t x,uint64_t y);
int getPixelSize();

#endif // LIBRARY_USER_H
