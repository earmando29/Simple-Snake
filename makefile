CC=g++

all: main

main: snake.cpp
	$(CC) snake.cpp -lncurses -o snake

clean:
	rm *snake