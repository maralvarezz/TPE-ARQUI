#include <stdint.h>

extern void _hlt();
char getKeyboard();
void keyboard_handler();
int isLetter(char key);
void addBuffer();
char getBuffer();
