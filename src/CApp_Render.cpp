#include "include/CApp.h"

void CApp::Render() {

    SDL_RenderClear(renderer);

    // won't want to render like this...
    for (uint i=0; i < textures.size(); i++){
        SDL_RenderCopy(renderer, textures[i], NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}
