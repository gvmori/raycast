#include "include/CApp.h"

#include <cstdlib>

void CApp::MainLoop() {
    // TODO: remove fillrect, shouldn't be necessary after floor+ceiling
    // drawing is in
    SDL_FillRect(screen_buffer_surf, NULL, 0x000000);
    // TODO: handle creature/object updates generally
    player.Update();
    
    Raycast();
    
    
}
