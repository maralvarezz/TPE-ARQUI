#include 

char USER[USER_SIZE] = "user";


//Imprime el tiempo en pantalla
void command_time(){
    printTime(); //ver como llamarlo
}

//Menu de comandos disponibles
void command_help(){

}

//Lo que se pone al inicial la terminal
void entry(){
    print("Bienvenidos al SO del Grupo 2 :)\n");
    scanf("Ingrese su nombre de usuario:\n");
}

//Limpia la terminal
void command_clear(){
    sys_clear();
}

void printUserDef(){ //cambiar nombre
    print(USER, strlen(USER));
    print(":~ $",3);
}