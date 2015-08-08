#include "include/CApp.h"

bool CApp::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    unsigned int width = config.view_width;
    unsigned int height = config.view_height;

    screen = SDL_CreateWindow("GameWindow!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            // use opengl??
            SDL_WINDOW_RESIZABLE
            );

    if (screen == nullptr) {
        return false;
    }

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        return false;
    }
    // screen_surface = SDL_GetWindowSurface(screen);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    LoadLevel();

    return true;
}
