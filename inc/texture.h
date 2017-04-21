//
// Created by Zachary Ingram on 4/3/17.
//

#ifndef BOUNCER_TEXTURE_H
#define BOUNCER_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "const.h"

class texture {
public:
    // load/init
    texture(const char* path, SDL_Renderer* renderer);
    // free
    ~texture();
    // set cols
    void settilesize(uint8_t wid, uint8_t hei);
    // set frame
    void setframe(int newframe);
    // render to screen
    void render(int x, int y, SDL_Renderer* renderer);
    // get frame
    int getFrame();

    // w/h per tile
    uint8_t width, height;
private:
    bool initalized;
    // texture
    SDL_Texture* txture;
    // # tiles per row
    uint8_t cols;
    // w/h of whole image
    int w, h;
    // current frame
    int frame;
};


#endif //BOUNCER_TEXTURE_H
