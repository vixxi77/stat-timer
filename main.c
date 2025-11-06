#include <stdio.h>
#include "timer.h"
#include <pthread.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include "window.h"

#define ACTIVITY_ONE "Programming C"
#define ACTIVITY_TWO "Loonix Work"
#define OPEN 1
#define CLOSE 0
//TEST1
//TEST2

/*
 * I dont know why this even works first try flawlesly lol, ts dumb ahh X11 api
 * boilerplate of some poor persons for wich this didint work,
 * probably for him the key that he desired to grab was already being grabbed by another program,
 * anyways i wouldnt count on this being consistent
 */

Display*    display;
Window      root;
XEvent      event;

unsigned int    modifiers;
int             keycode_open_window;     
int 		keycode_first_activity;	
int 		keycode_second_activity;	
int 		keycode_third_activity;	
int		keycode_terminate_program;
Window          grab_window;  
Bool            owner_events; 
int             pointer_mode; 
int             keyboard_mode;

void initXKeys(){

	display                     = XOpenDisplay(0);
	root                        = DefaultRootWindow(display);

	modifiers                   = ControlMask | ShiftMask; 
	keycode_open_window         = XKeysymToKeycode(display,XK_W);
	keycode_first_activity	    = XKeysymToKeycode(display, XK_F1);
	keycode_second_activity	    = XKeysymToKeycode(display, XK_F2);
	keycode_third_activity	    = XKeysymToKeycode(display, XK_F3);
	keycode_terminate_program   = XKeysymToKeycode(display,XK_X);

	grab_window                 = root;
	owner_events                = False;
	pointer_mode                = GrabModeAsync;
	keyboard_mode               = GrabModeAsync;

	XGrabKey(display, keycode_open_window, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	XGrabKey(display, keycode_first_activity, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	XGrabKey(display, keycode_second_activity, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	XGrabKey(display, keycode_third_activity, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	XGrabKey(display, keycode_terminate_program, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);




	XSelectInput(display, root, KeyPressMask);
};

void main(){
	int toggle = 0;	
	int running = 1;
	initXKeys();

	printf("\t\t\tChoose an activity: \n");
	printf("[CTRL+SHIFT+F1]Start The Timer \t [CTRL+SHIFT+F3]Stop The Timer \t [CTRL+SHIFT+W] Open/Close Timer Window \n");
	fflush(stdout);

	int code = 0;	
	int option;

	initWindow();
	initRenderer();
	initText();

	while(running){
		while(XPending(display)){
			XNextEvent(display, &event);
			KeySym symbol = XLookupKeysym(&event.xkey, 1); //So the index 1 says take in to account capitalization?? yeah have no idea,
							       //but for consistency ill keep it this way, just make sure caps are off
							       //when trying hotkeys
			if(event.type == KeyPress && (event.xkey.state & modifiers) == modifiers){
				switch(symbol){
					case XK_W: 
						if(toggle == 0){
							 printf("Close window \n");
							 actionWindow(CLOSE);
							 toggle = 1;
							 break;
						}else{
							printf("Open window \n");
							actionWindow(OPEN);
							toggle = 0;
							break;
						}
					case XK_F1:
						 //pthread_create(&thread1, NULL, startTimer, (void*)&code);
						 startTimer(ACTIVITY_ONE, 0);
						 break;
					case XK_F2:
						 startTimer(ACTIVITY_TWO, 1);
						 break;
					case XK_F3:
						 //pthread_join(thread1, NULL);
						 stopTimer();
						 break;
					case XK_X:
						 printf("terminating! \n");
						 running = 0;
						 break;
					default:
						 break;
				}
			}
		}
		updateTimer();
		renderTimer();
		renderSDLWindow();
		struct timespec sleep = { 1 , 10 * 100 * 1000 };
		nanosleep(&sleep, NULL);		
	}
	XCloseDisplay(display);
}








