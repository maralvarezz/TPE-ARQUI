#ifndef _TIME_H_
#define _TIME_H_

extern void _hlt();
void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void wait_time (int time);

#endif
