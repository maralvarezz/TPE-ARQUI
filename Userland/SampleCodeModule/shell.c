#include 

char USER[USER_MAX] = "user";
uint8_t USER_MAX = 32, USER_SIZE = 4;


//Imprime el tiempo en pantalla
void command_time(){
    printTime(); //ver como llamarlo
}

//Menu de comandos disponibles
void command_help(){

}

//Lo que se pone al inicial la terminal
void entry(){
    int c, size = 0;
    print("Bienvenidos al SO del Grupo 2 :)\n");
    //scanf("Ingrese su nombre de usuario:\n");
    print("Ingrese su nombre de usuario:\n");
    char aux[2]={0};
    while((c = getChar()) != '\n' && size < USER_MAX){
        //lamar al cursor
        USER[size] = c;
        size++;
        aux[0] = c;
        print(aux, 1);
    }
    USER[size] = '\0';
    USER_SIZE = size;
}

//Limpia la terminal
void command_clear(){
    sys_clear();
}

void printUserDef(){ //cambiar nombre
    print(USER, USER_SIZE);
    print(":~ $",3);
}