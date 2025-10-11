#include <time.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_SIZE 64
//TODO: make this accept shit like idk, activities so it can be modular 
//and also maybe a value to stop recording
int startTimer(char activity[MAX_SIZE]){

	int exit;
	int timePassLed = 0;
	printf("Press key to stop recording \n");
	printf("Recording activity: %s \n", activity);

	time_t start = time(NULL);
	struct tm *startTime;
	startTime = localtime(&start);

	//int h, m, s;

	float timeSpent;
	
	
	int last_second = -1;


	printf("Activity started: %s \n", asctime(startTime));	

	while(true){
		time_t current = time(NULL);
		timeSpent = (float)(current - start);	
		struct timespec timesleep = { 1, 0L };
		//scanf("%d", &exit);
		/*	
		if(exit > 0){
			break;
		}
		*/
		//TODO: actually use system time bruh
		
/*
		h = (timePassed /3600);
		m = (timePassed - (3600 * h)) / 60;
		s = (timePassed - (3600 * h) - (m * 60));
		printf("Youve done %d H: %d M: %d S  of this activity \n", h, m, s);	
	}

	return timePassed;
	*/
		printf("\r %.1f", timeSpent);
		fflush(stdout);
		nanosleep(&timesleep, NULL);
	}
}
