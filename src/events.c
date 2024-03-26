#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

#include "conway.h"
#include "events.h"
#include "defs.h"

void handleMouseButtonDown(SDL_MouseButtonEvent *event, CGOL *cgol){
    usize cellWidth;
    usize cellHeight;
    switch(event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button == SDL_BUTTON_LEFT) {
                cellWidth = (cellWidth = SCREEN_WIDTH / cgol->width) != 0 ? cellWidth : 1;
                cellHeight = (cellHeight = SCREEN_HEIGHT / cgol->height) != 0 ? cellHeight : 1;
                CGOL_createCell(cgol, event->x / cellWidth, event->y / cellHeight);
            } else if (event->button == SDL_BUTTON_RIGHT) {
                CGOL_clear(cgol);
            }
            break;
    default:
            break;
    }
    return;
}

// HACK: das ganze mit cellWidth ist einfach nicth schön aber es funktioniert (gilt auch für oben)
void handleMouseMotion(SDL_MouseMotionEvent *event, CGOL *cgol) {
    usize cellWidth;
    usize cellHeight;
    switch(event->type) {
        case SDL_MOUSEMOTION:
            if (CHECKFLAGS(event->state, SDL_BUTTON_LMASK)) {
                cellWidth = (cellWidth = SCREEN_WIDTH / cgol->width) != 0 ? cellWidth : 1;
                cellHeight = (cellHeight = SCREEN_HEIGHT / cgol->height) != 0 ? cellHeight : 1;
                CGOL_createCell(cgol, event->x / cellWidth, event->y / cellHeight);
            }
            break;
        default:
            break;
    }
}
