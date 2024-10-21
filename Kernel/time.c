#include "include/time.h"

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void wait_time (int time) {
	if(time <= 0){
		return;
	}
	int start = ticks;
	while (ticks - start < time){
		_hlt();
	}
}
