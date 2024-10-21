global sys_write
global sys_read
global sys_clear
global sys_time


section .text

sys_read:
    mov rax, 0x00
    int 0x80
    ret
    
sys_write:
    mov rax, 0x01
    int 0x80
    ret

sys_clear:
    mov rax, 0x02
    int 0x80
    ret

sys_wait:
    mov rax, 0x03
    int 0x80
    ret

sys_sound:
    mov rax, 0x04
    int 0x80
    ret