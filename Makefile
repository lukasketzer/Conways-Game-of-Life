CC = gcc
# CFLAGS = -Wall -Wextra -Wpedantic -g  `sdl2-config --cflags --libs` -fsanitize=address
CFLAGS = -Wall -Wextra -Wpedantic -g  `sdl2-config --cflags --libs`
FILES = $(filter-out ./src/conway_new.c, $(wildcard ./src/*.c))
OUTPUT = conway

.PHONY: all clean
all: clean main

main:
	$(CC) -o $(OUTPUT) $(FILES) $(CFLAGS)  

conway: clean
	$(CC) -o conway ./src/conway.c $(CFLAGS)

clean:
	rm -rf $(OUTPUT) conway_new
