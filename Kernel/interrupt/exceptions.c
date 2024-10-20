#include "../inlcude/libraryC.h"


#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 1
#define REGISTERS 18

static void zero_division();
static void opcode:exception();

extern const uint64_t regsBackUp[REGISTERS];
static char * regs[REGISTERS] = {
"RAX","RBX","RCX","RDX","RSI","RDI","RBP","R8","R9","R10","R11","R12","R13","R14","R15", "RSP","RIP", "RFLAGS"
};


void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if(exception == OPCODE_EXCEPTION_ID)
		opcode_exception();
}

void print_registers() { //fijarnos como imprimir
	for (int i = 0; i < 18; i++) {
		print(regs[i], 3);
		print(": ", 2);
		print(numToStr(regsBackUp[i]), 18);
		putchar('\n');
	}
}

static void zero_division() {
	print("ZERO DIVISION EXCEPTION\n", 22);
	print_registers();
	putchar('\n');
}

static void opcode_exception() {
	print("OPCODE EXCEPTION\n", 17);
	print_registers();
	putchar('\n');
}

