//
// Created by Zachary Ingram on 4/5/17.
//

#include "level.h"

level::level(int lnum) {
    lev = lnum;
    // TODO load level in

}

level::~level() {

}

void level::addTiles(texture *text) {
    tile = text;
}