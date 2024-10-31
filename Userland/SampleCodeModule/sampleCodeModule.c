/* sampleCodeModule.c */
#include "./include/shell.h"


int main() {
    entry();
    terminal();
    
     /*for (int row = 0; row < 1000/SQUARESIZE; row++) {
        for (int col = 0; col < 1000/SQUARESIZE; col++) {
            int x = col * SQUARESIZE;
            int y =20 + row * SQUARESIZE;
            ColorT *color = (row + col) % 2 == 0 ? &DARK_BLUE : &VIOLET;
            drawRect(x, y, SQUARESIZE, SQUARESIZE, color);
        }
    }*/
    //printStringColor("HOLA MUNDO PERO EN ROJO",23,&RED, &BLACK);
    //printStringColor("HOLA MUNDO PERO EN ROJO",23,&RED, &WHITE);
    //printStringColor("HOLA MUNDO PERO EN ROJO",23,&RED, &GREEN);
    //printStringColor("HOLA MUNDO PERO EN VERDE",24,&GREEN, &BLACK);
    
    return 0;
}