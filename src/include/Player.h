#ifndef _PLAYER_H_
    #define _PLAYER_H_
 
#include <SDL.h>
#include <cstdint>
#include "Vector.h"

class Player {
    private:
        Vector2<double> pos_vector;
        Vector3<double> rot_vector;

    public:
        Uint16 player_height;
        Vector2<double>* GetPosition();
        Vector3<double>* GetRotation();
        void SetPosition(double x, double y);
        void SetRotation(double pitch, double roll, double yaw);
        Player();
};

#endif
