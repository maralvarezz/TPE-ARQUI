GLOBAL sys_write
GLOBAL sys_read
GLOBAL sys_clear
GLOBAL sys_time
GLOBAL sys_sound
GLOBAL sys_seconds
GLOBAL sys_minutes
GLOBAL sys_hours
GLOBAL sys_cursor
GLOBAL sys_wait
GLOBAL sys_registers
GLOBAL sys_drawRectangle
GLOBAL sys_width
GLOBAL sys_height
GLOBAL sys_reduceSize
GLOBAL sys_increaseSize
GLOBAL sys_cursorSetterX
GLOBAL sys_cursorSetterY
GLOBAL sys_pixelSize

section .text

sys_read:
    mov rax, 0x00
    int 80h
    ret
    
sys_write:
    mov rax, 0x01
    mov r10, rcx
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

sys_reduceSize:
    mov rax, 0x0D
    int 80h
    ret

sys_increaseSize:
    mov rax, 0x0E
    int 80h
    ret

sys_cursorSetterX:
    mov rax, 0x0F
    int 80h
    ret

sys_cursorSetterY:
    mov rax, 0x10
    int 80h
    ret

sys_pixelSize:
    mov rax, 0x11
    int 80h
    ret
