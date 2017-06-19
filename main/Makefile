SOURCE=main.cpp lib/window.cpp lib/timer.cpp
PROGRAM=Eschatology
INCLUDES=
FLAGS=-std=c++14 -static-libgcc -static-libstdc++
LINKER=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CC=g++

all: $(PROGRAM)

$(PROGRAM): $(SOURCE)
	$(CC) $(INCLUDES) $(FLAGS) $(SOURCE) -o$(PROGRAM) $(LINKER)
clean:
	rm -f $(PROGRAM)
run:
	$(PROGRAM)
