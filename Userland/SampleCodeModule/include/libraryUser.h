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

/*--------------COLORES DISPONIBLES--------------*/
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

/**
 * Imprime el caracter c en pantalla.
 */
void putChar(char c);

/**
 * Imprime el string en pantalla.
 */
void printString(char * string, int length);

/**
 * Imprime el string en pantalla con colores.
 */
void printStringColor(char * string, int length,const ColorT* colorFte,const ColorT* colorFdo);

/**
 * Imprime el número num en pantalla.
 */
void printInt(int num);

/**
 * Imprime el número num en pantalla con colores.
 */
void printIntColor(int num,const ColorT* c1,const ColorT* c2);

/**
 * Levanta un caracter.
 */
char getChar();

/**
 * Espera una determinada cantidad de tiempo time.
 */
void sleep(uint64_t time);

/**
 * Calcula la longitud de un string.
 */
int strlen(char * str);

/**
 * Compara dos strings. Devuelve 0 si son iguales.
 */
int strcmp(const char * str1, const char * str2);

/**
 * Limpia la pantalla.
 */
void clearAll();

/**
 * Ejecuta excepción de código de operación invalido.
 */
void invokeOpCode();

/**
 * Ejecuta excepción de división por cero.
 */
void invokeDivZero();

/**
 * Envía una nota al parlante.
 */
void playNota(uint64_t freq, uint64_t time);

/**
 * Devuelve la cantidad de segundos.
 */
int gettingSeconds();

/**
 * Devuelve la cantidad de minutos.
 */
int gettingMinutes();

/**
 * Devuelve la cantidad de horas.
 */
int gettingHours();

/**
 * Imprime el cursor.
 */
void printCursor();

/**
 * Imprime los registros.
 */
void printRegisters();

/**
 * Dibuja un rectángulo en pantalla. 
 */
void drawRect(uint64_t x,uint64_t y,uint64_t x2,uint64_t y2, const ColorT* colorToPaint);

/**
 * Devuelve el ancho de la pantalla en w.
 */
void getWidth(uint64_t* w);

/**
 * Devuelve el alto de la pantalla en h.
 */
void getHeight(uint64_t* h);

/**
 * Aumenta el tamaño de la letra.
 */
void increaseSize();

/**
 * Reduce el tamaño de la letra.
 */
void reduceSize();

/**
 * Muestra el caracter sin levantarlo.
 */
char peekChar();

/**
 * Pasa el caracter c a minúscula.
 */
char toLower(char c);

/**
 * Setea el cursor en x.
 */
void setCursorX(uint64_t x);

/**
 * Setea el cursor en y.
 */
void setCursorY(uint64_t y);

/**
 * Mueve el cursor a la posición x,y.
 */
void moveCursor(uint64_t x,uint64_t y);

/**
 * Devuelve el tamaño de un pixel.
 */
int getPixelSize();

#endif // LIBRARY_USER_H
