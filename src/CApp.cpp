#include "include/CApp.h"

CApp::CApp() {
    screen = nullptr;
    renderer = nullptr;
    screen_buffer_tex = nullptr;
    screen_buffer_surf = nullptr;
    screen_format = nullptr;

    running = true;

    config = GameConfig();

    // pixel_buffer = new Uint32*[config.view_height];
    // for (int i = 0; i < config.view_height; i++){
    //     pixel_buffer[i] = new Uint32[config.view_width];
    // }
}

int CApp::Execute() {
    if (Init() == false) {
        return -1;
    }

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }

        MainLoop();
        Render();
    }

    Cleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    CApp main_app;

    return main_app.Execute();
}