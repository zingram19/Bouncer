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
                memcpy(lev_data[row], line.c_str(), 50);
            row++;
        }
        file.close();
    }

    // convert ASCII to numbers
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 50; j++) {
            lev_data[i][j] -= '0';
        }
    }
}

level::~level() {

}

void level::render(SDL_Renderer* render, double x) {
    // render each at proper location
    // for each col
    for (int j = 0; j < 50; j++) {
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