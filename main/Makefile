SOURCE=main.cpp lib/window.cpp lib/timer.cpp
PROGRAM=main
INCLUDES=
FLAGS=-std=c++14 -static-libgcc -static-libstdc++ -mwindows
LINKER=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer icon.res
CC=g++

all:
	$(CC) $(INCLUDES) $(FLAGS) $(SOURCE) -o$(PROGRAM) $(LINKER)
	$(PROGRAM)
