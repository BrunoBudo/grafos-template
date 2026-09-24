CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main
SRCS = $(wildcard *.c)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lm

clean:
	rm -f $(TARGET) *.o