#include "include/Player.h"

Player::Player() {
    pos_vector.x = 5.5;
    pos_vector.y = 5.5;

    rot_vector.pitch = 0;
    rot_vector.roll = 0;
    // TODO FORDEV: player starts facing north
    rot_vector.yaw = 90;

    player_height = 64;
}

Vector2* Player::GetPosition() {
    return &pos_vector;
}

Vector3* Player::GetRotation() {
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
