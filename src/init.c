#include <stdio.h>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "init.h"
#include "defs.h"
#include "structs.h"


void initSDL(App *app) {
    int rendererFlags, windowFlags;
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = SDL_WINDOW_RESIZABLE;
    app->screenWidth = SCREEN_WIDTH;
    app->screenHeight = SCREEN_HEIGHT;


    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could initalize sdl video: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // create window
    app->window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->screenWidth, app->screenHeight, windowFlags);

    if(!app->window) {
        fprintf(stderr, "Couldn't open window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // create renderer
    app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

    if(!app->renderer) {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return;
}


