// main header

#ifndef BOUNCER_MAIN_H
#define BOUNCER_MAIN_H

#include <SDL.h>
#include <SDL_image.h>

#include "const.h"

// classes
#include "game.h"
#include "texture.h"
#include "level.h"

// functions
void loop(game* g);
void handleInput(SDL_Event* e, cont* controls);

#endif //BOUNCER_MAIN_H
