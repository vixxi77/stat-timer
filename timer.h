#ifndef _TIMER_H
#define _TIMER_H

#include <time.h>

typedef struct {
	char *activityName;
	double totalTime;
	time_t startStamp;
} Activity;

void startTimer(char *activityString);
void stopTimer();
void updateTimer();
void renderTimer();
#endif 
