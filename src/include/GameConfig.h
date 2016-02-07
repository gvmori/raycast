#ifndef _GAMECONFIG_H_
    #define _GAMECONFIG_H_

#include <SDL.h>
#include <stdint.h>

class GameConfig {
    public: 
        Uint8 grid_size;
        
        Uint8 fov;

        Uint16 view_height;
        Uint16 view_width;

        Uint8 player_speed_forward;
        Uint8 player_speed_side;

        GameConfig();
};

#endif
