#include "init.h"
#include "draw.h"
#include "defs.h"
#include "structs.h"
#include "conway.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdbool.h>


void prepareScene(App *app)
{
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
}

void presentScene(App *app)
{
    SDL_RenderPresent(app->renderer);
}

// BUG: Am unteren rand werden pixel gerendert, die warscheinlich nicht zum board gehört (drübermalen löst segfault aus)
// und wenn man an den rechten rand mal, wird es auch links angezeigt
void drawUniverseCGOL(App *app, CGOL *cgol, bool rainbow){
    SDL_Rect cell;
    usize cellWidth = (cellWidth = SCREEN_WIDTH / cgol->width) != 0 ? cellWidth : 1;
    usize cellHeight = (cellHeight = SCREEN_HEIGHT / cgol->height) != 0 ? cellHeight : 1;

    for(usize y = 0; y < cgol->height; y++) {
        for(usize x = 0; x < cgol->width; x++) {
            cell.x = x * cellWidth;
            cell.y = y * cellHeight;
            cell.w = cellWidth;
            cell.h = cellHeight;

            if (CGOL_getValue(cgol, x, y)) {
                if(!rainbow) {
                    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
                } else {
                    SDL_SetRenderDrawColor(app->renderer, rand() % 255,rand() % 255, rand() % 255, 255);
                }
                SDL_RenderFillRect(app->renderer, &cell);
            }
            else {
                SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(app->renderer, &cell);
            }
        }
    }
    
    return;
}
