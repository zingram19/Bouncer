//
// Created by Zachary Ingram on 4/5/17.
//

#ifndef BOUNCER_LEVEL_H
#define BOUNCER_LEVEL_H


#include "texture.h"

class level {
public:
    // get level
    level(int lnum);
    // free level
    ~level();

    void addTiles(texture* text);

private:
    // level
    int lev;

    texture* tile;
};


#endif //BOUNCER_LEVEL_H
