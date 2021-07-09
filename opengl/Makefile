CC = gcc
CCFLAGS = -W -Wall -Wextra -pedantic -g

LINKERFLAGS = -lSDL2 -lGLEW -lGLU -lGL 

all: gui

debug: CCFLAGS += -DDEBUG
debug: gui

gui: 
	$(CC) $(CCFLAGS) src/main.c -o bin/gui $(LINKERFLAGS)

clean:
	rm -rf bin/*
