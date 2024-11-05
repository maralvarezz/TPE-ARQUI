#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>
#include "color.h"
#include "fuente.h"
#include "keyboard.h"
#include "libraryC.h"

//limpia la pantalla
void driver_clear();

//obtiene un caracter del buffer
void driver_read(char * buffer);

//salto de linea
void driver_lineBelow();

//borra el caracter anterior
void driver_backspace();

//imprime el cursor en pantalla
void driver_putCursor();

//imprime un caracter en pantalla con un color de fuente y de fondo
void driver_print_color(char * buffer, uint64_t count,ColorT colorFte,ColorT colorFdo);

//funcion para dibujar un rectangulo en pantalla
void driver_drawRect(uint64_t x,uint64_t y ,uint64_t x2 , uint64_t y2 ,ColorT colorToPaint);

//funcion para obtener el ancho de la pantalla
uint16_t driver_width();

//funcion para obtener el alto de la pantalla
uint16_t driver_height();

//funcion para reducir el tamaño de los pixeles
uint64_t driver_reduceSize();

//funcion para aumentar el tamaño de los pixeles
uint64_t driver_increaseSize();

//funcion para setear el cursor en x
void driver_setCursorX(uint64_t x);

//funcion para setear el cursor en y
void driver_setCursorY(uint64_t y);

//funcion para obtener el tamaño de los pixeles
uint64_t driver_getPixelSize();

#endif