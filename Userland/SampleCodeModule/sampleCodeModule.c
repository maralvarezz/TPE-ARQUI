/* sampleCodeModule.c */
/*#include "./include/shell.h"
#define SQUARESIZE 50

ColorT color1={0xB6, 0xE8, 0xE4};
ColorT color2={0xCD,0xF4,0xF1};
int main() {
    //entry();
    //terminal();
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


    return 0;
}
*/

#include "./include/shell.h"
#define SQUARESIZE 50
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
//HAY QUILOMBO DE COLORES
ColorT color1 = {1,0,0};
ColorT color2 = {0,0,0};

void drawGrid() {
    int rows = SCREEN_HEIGHT / SQUARESIZE;
    int cols = SCREEN_WIDTH / SQUARESIZE;
    int row=0;
    /*for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int x = col * SQUARESIZE;
            int y = row * SQUARESIZE;
            if(col%2){
                drawRect(0, y, SQUARESIZE, SQUARESIZE, &color1);    
            }else{
                drawRect(0, y, SQUARESIZE, SQUARESIZE, &color2);
            }
            //ColorT color = row % 2 == 0 ? color1 : color2;
            
        }
    }*/



    drawRect(0, 0, SQUARESIZE, SQUARESIZE, &color2);
    drawRect(0, 50, SQUARESIZE, SQUARESIZE, &color1);
    drawRect(0, 100, SQUARESIZE, SQUARESIZE, &color2);
    drawRect(0, 150, SQUARESIZE, SQUARESIZE, &color1);
    drawRect(0, 200, SQUARESIZE, SQUARESIZE, &color2);
}

int main() {
    drawGrid();
    return 0;
}
