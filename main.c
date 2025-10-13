#include <stdio.h>
#include "timer.h"
#include <pthread.h>


void main(){

	printf("\t\t\tChoose an activity: \n");
	printf("[1]Reading C \t [2]Programming \t [3]Watching Media \t [4]Loonix work \n");

	int code = 0;	
	int option;

	pthread_t thread1;

	for(;;){
		scanf("%d", &option);
		printf("Im waiting \n");	
		
		switch(option){
			case 1:
				code = option;
				pthread_create(&thread1, NULL, startTimer, (void*)&code);
				break;
			case 7:
				code = option;
				pthread_join(thread1, NULL);
				printf("I should be dead rn \n");
				code = 0;
				break;
		}
	}
}






