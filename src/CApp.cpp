#include "include/CApp.h"

CApp::CApp() {
    screen = nullptr;
    renderer = nullptr;
    screen_buffer_tex = nullptr;
    screen_buffer_surf = nullptr;
    screen_format = nullptr;

    running = true;

    config = GameConfig();

    start_time = 0;
    last_time = 0;
}

int CApp::Execute() {
    if (Init() == false) {
        return -1;
    }


    start_time = SDL_GetTicks();
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