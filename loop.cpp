// Event loop for game
#include <const.h>
#include "main.h"

void loop(game* g) {
    // TODO PLS NO GET MAD AT ME IS ONLY FOR DEBUG
    RESET:;

    // Loading graphics in
    // Load in tiles
    texture tiles("Tiles.png", g->getRender());
    tiles.settilesize(16, 16);
    // Load in level 1
    level lvl(1, &tiles);

    // Load dog in
    texture dog("Dog.png", g->getRender());
    dog.setframe(0);
    dog.settilesize(11, 11);

    // Dog wrapper and values
    d_t d;
    d.x = 140; d.y = 50; d.xv = 0; d.yv = 0; d.onGround = false;

    // Camera coord
    double camx = 0;

    // Initialize control variables
    cont controls;
    controls.up = false; controls.down = false; controls.left = false;
    controls.right = false; controls.reload = false;

    // Animation counter for death animation
    Uint8 frame = 0;

    // To break out of game
    bool running = true;
    // Event handler
    SDL_Event e;
    // Game loop
    while (running) {
        // Handling events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            // Get keyboard input
            else
                handleInput(&e, &controls);
        }
        // TODO REMOVE RESET CODE
        if (controls.reload) {
            lvl.~level();
            tiles.~texture();
            dog.~texture();
            goto RESET;
        }
        if (controls.newtext) {
            lvl.reload();
        }

        // Move dog
        dogControl(&controls, &d, &dog);

        // apply velocities
        d.x += d.xv;
        d.y += d.yv;

        // detect collisions
        lvl.detectCollision(&d);

        // Find camera
        if (d.x > SCR_W / 2) {
            camx = d.x - SCR_W / 2;
        }
        else {
            camx = 0;
        }
        if (camx > (TILE_DIM * LEVEL_W) - SCR_W)
            camx = TILE_DIM * LEVEL_W - SCR_W;

        // Start death
        if (d.y == SCR_H - DOG_W) {
            frame = 64;
            d.x = 140;
            d.y = 50;
            d.xv = 0;
            d.yv = 0;
            d.onGround = false;
        }

        //RENDERING BELOW
        // clear frame
        g->clear();

        // render all
        dog.render((int) d.x - (int) camx, (int) d.y, g->getRender());
        lvl.render(g->getRender(), camx);

        // Death animation
        if (frame) {
            SDL_SetRenderDrawColor(g->getRender(), 0xFF, 0x00, 0x00, frame * (Uint8)4);
            SDL_RenderFillRect(g->getRender(), NULL);
            frame--;
        }

        // draw frame to screen
        g->draw();
    }
};