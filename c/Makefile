all : main

build/ackermann.o: ackermann.c ackermann.h
	gcc -c ackermann.c -o build/ackermann.o

build/main.o: main.c
	gcc -c main.c -o build/main.o

main: build/main.o build/ackermann.o 
	gcc -o main build/main.o build/ackermann.o 

clean:
	rm -rf main build/ && mkdir build

.PHONY: all clean
