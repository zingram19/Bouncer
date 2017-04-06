// Handle controls

#include "main.h"
#include "const.h"

void handleInput(SDL_Event* e, cont* controls) {
    // Press key
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
            case SDLK_d:
                controls->right = true;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                controls->left = true;
                break;
            case SDLK_UP:
            case SDLK_w:
            case SDLK_SPACE:
                controls->up = true;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                controls->down = true;
        }
    }

    // Unpress keu
    else if (e->type == SDL_KEYUP && e->key.repeat == 0) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
            case SDLK_d:
                controls->right = false;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                controls->left = false;
                break;
            case SDLK_UP:
            case SDLK_w:
            case SDLK_SPACE:
                controls->up = false;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                controls->down = false;
        }
    }
}