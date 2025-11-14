#include <SDL2/SDL.h>
#include "../include/window.h"
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 300
#define HEIGHT 100
#define HORIZONTAL_POS 1618
#define VERTICAL_POS 10
//1618 5 300 100

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *activity_surface;
TTF_Font *font;
SDL_Texture *activity_texture;
SDL_Color White = {255, 255, 255};
SDL_Color Red = {255, 0, 0};
SDL_Rect activityRect;
SDL_Rect timerRect;
SDL_Color MAIN_COLOR;
SDL_Texture *timer_texture;
SDL_Surface *timer_surface;

char *activity;
char *timer;

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
	static int _called;
	switch (actionId){
		case 0:
			if(window_open == 0 && _called > 0) break;
			closeWindow();	
			window_open = 0;
			break;
		case 1:
			if(window_open == 1) break ;
			openWindow();
			window_open = 1;
			break;
	}
	_called++;
}

void openWindow(){
	SDL_ShowWindow(window);
}

void closeWindow(){
	SDL_HideWindow(window);
}

void renderSDLWindow(){
	SDL_RenderClear(renderer);
	renderSDLActivity();
	renderSDLTimer();
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

void renderSDLActivity(){
	if(activity == NULL){
		activity = "NO ACTIVITY";
		MAIN_COLOR = Red;
	}else if(strcmp(activity, "NO ACTIVITY") == 0 && activity != NULL){
		MAIN_COLOR = White;
	}

	activity_surface = TTF_RenderText_Solid(font, activity, MAIN_COLOR);
	activity_texture = SDL_CreateTextureFromSurface(renderer, activity_surface);

	activityRect.x = 0;
	activityRect.y = 0;
	activityRect.w = 200;
	activityRect.h = 20;

	SDL_RenderCopy(renderer, activity_texture, NULL, &activityRect);
	SDL_FreeSurface(activity_surface);
}

void renderSDLTimer(){

	timer_surface = TTF_RenderText_Solid(font, timer, MAIN_COLOR);
	timer_texture = SDL_CreateTextureFromSurface(renderer, timer_surface);

	timerRect.x = 25;
	timerRect.y = 25;
	timerRect.w = 50;
	timerRect.h = 50;

	SDL_RenderCopy(renderer, timer_texture, NULL, &timerRect);
	SDL_FreeSurface(timer_surface);
}

void setSDLActivity(char *activityName){
	activity = activityName;
}

void setSDLTimer(char *activityTimer){
	timer = activityTimer;
}
