
#include "./include/snakes.h"
//#define SQUARESIZE 32
//#define WIDTH 1024
//#define HEIGHT 768



void drawChart();
int eatItSelf(TPlayer p);

static const ColorT * color1 = &DARK_GREEN;
static const ColorT * color2 = &GREEN;
//variable global para los jugadores
char cantjug = 0;

int passengerX, passengerY;

int direc[4][2] = {
    {0, 1}, //abajo
    {0, -1}, //arriba
    {1, 0}, //derecha
    {-1, 0} //izquierda
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
player player1,player2;
TPlayer p1,p2;


void startGame(char jug){
    drawChart();
    p1= &player1;
    p2= &player2;
    if(jug == '1'){
        cantjug = 1;
        playGame1();
    }
    else{
        cantjug = 2;
        playGame2();
    }
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
            const ColorT *color = (row + col) % 2 == 0 ? color1 : color2;
            drawRect(x, y, SQUARESIZE, SQUARESIZE, color);
        }
    }
}

void initializePlayer(TPlayer p){
    if(p!=0){
        p->posX = 0;
        p->posY = 0;
        p->dirX = 1;
        p->dirY = 0;
        p->points = 0;
        p->l = 1;
        p->vagones[0][0] = p->posX;
        p->vagones[0][1] = p->posY;
        p -> pColor = &RED;
    }
}

void initializePlayers(TPlayer p1, TPlayer p2){
    initializePlayer(p1);
    p2->posX = WIDTH/SQUARESIZE - 1;
    p2->posY = HEIGHT/SQUARESIZE - 1;
    p2->dirX = -1;
    p2->dirY = 0;
    p2->points = 0;
    p2->l = 1;
    p2->vagones[0][0] = p2->posX;
    p2->vagones[0][1] = p2->posY;
    p2->pColor= &BLUE;
}


void playGame1(){
    initializePlayer(p1);
    setPassenger();
    char c;
    while(p1->l){
        sleep(3);
        if((c = peekChar()) != 0){
            c= toLower(c);
            switch(c){
                case 'w':
                    setDirection(p1, 1);
                    break;
                case 's':
                    setDirection(p1, 0);
                    break;
                case 'a':
                    setDirection(p1, 3);
                    break;
                case 'd':
                    setDirection(p1, 2);
                    break;
            }
        }
        movePlayer(p1);
    }
}

void playGame2(){
    initializePlayers(p1, p2);
    if(p1==p2){
        printStringColor("LOS 2 SON LO MISMO",18,&RED, &BLACK );
    }
    setPassenger();
    char c;
    while(p1->l && p2->l){
        sleep(3);
        if((c = peekChar()) != 0){
            c= toLower(c);
            switch(c){
                case 'w':
                    setDirection(p1, 1);
                    break;
                case 's':
                    setDirection(p1, 0);
                    break;
                case 'a':
                    setDirection(p1, 3);
                    break;
                case 'd':
                    setDirection(p1, 2);
                    break;
                case 'i':
                    setDirection(p2, 1);
                    break;
                case 'k':
                    setDirection(p2, 0);
                    break;
                case 'j':
                    setDirection(p2, 3);
                    break;
                case 'l':
                    setDirection(p2, 2);
                    break;
            }
        }
        movePlayer(p1);
        movePlayer(p2);
    }
    if(!p1->l && !p2->l ){
        printString("Pierden ambos jugadores\n",24);
    }
    else if(p2->l){
        printString("Gano el jugador 2\n",18);
    }else{
        printString("Gano el jugador 1\n",18);
    }
    sleep(20);
}

//devulve 0 si no hay colision
int collision(TPlayer p){
    if(p->posX + p->dirX >= WIDTH/SQUARESIZE || p->posX + p->dirX  < 0 
    || p->posY + p->dirY >= HEIGHT/SQUARESIZE || p->posY + p->dirY < 0
    || eatItSelf(p)){
        return 1;
    }
    else if(cantjug == 2 && crash(p)){
        return 1;
    }
    return 0;
}

int eatItSelf(TPlayer p){
    for(int i = p->points; i>0;i--){
        if(p->vagones[i][0] == p->posX){
            if(p->vagones[i][1] == p->posY){
                return 1;
            }
        }
    } 
    return 0;
}

//devuelve 1 si chocan
int crash(TPlayer p){
    if(p1->posX==p2->posX && p1->posY==p2->posY){
        p1->l = 0;
        p2->l = 0;
        return 1;
    }
    for(int i = 0; i < (WIDTH/SQUARESIZE); i++){
        for(int j = 0; j < (HEIGHT/SQUARESIZE); j++){
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
        playNota(150,10);
        setPassenger();
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
    p->mapa[p->vagones[p->points][0]][p->vagones[p->points][1]] = 0;//update de la cola en el mapa
    int x,y;
    x=p->vagones[p->points][0];
    y= p->vagones[p->points][1];
    const ColorT *color = (x + y) % 2 == 0 ? color1 : color2;
    x*=SQUARESIZE;
    y*=SQUARESIZE;
    drawRect(x,y,SQUARESIZE,SQUARESIZE,color); //dibujo el cuadrado que corresponde al fondo de la cola borrada

    for(int i = p->points; i > 0; i--){
        p->vagones[i][0] = p->vagones[i-1][0];
        p->vagones[i][1] = p->vagones[i-1][1];
    } // update del vector de posiciones de los vagones

    p->posX += p->dirX;
    p->posY += p->dirY;
    p->vagones[0][0] = p->posX;
    p->vagones[0][1] = p->posY;
    //update del primero
    drawRect(p->posX*SQUARESIZE,p->posY*SQUARESIZE,SQUARESIZE,SQUARESIZE,p->pColor);
    for(int i = 0; i < p->points; i++){ // update del mapa
        p->mapa[p->vagones[i][0]][p->vagones[i][1]] = 1;
    }
}

void addMap(TPlayer p){
    p->points++;
    p->mapa[p->posX][p->posY] = 1;
    drawRect(p->posX*SQUARESIZE,p->posY*SQUARESIZE,SQUARESIZE,SQUARESIZE,p->pColor);
}

void setDirection(TPlayer p, int dir){
    // si el jugador no es solo la cabeza, o la direccion nueva es valida, actualizo la direccion
    if(p->points!=0 && ((p->dirX == 0 && direc[dir][0]==0) || (p->dirY == 0 && direc[dir][1]==0))){
        return;
    }

    p->dirX = direc[dir][0];
    p->dirY = direc[dir][1];
}


static int random(){
    return gettingSeconds();
}

void setPassenger(){
    passengerX = random() % (WIDTH/SQUARESIZE);
    passengerY = random() % (HEIGHT/SQUARESIZE);
    drawRect(passengerX*SQUARESIZE,passengerY*SQUARESIZE,SQUARESIZE,SQUARESIZE,&ORANGE);
}



