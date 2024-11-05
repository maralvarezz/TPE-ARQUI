#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "color.h"
#include "videoDriver.h"
#include <stdint.h>
#include "libraryC.h"
#include "time.h"
#include "../include/keyboard.h"

//Función que es un dispatcher de las syscalls
uint64_t sysCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax);

//syscall de lectura
uint64_t sys_read(uint64_t fd, char * buffer);

//syscall de escritura
uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count,ColorT colorFte,ColorT colorFdo);

//syscall de limpiar pantalla
uint64_t sys_clear();

//syscall de sonido
uint64_t sys_sound(uint64_t freq, uint64_t time);

//syscall de esperar
uint64_t sys_wait(uint64_t time);

//syscall que retorna los segundos
uint64_t sys_seconds(uint64_t * rdi);

//syscall que retorna los minutos
uint64_t sys_minutes(uint64_t * rdi);

//syscall que retorna las horas
uint64_t sys_hours(uint64_t * rdi);

//syscall que coloca el cursor
uint64_t sys_cursor();

//syscall que guarda el contenido de los registros en un vector
uint64_t sys_registers(uint64_t vec[18], uint64_t * rsi);

//syscall que dibuja un rectángulo
uint64_t sys_drawRect(uint64_t rdi,uint64_t rsi ,uint64_t rdx , uint64_t r10 ,ColorT r8 );

//syscall que retorna el ancho de la pantalla
uint64_t sys_width(uint64_t* rdi);

//syscall que retorna el alto de la pantalla
uint64_t sys_height(uint64_t* rdi);

//syscall que aumenta el tamaño de la pantalla
uint64_t sys_increaseSize();

//syscall que reduce el tamaño de la pantalla
uint64_t sys_reduceSize();

//syscall que setea la posición x del cursor
uint64_t sys_cursorSetterX(uint64_t rdi);

//syscall que setea la posición y del cursor
uint64_t sys_cursorSetterY(uint64_t rdi);

//syscall que retorna el tamaño de un pixel
uint64_t sys_pixelSize(uint64_t* rdi);

#endif