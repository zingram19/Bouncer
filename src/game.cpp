// Game class functions
#include "game.h"

// Initializes SDL & SDL_image
game::game() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
        std::cout << "SDL Not Initalized ERR = " << SDL_GetError() << std::endl;
    }
    initialized = false;
    window = NULL;
    renderer = NULL;
    music = NULL;
    window = SDL_CreateWindow("Bouncer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
    if (window == NULL)
        std::cout << "Window not loaded ERR = " << SDL_GetError() << std::endl;
    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL)
            std::cout << "Renderer not created ERR = " << SDL_GetError() << std::endl;
        else {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                std::cout << "SDL_Image not loaded ERR = " << SDL_GetError() << std::endl;
            }
            // Start music
            if (Mix_OpenAudio(22050, AUDIO_U8, 2, 4096) == -1) {
                std::cout << "SDLMIXER not loaded ERR = " << Mix_GetError() << std::endl;
            }
            // load music
            music = Mix_LoadMUS("resources/Music.wav");
            // why do I need this?
            Mix_GetError();
            if (music == NULL) {
                std::cout << "Could not load music ERR = " << Mix_GetError() << std::endl;
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
        Mix_FreeMusic(music);
        Mix_CloseAudio();
    }
}

SDL_Renderer* game::getRender(void) {
    return renderer;
}

Mix_Music* game::getMusic(void) {
    return music;
}