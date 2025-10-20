#include <SDL2/SDL.h>
#include "window.h"
#include <stdio.h>

#define WIDTH 300
#define HEIGHT 100
#define HORIZONTAL_POS 1618
#define VERTICAL_POS 20

SDL_Window *window;
SDL_Renderer *renderer;

int window_open = 0;

void initWindow(){
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Timer", HORIZONTAL_POS, VERTICAL_POS, WIDTH, HEIGHT, 0);
	//SDL_SetWindowBordered(window, SDL_FALSE);
}

void initRenderer(){
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
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
	SDL_ShowWindow(window);
}

void closeWindow(){
	SDL_HideWindow(window);
}

void renderSDLWindow(){
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}
