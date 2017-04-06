// Game class functions
#include "game.h"

// Initalizes SDL & SDL_image
game::game() {
    initialized = false;
    window = NULL;
    renderer = NULL;
    window = SDL_CreateWindow("Bouncer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
    if (window == NULL)
        std::cout << "Window not loaded ERR = " << SDL_GetError() << std::endl;
    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL)
            std::cout << "Renderer not created ERR = " << SDL_GetError() << std::endl;
        else {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                std::cout << "SDL_Image not loaded ERR = " << SDL_GetError() << std::endl;
            }
            initialized = true;
            return;
        }
    }
}

// Fetch init
bool game::isInit() {
    return initialized;
}

// Clear frame
void game::clear() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
}

// Draw frame to screen
void game::draw() {
    SDL_RenderPresent(renderer);
}

// Quit all
game::~game() {
    if (initialized) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        SDL_DestroyWindow(window);
        window = NULL;
        IMG_Quit();
        SDL_Quit();
    }
}

SDL_Renderer* game::getRender(void) {
    return renderer;
}
