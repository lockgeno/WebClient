CC = gcc
CFLAGS = -g -Wall

all: main

main: src/main.c
	$(CC) $(CFLAGS) -o main src/main.c

clean:
	rm -f main *.o
	rm -r  *.dSYM