#include <time.h>
#include <stdio.h>
#include <unistd.h>
//#include <pthread.h>

typedef struct {
	int id;
	double  totalTime;
	time_t startStamp;
} Activity;

void startTimer(int activityId);
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

void startTimer(int activityId){
	
	if(timerRunning){
		stopTimer();
	}

	timerRunning = 1;
	current.id = activityId;
	current.totalTime = 0.0;
	lastTime = getCurrentTime();
	current.startStamp = time(NULL);	

	printf("Activity: %d, started at: %s \n", activityId, asctime(localtime(&current.startStamp)));
}

void stopTimer(){

	if(!timerRunning) return;

	timerRunning = 0;

	time_t endStamp = time(NULL);

	printf("Activity %d stopped at: %s \n", current.id, asctime(localtime(&endStamp)));
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
	
	printf("\rActivity %d running: %.2f ", current.id, current.totalTime);
	fflush(stdout);
};
