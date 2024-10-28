/* sampleCodeModule.c */
#include "./include/shell.h"
#define SQUARESIZE 50

ColorT color1={0xBB, 0xAA, 0x0A};
ColorT color2={0xAF,0xFA,0xAA};
int main() {
    entry();
    terminal();
    /*
     for (int row = 0; row < 1000/SQUARESIZE; row++) {
        for (int col = 0; col < 1000/SQUARESIZE; col++) {
            int x = col * SQUARESIZE;
            int y = row * SQUARESIZE;
            if((row+col)%2==0){
            drawRect(x, y, SQUARESIZE, SQUARESIZE, &color1);    
            }else{
                drawRect(x, y, SQUARESIZE, SQUARESIZE, &color2);
            }
            //ColorT *color = (row + col) % 2 == 0 ? &color1 : &color2;
            //drawRect(x, y, SQUARESIZE, SQUARESIZE, &color);
        }
    }
    */
    return 0;
}
