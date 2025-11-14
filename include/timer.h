#ifndef _TIMER_H
#define _TIMER_H

#include <time.h>

typedef struct {
	int id;
	char *activityName;
	int totalTime;
	time_t startStamp;
} Activity;

void startTimer(char *activityString, int activityId);
void stopTimer();
void updateTimer();
void renderTimer();
void saveTotalTime();
#endif 
