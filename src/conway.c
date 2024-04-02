#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "defs.h"

#include "conway.h"



void CGOL_free(CGOL *cgol){
    if (!cgol) return;
    if (cgol->universe) free(cgol->universe);
    free(cgol);
}

u8 CGOL_getValue(CGOL *cgol, usize x, usize y) {
    if (x > cgol->width  || y > cgol->height ) return 0;
    usize idx = (cgol->width * y + x); 
    usize part = idx >> 6; // div by 64
    u8 offset = idx % 64;
     
    return cgol->universe[part] & (1LL << offset) ? 1 : 0;
}

void CGOL_setValue(CGOL *cgol, usize x, usize y){
    if (x > cgol->width || y > cgol->height) return;
    usize idx = (cgol->width * y + x); 
    usize part = idx >> 6; // div by 64
    u8 offset = idx % 64;
    
    cgol->universe[part] |= 1LL << offset ;
}


u64* allocUniverse(usize width, usize height, usize *universeSize, usize *bufferSize){
    if (__builtin_umull_overflow(width, height, universeSize)) {
        fprintf(stderr, "width and hight are too large");
        exit(EXIT_FAILURE);
    }
    *bufferSize = (*universeSize / 64) + 1;
    u64 *universe = calloc(*bufferSize, sizeof(u64));

    if(!universe) {
        fprintf(stderr, "Error while allocating board");
        exit(EXIT_FAILURE);
    }
    return universe;
}

// DONE
void CGOL_fillUniverseRandom(CGOL *cgol, u32 chance) {
    for(usize y = 0; y < cgol->height; y++) {
        for(usize x = 0; x < cgol->width; x++) {
            if ((rand() % chance) == 0) {
                CGOL_setValue(cgol, x , y);
            }
        }
    }
}

// DONE
void CGOL_clear(CGOL *cgol) {
    free(cgol->universe);
    u64 *universe = allocUniverse(cgol->width, cgol->height, &cgol->universeSize, &cgol->bufferSize);
    cgol->universe = universe;
    return;
}



void CGOL_print(CGOL *cgol) {
    for(usize y = 0; y < cgol->height; y++) {
        for(usize x = 0; x < cgol->width; x++) {
            CGOL_getValue(cgol, x, y) ?  printf("■") : printf("□");
        }
        printf("\n");
    }
}

u8 getSurroundingValues(CGOL *cgol, usize x, usize y) {
    u8 value = 0; 
    value += CGOL_getValue(cgol, x-1, y-1);
    value += CGOL_getValue(cgol, x,   y-1);
    value += CGOL_getValue(cgol, x+1, y-1);

    value += CGOL_getValue(cgol, x-1, y);
    value += CGOL_getValue(cgol, x+1, y);

    value += CGOL_getValue(cgol, x-1, y+1);
    value += CGOL_getValue(cgol, x,   y+1);
    value += CGOL_getValue(cgol, x+1, y+1);

    return value;
}

CGOL* updateBoard(CGOL *cgol) {
    u8 neighbours;
    bool alive;
    
    CGOL *new_cgol = CGOL_createWorld(cgol->width, cgol->height);

    for(usize y = 0; y < cgol->height; y++) {
        for(usize x = 0; x < cgol->width; x++) {
            neighbours = getSurroundingValues(cgol, x, y);
            alive = CGOL_getValue(cgol, x, y);

            // Gamerules
            if (!alive && neighbours == 3){
                CGOL_setValue(new_cgol, x, y);            // lives
            } else if (alive && neighbours < 2) {
                continue;                                       // dies
            } else if (alive && (neighbours == 2 || neighbours == 3)) {
                CGOL_setValue(new_cgol, x, y);                // lives
            } else if (alive && neighbours > 3) {
                continue;                                       // dies
            } else {
                continue;                                       // dies
            }

        }
    }
    CGOL_free(cgol);
    return new_cgol;
}



CGOL* CGOL_createWorld(usize width, usize height) {
    usize universeSize;
    usize bufferSize;
    CGOL *cgol = (CGOL*) malloc(sizeof(CGOL));

    if(!cgol) {
        fprintf(stderr, "Error while allocating board");
        exit(EXIT_FAILURE);
    }

    u64 *universe = allocUniverse(width, height, &universeSize, &bufferSize);

    
    cgol->universe = universe;
    cgol->universeSize = universeSize;
    cgol->bufferSize = bufferSize;
    cgol->width = width;
    cgol->height = height;

    return cgol;
}

CGOL* CGOL_iterate(CGOL *cgol) {
    if (!cgol) {
        fprintf(stderr, "No object supplied. Maybe you didn't initalize the config");
        exit(EXIT_FAILURE);
    }
    return updateBoard(cgol);
}



