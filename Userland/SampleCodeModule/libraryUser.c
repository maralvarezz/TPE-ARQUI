#include <stdint.h>
#include "./include/libraryUser.h"
#include "./include/syscalls_user.h"
#include "./include/exceptions_user.h"

#define DIFFHOUR 3


static const ColorT DEFAULT_COLOR_FND=BLACK;
static const ColorT DEFAULT_COLOR_FTE=WHITE;
static void pasoHexa(uint64_t num1, char buffer[16]);

static char *registros64[19] = {"RAX","RBX","RCX","RDX","RSI","RDI","RBP","R8","R9","R10","R11","R12","R13","R14","R15","RIP","CS","RFLAGS", "RSP"};


void playNota(uint64_t freq, uint64_t time){
    sys_sound(freq, time);
}


static void pasoHexa(uint64_t num1, char buffer[16]){
	int i = 15;
	do
	{
		int num2 = num1 % 16;
		buffer[i] = (num2 < 10 ? '0' : ('A' - 10)) + num2;
		num1 /= 16;
	} while (i-- != 0);
}

void printRegisters(){
    putChar('\n');
    char hexbuf[19];
	hexbuf[0] = '0';
	hexbuf[1] = 'x';
	hexbuf[18] = '\0';
	uint64_t infoRegistros[19];
    uint64_t flag=0;
	sys_registers(infoRegistros, &flag);
	if (flag==1){
		for (int i = 0; i < 19; i++)
		{
			printString(registros64[i], strlen(registros64[i]));
			printString(": ", 1);
            pasoHexa(infoRegistros[i], hexbuf + 2);
            printString(hexbuf, 18);
			if (i % 4 == 3)
				putChar('\n');
			else
				printString("   ", 3);
		}
	}
	else
	{
		printString("ERROR: presionar primero la tecla Ctrl", 46);
	}
}


void printString(char * string, int length){
    printStringColor(string,length,&DEFAULT_COLOR_FTE,&DEFAULT_COLOR_FND);
}

void printStringColor(char * string, int length, const ColorT* colorFte,const ColorT* colorFdo){
    sys_write(1,string, length,colorFte,colorFdo);
}

void putChar(char c){
    char * c1 = &c;
    printString(c1,1);
}

char getChar(){
    char c;
    printCursor();
    sys_read(0,&c, 1);
    
    return c;
}

char peekChar(){
    char c;
    sys_read(0,&c, 1);
    return c;
}

void clearAll(){
    sys_clear();
}

void sleep(uint64_t time){
    sys_wait(time);
}

int strcmp(const char * str1, const char * str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return -1;
        }
        i++;
    }
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 0;
    }
    return 1;
}

int strlen(char * str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

void printCursor(){
    sys_cursor();
    return;
}

void invokeOpCode(){
    putChar('\n');
    exc_invalidopcode();
}

void invokeDivZero(){
    putChar('\n');
    exc_divzero();
}

int gettingSeconds(){
    uint64_t seconds;
    sys_seconds(&seconds);
    return seconds;
}

int gettingMinutes(){
    uint64_t minutes;
    sys_minutes(&minutes);
    return minutes;
}

int gettingHours(){
    uint64_t hours;
    sys_hours(&hours);
    return hours-DIFFHOUR;
}

void printInt(int num) {
    char buffer[12]; // Suficiente para almacenar int de 32 bits con signo
    int i = 0;
    if (num == 0) {
        putChar('0');
        return;
    }
    if (num < 0) {   // Maneja el signo
        putChar('-');
        num = -num;
    }
    while (num > 0) { // Convierte el número a caracteres
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    // Imprime el número en el orden correcto
    for (int j = i - 1; j >= 0; j--) {
        putChar(buffer[j]);
    }
}

void printIntColor(int num,const ColorT* c1,const ColorT* c2){
    char buffer[12]; // Suficiente para almacenar int de 32 bits con signo
    int i = 0;
    if (num == 0) {
        printStringColor("0",1,c1,c2);
        return;
    }
    if (num < 0) {   // Maneja el signo
        printStringColor("-",1,c1,c2);
        num = -num;
    }
    while (num > 0) { // Convierte el número a caracteres
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    // Imprime el número en el orden correcto
    for (int j = i - 1; j >= 0; j--) {
        printStringColor(buffer+j,1,c1,c2);
    }
}

void drawRect(uint64_t x,uint64_t y,uint64_t x2,uint64_t y2,const ColorT* colorToPaint){
    sys_drawRectangle(x,y,x2,y2,colorToPaint);
}

void getWidth(uint64_t* w){
    sys_width(w);
}

void getHeight(uint64_t* h){
    sys_height(h);
}

void reduceSize(){
    sys_reduceSize();
}

void increaseSize(){
    sys_increaseSize();
}

char toLower(char c){
    if(c>='A' && c<='Z'){
        return c + 'a'-'A' ;
    }
    return c;
}

void setCursorX(uint64_t x){
    sys_cursorSetterX(x);
}

void setCursorY(uint64_t y){
    sys_cursorSetterY(y);
}

void moveCursor(uint64_t x,uint64_t y){
    setCursorY(y);
    setCursorX(x);
}

int getPixelSize(){
    uint64_t size;
    sys_pixelSize(&size);
    return size;
}
