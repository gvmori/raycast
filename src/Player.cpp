#include "include/Player.h"

Player::Player() {

    // store pos in world coords, not grid coords
    pos_vector.x = 768;
    pos_vector.y = 500;

    // in degrees
    rot_vector.pitch = 0;
    rot_vector.roll = 0;
    rot_vector.yaw = 0;

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
    // TODO: quick POC, works for one quadrant only.
    // rework to work with all quadrants
    if (rot_vector.yaw > 0 && rot_vector.yaw < 90){
        dx = -(cos(LocalMath::DegToRad(rot_vector.yaw)) * move_vector.y);
        dy = sin(LocalMath::DegToRad(rot_vector.yaw)) * move_vector.y;
    }

    pos_vector.y += dy;
    pos_vector.x += dx;

    // clear the move vector so the player stops.
    // TODO: replace this with something that accounts for momentum, etc
    move_vector.x = 0;
    move_vector.y = 0;

}
