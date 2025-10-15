#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_SIZE 64
//TODO: make this accept shit like idk, activities so it can be modular 
//and also maybe a value to stop recording
void* startTimer(void *code){

	printf("Press key to stop recording \n");

	time_t start = time(NULL);
	struct tm *startTime;
	startTime = localtime(&start);

	struct tm *endTime;

	float timeSpent;
	
	if(*(int*) code != 7){	
		printf("Activity started: %s \n", asctime(startTime));	
	}

	while(true){
		
		time_t current = time(NULL);

		if(*(int*) code == 7){
			printf("Exiting \n");
			endTime = localtime(&current);
			int h = (timeSpent / 3600);
			int m = (timeSpent - (3600 * h)) / 60;
			int s = (timeSpent - (3600 * h) - (m * 60));
			printf("Ended: %s \n Total time spent: %d:%d:%d \n", asctime(endTime), h, m, s);	
			fflush(stdout);
			pthread_exit(NULL);
			break;
		}

		timeSpent = (float)(current - start);	
		struct timespec timesleep = { 1, 0L };
	

		printf("\r %.1f", timeSpent);
		fflush(stdout);
		nanosleep(&timesleep, NULL);
	}
}
