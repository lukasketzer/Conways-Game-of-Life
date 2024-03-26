CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g  `sdl2-config --cflags --libs`
FILES = ./src/*c
OUTPUT = conway

.PHONY: all
all: clean main

main:
	$(CC) -o $(OUTPUT) $(FILES) $(CFLAGS)  

.PHONY: clean
clean:
	rm -rf $(OUTPUT) conway
