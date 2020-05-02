CC=g++
# CFLAGS=--std=c++11
SRC=src/arbres.cpp main.cpp
EXEC=bin/arbres
DIRS=bin

all: $(EXEC)

bin/arbres: src/arbres.cpp src/main.cpp
	$(CC) -o bin/arbres src/arbres.cpp src/main.cpp

clean:
	rm -rf bin

# will create all necessary directories after the Makefile is parsed
$(shell mkdir -p $(DIRS))
