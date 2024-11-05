#include "libraryUser.h"
#include "snakes.h"
#include <stdint.h>

extern void invalidopcode();

extern void divzero();

//Muestra la lista de comandos disponibles.
void command_help();

//Muestra la hora actual.
void command_time();

//Limpia la terminal.
void command_clear();

//Permite cambiar el nombre del usuario.
void command_modifyuser();

//Muestra el estado actual de los registros.
void command_registers();


//Excepción de dividir por cero.
void command_divzero();

//Excepción de operación de codigo inválido.
void command_invalidopcode();

//Inicia el juego snakes.
void command_snakes();

//Muestra el nombre de usuario actual.
void command_username();

//Cierra la terminal.
void command_exit();

//Reduce el tamaño de la letra.
void command_reducesize();


//Aumenta el tamaño de la letra.
void command_increasesize();

//Inicio de la terminal.
void entry();

//Maneja el entorno de la terminal.
void terminal();

//Muestra el error de comando no encontrado.
void noCommand();

//Permite leer una línea de la terminal.
void readLine();

//Verifica si lo ingresado es un comando.
void checkCommand(char*  c);

//Verifica si el comando ingresado es válido.
void check();

//Pone una línea en la terminal.
void putLine();

//Imprime el nombre de usuario al principio de la línea.
void printUserDef();

