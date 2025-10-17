#include <SDL2/SDL.h>
#include "window.h"
#include <stdio.h>

#define WIDTH 300
#define HEIGHT 100
#define HORIZONTAL_POS 1618
#define VERTICAL_POS 20
SDL_Window *window;

int window_open = 0;

void initWindow(){
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Timer", HORIZONTAL_POS, VERTICAL_POS, WIDTH, HEIGHT, 0);
}

void actionWindow(int actionId){
	switch (actionId){
		case 0:
			if(window_open == 0) break;
			closeWindow();	
			window_open = 0;
			break;
		case 1:
			if(window_open == 1) break ;
			openWindow();
			window_open = 1;
			break;
	}
}

void openWindow(){
	printf("opening window! \n");
	SDL_ShowWindow(window);
	printf("window running! \n");
}

void closeWindow(){
	printf("closing window! \n");
	SDL_HideWindow(window);
	printf("WINDOW CLOSED! \n");
}
	

