//
// Created by Zachary Ingram on 4/5/17.
//

#ifndef BOUNCER_LEVEL_H
#define BOUNCER_LEVEL_H


#include "texture.h"

class level {
public:
    // get level & load & pass in textures
    level(char lnum, texture* text);
    // free level
    ~level();
    // render level
    void render(SDL_Renderer* render, double x);
private:
    // level
    int lev;
    // texture holding tile sprites
    texture* tile;
    char lev_data[9][50];
};


#endif //BOUNCER_LEVEL_H
