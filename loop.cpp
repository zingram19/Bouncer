// Event loop for game
#include "main.h"

void loop(game* g) {
    // Loading graphics in
    // Load in tiles
    texture tiles("Tiles.png", g->getRender());
    tiles.settilesize(16, 16);
    // Load in level 1
    level lvl1(1, &tiles);

    // Load dog in
    texture dog("Dog.png", g->getRender());
    dog.setframe(0);
    dog.settilesize(11, 11);
    // wrapper for dog
    struct {
        double x = 50, y = 50;
        double xv = 0, yv = 0;
        bool onGround = false;
    } d;

    // Initialize control variables
    cont controls;
    controls.up = false;
    controls.down = false;
    controls.left = false;
    controls.right = false;

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
        // L/R control application
        if (controls.right) {
            d.xv += D_WALK_SPEED;
            // walkin jump
            if (d.onGround && !controls.up && !controls.down) {
                d.onGround = false;
                d.yv = D_WALK_J;
            }
            if (controls.down)
                d.xv -= D_CWALK_SPEED;
        }
        if (controls.left) {
            d.xv -= D_WALK_SPEED;
            // walkin jump
            if (d.onGround && !controls.up && !controls.down) {
                d.onGround = false;
                d.yv = D_WALK_J;
            }
            if (controls.down)
                d.xv += D_CWALK_SPEED;
        }

        // Point the right way
        //right
        if (d.xv > .3)
            dog.setframe(0);
        //left
        if (d.xv < -.3)
            dog.setframe(2);
        // sit
        if (controls.down && !controls.up) {
            if (!(dog.getFrame() % 2))
                dog.setframe(dog.getFrame() + 1);
        }
        // stand
        if ((((controls.left or controls.right) && !controls.down) or controls.up) && (dog.getFrame() % 2))
            dog.setframe(dog.getFrame() - 1);

        // gravity
        if (!d.onGround) {
            d.yv += GRAVITY;
        }

        // land on bottom TODO land on platform
        if (d.y > SCR_H - (dog.height * IMG_SCALE)) {
            d.y = SCR_H - (dog.height * IMG_SCALE);
            d.yv = 0;
            d.onGround = true;
        }

        // jump
        if (d.onGround && controls.up) {
            d.yv = D_JUMP_MAX;
            d.onGround = false;
        }

        // variable jump here
        if (!d.onGround && !controls.up && d.yv < D_JUMP_MIN) {
            d.yv = D_JUMP_MIN;
        }

        // apply velocities
        d.x += d.xv;
        d.y += d.yv;
        d.xv -= d.xv / 6;
        if (controls.down)
            d.xv = d.xv * RESISTANCE;
        if ((d.xv < .25 && d.xv > 0) or (d.xv > -.25 && d.xv < 0))
            d.xv = 0;

        //RENDERING BELOW
        // clear frame
        g->clear();

        // render all
        //d.render();
        dog.render((int) d.x, (int) d.y, g->getRender());
        lvl1.render(g->getRender());

        // draw frame to screen
        g->draw();
    }
};