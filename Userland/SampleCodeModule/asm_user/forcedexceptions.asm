section .text
GLOBAL invalidopcode
GLOBAL divzero

exc_invalidopcode:
    db 0x0F, 0x0B
    ret

exc_divzero:
    mov rax, 0
    div rax
    ret

