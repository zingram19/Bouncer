// Game wrapper class

#ifndef BOUNCER_GAME_H
#define BOUNCER_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "const.h"
#include "texture.h"

class game {
public:
    // init
    game();
    // quit
    ~game();
    // fetch var
    bool isInit(void);
    // clear frame
    void clear(void);
    // draw frame to screen
    void draw(void);
    // fetch renderer
    SDL_Renderer* getRender(void);
private:
    // window
    SDL_Window* window;
    // renderer
    SDL_Renderer* renderer;
    // init success val
    bool initialized;
};


#endif //BOUNCER_GAME_H
