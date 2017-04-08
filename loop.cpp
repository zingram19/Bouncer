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
    d.x = 50; d.y = 50; d.xv = 0; d.yv = 0; d.onGround = false;

    // Camera coord
    double camx = 0;

    // Initialize control variables
    cont controls;
    controls.up = false; controls.down = false; controls.left = false;
    controls.right = false; controls.reload = false;

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

        // Find camera
        if (d.x > SCR_W / 2)
            camx = d.x - SCR_W / 2;
        if (camx > (TILE_DIM * LEVEL_W) - SCR_W)
            camx = TILE_DIM * LEVEL_W - SCR_W;

        //RENDERING BELOW
        // clear frame
        g->clear();

        // render all
        dog.render((int) d.x - (int) camx, (int) d.y, g->getRender());
        lvl.render(g->getRender(), camx);

        // draw frame to screen
        g->draw();
    }
};