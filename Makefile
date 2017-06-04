SOURCE=main.cpp lib/window.cpp lib/timer.cpp
MYPROGRAM=Eschatology
MYINCLUDES=
MYFLAGS=-std=c++14
MYLIBRARIES=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
CC=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) $(MYINCLUDES) $(MYFLAGS) $(SOURCE) -o$(MYPROGRAM) $(MYLIBRARIES)
clean:
	rm -f $(MYPROGRAM)
run:
	$(MYPROGRAM)
