CC = gcc
CFLAGS = -Wall -Wextra

all: chip8

run: chip8
		./chip8

chip8: main.c
		$(CC) $(CFLAGS) -o chip8 main.c

clean:
		rm -f chip8