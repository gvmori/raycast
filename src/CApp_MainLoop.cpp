#include "include/CApp.h"

#include <cstdlib>

void CApp::MainLoop() {
    // TODO
    // raycast+render view to pixel_buffer
    // int y_max = config.view_height;
    // for (int i=0; i < config.view_width; i++){
    //     DrawLine(i, 0, y_max);
    // }

    // TODO: remove fillrect, shouldn't be necessary after floor+ceiling
    // drawing is in
    SDL_FillRect(screen_buffer_surf, NULL, 0x000000);
    Raycast();
    
    
}
