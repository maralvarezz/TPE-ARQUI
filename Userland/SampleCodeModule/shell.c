#include "./include/shell.h"


#define USER_MAX 32 
#define COMMAND_MAX 150
#define BUFFER 300
#define TOTAL_COMMANDS 12

int on = 1;

int first = 1;
char command[COMMAND_MAX] = {0};

char * commandList[] = {"-help", "-time", "-clear", "-modifyuser", "-registers", "-divzero", "-invalidopcode", "-snakes", "-reducesize", "-increasesize", "-username", "-exit"};

int USER_SIZE = 5;
char USER[USER_MAX] = "guest";


void command_help(){
    printString("\nLista de comandos disponibles:\n", 32);
    printString("-help: Muestra la lista de comandos disponibles\n", 50);
    printString("-time: Muestra la hora actual\n", 30);
    printString("-clear: Limpia la terminal\n", 27);
    printString("-modifyuser: Cambia el nombre de usuario\n", 45);
    printString("-registers: Muestra el estado actual de los registros\n", 54);
    printString("-divzero: Excepcion de dividir por cero\n", 42); 
    printString("-invalidopcode: Excepcion de codigo de operacion invalido\n", 58);
    printString("-snakes: Inicia el juego Snakes\n", 33);
    printString("-reducesize: Reduce el tamaño de la letra\n", 45);
    printString("-increasesize: Aumenta el tamaño de la letra\n", 49);
    printString("-username: Muestra el nombre de usuario actual\n", 48);
    printString("-exit: Cierra la terminal", 26);
}

void command_time(){
    putChar('\n');
    printString("Su hora actual es: ", 19);
    int hours=gettingHours();
    printInt(hours);
    putChar(':');
    int minutes=gettingMinutes();
    printInt(minutes);
    putChar(':');
    int seconds=gettingSeconds();
    printInt(seconds);
}

void command_clear(){
    clearAll();
}

void command_modifyuser(){
    int c=0, size = 0;
    putChar('\n');
    printString("Ingrese su nombre de usuario (maximo 32 caracteres): ", 53);
    while((c = getChar()) != '\n' && size < USER_MAX){
        if(c!=0){
            if(c == '\b' && size > 0){
                size--;
                putChar('\b');
                putChar(' ');
                putChar('\b');
            }
            else if(c != '\b'){
                USER[size] = c;
                size++;
                putChar(c);
            }
        }
    }
    if(size >= USER_MAX){
        printString("\nIngrese un nombre de usuario valido", 36);
        command_modifyuser();
        return;
    }
    else{
        USER[size] = '\0';
        USER_SIZE = size;
        putChar('\n');
        printString("Bienvenido ", 11);
        printString(USER, USER_SIZE);
    }
}

void command_registers(){
    printRegisters();
}

void command_divzero(){
    invokeDivZero();
}

void command_invalidopcode(){
    invokeOpCode();
}

void command_snakes(){
    putChar('\n');
    printString("Bienvenido a SNAKES, para moverte usa W-A-S-D (Juador 1) o I-J-K-L (Jugador 2)\n", 79);
    printString("Ingrese el numero de jugadores (1-2):",37);
    char jug;
    while((jug = getChar()) != '1' && jug != '2'){
        
    }
    startGame(jug);
}

void command_username(){
    putChar('\n');
    printString("Su nombre de usuario es: ", 25);
    printString(USER, USER_SIZE);
    putChar('\n');
}

void command_exit(){
    putChar('\n');
    printString("Muchas gracias por su visita :)\n", 31);
    on = 0;
}

void command_reducesize(){
    clearAll();
    reduceSize();
}

void command_increasesize(){
    clearAll();
    increaseSize();
}

void entry(){
    if(first){
        first = 0;
        printString("Bienvenidos al SO del Grupo 2 :)", 32);
        command_modifyuser();
        printString("\nPara ver los comandos disponibles, escriba -help\n", 49);
    }
}

void terminal(){
    printString("\nIngrese un comando:\n", 21);
    while(1 && on){
        putLine();
        printCursor();
        readLine();
        putChar('\n');
    }
}

void noCommand(){
    putChar('\n');
    printString("Comando no encontrado. Escriba -help para ver los comandos disponibles\n", 70);
}

void readLine(){
    char c;
    int i = 0;

    while((c = getChar()) != '\n' && i < COMMAND_MAX) {
        if( c != 0){
            if(c == '\b' && i > 0){
                i--;
                putChar('\b');
                putChar(' ');
                putChar('\b');
            }
            else if(c != '\b'){
                command[i] = c;
                i++;
                putChar(c);
            }
        }
    }
    command[i] = '\0';
    checkCommand(command);
}

void checkCommand(char*  c){
    if(command[0] == '-'){
        check();
    }
    return;
}

void check(){
    for(int j = 0; j < TOTAL_COMMANDS; j++){
        if(strcmp(commandList[j], command) == 0){
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
                        command_reducesize();
                        break;
                    case 9:
                        command_increasesize();
                        break;
                    case 10:
                        command_username();
                        break;
                    case 11:
                        command_exit();
                        break;
                    default:
                        noCommand();
                        break;
                }
            return;
        }
    }
    noCommand();
}

void putLine(){
    printUserDef();
}


void printUserDef(){
    printStringColor(USER, USER_SIZE,&GREEN,&BLACK);
    printString(":~ $",3);
}

