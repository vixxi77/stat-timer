CC = gcc

CFLAGS = $(shell sdl2-config --cflags --libs)

LDFLAGS = -lX11 -lSDL2_ttf

SRC = $(wildcard src/*.c)

TARGET = program 

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET)

clean:
	rm program
