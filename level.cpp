//
// Created by Zachary Ingram on 4/5/17.
//

#include "level.h"
#include <fstream>
using namespace std;

level::level(int lnum, texture* text) {
    lev = lnum;
    tile = text;
    // TODO load level in by number
    string line;
    ifstream file("lvl1");
    int row = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
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

void level::render(SDL_Renderer* render) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 50; j++) {
            if (lev_data[i][j] > 0) {
                tile->setframe(lev_data[i][j] - 1);
                tile->render(j * TILE_DIM, i * TILE_DIM, render);
            }
        }
    }
}