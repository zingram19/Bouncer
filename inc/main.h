// main header

#ifndef BOUNCER_MAIN_H
#define BOUNCER_MAIN_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "const.h"

// classes
#include "game.h"
#include "texture.h"
#include "level.h"

// functions
void loop(game* g);
void handleInput(SDL_Event* e, cont* controls);
void dogControl(cont* controls, d_t* d, texture* dog);

#endif //BOUNCER_MAIN_H
