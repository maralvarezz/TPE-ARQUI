#include "./include/snakes.h"


void startGame(char jug){
    if(jug == '1'){
       // playGame1();
    }
    else{
        //playGame2();
    }
}

/*
//variable global para los jugadores
char cantjug;

int passengerX, passengerY;

int direc[4] = {
    {0, 1}, //derecha
    {0, -1}, //izquierda
    {1, 0}, //abajo
    {-1, 0} //arriba
}

typedef struct player{
    int posX;
    int posY;
    int dirX;
    int dirY;
    int points;
    //faltaria el color
}player;

typedef struct player * TPlayer;

    void playGame1(){
        char l = 1;
        TPlayer p1;
        while(l){
            movePlayer(p1);
        }
    }

    void playGame2(){
        char l1 = 1, l2 = 1;
        TPlayer p1, p2;
        while(l){
            movePlayer(p1);
            movePlayer(p2);
        }
    }

    //devulve 0 si no hay colision
    int collision(TPlayer p){
        if(p->posX + p->dirX >= BOARD_SIZE || p->posY + p->dirY >= BOARD_SIZE){
            return 1;
        }
        else if(cantjug == 2 && // fijarse colision con otro jugador){
            //una idea seria que cada jugador tuviera su matriz donde se muestra dependiendo de sus puntos y como se fue moviendo cuanto y donde ocupa y se comparan matrices para ver si hay colision
            //idea fea y aspera
            return 1;
        }
        return 0;
    }

    int checkPassenger(TPlayer p){
        if(p->posX == passengerX && p->posY == passengerY){
            return 1;
        }
    }

    void movePlayer(TPlayer p){
        if(collision(p)){
            l = 0;
        }
        else{
            if(checkPassenger(p)){
                p->points++;
            }
            p->posX += p->dirX;
            p->posY += p->dirY;
        }
    }

    void setDirection(TPlayer p, int dir){
        p->dirX = direc[dir][0];
        p->dirY = direc[dir][1];

    }

    static int random(){
        return gettingSeconds();
    }

    void setPassenger(){
        passengerX = random() % BOARD_SIZE;
        passengerY = random() % BOARD_SIZE;
    }


*/


