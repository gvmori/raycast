#include "include/CApp.h"

#include <cstdlib>

void CApp::MainLoop() {
    // TODO
    // raycast+render view to pixel_buffer
    int y_max = config.view_height;
    for (int i=0; i < config.view_width; i++){
        DrawLine(i, 0, y_max);
    }
}

