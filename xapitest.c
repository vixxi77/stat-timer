#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>


int keyPressCounter = 0;

/*
 * I dont know why this even works first try flawlesly lol, ts dumb ahh X11 api
 * boilerplate of some poor persons for wich this didint work,
 * probably for him the key that he desired to grab was already being grabbed by another program,
 * anyways i wouldnt count on this being consistent
 */








void main(){
	Display*    display     = XOpenDisplay(0);
	Window      root    = DefaultRootWindow(display);
	XEvent      event;

	unsigned int    modifiers       = ControlMask | ShiftMask; //Ctrl + Shift
	int             keycode_open_window         = XKeysymToKeycode(display,XK_W);// +W
	int 		keycode_first_activity	    = XKeysymToKeycode(display, XK_F1);
	int 		keycode_second_activity	    = XKeysymToKeycode(display, XK_F2);
	int 		keycode_third_activity	    = XKeysymToKeycode(display, XK_F3);

	Window          grab_window     =  root;
	Bool            owner_events    = False;
	int             pointer_mode    = GrabModeAsync;
	int             keyboard_mode   = GrabModeAsync;

	XGrabKey(display, keycode_open_window, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	XGrabKey(display, keycode_first_activity, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	XGrabKey(display, keycode_second_activity, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);
	XGrabKey(display, keycode_third_activity, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);

	XSelectInput(display, root, KeyPressMask);
	for(;;){
		 XNextEvent(display, &event);
		 KeySym symbol = XLookupKeysym(&event.xkey, 0);
		 if(event.type == KeyPress && (event.xkey.state & modifiers) == modifiers){
			 switch(symbol){
				 case XK_W:
					 ++keyPressCounter;
					 printf("Open window; Total keypresses:  %d \n", keyPressCounter);
					 break;
				 case XK_F1:
					 ++keyPressCounter;
					 printf("Activity 1; Total keypresses: %d \n", keyPressCounter);
					 break;
				 case XK_F2:
					 ++keyPressCounter;
					 printf("Activty 2; Total keypresses %d \n", keyPressCounter);
					 break;
				 case XK_F3:
					 ++keyPressCounter;
					 printf("Activty 3; Total keypresses: %d \n", keyPressCounter);
					 break;
				default:
					 break;
			}
		}
	}
	XCloseDisplay(display);
}

