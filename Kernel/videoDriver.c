disn#include "videoDriver.h"

#define NEWLINE = 16

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

typedef struct cursor{
	uint16_t x = 0;
	uint16_t y = 0;
} cursor;

uint8_t escalaPixel=1;

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void driver_clear(){
    //limpia la pantalla
    for(uint16_t i = 0; i <= (VBEInfoPtr -> width * VBEInfoPtr->height); i++){
		VBEInfoPtr->framebuffer[i] = 0;
	}

    //se van los cursores arriba 
    cursor -> x = 0;
    cursor -> y = 0;
}

void driver_read(char * buffer, uint64_t count){
	for(uint64_t i = 0; i < count; i++){
		buffer[i] = keyboard_handler();
	}
}

void driver_write(char * buffer, uint64_t count){
	for(uint64_t i = 0; i < count; i++){
		if(buffer[i] == '\n'){
			driver_newLine(); //salto de linea
		}else if(buffer[i] == '\b'){
			driver_backspace(); //borra el caracter anterior
		}
		else if(buffer[i] == '\0'){
			return; 
		}
		else if(buffer[i] == '\t'){
			driver_tab(); 
		}
		else{
			drawChar(buffer[i]); //si no es ninguno de los casos especiales 
		}
	}
}

void driver_newLine(){
	cursor -> x = 0;
	cursor -> y += NEWLINE;
}


void driver_backspace(){
	if(curX == 0){
		//hacer sonido
	}
	else{
		drawChar(' ');
	}
}
