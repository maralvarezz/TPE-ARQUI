section .text
global getHours
global getMinutes
global getSeconds
global getKey


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

getKey:
    cli
.ciclo:
    in al, 0x64
    and al, 0x01
    je .ciclo
    in al, 0x60
    sti
    ret
