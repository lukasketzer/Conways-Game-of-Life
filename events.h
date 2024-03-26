#pragma once
#include <SDL2/SDL_events.h>

#include "conway.h"


void handleMouseButtonDown(SDL_MouseButtonEvent *event, CGOL *cgol);
void handleMouseMotion(SDL_MouseMotionEvent *event, CGOL *cgol);
