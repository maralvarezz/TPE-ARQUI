global sys_write
global sys_read
global sys_clear
global sys_time
global sys_sound
global sys_seconds
global sys_minutes
global sys_hours
global sys_cursor
global sys_wait
global sys_registers
global sys_drawRectangle
global sys_width
global sys_height

section .text

sys_read:
    mov rax, 0x00
    int 80h
    ret
    
sys_write:
    mov rax, 0x01
    int 80h
    ret

sys_clear:
    mov rax, 0x02
    int 80h
    ret

sys_wait:
    mov rax, 0x03
    int 80h
    ret

sys_sound:
    mov rax, 0x04
    int 80h
    ret

sys_seconds:
    mov rax, 0x05
    int 80h
    ret

sys_minutes:
    mov rax, 0x06
    int 80h
    ret

sys_hours:
    mov rax, 0x07
    int 80h
    ret

sys_cursor:
    mov rax, 0x08
    int 80h
    ret
    
sys_drawRectangle:
    mov rax, 0x09
    mov r10, rcx
    int 80h
    ret

    
sys_registers:
    mov rax, 0x0A
    int 80h
    ret

    
sys_width:
    mov rax, 0x0B
    int 80h
    ret

sys_height:
    mov rax, 0x0C
    int 80h
    ret
