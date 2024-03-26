#pragma once

#include <stddef.h>
#include "defs.h"

typedef struct {
    u8 *universe;
    usize universeSize;
    usize width;
    usize height;
} CGOL;

// TODO: documentation

CGOL* CGOL_createWorld(usize width, usize height);
void CGOL_iterate(CGOL *cgol);
void CGOL_print(CGOL *cgol);
void CGOL_fillUniverseRandom(CGOL *cgol, u32 chance);
void CGOL_createCell(CGOL *cgol, usize x, usize y);
void CGOL_clear(CGOL *cgol);
