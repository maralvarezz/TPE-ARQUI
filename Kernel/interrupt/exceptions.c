#include "../include/exceptions.h"


#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 1
#define REGISTERS 18

static void zero_division();
static void opcode_exception();


extern const uint64_t exceptionRegs[REGISTERS];
static char * regs[REGISTERS] = {
"RAX","RBX","RCX","RDX","RSI","RDI","RBP","R8","R9","R10","R11","R12","R13","R14","R15", "RSP","RIP", "RFLAGS"
};


void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if(exception == OPCODE_EXCEPTION_ID)
		opcode_exception();
}

//esto no va acá pero lo dejo hasta que le preguntemos a Fede
void print_registers() { //fijarnos como imprimir
	for (int i = 0; i < 18; i++) {
		print(regs[i], 3);
		print(": ", 2);
		print(numToStr(exceptionRegs[i], 18),18);
		print("\n",1);
	}
}

static void zero_division() {
	print("ZERO DIVISION EXCEPTION\n", 22);
	print_registers();
	print("\n",1);
}

static void opcode_exception() {
	print("OPCODE EXCEPTION\n", 17);
	print_registers();
	print("\n",1);
}

