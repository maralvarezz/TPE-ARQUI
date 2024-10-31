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
    ;guardamos los registros en el orden en el que quiero para luego mostrarlos en pantalla
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
    mov rax, rsp 
    add rax, 160 ;nos ponemos antes de que suceda el error 
    mov [exceptionRegs + 120], rax
    mov rax, [rsp+120] ;Obtenemos el valor de RIP en el momento en el que sucede la excepción tomando el valor de la interrupción que se encuentra en la pila.
	mov [exceptionRegs+128], rax
	mov rax, [rsp+128] ;Obtenemos el valor de RFLAGS también de esta manera, ya que son pusheadas cuando ocurre una interrupción
	mov [exceptionRegs+136], rax
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
	;signal pic EOI (End of Interrupt)
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
    mov [registros+2*8], rbx
    mov [registros+3*8], rcx
    mov [registros+4*8], rdx
    mov [registros+5*8], rsi
    mov [registros+6*8], rdi
    mov [registros+7*8], rbp
    mov [registros+9*8], r8
    mov [registros+10*8], r9
    mov [registros+11*8], r10
    mov [registros+12*8], r11
    mov [registros+13*8], r12
    mov [registros+14*8], r13
    mov [registros+15*8], r14
    mov [registros+16*8], r15
	mov rax, rsp
    add rax, 160
    mov [registros+8*8], rax
    mov rax, [rsp+15*8]
    mov [registros], rax
    mov rax, [rsp+14*8]
    mov [registros+1*8], rax
	popState
	ret

_hlt:
	sti ;permite que se reciban interrupciones mientras el procesador esta en hlt
	hlt 
	ret

_cli:
	cli
	ret

_sti:
	sti
	ret

;8254 Timer (Timer Tick)
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


;Zero Division Exception
exception_zero_division:
    backupRegs 0	

;Op Code Exception
exception_op_code:
    backupRegs 6

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	ctrlFlag resb 1 ;variable que se usa para saber si se presiono shift
    exceptionRegs resq 18
	registros resq 18