#include <stdio.h>

typedef struct {
    int frec;
    int time;
} NotaT;

void printChar(char c);
void printString(char * string, int length);
void printInt(int num);
char getChar();
void sleep();
int strlen(char * str);
int strcmp(char * str1, char * str2);
void clearAll();
void invokeOpCode();
void invokeDivZero();
void playNota(uint64_t freq, uint64_t time);
void playMusic(NotaT * music, int duration);
int gettingSeconds();
int gettingMinutes();
int gettingHours();