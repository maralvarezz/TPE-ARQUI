section .text
GLOBAL invalidopcode
GLOBAL divzero

invalidopcode:
    db 0x0F, 0x0B
    ret

divzero:
    mov rax, 0
    div rax
    ret

