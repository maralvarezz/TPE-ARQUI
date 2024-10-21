#include "videoDriver.h"
#include "./include/keyboard.h"

#define WIDTH 16


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

VBEInfoPtr screen = (VBEInfoPtr) 0x0000000000005C00;

typedef struct cursor{
	uint16_t x;
	uint16_t y;
} cursorT;
cursorT cursor ={0,0};

typedef struct color{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}ColorT;
ColorT color = {0,0,0};


uint8_t escalaPixel=1;

//función para pasar el color a hexadecimal
uint32_t ColorToHexa(ColorT color) {
    uint32_t hexValue = 0;
    hexValue |= (color.red << 16);
    hexValue |= (color.green << 8);
    hexValue |= color.blue;
    return hexValue;
}

static uint32_t* getPixel(uint16_t y, uint16_t x);
static void scrolleo();


//font_bitmap es el un arreglo que tiene arreglos de los mapas de caracteres de cada letra
static void drawChar(char c, cursorT cursor,ColorT fuenteColor, ColorT fondoColor){
	//es una mascara para chequear cada uno de los bits del mapa de bits
	int mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	char * charBitMap = font_bitmap+16*(c-32); // c es el ASCII del caracter a imprimir, en esa direccion se encuentra el primer byte del caracter
	checkInsideScreen();
	for (cy = 0; cy < 16; cy++) {
        for (cx = 0; cx < 8; cx++) {
            for (int i = 0; i < escalaPixel; i++) {
                for (int j = 0; j < escalaPixel; j++) {
                    putPixel(charBitMap[cy] & mask[cx] ? colorToHexa(fuenteColor) : colorToHexa(fondoColor),
					cursor.x + (8 - cx) * pixelScale + i, cursor.y + cy * pixelScale + j );
                }
            }
        }
    }
}

//función para chequear que el cursor no se pase de la pantalla
static void checkInsideScreen(){
	if(cursor.x >= screen->width){
		cursor.x = 0;
		if(cursor.y + 16*escalaPixel > screen->height){
			scrolleo();
		}
		else{
			cursor.y += 16*escalaPixel;
		}
	}
}

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *)screen->framebuffer;
    uint64_t offset = (x * ((screen->bpp)/8)) + (y * screen->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void driver_clear(){
    //limpia la pantalla
	for(uint16_t i = 0; i <= (screen -> width * screen->height); i++){
		((uint8_t *)screen->framebuffer)[i] = 0;
	}
    //se va el cursor arriba
	cursor.x = 0;
	cursor.y = 0;
}

void driver_read(char * buffer, uint64_t count){
	for(uint64_t i = 0; i < count; i++){
		buffer[i] = keyboard_handler();
	}
}

void driver_write(char * buffer, uint64_t count){
	for(uint64_t i = 0; i < count; i++){
		if(buffer[i] == '\n'){
			driver_WIDTH(); //salto de linea
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

static void scrolleo(){
	ColorT*  pixel;
	ColorT*  pixelAfter;

	for(int i=0; i<screen->height-WIDTH*escalaPixel; i++){
		for(int j=0; j<screen->width; j++){
			pixel = (ColorT *)getPixel(i,j);
			pixelAfter = (ColorT *)getPixel(i+WIDTH*escalaPixel,j);
			*pixel = *pixelAfter;
		}
	}
}


void driver_WIDTH(){
	cursor.x = 0;
	if(cursor.y + WIDTH*escalaPixel > screen->height){
		//lo que hacemos acá es que todo el código que teníamos se mueve una linea hacia 
		//arriba, se borra la primer linea y se pone el cursor en la ultima linea
		scrolleo();
	}
	else{
		cursor.y += WIDTH*escalaPixel;
	}
}


void driver_backspace(){
	if(cursor.x == 0){
		driver_sound();
		return;
	}
	else{
		cursor.x -= 8*escalaPixel;
		drawChar(' ');
	}
}

//te paso una coordenada de la pantalla en (x,y) y te devuelvo la direccion de la pantalla que representa ese pixel
static uint32_t* getPixel(uint16_t y, uint16_t x) {
    uint8_t pixelwidth = screen->bpp/8;     //la cantidad de bytes hasta el siguiente pixel a la derecha
    uint16_t pixelHeight = screen-> pitch;  //cantidad de bytes hasta el siguiente pixel abajo
    uintptr_t pixelPtr = (uintptr_t)(screen->framebuffer) + (x * pixelwidth) + (y * pixelHeight);
    return (uint32_t*)pixelPtr;
}
