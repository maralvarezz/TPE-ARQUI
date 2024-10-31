#include "../include/keyboard.h"

#define BUFFER_MAX 256

extern char getKey();
extern void guardar_registros();

unsigned char teclaPressed = 0;
int bloqMayus = 0;
int shift = 0;
char BUFFER[BUFFER_MAX] = {0};
unsigned char ctrl=0;

int w = 0, r = 0;



static const char vecMay[] = {
      0,   27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
   '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
   '\n',    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
      0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0, '*',
      0, ' ',    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,    0,   0, '-',   0,   0,   0, '+',   0,   0,   0,   0,   0,
      0,   0,    0,   0,   0,   0
};

static const char vecMin[] = {
      0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
   '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']',
   '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
      0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   38,   0, '-',   37,   0,   39, '+',   0,   40,   0,    0,   0,
      0,    0,   0,   0,   0,   0,   0,   0,  0,    0,   0,   0,    0,   0,

};


static const char * mapLetras[] = {vecMin,vecMay};

//nos entra la tecla que se oprimió
void keyboard_handler(){
    teclaPressed = getKey();
    if(((teclaPressed) <= 0x79) || teclaPressed == 0xAA || teclaPressed == 0xB6 ){
        //shift oprimido
        if (teclaPressed == 0x2A || teclaPressed == 0x36){
            shift = 1;
        }
        //shift no oprimido
        if (teclaPressed == 0xAA || teclaPressed == 0xB6) {
            shift = 0;
        }
        //tecla ctrl oprimida
        if(teclaPressed == 0x1D){
            ctrl=1;
            guardar_registros();
        }
        //bloq mayus oprimido
        if (teclaPressed == 0x3A) {
            bloqMayus = (bloqMayus+1)%2; //si esta en 1 lo pongo en 0 y viceversa
        }
        addBuffer();
    }
}

void addBuffer(){
    if(w >= BUFFER_MAX){
        w = 0;
    }
    BUFFER[w++] = getKeyboard();
}

uint64_t getCtrlFlag(){
    uint64_t resp=ctrl;
    ctrl=0;
    return resp;
}

char getBuffer(){
    if(r == w){
        return 0;
    }
    if(r >= BUFFER_MAX){
        r = 0;
    }
    return BUFFER[r++];
}


char getKeyboard(){
    if(isLetter(teclaPressed)){
        return mapLetras[(bloqMayus+shift)%2][(int)teclaPressed];
    }
    return mapLetras[shift][(int)teclaPressed];
}

//nos dice si la tecla es una letra
int isLetter(char key){
    int flag = 0;
    if((key <= 0x19 && key >= 0x10) || (key <= 0x26 && key >= 0x1E) || (key <= 0x32 && key >= 0x2C)){
        flag=1;
    }
    return flag;
}