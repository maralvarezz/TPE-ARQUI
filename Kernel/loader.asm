global loader
global load_main
extern main
extern initializeKernelBinary
extern getStackBase

loader:
	call initializeKernelBinary	; Configura el binario del kernel y obtiene la dirección del stack
	mov rsp, rax				; Setea el stack con la dirección obtenida
	call main
load_main: ;Esta es la función que se llama después de llamar a una excepción
	call getStackBase 
	mov rsp,rax 
	call main
hang:
	cli
	hlt	
	jmp hang
