#include "include/Player.h"

Player::Player() {
    pos_vector[0] = 5.5;
    pos_vector[1] = 5.5;

    rot_vector[0] = 0;
    rot_vector[1] = 0;
    rot_vector[2] = 0;

    player_height = 64;
}

float* Player::GetPosition() {
    return pos_vector;
}

float* Player::GetRotation() {
    return rot_vector;
}

void Player::SetPosition(float x, float y) {
    pos_vector[0] = x;
    pos_vector[1] = y;
}

void Player::SetRotation(float x, float y, float z) {
    rot_vector[0] = x;
    rot_vector[1] = y;
    rot_vector[2] = z;
}
