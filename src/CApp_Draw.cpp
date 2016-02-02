#include "include/CApp.h"

void CApp::DrawLine(
    Uint16 x, 
    Uint16 y_min, 
    Uint16 y_max,
    Uint32 pixel_color
){
    // if (x < 50) { pixel_color = SDL_MapRGB(screen_format, 255, 0, 0); }
    // else if (x > config.view_width - 50) { pixel_color = SDL_MapRGB(screen_format, 0, 255, 0); }
    // else if (x % 10 == 0) { pixel_color = SDL_MapRGB(screen_format, 0, 0, 255); }
    // else { pixel_color = SDL_MapRGB(screen_format, 255, 255, 255); }

    Uint32* ptr = (Uint32*)screen_buffer_surf->pixels;
    int offset_delta = (screen_buffer_surf->pitch / sizeof(Uint32));
    for (int i=y_min; i < y_max; i++) {
        int line_offset = i * offset_delta;
        ptr[line_offset + x] = pixel_color;
    }
    ptr = nullptr;
}
