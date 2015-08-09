#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <cstdint>
#include <vector>
#include <cmath>
#include <algorithm>

#include "GameConfig.h"
#include "Player.h"
#include "Vector.h"

// TODO: remove
#include <iostream>

class CApp {
    private:
        bool running;
        SDL_Window* screen;
        SDL_Renderer* renderer;
        SDL_Surface* screen_buffer_surf;
        SDL_Texture* screen_buffer_tex;
        SDL_PixelFormat* screen_format;
        int screen_pitch_mod;

        std::vector<SDL_Texture*> textures;

        std::vector< std::vector<int> > level_array;

        Uint32 start_time;
        Uint32 last_time;

        GameConfig config;
        Player player;

    public:
        CApp();
        int Execute();
        bool Init();
        bool LoadLevel();
        void OnEvent(SDL_Event* event);
        void MainLoop();
        void Render();
        void Cleanup();

        // raycast functions
        // TODO: move to own class?
        void Raycast();
        int FindDistance(
            int view_x, 
            double angle_increment,
            Vector2<double>* pos, 
            Vector3<double>* rot, 
            short grid_size
            );

        // drawing funtions
        void DrawLine(
            Uint16 x, 
            Uint16 y_min, 
            Uint16 y_max,
            Uint32 pixel_color
            );

        // math
        // TODO: move elsewhere
        double RadToDeg(double degrees);
        double DegToRad(double degrees);
};
#endif
