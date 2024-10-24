GLOBAL cpuVendor
global getHours
global getMinutes
global getSeconds
global getKey
global hlt_aux
global sound
global stop_sound

section .text

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


getHours:
    cli
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al

    mov al, 0x04
    out 70h, al
    in al, 71h
    sti
    ret

getMinutes:
    cli
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al

    mov al, 0x02
    out 70h, al
    in al, 71h
    sti

    ret

getSeconds:
    cli
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al

    mov al, 0x00
    out 70h, al
    in al, 71h
    sti
    ret

sound:
    push rbp
    push rax
    push rdx
    push rdi
    mov rbp, rsp

    ;configuramos el PIT(Programmable Interval Timer)
    mov al, 0xB6 ;configura el canal 2 para que genere un sonido
    out 0x43, al ;Envía el comando al puerto 0x43(puerto del PIT). Esto le indica al PIT que queremos cambiar la frecuencia del canal 2
                 ;el cual está conectado al speaker
    mov rax, 1193180 ;frecuencia de 1193180 Hz la cual es la frecuencia del reloj del PIT
    mov rdx, 0 ;lo dejo en 0 así no divide basura 
    div rdi ;dividimos la frecuencia del reloj por el valor que se encuentra en rdi que va a ser la frecuencia del sonido querido

    out 0x42, al ;configuramos el PIT enviandole la parte alta y la baja de la frecuencia al puerto 0x42
    mov al, ah
    out 0x42, al

    in al, 61h ;lee el valor del puerto 61h que controla el altavoz
    or al, 03h ;enciende el bit 0 y 1
    out 61h, al ;Escribe el valor modificado nuevamente al puerto 0x61, activando el altavoz para que emita el tono generado

    mov rsp, rbp
    pop rdi
    pop rdx
    pop rax
    pop rbp
    ret

stop_sound:
    in al , 61h ;leo lo que hay dentro del puerto
    and al, 0xFC ;apago el bit 0 y 1
    out 61h, al ;escribo el valor modificado en el puerto
    ret


    

