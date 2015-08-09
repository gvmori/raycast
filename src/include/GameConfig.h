#ifndef _GAMECONFIG_H_
    #define _GAMECONFIG_H_

#include <SDL.h>
#include <stdint.h>

class GameConfig {
    public: 
        Uint16 player_height;
        Uint16 wall_height;
        
        Uint8 fov;

        Uint16 view_height;
        Uint16 view_width;

        // Uint32 pixel_format;

        GameConfig();
};

#endif