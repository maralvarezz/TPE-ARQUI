#include <stdio.h>

char 


static const char vecMin[] = {

      0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
    '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']',
    '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
      0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   38,   0, '-',   37,   0,   39, '+',   0,   40,   0,    0,   0,
      0,    0,   0,   0,   0,   0,   0,   0,  0,    0,   0,   0,    0,   0,

};

static const char vecMay[] = {

      0,   27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
   '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
   '\n',    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
      0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0, '*',
      0, ' ',    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,    0,   0, '-',   0,   0,   0, '+',   0,   0,   0,   0,   0,
      0,   0,    0,   0,   0,   0

};
static const char mapLetras[][] = {vecMin,vecMay};

char getKeyboard(){

}

// chequear 
void keyboard_handler(uint8_t keyPressed) {
    notChar = keyPressed;
    //shift pressed
    if (notChar == 0x2A  notChar == 0x36){
        shift = 1;
    }
    //shift not pressed
    if (notChar == 0xAA  notChar == 0xB6) {
        shift = 0;
    }
    //capsLock
    if (notChar == 0x3A) {
        capsLock = (capsLock+1)%2;
    }


}