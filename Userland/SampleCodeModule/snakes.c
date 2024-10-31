
#include "./include/snakes.h"
#define SQUARESIZE 32
//#define WIDTH 1024
//#define HEIGHT 768

void drawChart();



//variable global para los jugadores
char cantjug = 0;

int passengerX, passengerY;

int direc[4][2] = {
    {0, 1}, //derecha
    {0, -1}, //izquierda
    {1, 0}, //abajo
    {-1, 0} //arriba
};
/*
typedef struct player{
    char l; //si esta vivo
    int posX;
    int posY;
    int dirX;
    int dirY;
    int points;
    //faltaria el color
    char mapa[WIDTH][HEIGHT];  //mapea donde se esta moviendo el jugador
}player;

typedef struct player * TPlayer;
*/
TPlayer p1;
TPlayer p2;

//una idea seria que cada jugador tuviera su matriz donde se muestra dependiendo de sus puntos y como se fue moviendo cuanto y donde ocupa y se comparan matrices para ver si hay colision
//idea fea y aspera

void startGame(char jug){
    drawChart();
    if(jug == '1'){
        cantjug = 1;
        playGame1();
    }
    else{
        cantjug = 2;
        playGame2();
    }
    sleep(10);
    clearAll();
}


void drawChart(){
    uint64_t w; 
    uint64_t h;
    getWidth(&w);
    getHeight(&h);
    for (int row = 0; row <h/SQUARESIZE; row++) {
        for (int col = 0; col < w/SQUARESIZE; col++) {
            int x = col * SQUARESIZE;
            int y = row * SQUARESIZE;
            ColorT *color = (row + col) % 2 == 0 ? &RED : &ORANGE;
            drawRect(x, y, SQUARESIZE, SQUARESIZE, color);
        }
    }
}

void initializePlayer(TPlayer p){
    p->posX = 0;
    p->posY = 0;
    p->dirX = 1;
    p->dirY = 0;
    p->points = 0;
    p->l = 1;
    p->vagones[0][0] = p->posX;
    p->vagones[0][1] = p->posY;
}

void initializePlayers(TPlayer p1, TPlayer p2){
    initializePlayer(p1);
    p2->posX = WIDTH;
    p2->posY = HEIGHT;
    p2->dirX = -1;
    p2->dirY = 0;
    p2->points = 0;
    p2->l = 1;
    p2->vagones[0][0] = p2->posX;
    p2->vagones[0][1] = p2->posY;
}


void playGame1(){
    initializePlayer(p1);
    while(p1->l){
        movePlayer(p1);
    }
}

void playGame2(){
    initializePlayers(p1, p2);
    while(p1->l && p2->l){
        movePlayer(p1);
        movePlayer(p2);
    }
    if(!p1->l){
        printString("Gano el jugador 2\n",18);
    }
    else{
        printString("Gano el jugador 1\n",18);
    }
}

//devulve 0 si no hay colision
int collision(TPlayer p){
    if(p->posX + p->dirX >= WIDTH * HEIGHT || p->posY + p->dirY >= WIDTH * HEIGHT){
        return 1;
    }
    else if(cantjug == 2 && crash(p)){
        return 1;
    }
    return 0;
}

//devuelve 1 si chocan
int crash(TPlayer p){
    for(int i = 0; i < (WIDTH * HEIGHT); i++){
        for(int j = 0; j < (WIDTH * HEIGHT); j++){
            if(p1->mapa[i][j] == 1 && p2->mapa[i][j] == 1){
                p->l = 0;
                return 1;
            }
        }
    }
    return 0;
}

int checkPassenger(TPlayer p){
    if(p->posX == passengerX && p->posY == passengerY){
        return 1;
    }
    return 0;
}

void movePlayer(TPlayer p){
    if(collision(p)){
        p->l = 0;
    }
    else{
        if(checkPassenger(p)){
            addMap(p);
        }
        else{
            updateMap(p);
        }
    }
}

void updateMap(TPlayer p){

    for(int i = p->points; i > 0; i--){
        p->vagones[i][0] = p->vagones[i-1][0];
        p->vagones[i][1] = p->vagones[i-1][1];
    }

    p->posX += p->dirX;
    p->posY += p->dirY;
    p->vagones[0][0] = p->posX;
    p->vagones[0][1] = p->posY;

    for(int i = 0; i < p->points; i++){
        p->mapa[p->vagones[i][0]][p->vagones[i][1]] = 1;
    }

}

void addMap(TPlayer p){
    p->points++;
    p->mapa[p->posX][p->posY] = 1;
}

void setDirection(TPlayer p, int dir){
    p->dirX = direc[dir][0];
    p->dirY = direc[dir][1];

}

static int random(){
    return gettingSeconds();
}

void setPassenger(){
    passengerX = random() % (WIDTH * HEIGHT);
    passengerY = random() % (WIDTH * HEIGHT);
}



