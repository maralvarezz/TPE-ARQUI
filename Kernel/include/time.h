#ifndef _TIME_H_
#define _TIME_H_

extern void _hlt();

//función que se llama cada vez que se produce una interrupción de timer
void timer_handler();

//devuelve la cantidad de ticks acumulados
int ticks_elapsed();

//devuelve los segundos que pasaron 
int seconds_elapsed();

//espera time segundos
void wait_time (int time);

#endif
