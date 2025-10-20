#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "window.h"
//#include <pthread.h>

typedef struct {
	char *activityName;
	double  totalTime;
	time_t startStamp;
} Activity;

void startTimer(char *activityString);
void stopTimer(void);
void renderTimer(void);
void updateTimer(void);
static Activity current = {0};
static int timerRunning = 0;
static double lastTime = 0.0;


static double getCurrentTime(){

	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + ts.tv_nsec / 1e9;
};

void startTimer(char *activityString){
	
	if(timerRunning){
		stopTimer();
	}

	timerRunning = 1;
	current.activityName = activityString;
	current.totalTime = 0.0;
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

	printf("Activity %s stopped at: %s \n", current.activityName, asctime(localtime(&endStamp)));
	printf("Total time spent: %.2f \n", current.totalTime);
}

void updateTimer(){
	if(!timerRunning) return;

	double now = getCurrentTime();
	double delta = now - lastTime;
	lastTime = now;
	current.totalTime += delta;
}

void renderTimer(){

	if(!timerRunning) return;
	
	printf("\rActivity %s running: %.2f ", current.activityName, current.totalTime);
	fflush(stdout);
}
