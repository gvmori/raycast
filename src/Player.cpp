#include "include/Player.h"
#include <iostream>

Player::Player() {

    // store pos in world coords, not grid coords
    pos_vector.x = 600;
    pos_vector.y = 500;

    // in degrees
    rot_vector.pitch = 0;
    rot_vector.roll = 0;
    rot_vector.yaw = 45;

    move_vector.x = 0;
    move_vector.y = 0;

    player_height = 64;
}

void Player::AddMoveVector(double x, double y){
    move_vector.x = x;
    move_vector.y = y;
}

Vector2<double>* Player::GetPosition() {
    return &pos_vector;
}

Vector3<double>* Player::GetRotation() {
    return &rot_vector;
}

void Player::SetPosition(double x, double y) {
    pos_vector.x = x;
    pos_vector.y = y;
}

// TODO: likely will only have 2d (up/down left/right) rotation, use vec2?
void Player::SetRotation(double pitch, double roll, double yaw) {
    rot_vector.pitch = pitch;
    rot_vector.roll = roll;
    rot_vector.yaw = yaw;
}

void Player::Update() {
    // move the player based on its move_vector. note that y is a
    // forward/backward movement, x is a side-to-side movement. 

    // forward/backward movement:
    // first, convert the relative (player-based) vector to an absolute (world-
    // coord) vector.
    double dx;
    double dy;

    double test_angle;
    double movement_angle = rot_vector.yaw + move_vector.y;
    if (movement_angle > 360) {
        movement_angle -= 360;
    }

    uint test_angle_bound = 90;
    while (test_angle_bound < movement_angle) {
        test_angle_bound += 90;
    }
    test_angle = test_angle_bound - movement_angle;

    dx = sin(LocalMath::DegToRad(test_angle)) * move_vector.x;
    dy = cos(LocalMath::DegToRad(test_angle)) * move_vector.x;

    // quadrants are rotated 90 degrees from standard, 0,0 is in the NW corner
    // of the map, any movements in that direction will have both negative, NE
    // corner will be +x -y, SE +x +y, SW -x +y.
    if (movement_angle > 180) {
        dx *= -1;
    }
    if (movement_angle > 270 || movement_angle < 90) {
        dy *= -1;
    }

    // TODO:  this works, but it's too late at night to figure out why. the
    // NE/SW quadrants seem to be reflected, swapping and inverting dx and dy
    // give the correct movement, leaving them as-is causes, uh, reflected and
    // inverted movement. this is probably because of an oversight in the
    // trigonometry above, double check it on paper. 
    if (movement_angle > 270 || (movement_angle > 90 && movement_angle < 180)){
        double hold = dx;
        dx = dy;
        dy = hold;
        dx *= -1;
        dy *= -1;
    }

    pos_vector.y += dy;
    pos_vector.x += dx;

// std::cout << "angle: " << movement_angle << " dx: " << dx << " dy: " << dy << std::endl;


    // clear the move vector so the player stops.
    // TODO: replace this with something that accounts for momentum, etc
    move_vector.x = 0;
    move_vector.y = 0;

}
