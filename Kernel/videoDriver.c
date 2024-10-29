#include "./include/videoDriver.h"


#define WIDTH 8
#define HEIGHT 16

uint64_t flagCursor=1;

uint16_t cursorX = 0;
uint16_t cursorY = 0;




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
static void setPixel(uint16_t x, uint16_t y, ColorT clr);
static uint32_t* getPixel(uint16_t y, uint16_t x);

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
						setPixel(cursorX + (8 - cx) * escalaPixel + i, cursorY + cy * escalaPixel + j 
						,charBitMap[cy] & mask[cx] ? caracterColor : fondoColor);
					}
				}
			}
		}

}

//función para chequear que el cursor no se pase de la pantalla
static void checkInsideScreen(){
    if(cursorX >= screen->width){
        cursorX = 0;
        if(cursorY + HEIGHT*escalaPixel > screen->height){ 
			cursorY -= HEIGHT*escalaPixel;
            scrolleo();
        } else {
            cursorY += HEIGHT*escalaPixel;
        }
    }
}

void driver_clear(){
    //limpia la pantalla
	for(uint32_t i = 0; i <= (uint32_t)(screen -> width * screen->height); i++){
		((uint32_t *)(uintptr_t)screen->framebuffer)[i] = 0;
	}

    //se va el cursor arriba
	cursorX = 0;
	cursorY = 0;
}

void driver_read(char * buffer){
		*buffer = keyboard_handler();
		if(*buffer == 0){
			return;
		}
}

void driver_print_color(char * buffer, uint64_t count,ColorT colorFte,ColorT colorFdo){ 
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
			drawChar(buffer[i],colorFte,colorFdo); //si no es ninguno de los casos especiales 
		}
		checkInsideScreen();
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
	for(int i=0;i<HEIGHT*escalaPixel;i++){
	for(int j=0; j<screen->width; j++){
		pixel=(ColorT *)getPixel(screen->height-HEIGHT*escalaPixel+i,j);
		*pixel=BLACK; 
	}
	}
}
void driver_lineBelow(){
	if(flagCursor==0){
		driver_putCursor();
	}
	cursorX = 0;
	cursorY += HEIGHT*escalaPixel;
	if(cursorY + HEIGHT*escalaPixel > screen->height){
		cursorY -= HEIGHT*escalaPixel;
		//lo que hacemos acá es que todo el código que teníamos se mueve una linea hacia 
		//arriba, se borra la primer linea y se pone el cursor en la ultima linea
		scrolleo();
	}
}

// borra el caracter anterior
void driver_backspace(){
	if(cursorX == 0 && cursorY == 0){
		return;
	}
	else{
	if(flagCursor==0){
		driver_putCursor();
	}
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

static void setPixel(uint16_t x, uint16_t y, ColorT clr){
	if (x >= screen->width || y >= screen->height){
		return;
	}
    ColorT* pixel = (ColorT*) getPixel(y, x);
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
	checkInsideScreen();
}


// x2 representa el ancho, y2 la altura
void driver_drawRect(uint64_t x,uint64_t y ,uint64_t x2 , uint64_t y2 ,ColorT colorToPaint){
	ColorT* pixel;
	for(int i=0;i<y2;i++){
		pixel = (ColorT*) getPixel(y+i,x);
		for(int j=0; j<x2;j++,pixel++){
			*pixel=colorToPaint;
		}
	}
}

uint16_t driver_width(){
	return screen->width;
}
uint16_t driver_height(){
	return screen->height;
}
