//
// Created by Zachary Ingram on 4/5/17.
//

#include "level.h"
#include <fstream>

using namespace std;

level::level(char lnum, texture* text) {
    lev = lnum;
    tile = text;
    // Name of level file
    char name[] = "lvl0";
    name[3] = lnum + '0';
    string line;
    // open file
    ifstream file(name);
    int row = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            // copy line by line level into array
            if (row < 9)
                memcpy(lev_data[row], line.c_str(), LEVEL_W);
            row++;
        }
        file.close();
    }

    // convert ASCII to numbers
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < LEVEL_W; j++) {
            lev_data[i][j] -= '0';
        }
    }
}

level::~level() {

}

void level::render(SDL_Renderer* render, double x) {
    // render each at proper location
    // for each col
    for (int j = 0; j < LEVEL_W; j++) {
        // if col in screen
        if (j * TILE_DIM > x - TILE_DIM && j * TILE_DIM < x + SCR_W) {
            // render col
            for (int i = 0; i < 9; i++) {
                if (lev_data[i][j] > 0) {
                    tile->setframe(lev_data[i][j] - 1);
                    tile->render(j * TILE_DIM - (int) x, i * TILE_DIM, render);
                }
            }
        }
    }
}

void level::reload() {
    char name[] = "lvl0";
    name[3] = (char) lev + '0';
    string line;
    // open file
    ifstream file(name);
    int row = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            // copy line by line level into array
            if (row < 9)
                memcpy(lev_data[row], line.c_str(), LEVEL_W);
            row++;
        }
        file.close();
    }

    // convert ASCII to numbers
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < LEVEL_W; j++) {
            lev_data[i][j] -= '0';
        }
    }
}

int level::detectCollisionCor(d_t* d) {
    // 1 = Top/left 2 = Top/right 4 = Bottom/left 8 = Bottom/right
    int col = 0;
    // TL corner
    if (lev_data[(int) d->y / TILE_DIM][(int)d->x / TILE_DIM]) {
        if (lev_data[(int) d->y / TILE_DIM][(int)d->x / TILE_DIM] < 12) {
            col |= 1;
        }
    }
    // TR corner
    if (lev_data[(int) d->y / TILE_DIM][((int) d->x + DOG_W)/ TILE_DIM]) {
        if (lev_data[(int) d->y / TILE_DIM][((int) d->x + DOG_W) / TILE_DIM] < 12) {
            col |= 2;
        }
    }
    // BL corner
    if (lev_data[((int) d->y + DOG_W) / TILE_DIM][(int) d->x / TILE_DIM]) {
        if (lev_data[((int) d->y + DOG_W) / TILE_DIM][(int)d->x / TILE_DIM] < 12) {
            col |= 4;
        }
    }
    // BR corner
    if (lev_data[((int) d->y + DOG_W) / TILE_DIM][((int) d->x + DOG_W) / TILE_DIM]) {
        if (lev_data[((int) d->y + DOG_W) / TILE_DIM][((int) d->x + DOG_W) / TILE_DIM] < 12) {
            col |= 8;
        }
    }
    return col;
}

// 1 = Top/left 2 = Top/right 4 = Bottom/left 8 = Bottom/right

void level::detectCollision(d_t* d) {
    int col = this->detectCollisionCor(d);
    // Full down collision
    if ((col & 12) == 12) {
        d->y = (1 + (int) d->y / TILE_DIM) * TILE_DIM - DOG_W;
        d->yv = 0;
        d->onGround = true;
        col -= 12;
    }
    // full up collision
    else if ((col & 3) == 3) {
        d->y = (1 + (int) d->y / TILE_DIM) * TILE_DIM;
        d->yv = 1;
        col -= 3;
    }
    // full left collision
    if ((col & 5) == 5) {
        d->x = (1 + (int) d->x / TILE_DIM) * TILE_DIM;
        d->xv = 0;
        col -= 5;
    }
    // full right collision
    else if ((col & 10) == 10) {
        d->x = (1 + (int) d->x / TILE_DIM) * TILE_DIM - DOG_W;
        d->xv = 0;
        col -= 10;
    }
    // speed up
    if (!col)
        return;

    // Partial collisions (one corner)
    //TL
    if (col & 1) {
        if (TILE_DIM - ((int) d->x % TILE_DIM) > TILE_DIM - ((int) d->y % 64)) {
            d->y = (1 + (int) d->y / TILE_DIM) * TILE_DIM;
            d->yv = 1;
        }
        // collided on the left
        else {
            d->x = (1 + (int) d->x / TILE_DIM) * TILE_DIM;
            d->xv = 0;
        }
    }
    //TR
    else if (col & 2) {
        if ((int) d->x % TILE_DIM > TILE_DIM - ((int) d->y % 64)) {
            d->y = (1 + (int) d->y / TILE_DIM) * TILE_DIM;
            d->yv = 1;
        }
        else {
            d->x = (1 + (int) d->x / TILE_DIM) * TILE_DIM - DOG_W;
            d->xv = 0;
        }
    }
    //BL
    else if (col & 4) {
        // collided on bottom of dog
        if ((TILE_DIM - ((int) d->x % TILE_DIM)) + 8 > (int) d->y % 64) {
            d->y = (1 + (int) d->y / TILE_DIM) * TILE_DIM - DOG_W;
            d->yv = 0;
            d->onGround = true;
        }
        // collided on the left
        else {
            d->x = (1 + (int) d->x / TILE_DIM) * TILE_DIM;
            d->xv = 0;
        }
    }
    //BR
    else {
        if ((int) d->x % TILE_DIM > (int) d->y % 64) {
            d->y = (1 + (int) d->y / TILE_DIM) * TILE_DIM - DOG_W;
            d->yv = 0;
            d->onGround = true;
        }
        else {
            d->x = (1 + (int) d->x / TILE_DIM) * TILE_DIM - DOG_W;
            d->xv = 0;
        }
    }
}

void level::setLev(int level) {
    lev = level;
}