global loader
global load_main
extern main
extern initializeKernelBinary
extern getStackBase

loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	mov rsp, rax				; Set up the stack with the returned address
	call main
load_main: ; This is the function that will be called after an exception
	call getStackBase ; Get the stack base address
	mov rsp,rax 
	call main
hang:
	cli
	hlt	; halt machine should kernel return
	jmp hang
