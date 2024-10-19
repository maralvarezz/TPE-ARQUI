

global backupRegs

extern keyboard.c

%macro pushReg 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popReg 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

interrupcion_teclado:
    pushReg
    xor rax, rax //limpio rax
    in al, 0x60 //leo el scancode
    cmp al, 0x2A //veo si es la tecla shift
    mov byte [rsi], 1 //puedo usar acá rsi??



section .bss 

    backupRegs resq 17 //basicamente lo que hacemos con esto es mantener los registros que se usan en la interrupcion para que no se pierdan