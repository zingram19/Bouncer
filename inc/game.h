// Game wrapper class

#ifndef BOUNCER_GAME_H
#define BOUNCER_GAME_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <SDL2_mixer/SDL_mixer.h>

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
    // fetch music
    Mix_Music* getMusic(void);
private:
    // window
    SDL_Window* window;
    // renderer
    SDL_Renderer* renderer;
    // init success val
    bool initialized;
    // Music holder
    Mix_Music* music;
};


#endif //BOUNCER_GAME_H
