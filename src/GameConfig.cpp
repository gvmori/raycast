#include "include/GameConfig.h"

GameConfig::GameConfig() {
    // viewport
    view_width = 800;
    view_height = 600;
    
    fov = 90;

    // player settings
    player_height = 64;
    wall_height = 128;
    
    // render settings
    // pixel_format = SDL_PIXELFORMAT_RGB888;
}
