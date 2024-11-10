#include <exceptions.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6
#define REGISTERS 19

static void zero_division();
static void opcode_exception();

extern const uint64_t exceptionRegs[REGISTERS];
static char * regs[REGISTERS] = {
"RAX","RBX","RCX","RDX","RSI","RDI","RBP","R8","R9","R10","R11","R12","R13","R14","R15","RIP","CS", "RFLAGS", "RSP"
};
static void pasoHexa(uint64_t num1, char buffer[16]);

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if(exception == OPCODE_EXCEPTION_ID)
		opcode_exception();
}

void print_registers() {
    char buffer[16];
    for (int i = 0; i < 19; i++) {
        print(regs[i], strleng(regs[i]));
        print(": ", 2);
        pasoHexa(exceptionRegs[i], buffer);
        print(buffer, 16);
        print("\n", 1);
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

static void zero_division() {
	print("ZERO DIVISION EXCEPTION\n", 24);
	print_registers();
	print("\n",1);
	return;
}

static void opcode_exception() {
	print("OPCODE EXCEPTION\n", 17);
	print_registers();
	print("\n",1);
	return;
}

