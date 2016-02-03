#include "include/CApp.h"

void CApp::OnEvent(SDL_Event* event) {
    // TODO: this vector for testing only!
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
            // movement vectors will be (magnitude, relative_angle_of_movement)
            case SDLK_w:
            player.AddMoveVector(3, 0);
            break;
            
            case SDLK_s:
            player.AddMoveVector(3, 180);
            break;

            case SDLK_a:
            player.AddMoveVector(3, 270);
            break;
            
            case SDLK_d:
            player.AddMoveVector(3, 90);
            break;

            case SDLK_LEFT:
            rot->yaw -= 3;
            if (rot->yaw < 0) { rot->yaw += 360; }
            rot->yaw = fmod(rot->yaw, 360);
            break;
            
            case SDLK_RIGHT:
            rot->yaw += 3;
            rot->yaw = fmod(rot->yaw, 360);
            break;
        }

    }
    else if (event->type == SDL_MOUSEMOTION) {
        rot->yaw += event->motion.xrel;
        if (rot->yaw < 0) { rot->yaw = 360 + rot->yaw; }
        rot->yaw = fmod(rot->yaw, 360);
    }

}
