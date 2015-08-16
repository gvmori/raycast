#include "include/CApp.h"

bool CApp::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    Uint16 width = config.view_width;
    Uint16 height = config.view_height;

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

    renderer = SDL_CreateRenderer(
        screen, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

    if (renderer == nullptr) {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // TODO: reset pitch on window resize
    // don't free this surface, will be cleaned up on window destruction
    SDL_Surface* screen_surface = SDL_GetWindowSurface(screen);
    screen_pitch_mod = screen_surface->pitch;
    screen_format = screen_surface->format;
    screen_surface = nullptr;

    int amask;
    int rmask;
    int gmask;
    int bmask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    screen_buffer_surf = SDL_CreateRGBSurface(
        0, width, height, 32, 
        rmask, gmask, bmask, amask
        );

    screen_buffer_tex = SDL_CreateTexture(
        renderer, 
        screen_format->format,
        SDL_TEXTUREACCESS_STREAMING,
        width, height
        );

    SDL_ShowCursor(0);
    LoadLevel();


    return true;
}
