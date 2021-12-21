all: build run clean

build:
	gcc -Wall -std=c99 *.c ../interfaces/dynamic_array/*.c -lm -o example
run:
	./example
clean:
	rm example
