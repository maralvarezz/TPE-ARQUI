include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
ASM_SOURCES=$(wildcard asm_user/*.asm)
ASM_OBJECTS=$(ASM_SOURCES:asm_user/%.asm=obj/%.asm.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(ASM_OBJECTS)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c $(SOURCES) $(ASM_OBJECTS) -o ../$(MODULE)

obj/%.asm.o : asm_user/%.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@
	
clean:
	rm -rf *.o
	rm -rf obj

.PHONY: all clean print
