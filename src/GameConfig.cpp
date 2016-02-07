#include "include/GameConfig.h"

GameConfig::GameConfig() {
    // viewport
    view_width = 800;
    view_height = 600;
    
    fov = 90;

    // world settings
    grid_size = 128;

    // player settings
    player_speed_forward = 1.25;
    player_speed_side = 1.25;
}
