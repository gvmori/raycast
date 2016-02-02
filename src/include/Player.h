#ifndef _PLAYER_H_
    #define _PLAYER_H_
 
#include <SDL.h>
#include <cstdint>
#include "Vector.h"

// for movement--remove once movement is generalized
#include <cmath>
#include "LocalMath.h"

class Player {
    private:
        Vector2<double> pos_vector;
        Vector3<double> rot_vector;
        Vector2<double> move_vector;

    public:
        Uint16 player_height;

        void AddMoveVector(double x, double y);
        Vector2<double>* GetPosition();
        Vector3<double>* GetRotation();
        void SetPosition(double x, double y);
        void SetRotation(double pitch, double roll, double yaw);
        void Update();
        void Move();
        Player();
};

#endif
