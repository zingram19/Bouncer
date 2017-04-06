//
// Created by Zachary Ingram on 4/3/17.
//

#include "texture.h"

// Loads in texture
texture::texture(const char *path, SDL_Renderer* renderer) {
    initalized = false;
    txture = NULL;
    SDL_Surface* loader = NULL;
    loader = IMG_Load(path);
    if (loader == NULL)
        std::cout << "Unable to load img ERR = " << IMG_GetError() << std::endl;
    else {
        // erase cyan pixels (for BMPs)
        SDL_SetColorKey(loader, SDL_TRUE, SDL_MapRGB(loader->format, 0, 0xFF, 0xFF));

        // create texture
        txture = SDL_CreateTextureFromSurface(renderer, loader);
        if (txture == NULL)
            std::cout << "Couldn't create txture ERR = " << SDL_GetError() << std::endl;
        else {
            // get dims
            w = loader->w;
            h = loader->h;
            initalized = true;
        }

        // free surface
        SDL_FreeSurface(loader);
    }
}

// free all
texture::~texture() {
    if (txture != NULL) {
        SDL_DestroyTexture(txture);
        w = 0;
        h = 0;
        width = 0;
        height = 0;
        cols = 0;
        initalized = false;
        txture = NULL;
    }
}

// Set size of tile
void texture::settilesize(uint8_t wid, uint8_t hei) {
    width = wid;
    height = hei;
    cols = (uint8_t)(w / wid);
}

// sets frame
void texture::setframe(int newframe) {
    frame = newframe;
}

// renders tile to renderer
void texture::render(int x, int y, SDL_Renderer* renderer) {
    SDL_Rect src;
    src.x = (frame % cols) * width;
    src.y = (frame / cols) * height;
    src.w = width;
    src.h = height;

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = width * IMG_SCALE;
    dest.h = height * IMG_SCALE;

    // actually render
    SDL_RenderCopy(renderer, txture, &src, &dest);
}

int texture::getFrame() {
    return frame;
}