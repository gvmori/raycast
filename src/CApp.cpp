#include "include/CApp.h"

CApp::CApp() {
    screen = nullptr;
    renderer = nullptr;
    // content_manager = ContentManager();
    running = true;

    config = GameConfig();
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