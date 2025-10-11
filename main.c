#include <stdio.h>
#include "timer.h"


void main(){

	printf("\t\t\tChoose an activity: \n");
	printf("[1]Reading C \t [2]Programming \t [3]Watching Media \t [4]Loonix work \n");
	
	
	int option;

	scanf("%d", &option);

		
	switch(option){
		case 1:
			printf("Reading C \n");	
			startTimer("Reading C");
			break;
		case 2:
			printf("Programming  \n");
			break;
		case 3:
			printf("Watching media \n");
			break;
		case 4:
			printf("Loonix working \n");
			break;
	}	

	
	
}






