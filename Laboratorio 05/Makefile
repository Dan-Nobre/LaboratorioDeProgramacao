# Makefile

CC = gcc
CFLAGS = -Wall
TARGET = investimento

SRC = src/main.c src/calculo_investimento.c src/gerenciamento_investimento.c
HEADERS = src/calculo_investimento.h src/gerenciamento_investimento.h src/investimento.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

