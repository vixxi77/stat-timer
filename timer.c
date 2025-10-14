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
			printf("Im trying to exit maannnn!! \n");
			endTime = localtime(&current);
			break;
		}

		timeSpent = (float)(current - start);	
		struct timespec timesleep = { 1, 0L };
	

		printf("\r %.1f", timeSpent);
		fflush(stdout);
		nanosleep(&timesleep, NULL);
	}
	printf("Ended: %s \n", asctime(endTime));	
	pthread_exit(NULL);	
}
/*
		h = (timePassed /3600);
		m = (timePassed - (3600 * h)) / 60;
		s = (timePassed - (3600 * h) - (m * 60));
		printf("Youve done %d H: %d M: %d S  of this activity \n", h, m, s);	
*/
