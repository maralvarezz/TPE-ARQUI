#include "libraryUser.h"

#define WIDTH 1024
#define HEIGHT 768
#define MAX_VAGONES 100
#define SQUARESIZE 32

typedef struct player{
    char l; //si esta vivo
    int posX;
    int posY;
    int dirX;
    int dirY;
    int points;
    int vagones[MAX_VAGONES][2];
    const ColorT* pColor;
    char mapa[WIDTH/SQUARESIZE][(HEIGHT/SQUARESIZE)];  //mapea donde se esta moviendo el jugador
}player;

typedef struct player * TPlayer;

void startGame(char jug);

void drawChart();

void initializePlayer(TPlayer p);

void initializePlayers(TPlayer p1, TPlayer p2);

void playGame1();

void playGame2();

void movePlayer(TPlayer p);

void updateMap(TPlayer p);

void addMap(TPlayer p);

void setDirection(TPlayer p, int dir);

void setPassenger();

int collision(TPlayer p);

int checkPassenger(TPlayer p);

int crash(TPlayer p);