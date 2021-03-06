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
    int max_x = 10;
    int max_y = 20;
    for (int x = 0; x < max_x; x++) {
        level_array.emplace_back(std::vector<int>());
        for (int y = 0; y < max_y; y++){
            level_array[x].push_back(0);
            // border around the outside
            if (x == 0 || x == max_x - 1 || y == 0 || y == max_y -1) {
                level_array[x][y] = 1;
            }
            // else if (!(x % 2) && !(y % 2)){
                // level_array[x][y] = 1;
            // }
            else if ((x == 3) && (y == 3 || y == 6)) {
                level_array[x][y] = 1;
            }
        }
    }

    player = Player();
    return true;
}
