#ifndef _PLAYER_H_
    #define _PLAYER_H_

#include "CApp.h"

class Player {
    private:
        float pos_vector[2];
        float rot_vector[3];

    public:
        Uint16 player_height;
        float* GetPosition();
        float* GetRotation();
        void SetPosition(float x, float y);
        void SetRotation(float x, float y, float z);
        Player();
};

#endif