#include "include/CApp.h"

// void CApp::HandleEvents(SDL_Event* event) {
void CApp::HandleEvents() {
    HandleDiscreteEvents();
    HandleMomentaryEvents();
}

void CApp::HandleDiscreteEvents() {
    // TODO: this vector for testing only!
    Vector3<double>* rot = player.GetRotation();

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                running = false;
                return;
                
                // case SDLK_LEFT:
                // rot->yaw -= 3;
                // if (rot->yaw < 0) { rot->yaw += 360; }
                // rot->yaw = fmod(rot->yaw, 360);
                // break;
                
                // case SDLK_RIGHT:
                // rot->yaw += 3;
                // rot->yaw = fmod(rot->yaw, 360);
                // break;
            }

        }
        else if (event.type == SDL_MOUSEMOTION) {
            rot->yaw += event.motion.xrel;
            if (rot->yaw < 0) { rot->yaw = 360 + rot->yaw; }
            rot->yaw = fmod(rot->yaw, 360);
        }
    }
}

void CApp::HandleMomentaryEvents() {
    kbstate = SDL_GetKeyboardState(NULL);

    // movement vectors will be (magnitude, relative_angle_of_movement)
    if (kbstate[SDL_SCANCODE_W]) {
        player.AddMoveVector(config.player_speed_forward, 0);
    }
    if (kbstate[SDL_SCANCODE_S]) {
        player.AddMoveVector(config.player_speed_forward, 180);
    }
    if (kbstate[SDL_SCANCODE_A]) {
        player.AddMoveVector(config.player_speed_side, 270);
    }
    if (kbstate[SDL_SCANCODE_D]) {
        player.AddMoveVector(config.player_speed_side, 90);
    }
}
