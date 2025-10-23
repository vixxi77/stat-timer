CC = gcc

CFLAGS = $(shell sdl2-config --cflags --libs)

LDFLAGS = -lX11 -lSDL2_ttf

program:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c window.c timer.c -o program

clean:
	rm program
