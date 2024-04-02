#pragma once

#include <stddef.h>
#include "defs.h"

typedef struct {
    u64 *universe;
    usize universeSize;
    usize bufferSize;
    usize width;
    usize height;
} CGOL;

// TODO: documentation

CGOL* CGOL_createWorld(usize width, usize height);
CGOL* CGOL_iterate(CGOL *cgol);
void CGOL_print(CGOL *cgol);
void CGOL_fillUniverseRandom(CGOL *cgol, u32 chance);
void CGOL_setValue(CGOL *cgol, usize x, usize y);
u8 CGOL_getValue(CGOL *cgol, usize x, usize y);
void CGOL_clear(CGOL *cgol);
void CGOL_free(CGOL *cgol);

