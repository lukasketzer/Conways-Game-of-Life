CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g  `sdl2-config --cflags --libs`
FILES = ./src/*c
OUTPUT = conway

.PHONY: all clean
all: clean main

main:
	$(CC) -o $(OUTPUT) $(FILES) $(CFLAGS)  

conway: clean
	$(CC) -o conway_new ./src/conway_new.c $(CFLAGS)

clean:
	rm -rf $(OUTPUT) conway_new
