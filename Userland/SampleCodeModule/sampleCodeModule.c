/* sampleCodeModule.c */
/*
#include "libraryC.h"
char * v = (char*)0xB8000 + 80 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {

	printTime(v);
	//corrige donde se ve en consola
	v+=16;
	while(1){
		*v++ = keyboard_handler();
		*v++ = 0x3F;
	}
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
*/