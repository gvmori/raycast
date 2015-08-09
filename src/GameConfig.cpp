#include "include/GameConfig.h"

GameConfig::GameConfig() {
    // viewport
    view_width = 800;
    view_height = 600;
    
    fov = 90;

    // world settings
    grid_size = 128;
}
