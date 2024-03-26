#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "defs.h"

#include "conway.h"


void CGOL_fillUniverseRandom(CGOL *cgol, u32 chance) {
    for(usize i = 0; i < cgol->universeSize; i++) {
        if ((rand() % chance) == 0) {
            cgol->universe[i] = 1;
        }
    } 
}


void CGOL_clear(CGOL *cgol) {
    free(cgol->universe);
    u8 *universe = calloc(cgol->universeSize, sizeof(u8));
    if(!universe) {
        fprintf(stderr, "Error while allocating memory");
        exit(EXIT_FAILURE);
    }
    cgol->universe = universe;
    return;
}

void CGOL_print(CGOL *cgol) {
    for(usize y = 0; y < cgol->height; y++) {
        for(usize x = 0; x < cgol->width; x++) {
            cgol->universe[y * cgol->width + x] ? printf("■") : printf("□");
        }
        printf("\n");
    }
}

u8 getValue(CGOL *cgol, usize x, usize y) {
    // HACK: Veiileicht gibt es hier einen wraparound der dann falsch ist
    if (x > cgol->width  || y > cgol->height ) {
        return 0;
    }
    return cgol->universe[y * cgol->width + x] ? 1 : 0;
}

u8 getSurroundingValues(CGOL *cgol, usize x, usize y) {
    u8 value = 0; 
    value += getValue(cgol, x-1, y-1);
    value += getValue(cgol, x,   y-1);
    value += getValue(cgol, x+1, y-1);

    value += getValue(cgol, x-1, y);
    value += getValue(cgol, x+1, y);

    value += getValue(cgol, x-1, y+1);
    value += getValue(cgol, x,   y+1);
    value += getValue(cgol, x+1, y+1);

    return value;
}

void updateBoard(CGOL *cgol) {
    // TODO: Umschrieben, so dass das INPLACE gemacht wird
    u8 neighbours;
    u8 alive;
    usize idx;
    u8 *updatedUniverse = calloc(cgol->universeSize, sizeof(u8));
    if(!updatedUniverse) {
        fprintf(stderr, "Error while allocating board");
        exit(EXIT_FAILURE);
    }
    
    for(usize y = 0; y < cgol->height; y++) {
        for(usize x = 0; x < cgol->width; x++) {
            neighbours = getSurroundingValues(cgol, x, y);
            idx = y * cgol->width + x;
            alive = cgol->universe[idx];

            // Gamerules
            if (!alive && neighbours == 3){
                updatedUniverse[idx] = 1;          // lives
            } else if (alive && neighbours < 2) {
                continue;                       // dies
            } else if (alive && (neighbours == 2 || neighbours == 3)) {
                updatedUniverse[idx] = 1;          // lives
            } else if (alive && neighbours > 3) {
                continue;                       // dies
            } else {
                continue;                       // dies
            }

        }
    }
    free(cgol->universe);
    cgol->universe = updatedUniverse;
}


CGOL* CGOL_createWorld(usize width, usize height) {
    usize universeSize;
    CGOL *cgol = (CGOL*) malloc(sizeof(CGOL));

    if(!cgol) {
        fprintf(stderr, "Error while allocating board");
        exit(EXIT_FAILURE);
    }

    if (__builtin_umull_overflow(width, height, &universeSize)) {
        fprintf(stderr, "width and hight are too large");
        exit(EXIT_FAILURE);
    }

    u8 *universe = calloc(universeSize, sizeof(u8));
    if(!universe) {
        fprintf(stderr, "Error while allocating board");
        exit(EXIT_FAILURE);
    }


    
    cgol->universe = universe;
    cgol->universeSize = universeSize;
    cgol->width = width;
    cgol->height = height;

    return cgol;
}

void CGOL_iterate(CGOL *cgol) {
    if (!cgol) {
        fprintf(stderr, "No object supplied. Maybe you didn't initalize the config");
        return;
    }
    updateBoard(cgol);
    return;
}

void CGOL_createCell(CGOL *cgol, usize x, usize y){
    if (x > cgol->width || y > cgol->height) return;

    cgol->universe[y * cgol->width + x] = 1;
}





