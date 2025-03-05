CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: main

main: main.o malloc.o free.o
	$(CC) $(CFLAGS) -o main main.o malloc.o free.o

main.o: main.c malloc.h
	$(CC) $(CFLAGS) -c main.c

malloc.o: malloc.c malloc.h
	$(CC) $(CFLAGS) -c malloc.c

free.o: free.c malloc.h
	$(CC) $(CFLAGS) -c free.c

clean:
	rm -f *.o main
