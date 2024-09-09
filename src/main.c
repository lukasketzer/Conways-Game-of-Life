#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

#include "conway.h"
#include "draw.h"
#include "init.h"
#include "structs.h"
#include "defs.h"
#include "events.h"

void handleEvents(CGOL *cgol) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseButtonDown(&event.button, cgol);
                break;
            case SDL_MOUSEMOTION:
                handleMouseMotion(&event.motion, cgol);
                break;
            default:
                break;
        }
    }
}

int main() {
    App app;
    CGOL *cgol;
    srand(time(NULL));
    cgol = CGOL_createWorld(20, 20);
    CGOL_fillUniverseRandom(cgol, 5);

    initSDL(&app);

    f32 fps = 20.0; 
    u32 delay;
    
    while(1) {
        prepareScene(&app);
        handleEvents(cgol);

        drawUniverseCGOL(&app, cgol, false);
        cgol = CGOL_iterate(cgol);
        
        presentScene(&app);
        delay = (u32) ((1.0/fps) * 1000.0);
        SDL_Delay(delay);
    }
    free(cgol); 
    return 0;
}
