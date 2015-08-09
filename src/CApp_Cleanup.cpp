#include "include/CApp.h"

void CApp::Cleanup() {
    for (Uint8 i=0; i < textures.size(); i++){
        if (textures.at(i)) {
            SDL_DestroyTexture(textures[i]);
        }
    }

    SDL_FreeSurface(screen_buffer_surf);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_DestroyTexture(screen_buffer_tex);

    screen = nullptr;
    renderer = nullptr;
    screen_buffer_tex = nullptr;
    screen_buffer_surf = nullptr;
    screen_format = nullptr;

    SDL_Quit();
}
