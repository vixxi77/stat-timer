#include <SDL2/SDL.h>
#include "window.h"
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 300
#define HEIGHT 100
#define HORIZONTAL_POS 1618
#define VERTICAL_POS 10
//1618 5 300 100

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
TTF_Font *font;
SDL_Texture *texture;
SDL_Color White = {255, 255, 255};
SDL_Color Red = {255, 0, 0};
SDL_Rect textRect;
SDL_Color MAIN_COLOR;

char *activity;

int window_open = 0;

void initWindow(){
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Timer", HORIZONTAL_POS, VERTICAL_POS, WIDTH, HEIGHT, 0);
	SDL_SetWindowBordered(window, SDL_FALSE);
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
	renderSDLText();
	SDL_RenderPresent(renderer);
}

void initText(){
	if(TTF_Init() == -1){
	       	printf("ttf failure \n");
	}else{
		printf("ttf good \n");
	}
	font = TTF_OpenFont("FSEX300.ttf", 15);
}

void renderSDLText(){
	if(activity == NULL){
		activity = "NO ACTIVITY";
		MAIN_COLOR = Red;
	}else if(activity != "NO ACTIVITY" && activity != NULL){
		MAIN_COLOR = White;
	}

	surface = TTF_RenderText_Solid(font, activity, MAIN_COLOR);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	textRect.x = 0;
	textRect.y = 0;
	textRect.w = 200;
	textRect.h = 20;

	SDL_RenderCopy(renderer, texture, NULL, &textRect);
	SDL_FreeSurface(surface);
}

void setSDLActivity(char *activityName){
	activity = activityName;
}
