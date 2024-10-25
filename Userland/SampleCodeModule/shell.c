#include "./include/shell.h"
#include <stdint.h>

#define USER_MAX 32 
#define COMMAND_MAX 50
#define BUFFER 300
#define TOTAL_COMMANDS 10

int on = 1;
char command[COMMAND_MAX] = {0};

char * commandList[] = {"-help", "-time", "-clear", "-modifyuser", "-registers", "-divzero", "-invalidopcode", "-snakes", "-username", "-exit"};

int USER_SIZE = 5;
char USER[USER_MAX] = "guest";

//voy guardando los comandos que se van haciendo para poder llamarlos con las flechas
//char commandHist[COMMAND_MAX][BUFFER] = {0}



//Menu de comandos disponibles
void command_help(){
    printString("Lista de comandos disponibles:\n", 30);
    printString("-help: Muestra la lista de comandos disponibles\n", 50);
    printString("-time: Muestra la hora actual\n", 30);
    printString("-clear: Limpia la terminal\n", 27);
    printString("-modifyuser: Cambia el nombre de usuario\n", 45);
    printString("-registers: Muestra el estado actual de los registros\n", 54);
    printString("-divzero: Excepcion de dividir por cero\n", 42); // NO VA
    printString("-invalidopcode: Excepcion de codigo de operacion invalido\n", 58);// NO VA
    printString("-snakes: Inicia el juego Snakes\n", 33);
    printString("-username: Muestra el nombre de usuario actual\n", 48);
    printString("-exit: Cierra la terminal\n", 27);
}

//Imprime el tiempo en pantalla
void command_time(){
    printString("Su hora actual es: ", 19);
    int segundos=gettingSeconds();
    int minutos=gettingMinutes();
    int horas=gettingHours();
    printInt(horas);
    putChar(':');
    printInt(minutos);
    putChar(':');
    printInt(segundos);
    putChar('\n');
}

//Limpia la terminal
void command_clear(){
    clearAll();
}

void command_modifyuser(){
    int c, size = 0;
    while((c = getChar()) != '\n' && size < USER_MAX){
        if( c != 0){//llamar al cursor
            if(c !='\b'|| size==0){
                if(c=='\b'){
                    size--;
                }else{
                USER[size] = c;
                size++;
                putChar(c);
                }
            }
        }
    }
    if(size >= USER_MAX){
        printString("Ingrese un nombre de usuario valido\n", 36);
        command_modifyuser();
        return;
    }
    else{
        USER[size] = '\0';
        USER_SIZE = size;
        putChar('\n');
        printString("Bienvenido ", 11);
        printString(USER, USER_SIZE);
        putChar('\n');
    }
}

//Imprimir el estado de todos los registros
void command_registers(){
    //sys_registers();
}

//Excepcion de dividir por cero
void command_divzero(){
    invokeDivZero();
}

//Excepcion de codigo de operacion invalido
void command_invalidopcode(){
    invokeOpCode();
}

void command_snakes(){
    //iniciar juego
}

void command_username(){
    printString("Su nombre de usuario es: ", 25);
    printString(USER, USER_SIZE);
    putChar('\n');
}

void command_exit(){
    printString("Muchas gracias por su visita :)\n", 31);
    on = 0;
}

//Lo que se pone al inicial la terminal
void entry(){
    printString("Bienvenidos al SO del Grupo 2 :)\n", 33);
    //scanf("Ingrese su nombre de usuario:\n");
    printString("Ingrese su nombre de usuario (maximo 32 caracteres): ", 53);
    command_modifyuser();
    printString("Para ver los comandos disponibles, escriba -help\n", 49);
}

void terminal(){
    //entry();
    printString("Ingrese un comando:\n", 21);
    while(on){
        putLine();
        printCursor();
        readLine();
        putChar('\n');
    }
    

}

void noCommand(){
    printString("Comando no encontrado. Escriba -help para ver los comandos disponibles\n", 70);
}

void readLine(){
    char c;
    int i = 0;
    while((c = getChar()) != '\n' && i < COMMAND_MAX){
        if( c != 0){//llamar al cursor
            if(c !='\b'|| i==0){
                if(c=='\b'){
                    i--;
                }
                else{
                    command[i] = c;
                    i++;
                }
                putChar(c);
            }
        }
    }
    checkCommand(command);
}

void checkCommand(char*  c){
    int i = 0;
    if(command[i] == '-'){
        check(i+1);
    }
    return;
}

void check(int i){
    for(int j = 0; j < TOTAL_COMMANDS; j++){
        if(commandList[j][0] == command[i]){
            if(strcmp(commandList[j], getCommand(i))){
                switch(j){
                    case 0:
                        command_help();
                        break;
                    case 1:
                        command_time();
                        break;
                    case 2:
                        command_clear();
                        break;
                    case 3:
                        command_modifyuser();
                        break;
                    case 4:
                        command_registers();
                        break;
                    case 5:
                        command_divzero();
                        break;
                    case 6:
                        command_invalidopcode();
                        break;
                    case 7:
                        command_snakes();
                        break;
                    case 8:
                        command_username();
                        break;
                    case 9:
                        command_exit();
                        break;
                    default:
                        noCommand();
                        break;
                }
            }
        }
    }
}

char * getCommand(int i){
    char * res ;
    for(int j = i, k = 0; (command[j] != ' ') && (command[j] != '\0'); j++, k++){
        res[k] = command[j];
    }
    return res;//corregir
}

void putLine(){
    printUserDef();
}


void printUserDef(){ //cambiar nombre
    printString(USER, USER_SIZE);
    printString(":~ $",3);
}

