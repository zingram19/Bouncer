// Handle controls

#include "main.h"

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
                break;
            case SDLK_BACKQUOTE:
                controls->reload = true;
                break;
            case SDLK_1:
                controls->newtext = true;
                break;
            default:
                break;
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
                break;
            case SDLK_BACKQUOTE:
                controls->reload = false;
            case SDLK_1:
                controls->newtext = false;
                break;
            default:
                break;
        }
    }
}

void dogControl(cont* controls, d_t* d, texture* dog) {
    // L/R control application
    if (controls->right) {
        d->xv += D_WALK_SPEED;
        // walkin jump
        if (d->onGround && !controls->up && !controls->down) {
            d->onGround = false;
            d->yv = D_WALK_J;
        }
        if (controls->down)
            d->xv -= D_CWALK_SPEED;
    }
    if (controls->left) {
        d->xv -= D_WALK_SPEED;
        // walkin jump
        if (d->onGround && !controls->up && !controls->down) {
            d->onGround = false;
            d->yv = D_WALK_J;
        }
        if (controls->down)
            d->xv += D_CWALK_SPEED;
    }

    // Point the right way
    //right
    if (d->xv > .3)
        dog->setframe(0);
    //left
    if (d->xv < -.3)
        dog->setframe(2);
    // sit
    if (controls->down && !controls->up) {
        if (!(dog->getFrame() % 2))
            dog->setframe(dog->getFrame() + 1);
    }
    // stand
    if ((((controls->left or controls->right) && !controls->down) or controls->up) && (dog->getFrame() % 2))
        dog->setframe(dog->getFrame() - 1);





    // gravity
    if (!d->onGround) {
        d->yv += GRAVITY;
    }

    // land on bottom TODO land on platform
    if (d->y > SCR_H - (dog->height * IMG_SCALE)) {
        d->y = SCR_H - (dog->height * IMG_SCALE);
        d->yv = 0;
        d->onGround = true;
    }

    // jump
    if (d->onGround && controls->up) {
        d->yv = D_JUMP_MAX;
        d->onGround = false;
    }

    // variable jump here
    if (!d->onGround && !controls->up && d->yv < D_JUMP_MIN) {
        d->yv = D_JUMP_MIN;
    }

    // apply velocities
    d->x += d->xv;
    d->y += d->yv;
    d->xv -= d->xv / 6;
    if (controls->down)
        d->xv = d->xv * RESISTANCE;
    if ((d->xv < .25 && d->xv > 0) or (d->xv > -.25 && d->xv < 0))
        d->xv = 0;
    if (d->x < 0)
        d->x = 0;
}