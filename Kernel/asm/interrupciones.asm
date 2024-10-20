global backupRegs
global interrupt_syscall

extern keyboard_handler
extern sysCaller
extern exceptionsCaller


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
    jne .shift
    mov byte [shiftFlag], 1 //pongo la flag del shift en 1

.shift:
	cmp al, 0xAA //veo si se solto la tecla shift
	jne.handle_keyboard 
	mov byte [shiftFlag], 0 //pongo la flag del shift en 0

//aca vamos a tener que completar con lo que querramos que haga si se presiona el shift

.handle_keyboard:
	call keyboard_handler
	mov al, 0x20
	out 0x20, al
	popReg
	iretq

interrupt


interrupt_syscall:
    pushReg
    mov rbp, rsp
    mov rcx, r10  //como en el modo usuario el cuarto parametro se pasa por r10, lo guardamos en rcx para que reciba el valor adecuado
    mov r9, rax   
    call sysCaller
    mov rsp, rbp
    popReg
    iretq


section .bss
	shiftFlag resb 1 //variable que se usa para saber si se presiono shift
    backupRegs resq 17 //basicamente lo que hacemos con esto es mantener los registros que se usan en la interrupcion para que no se pierdan