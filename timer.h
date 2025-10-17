#ifndef _TIMER_H
#define _TIMER_H

#include <time.h>

typedef struct {
	int id;
	double totalTIme;
	time_t startStamp;
} Activity;

void startTimer(int activityId);
void stopTimer();
void updateTimer();
void renderTimer();
#endif 
