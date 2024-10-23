#include "./include/videoDriver.h"


#define WIDTH 10
#define HEIGHT 16

uint64_t flagCursor=1;

uint16_t cursorX = 0;
uint16_t cursorY = 0;

const uint16_t WIDTH_FONT = 9;
const uint16_t HEIGHT_FONT = 16;


ColorT WHITE = {255,255,255};
ColorT BLACK = {0,0,0};

ColorT color = {0,0,0};

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

uint8_t escalaPixel=1;

static uint32_t* getPixel(uint16_t y, uint16_t x);
static void scrolleo();
static void checkInsideScreen();
static void drawChar(char c, ColorT fuenteColor, ColorT fondoColor);

void driver_putCursor(){
		//es una mascara para chequear si el color es 
		int mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
		ColorT caracterColor = flagCursor ? WHITE : BLACK;
		ColorT fondoColor = flagCursor ? WHITE : BLACK;
		const  uint8_t *charBitMap;
		if(flagCursor){
			charBitMap = font_bitmap+16*(219-32); // 219 es el ASCII del cursor
			flagCursor = 0;
		}
		else{
			charBitMap = font_bitmap+16*(32-32); // 32 es el ASCII del espacio
			flagCursor = 1;
		}
		//hacemos el chequeo para que no se pase de la pantalla
		checkInsideScreen();
		int cy,cx;
		//iteramos sobre el mapa de bits del cursor
		for (cy = 0; cy < 16; cy++) {
			for (cx = 0; cx < 8; cx++) {
				for (int i = 0; i < escalaPixel; i++) {
					for (int j = 0; j < escalaPixel; j++) {
						putPixel(charBitMap[cy] & mask[cx] ? colorToHexa(caracterColor) : colorToHexa(fondoColor),
						cursorX + (8 - cx) * escalaPixel + i, cursorY + cy * escalaPixel + j );
					}
				}
			}
		}

}

//-----------------------------------------------------------------------------------
// Obtener el ancho real de un carácter según el factor de escala actual
uint16_t getRealCharWidth() {
    return WIDTH_FONT * escalaPixel;
}

// Obtener el alto real de un carácter según el factor de escala actual
uint16_t getRealCharHeight() {
    return HEIGHT_FONT * escalaPixel;
}
//HAY Q SACAR ESTO---------------------------------------------------------------------


//función para chequear que el cursor no se pase de la pantalla
static void checkInsideScreen(){
	if(cursorX >= screen->width){
		cursorX = 0;
		if(cursorY + HEIGHT*escalaPixel > screen->height){ 
			scrolleo();
		}
		else{
			cursorY += HEIGHT*escalaPixel;
		}
	}

	/*
	if (cursorX >= screen->width) {
        cursorX = 0;
        if (cursorY + getRealCharHeight() > screen->height) {
            cursorY -= getRealCharHeight();
            scrolleo();
        } else {
            cursorY += getRealCharHeight();
        }
    }*/


}

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y){
    uint8_t * framebuffer = (uint8_t *)(uintptr_t)screen->framebuffer;
    uint64_t offset = (x * ((screen->bpp)/8)) + (y * screen->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void driver_clear(){
    //limpia la pantalla
	ColorT clr=BLACK;
	ColorT* pixel = (ColorT*) ((uint64_t)screen->framebuffer);
	for(uint32_t i = 0; i <= (uint32_t)(screen -> width * screen->height); i++){
		((uint32_t *)(uintptr_t)screen->framebuffer)[i] = 0;
	}

    //se va el cursor arriba
	cursorX = 0;
	cursorY = 0;
}

void driver_read(char * buffer, uint64_t count){
	for(uint64_t i = 0; i < count; i++){
		buffer[i] = keyboard_handler();
		drawChar(buffer[i],WHITE,BLACK);
	}
}

void driver_print(char * buffer, uint64_t count){ 
	for(uint64_t i = 0; i < count; i++){
		if(buffer[i] == '\n'){
			driver_lineBelow(); //salto de linea
		}else if(buffer[i] == '\b'){
			driver_backspace(); //borra el caracter anterior
		}
		else if(buffer[i] == '\0'){
			return; 
		}
		else{
			drawChar(buffer[i],WHITE,BLACK); //si no es ninguno de los casos especiales 
		}
	}
}

static void scrolleo(){
	ColorT*  pixel;
	ColorT*  pixelAfter;

	for(int i=0; i<screen->height-HEIGHT*escalaPixel; i++){ //cambie WIDTH por HEIGht
		for(int j=0; j<screen->width; j++){
			pixel = (ColorT *)getPixel(i,j); 
			pixelAfter = (ColorT *)getPixel(i+HEIGHT*escalaPixel,j);
			*pixel = *pixelAfter; 
		}
	}
}

void driver_lineBelow(){
	cursorX = 0;
	if(cursorY + HEIGHT*escalaPixel > screen->height){
		//lo que hacemos acá es que todo el código que teníamos se mueve una linea hacia 
		//arriba, se borra la primer linea y se pone el cursor en la ultima linea
		scrolleo();
	}
	else{
		cursorY += HEIGHT*escalaPixel;
	}
}

// borra el caracter anterior
void driver_backspace(){
	if(cursorX == 0){
		return;
	}
	else{
		cursorX -= WIDTH*escalaPixel;
		drawChar(' ',WHITE,BLACK);
		cursorX -= WIDTH*escalaPixel;
	}
}
// uso el colorT como si fuera un pixel
//te paso una coordenada de la pantalla en (x,y) y te devuelvo la direccion de la pantalla que representa ese pixel
static uint32_t* getPixel(uint16_t y, uint16_t x) {
    uint8_t pixelwidth = screen->bpp/8;     //la cantidad de bytes hasta el siguiente pixel a la derecha
    uint16_t pixelHeight = screen-> pitch;  //cantidad de bytes hasta el siguiente pixel abajo
    uintptr_t pixelPtr = (uintptr_t)(screen->framebuffer) + (x * pixelwidth) + (y * pixelHeight);
    return (uint32_t*)pixelPtr;
}

static void setPixel(uint16_t y, uint16_t x, ColorT clr){
	if (x >= screen->width || y >= screen->height)
        return;
    ColorT* pixel = (ColorT*) getPixel(x, y);
    *pixel = clr;
}

//font_bitmap es el un arreglo que tiene arreglos de los mapas de caracteres de cada letra
static void drawChar(char c, ColorT fuenteColor, ColorT fondoColor){
	
	//es una mascara para chequear cada uno de los bits del mapa de bits
	int mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	const uint8_t * charBitMap = font_bitmap+16*(c-32); // c es el ASCII del caracter a imprimir, en esa direccion se encuentra el primer byte del caracter
	checkInsideScreen();
	int cy,cx;
	for (cy = 0; cy < 16; cy++) {
        for (cx = 0; cx < 8; cx++) {
            for (int i = 0; i < escalaPixel; i++) {
                for (int j = 0; j < escalaPixel; j++) {
                    setPixel(cursorX + (8 - cx) * escalaPixel + i ,cursorY + cy * escalaPixel + j,
					charBitMap[cy] & mask[cx] ? fuenteColor : fondoColor );
                }
            }
        }
    }
	cursorX += WIDTH*escalaPixel;	
	
	
}

//función para pasar el color a hexadecimal
uint32_t colorToHexa(ColorT color){
    uint32_t hexValue = 0;
    hexValue |= (color.red << 16);
    hexValue |= (color.green << 8);
    hexValue |= color.blue;
    return hexValue;
}
