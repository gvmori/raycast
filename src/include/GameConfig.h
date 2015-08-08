#ifndef _GAMECONFIG_H_
    #define _GAMECONFIG_H_

class GameConfig {
    public: 
        unsigned int player_height;
        unsigned int wall_height;
        
        unsigned int fov;

        unsigned int view_height;
        unsigned int view_width;

        GameConfig();
};

#endif