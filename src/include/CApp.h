#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <stdint.h>
#include <vector>
#include "GameConfig.h"

// TODO: remove
#include <iostream>

class CApp {
    private:
        bool running;
        SDL_Window* screen;
        SDL_Renderer* renderer;
        SDL_Texture* screen_buffer_tex;
        // Uint32** pixel_buffer;

        std::vector<SDL_Texture*> textures;

        std::vector< std::vector<int> > level_array;

        int screen_pitch_mod;
        SDL_PixelFormat* screen_format;
        SDL_Surface* screen_buffer_surf;

        GameConfig config;

    public:
        CApp();
        int Execute();
        bool Init();
        bool LoadLevel();
        void OnEvent(SDL_Event* event);
        void MainLoop();
        void Render();
        void Cleanup();

        // drawing funtions
        void DrawLine(
            Uint16 x, 
            Uint16 y_min, 
            Uint16 y_max//,
            //SDL_Texture* texture
            );
};
#endif
