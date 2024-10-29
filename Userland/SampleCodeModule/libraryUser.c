#include <stdint.h>
#include "./include/libraryUser.h"
#include "./include/syscalls_user.h"
#include "./include/exceptions_user.h"


static ColorT DEFAULT_COLOR_FND=BLACK;
static ColorT DEFAULT_COLOR_FTE=WHITE;
static void pasoHexa(uint64_t num1, char buffer[16]);

static char *registros64[17] = {
	"RIP", "RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "RSP", "R8 ", "R9 ", "R10", "R11", "R12", "R13", "R14", "R15"};


void playNota(uint64_t freq, uint64_t time){
    sys_sound(freq, time);
}

void playMusic(NotaT * music, int duration){
    for(int i = 0; i < duration; i++){
        playNota(music[i].frec, music[i].time);
    }
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
    char hexbuf[19];
	hexbuf[0] = '0';
	hexbuf[1] = 'x';
	hexbuf[18] = '\0';
	uint64_t infoRegistros[17];
    uint64_t flag=0;
	int i=sys_registers(infoRegistros, &flag);
	putChar('\n');
	if (flag==1){
		for (int i = 0; i < 17; i++)
		{
			printString(registros64[i], 3);
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
		printString("\nERROR: presionar primero la tecla Ctrl\n", 47);
	}
}


void printString(char * string, int length){
    printStringColor(string,length,&DEFAULT_COLOR_FTE,&DEFAULT_COLOR_FND);
}

void printStringColor(char * string, int length, ColorT* colorFte, ColorT* colorFdo){
    sys_write(1,string, length,colorFte,colorFdo); //mando 1 porque es la salida estandar
}

void putChar(char c){
    char * c1 = &c;
    printString(c1,1);
}

char getChar(){
    char c;
    printCursor();
    sys_read(0,&c, 1); //mando 0 porque es la entrada estandar
    //sleep(2); // no esta definido
    
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
    return sys_seconds();
}

int gettingMinutes(){
    return sys_minutes();
}

int gettingHours(){
    return sys_hours();
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

void drawRect(uint64_t x,uint64_t y,uint64_t x2,uint64_t y2, ColorT* colorToPaint){
    sys_drawRectangle(x,y,x2,y2,colorToPaint);
}

void getWidth(uint64_t* w){
    sys_width(w);
}
void getHeight(uint64_t* h){
    sys_height(h);
}



