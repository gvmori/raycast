#include "include/CApp.h"

bool CApp::LoadLevel() {
    // TODO actually do this
    SDL_Surface* bmp = SDL_LoadBMP("/code/cpp/raycast/img/1.bmp");
    if (bmp == nullptr) {
        return false;
    }

    textures.emplace_back(SDL_CreateTextureFromSurface(renderer, bmp));
    // TODO: check for nullptr at end of textures, if loading failed

    SDL_FreeSurface(bmp);
    bmp = nullptr;

    // generate test level
    int max_x = 12;
    int max_y = 12;
    for (int x = 0; x < max_x; x++) {
        level_array.emplace_back(std::vector<int>());
        for (int y = 0; y < max_y; y++){
            level_array[x].push_back(0);
            // border around the outside
            // if (x == 0 || x == max_x - 1 || y == 0 || y == max_y -1) {
            if (x == 1 || x == 10 || y == 1 || y == 10) {
                level_array[x][y] = 1;
            }
        }
    }

    player = Player();

    return true;
}
