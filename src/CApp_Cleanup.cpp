#include "include/CApp.h"

void CApp::Cleanup() {
    // for (int i=0; i < config.view_height; i++){
    //     delete pixel_buffer[i];
    // }
    // delete pixel_buffer;

    SDL_FreeSurface(screen_buffer_surf);

    for (int i=0; i < textures.size(); i++){
        if (textures.at(i)) {
            SDL_DestroyTexture(textures[i]);
        }
    }
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

