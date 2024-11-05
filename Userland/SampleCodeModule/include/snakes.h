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

/**
 * Setea la escala.
 */
void setScale(int n);

/**
 * Imprime el puntaje.
 */
void printScore(TPlayer p);

/**
 * Imprime al ganador.
 */
void printWinner(int n);

/**
 * Imprime puntuación final en modo un jugador.
 */
void printEndGame1();

/**
 * Comienza el juego con cantidad 'jug' de jugadores.
 */
void startGame(char jug);

/**
 * Dibuja el tablero.
 */
void drawChart();

/**
 * Inicializa un jugador.
 */
void initializePlayer(TPlayer p);

/**
 * Inicializa a los dos jugadores.
 */
void initializePlayers(TPlayer p1, TPlayer p2);

/**
 * Juego para un solo jugador.
 */
void playGame1();

/**
 * Juego para dos jugadores.
 */
void playGame2();

/**
 * Mueve al jugador.
 */
void movePlayer(TPlayer p);

/**
 * Actualiza el mapa del jugador.
 */
void updateMap(TPlayer p);

/**
 * Agrega una posición al mapa del jugador.
 */
void addMap(TPlayer p);

/**
 * Setea la dirección del jugador.
 */
void setDirection(TPlayer p, int dir);

/**
 * Setea el pasajero.
 */
void setPassenger();

/**
 * Chequea si hay colisión. Devuelve 0 si no hay colisión.
 */
int collision(TPlayer p);

/**
 * Dibuja al pasajero.
 */
void drawPassenger();

/**
 * Chequea si el jugador pasó por el pasajero. Devuelve 1 si pasó por el pasajero.
 */
int checkPassenger(TPlayer p);

/**
 * Chequea si el jugador chocó. Devuelve 1 si chocó.
 */
int crash(TPlayer p);

/**
 * Chequea si el jugador se comió a sí mismo. Devuelve 1 si se comió a sí mismo.
 */
int eatItSelf(TPlayer p);
