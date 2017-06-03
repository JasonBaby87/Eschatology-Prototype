SOURCE=main.cpp lib/window.cpp
MYPROGRAM=Eschatology
MYINCLUDES=-std=c++14
MYLIBRARIES=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
CC=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) $(MYINCLUDES) $(SOURCE) -o$(MYPROGRAM) $(MYLIBRARIES)
clean:
	rm -f $(MYPROGRAM)
run:
	$(MYPROGRAM)
