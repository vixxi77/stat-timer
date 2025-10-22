#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "window.h"
#include "timer.h"
//#include <pthread.h>

#define MAX_ACTIVITIES 8

static Activity current = {0};
static int timerRunning = 0;
static double lastTime = 0.0;

int activityIds[MAX_ACTIVITIES];

char buffer[12];

static double getCurrentTime(){

	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + ts.tv_nsec / 1e9;
};

void startTimer(char *activityString, int activityId){
	
	if(timerRunning){
		stopTimer();
	}

	timerRunning = 1;
	current.id = activityId;
	current.activityName = activityString;
	current.totalTime = activityIds[current.id];
	lastTime = getCurrentTime();
	current.startStamp = time(NULL);	
	setSDLActivity(current.activityName);

	printf("Activity: %s, started at: %s \n", current.activityName, asctime(localtime(&current.startStamp)));
}

void stopTimer(){

	if(!timerRunning) return;

	timerRunning = 0;
	setSDLActivity(NULL);

	time_t endStamp = time(NULL);

	saveTotalTime();

	printf("Activity %s stopped at: %s \n", current.activityName, asctime(localtime(&endStamp)));
	printf("Total time spent: %d \n", current.totalTime);
}

void updateTimer(){
	if(!timerRunning) return;

	double now = getCurrentTime();
	double delta = now - lastTime;
	lastTime = now;
	current.totalTime += (int)delta;
	
}

void renderTimer(){

	if(!timerRunning) return;
	sprintf(buffer, "%d", current.totalTime);
	setSDLTimer(buffer);
}

void saveTotalTime(){
	activityIds[current.id] += current.totalTime;
}
