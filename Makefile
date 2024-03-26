CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g  `sdl2-config --cflags --libs`
FILES = main.c draw.c init.c conway.c events.c
OUTPUT = main

.PHONY: all
all: clean main

main:
	$(CC) -o $(OUTPUT) $(FILES) $(CFLAGS)  
conway: clean
	$(CC) -o conway conway.c $(CFLAGS)

	
.PHONY: clean
clean:
	rm -rf $(OUTPUT) conway
