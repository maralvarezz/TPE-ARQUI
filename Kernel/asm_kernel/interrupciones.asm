GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt
GLOBAL _irq00Handler

GLOBAL exception_zero_division
GLOBAL exception_op_code

GLOBAL backupRegs
GLOBAL syscallHandler
GLOBAL interrupcion_teclado
GLOBAL exceptionRegs
GLOBAL registros
GLOBAL registersFlag
GLOBAL guardar_registros

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN load_main
EXTERN keyboard_handler
EXTERN sysCaller
EXTERN exceptionsCaller

SECTION .text


%macro pushState 0
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

%macro popState 0
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

%macro backupRegs 1
    pushState
    mov [exceptionRegs + 0], rax
    mov [exceptionRegs + 8], rbx
    mov [exceptionRegs + 16], rcx
    mov [exceptionRegs + 24], rdx
    mov [exceptionRegs + 32], rsi
    mov [exceptionRegs + 40], rdi
    mov [exceptionRegs + 48], rbp
    mov [exceptionRegs + 56], r8
    mov [exceptionRegs + 64], r9
    mov [exceptionRegs + 72], r10
    mov [exceptionRegs + 80], r11
    mov [exceptionRegs + 88], r12
    mov [exceptionRegs + 96], r13
    mov [exceptionRegs + 104], r14
    mov [exceptionRegs + 112], r15
    mov rax, [rsp+120] ;Obtenemos el valor de RIP
	mov [exceptionRegs+120], rax
	mov rax, [rsp+128] ;Obtenemos el valor de CS
	mov [exceptionRegs+128], rax
	mov rax, [rsp+136] ;Obtenemos el valor de RFLAGS
	mov [exceptionRegs+136], rax
	mov rax, [rsp+144] ;Obtenemos el valor de RSP
	mov [exceptionRegs+144], rax
    mov rdi, %1 ;pasaje de parametro
	call exceptionDispatcher
	popState
	add rsp, 8 ;saco el error code de la pila
	push load_main ;vuelvo a la función main
	iretq
%endmacro

%macro irqHandlerMaster 1
	pushState
	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher
	;pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
	popState
	iretq
%endmacro

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

interrupcion_teclado: 
	mov [backupRegistros + 0], rax
	mov [backupRegistros + 8], rbx
	mov [backupRegistros + 16], rcx
	mov [backupRegistros + 24], rdx
	mov [backupRegistros + 32], rsi
	mov [backupRegistros + 40], rdi
	mov [backupRegistros + 48], rbp
	mov [backupRegistros + 56], r8
	mov [backupRegistros + 64], r9
	mov [backupRegistros + 72], r10
	mov [backupRegistros + 80], r11
	mov [backupRegistros + 88], r12
	mov [backupRegistros + 96], r13
	mov [backupRegistros + 104], r14
	mov [backupRegistros + 112], r15
	push rax
	mov rax, [rsp+8] ;cargo el rip
	mov [backupRegistros + 120], rax
	mov rax, [rsp+16] ;cargo el cs
	mov [backupRegistros + 128], rax
	mov rax, [rsp+24] ;cargo el rflags
	mov [backupRegistros + 136], rax
	mov rax, [rsp+32] ;cargo el rsp
	mov [backupRegistros + 144], rax
	pop rax
	pushState
	xor rax, rax ; limpio rax
.handle_keyboard:
	call keyboard_handler
	mov al, 0x20 ;EOI
	out 0x20, al
	popState
	iretq

guardar_registros:
	pushState
	mov rax, [backupRegistros + 0] ;cargo el rax
	mov [registros + 0], rax 
	mov rax, [backupRegistros + 8] ;cargo el rbx
    mov [registros + 8], rax
	mov rax, [backupRegistros + 16] ;cargo el rcx
    mov [registros + 16], rax
	mov rax, [backupRegistros + 24] ;cargo el rdx
    mov [registros + 24], rax
	mov rax, [backupRegistros + 32] ;cargo el rsi
    mov [registros + 32], rax
	mov rax, [backupRegistros + 40] ;cargo el rdi
    mov [registros + 40], rax
	mov rax, [backupRegistros + 48] ;cargo el rbp
    mov [registros + 48], rax
	mov rax, [backupRegistros + 56] ;cargo el r8
	mov [registros + 56], rax
	mov rax, [backupRegistros + 64] ;cargo el r9
    mov [registros + 64], rax
	mov rax, [backupRegistros + 72] ;cargo el r10
    mov [registros + 72], rax
	mov rax, [backupRegistros + 80] ;cargo el r11
    mov [registros + 80], rax
	mov rax, [backupRegistros + 88] ;cargo el r12
	mov [registros + 88], rax
	mov rax, [backupRegistros + 96] ;cargo el r13
    mov [registros + 96], rax
	mov rax, [backupRegistros + 104] ;cargo el r14
    mov [registros + 104], rax
	mov rax, [backupRegistros + 112] ;cargo el r15
    mov [registros + 112], rax
	mov rax, [backupRegistros + 120] ;cargo el rip
    mov [registros + 120], rax
	mov rax, [backupRegistros + 128] ;cargo el cs
	mov [registros + 128], rax
	mov rax, [backupRegistros + 136] ;cargo el rflags
	mov [registros + 136], rax
	mov rax, [backupRegistros + 144] ;cargo el rsp
	mov [registros + 144], rax
	popState
	ret

_hlt:
	sti 
	hlt 
	ret

_cli:
	cli
	ret

_sti:
	sti
	ret

;Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

syscallHandler:
	pushState
	mov rbp,rsp
	push r9 ;guardo r9 porque sysCaller lo puede modificar
	mov rcx, r10	;acomodo los argumentos para que sysCaller los pueda tomar
	mov r9, rax
	call sysCaller
	pop r9
	mov al, 20h
	out 20h, al
	mov rsp, rbp
	popState
	iretq

exception_zero_division:
    backupRegs 0	

exception_op_code:
    backupRegs 6

haltcpu:
	cli
	hlt
	ret

SECTION .bss
    exceptionRegs resq 19
	registros resq 19
	backupRegistros resq 19