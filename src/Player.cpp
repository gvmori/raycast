#include "include/Player.h"

Player::Player() {

    // store pos in world coords, not grid coords
    pos_vector.x = 768;
    pos_vector.y = 500;

    // in degrees
    rot_vector.pitch = 0;
    rot_vector.roll = 0;
    rot_vector.yaw = 0;

    player_height = 64;
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
