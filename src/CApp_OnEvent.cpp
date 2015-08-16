#include "include/CApp.h"

void CApp::OnEvent(SDL_Event* event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }
    else if (event->type == SDL_KEYDOWN) {
        Vector2<double>* pos = player.GetPosition();
        Vector3<double>* rot = player.GetRotation();
        switch (event->key.keysym.sym) {
            // just for testing
            case SDLK_ESCAPE:
            running = false;
            return;

            case SDLK_w:
            pos->y -= 3;
            break;
            
            case SDLK_s:
            pos->y += 3;
            break;

            case SDLK_a:
            pos->x -= 3;
            break;
            
            case SDLK_d:
            pos->x += 3;
            break;

            case SDLK_LEFT:
            rot->yaw += 3;
            rot->yaw = fmod(rot->yaw, 360);
            break;
            
            case SDLK_RIGHT:
            rot->yaw -= 3;
            if (rot->yaw < 0) { rot->yaw = 359.9 + rot->yaw; }
            rot->yaw = fmod(rot->yaw, 360);
            break;


        }

    }
}
