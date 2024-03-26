#pragma once

#include "init.h"
#include "draw.h"
#include "conway.h"
#include "structs.h"
#include <stdbool.h>



void prepareScene(App *app);
void presentScene(App *app);
void drawUniverseCGOL(App *app, CGOL *cgol, bool rainbow);
