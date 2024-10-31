#include "../include/syscalls.h"
#include "../include/keyboard.h"

#define READ 0
#define WRITE 1
#define CLEAR 2
#define WAIT 3
#define SOUND 4
#define SECONDS 5
#define MINUTES 6
#define HOURS 7
#define CURSOR 8
#define PAINT 9
#define REGISTERS 10
#define GETWIDTH 11
#define GETHEIGHT 12
#define REDUCESIZE 13
#define INCREASESIZE 14
#define CURSORSETTERX 15
#define CURSORSETTERY 16



//extern int getSeconds();
//extern int getMinutes();
//extern int getHours();
extern void sound(int freq);
extern void stop_sound();
extern uint8_t registersFlag;
extern uint64_t registros[17];

uint64_t sysCaller(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax) {
	switch (rax) {
        case READ:
			return sys_read(rdi, (char *)rsi);
		case WRITE:
            ColorT* colorFd=(ColorT*)r8;
            ColorT* colorFte=(ColorT*)r10;
            ColorT auxfd={colorFd->blue,colorFd->green,colorFd->red};
            ColorT auxfte={colorFte->blue,colorFte->green,colorFte->red};
			return sys_write(rdi, (char *)rsi, rdx, auxfte,auxfd);
		case CLEAR:
			return sys_clear();
        case WAIT:
            return sys_wait(rdi);
        case SOUND:
            return sys_sound(rdi, rsi);
        case SECONDS:
            return sys_seconds((uint64_t *) rdi);
        case MINUTES:
            return sys_minutes((uint64_t *) rdi);
        case HOURS:
            return sys_hours((uint64_t *) rdi);
        case CURSOR:
            return sys_cursor();
        case PAINT:
            ColorT* color=(ColorT*)r8;
            ColorT aux={color->blue,color->green,color->red}; // por la forma en la que llega el color debo invertir el red y el blue
            return sys_drawRect(rdi, rsi ,rdx ,r10 , aux); // se le pasan la esquina sup izq, su largo y su altura
        case REGISTERS:
            return sys_registers((uint64_t *) rdi, (uint64_t *) rsi);
        case GETWIDTH:
            return  sys_width((uint64_t *) rdi);
        case GETHEIGHT:
            return  sys_height((uint64_t *) rdi);
        case REDUCESIZE:
            return sys_reduceSize();
        case INCREASESIZE:
            return sys_increaseSize();
        case CURSORSETTERX:
            return sys_cursorSetterX(rdi);
        case CURSORSETTERY:
            return sys_cursorSetterY(rdi);
        default:
            return 0;
	}
}

uint64_t sys_read(uint64_t fd, char * buffer){
    if(fd == 0){
        driver_read(buffer);
        return 1;
    }
    return 0;
}

uint64_t sys_write(uint64_t fd, char * buffer, uint64_t count,ColorT colorFte,ColorT colorFdo){
    if(fd == 1){
        driver_print_color(buffer, count,colorFte,colorFdo);
        return 1;
    }
    return 0;
}

uint64_t sys_cursor(){
    driver_putCursor();
    return 1;
}

uint64_t sys_cursorSetterX(uint64_t x){
    driver_setCursorX(x);
    return 1;
}

uint64_t sys_cursorSetterY(uint64_t y){
    driver_setCursorY(y);
    return 1;
}



uint64_t sys_clear(){
    driver_clear();
    return 1;
}

uint64_t sys_registers(uint64_t vec[17],uint64_t * flag){
    *flag=getCtrlFlag();
    if(*flag){
        for(int i = 0; i < 17; i++){
            vec[i] = registros[i];
        }
    }
    return 1;
}


uint64_t sys_seconds(uint64_t * flag){
    *flag=getSeconds();
    return 1;
}

uint64_t sys_minutes(uint64_t * flag){
    *flag=getMinutes();
    return 1;
}

uint64_t sys_hours(uint64_t * flag){
    *flag=getHours();
    return 1;
}

uint64_t sys_wait(uint64_t time){
    wait_time(time);
    return 1;
}

uint64_t sys_sound(uint64_t freq, uint64_t time){
    if(freq>0){
        sound(freq);
    }
    wait_time(time);
    stop_sound();
    return 1;
}

uint64_t sys_drawRect(uint64_t x,uint64_t y ,uint64_t x2 , uint64_t y2 ,ColorT color){
    driver_drawRect(x,y,x2,y2,color);
    return 0;
}

uint64_t sys_width(uint64_t* rdi){
    *rdi = driver_width();
    return 1;
}
uint64_t sys_height(uint64_t* rdi){
    *rdi = driver_height();
    return 1;
}

uint64_t sys_reduceSize(){
    driver_reduceSize();
    return 1;
}

uint64_t sys_increaseSize(){
    driver_increaseSize();
    return 1;
}