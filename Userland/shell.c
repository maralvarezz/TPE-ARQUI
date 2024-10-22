#include "shell.h"
#include "../../Kernel/include/libraryC.h"
#include <stdint.h>

#define USER_MAX 32 

uint8_t USER_SIZE = 4;
char USER[USER_MAX] = "user";


extern void print(char * , int);


//Menu de comandos disponibles
void command_help(){
    print("Lista de comandos disponibles:\n", 30);
    print("-help: Muestra la lista de comandos disponibles\n", 50);
    print("-time: Muestra la hora actual\n", 30);
    print("-clear: Limpia la terminal\n", 27);
    print("-changeuser: Cambia el nombre de usuario\n", 45);
    print("-registers: Muestra el estado actual de los registros\n", 54);
    print("-divzero: Excepcion de dividir por cero\n", 42);
    print("-invalidopcode: Excepcion de codigo de operacion invalido\n", 58);
    print("-snakes: Inicia el juego Snakes\n", 33);
    print("-username: Muestra el nombre de usuario actual\n", 48);
    print("-exit: Cierra la terminal\n", 27);
}

//Imprime el tiempo en pantalla
void command_time(){
    print("Su hora actual es: ", 19);
    //printTime(); //ver como llamarlo
}

//Limpia la terminal
void command_clear(){
    sys_clear();
}

void command_changeuser(){
    int c, size = 0;
    char aux[2]={0};
    while((c = getChar()) != '\n' && size < USER_MAX){
        //lamar al cursor
        USER[size] = c;
        size++;
        aux[0] = c;
        print(aux, 1);
    }
    if(size >= USER_MAX){
        print("Ingrese un nombre de usuario valido\n", 32);
        return;
    }
    else{
        USER[size] = '\0';
        USER_SIZE = size;
        print("Bienvenido ", 10);
        print(USER, USER_SIZE);
        print("\n", 1);
    }
}

//Imprimir el estado de todos los registros
void command_registers(){
    //sys_registers();
}

//Excepcion de dividir por cero
void command_divzero(){
    divzero();
}

//Excepcion de codigo de operacion invalido
void command_invalidopcode(){
    invalidopcode();
}

void command_snakes(){
    //iniciar juego
}

void command_username(){
    print("Usuario: ", 9);
    print(USER, USER_SIZE);
    print("\n", 1);
}

void command_exit(){
    print("Muchas gracias por su visita :)\n", 31);
    //sys_exit();
}

//Lo que se pone al inicial la terminal
void entry(){
    print("Bienvenidos al SO del Grupo 2 :)\n", 31);
    //scanf("Ingrese su nombre de usuario:\n");
    print("Ingrese su nombre de usuario (maximo 32 caracteres):\n", 45);
    command_changeuser();
}


void printUserDef(){ //cambiar nombre
    print(USER, USER_SIZE);
    print(":~ $",3);
}

