#include "include/Player.h"

Player::Player() {
    // store pos in world coords, not grid coords
    pos_vector.x = 650;
    pos_vector.y = 500;

    // in degrees
    rot_vector.pitch = 0;
    rot_vector.roll = 0;
    rot_vector.yaw = 0;

    player_height = 64;

    // std::vector<Vector2<double> > move_vectors;
}

void Player::AddMoveVector(double x, double y){
    move_vectors.emplace_back(Vector2<double>(x, y));
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
    Move();
}

void Player::Move() {
    double dx = 0;
    double dy = 0;
    double movement_angle;
    for (auto move_vector = move_vectors.begin(); move_vector != move_vectors.end(); move_vector++) {
        // move the player based on its move_vector, which will be
        // (x=distance, y=angle). assume the movement angle is relative to the
        // player's facing.
        movement_angle = rot_vector.yaw + move_vector->y;
        while (movement_angle > 360) {
            movement_angle -= 360;
        }

        dx += sin(LocalMath::DegToRad(movement_angle)) * move_vector->x;
        dy += cos(LocalMath::DegToRad(movement_angle)) * move_vector->x;
    }
    // NW corner is 0,0--dy should decrease as one moves north
    dy *= -1;

    // TODO: check collisions first
    pos_vector.x += dx;
    pos_vector.y += dy;

    // clear the move vectors so the player stops.
    // TODO: replace this with something that accounts for momentum, etc
    move_vectors.clear();
}
