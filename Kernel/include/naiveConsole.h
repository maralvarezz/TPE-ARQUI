#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

//Imprime a string in the screen
void ncPrint(const char * string);

//Imprime un char en la pantalla
void ncPrintChar(char character);

//Imprime un salto de linea
void ncNewline();

//Imprime un numero en decimal
void ncPrintDec(uint64_t value);

//Imprime un numero en hexa
void ncPrintHex(uint64_t value);

//Imprime un binario
void ncPrintBin(uint64_t value);

//imprime un numero en la base que se le pase
void ncPrintBase(uint64_t value, uint32_t base);

//Clear de la pantalla
void ncClear();

#endif