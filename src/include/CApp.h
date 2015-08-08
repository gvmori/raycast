#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h> 
#include <vector>
#include "GameConfig.h"
// #include "ContentManager.h"

class CApp {
    private:
        bool running;
        SDL_Window* screen;
        SDL_Renderer* renderer;
        // ContentManager content_manager;

        SDL_Surface* bmp;
        std::vector<SDL_Texture*> textures;

        std::vector< std::vector<int> > level_array;

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
};
#endif
