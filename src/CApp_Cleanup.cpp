#include "include/CApp.h"

void CApp::Cleanup() {
    for (uint i=0; i < textures.size(); i++){
        if (textures[i]) {
            SDL_DestroyTexture(textures[i]);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);

    screen = nullptr;
    renderer = nullptr;

    SDL_Quit();
}

