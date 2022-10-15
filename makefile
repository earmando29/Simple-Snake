CC=g++

all: main 

main: main.cpp
	$(CC) main.cpp -lncurses -o main

clean:
	rm *main