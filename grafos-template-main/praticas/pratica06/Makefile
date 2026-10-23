CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: main

main: main.o dijkstra.o
	$(CC) $(CFLAGS) -o main main.o dijkstra.o

main.o: main.c dijkstra.h
	$(CC) $(CFLAGS) -c main.c99

dijkstra.o: dijkstra.c dijkstra.h
	$(CC) $(CFLAGS) -c dijkstra.c99

clean:
	rm -f *.o main main.exe

.PHONY: all clean