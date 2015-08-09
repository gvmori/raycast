#include "include/CApp.h"

void CApp::Render() {
    SDL_UpdateTexture(
        screen_buffer_tex, 
        NULL,  
        screen_buffer_surf->pixels,
        screen_pitch_mod);


    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screen_buffer_tex, NULL, NULL);

    SDL_RenderPresent(renderer);
}
