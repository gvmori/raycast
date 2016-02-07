#include "include/CApp.h"
#include <iostream>

void CApp::Raycast() {
    Vector2<double>* pos = player.GetPosition();
    Vector3<double>* rot = player.GetRotation();
    short grid_size = (short)config.grid_size;
    double angle_increment = (double)(config.fov)/(double)config.view_width;
    int dist_to_proj_plane = (int)((config.view_width / 2) / tan(config.fov * config.fov));

    int max_x = level_array.size() - 1;
    int max_y = level_array[0].size() - 1;

    for (int i=0; i < config.view_width; i++){
        double distance = FindDistance(i, angle_increment, pos, rot, grid_size, max_x, max_y); 
        // for wall size, see http://permadi.com/1996/05/ray-casting-tutorial-9/
        int wall_size = (int)ceil(((grid_size / distance) * dist_to_proj_plane));

        // TODO: figure out top bound based on current player height instead of view height
        int top = (config.view_height / 2) - (wall_size / 2);
        wall_size = std::min((int)config.view_height, (int)wall_size + top);

        // temporary shading by distance
        // int red_color = 255 - (((distance/grid_size) * 255) / max_x);
        uint red = 0;
        uint green = 0;
        uint blue = 0;
        uint fadeout_const = 25;
        if (rot->yaw > 270) {
            green = 255 - (((distance/grid_size) * 255) / fadeout_const);
            red = 255 - (((distance/grid_size) * 255) / fadeout_const);
        }
        else if (rot->yaw > 180) {
            blue = 255 - (((distance/grid_size) * 255) / fadeout_const);
        }
        else if (rot->yaw > 90) {
            green = 255 - (((distance/grid_size) * 255) / fadeout_const);
        }
        else {
            red = 255 - (((distance/grid_size) * 255) / fadeout_const);
        }

        DrawLine(i, top, wall_size, SDL_MapRGB(screen_format, red, green, blue));
    }
}

// given the column of the player's view, determine the shortest distance to a
// wall. 
// adapted from http://permadi.com/1996/05/ray-casting-tutorial-7/ TODO
// -- will also need the texture + column of intersection for rendering
// textures?
double CApp::FindDistance(
    const int view_x, 
    const double angle_increment,
    const Vector2<double>* pos,
    const Vector3<double>* rot,
    const short grid_size,
    const int max_x, int max_y
) {
    double relative_angle = (double)(angle_increment * view_x); 
    // TODO --  precalculate yaw - fov/2 for all traces?
    double absolute_angle = fmod((rot->yaw - (config.fov/2) + relative_angle), 360);
    if (absolute_angle < 0){
        absolute_angle += 360;
    }

    // TODO: precalculate or cache?
    double alpha_tan = tan(LocalMath::DegToRad(absolute_angle));

    Vector2<double> horiz_vertex;
    Vector2<double> horiz_interval;

    horiz_vertex.y = (int)(pos->y / grid_size) * grid_size;
    // if the angle is pointing north, check the grid square north (lower y)
    // of the player's current square, and ensure the y interval is negative
    if (absolute_angle < 90 || absolute_angle > 270) {
        horiz_vertex.y--;
        horiz_interval.y = -grid_size;
    }
    // otherwise check the square south (higher y) of the player, and the y
    // interval is positive
    else {
        horiz_vertex.y += grid_size;
        horiz_interval.y = grid_size;
    }
    horiz_vertex.x = pos->x + (alpha_tan * (pos->y - horiz_vertex.y));
    // x interval should be negative when heading west (> 180)
    horiz_interval.x = -(horiz_interval.y * alpha_tan);

    Vector2<double> vert_vertex;
    Vector2<double> vert_interval;

    vert_vertex.x = (int)(pos->x / grid_size) * grid_size;
    // values decrease westward
    if (absolute_angle > 180) {
        vert_vertex.x--;
        vert_interval.x = -grid_size;
    }
    else {
        vert_vertex.x += grid_size;
        vert_interval.x = grid_size;
    }
    vert_vertex.y = pos->y - ((vert_vertex.x - pos->x) / alpha_tan);
    vert_interval.y = -(vert_interval.x / alpha_tan);

    Vector2<int> horiz_wall;
    Vector2<int> vert_wall;
    FindWall(horiz_vertex, horiz_interval, horiz_wall, grid_size, max_x, max_y);
    FindWall(vert_vertex, vert_interval, vert_wall, grid_size, max_x, max_y);

    double horiz_distance;
    double vert_distance;
    // TODO (?): replace distance calculation with precalculated tables per
    // http://permadi.com/1996/05/ray-casting-tutorial-8/
    if (horiz_wall.x >= 0) {
        horiz_distance = std::sqrt(std::pow(pos->x - horiz_vertex.x, 2.0) + std::pow(pos->y - horiz_vertex.y, 2.0));
    }
    else {
        horiz_distance = std::numeric_limits<double>::max();
    }
    if (vert_wall.x >= 0) {
        vert_distance = std::sqrt(std::pow(pos->x - vert_vertex.x, 2.0) + std::pow(pos->y - vert_vertex.y, 2.0));
    }
    else {
        vert_distance = std::numeric_limits<double>::max();
    }

    return std::min(horiz_distance, vert_distance);
}

void CApp::FindWall(
    Vector2<double>& vertex, 
    const Vector2<double>& interval, 
    Vector2<int>& result,
    const short grid_size,
    const int max_x,
    const int max_y
) {
    while (true) {
        result.x = (int)(vertex.x/grid_size);
        result.y = (int)(vertex.y/grid_size);

        if (result.x > max_x
            || result.y > max_y
            || result.x < 0
            || result.y < 0
            ) {
            // for now, use negative values to indicate failure.
            // in the future result should include a ref to the 
            // collided object, which can be null for failure
            result.x = -1;
            result.y = -1;
            return;
        }
        else if (level_array[result.x][result.y]) {
            return;
        }

        vertex.x += interval.x;
        vertex.y += interval.y;
    }
}

