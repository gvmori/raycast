#include "include/CApp.h"

void CApp::OnEvent(SDL_Event* event) {
    // TODO: these vectors for testing only!
    Vector2<double>* pos = player.GetPosition();
    Vector3<double>* rot = player.GetRotation();

    if (event->type == SDL_QUIT) {
        running = false;
    }
    else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
            running = false;
            return;
            
            // TODO: 
            // build out Player to handle pos+rot translation requests, send requests
            // based on input. 
            // these are for quick render testing only
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
            if (rot->yaw < 0) { rot->yaw = 360 + rot->yaw; }
            rot->yaw = fmod(rot->yaw, 360);
            break;
        }

    }
    else if (event->type == SDL_MOUSEMOTION) {
        rot->yaw -= event->motion.xrel;
        if (rot->yaw < 0) { rot->yaw = 360 + rot->yaw; }
        rot->yaw = fmod(rot->yaw, 360);
    }

}
