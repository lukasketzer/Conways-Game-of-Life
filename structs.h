#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

#include "defs.h"
#include "conway.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    usize screenWidth;
    usize screenHeight;
    CGOL *cgol;
} App;


