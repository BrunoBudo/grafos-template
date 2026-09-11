CC = gcc

CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g

TARGET = programa

OBJ = main.o busca_largura.o busca_profundidade.o


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)


main.o: main.c busca_largura.h busca_profundidade.h
	$(CC) $(CFLAGS) -c main.c


busca_largura.o: busca_largura.c busca_largura.h
	$(CC) $(CFLAGS) -c busca_largura.c


busca_profundidade.o: busca_profundidade.c busca_profundidade.h busca_largura.h
	$(CC) $(CFLAGS) -c busca_profundidade.c


clean:
	rm -f $(OBJ) $(TARGET)