#include "include/CApp.h"

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

        int red = 0;
        int green = 0;
        int blue = 0;
        if (rot->yaw > 270) {
            green = 255 - (((distance/grid_size) * 255) / max_x);
            red = 255 - (((distance/grid_size) * 255) / max_x);
        }
        else if (rot->yaw > 180) {
            blue = 255 - (((distance/grid_size) * 255) / max_x);
        }
        else if (rot->yaw > 90) {
            green = 255 - (((distance/grid_size) * 255) / max_x);
        }
        else {
            red = 255 - (((distance/grid_size) * 255) / max_x);
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
    int view_x, 
    double angle_increment,
    Vector2<double>* pos,
    Vector3<double>* rot,
    short grid_size,
    int max_x, int max_y
) {

    double relative_angle = (double)(angle_increment * view_x); 
    // TODO --  precalculate yaw + fov/2 for all traces?
    double absolute_angle = fmod((rot->yaw + (config.fov/2) - relative_angle), 360);
    if (absolute_angle < 0){
        absolute_angle += 360;
    }

    // TODO: precalculate or cache?
    double alpha_tan = tan(LocalMath::DegToRad(absolute_angle));

    Vector2<double> horiz_vertex;
    Vector2<double> vert_vertex;

    // find the vertex of the intersection of the ray with the nearest
    // horizontal grid line. 
    if (absolute_angle < 180) {
        horiz_vertex.y = (int)(pos->y / grid_size) * grid_size - 1;
    }
    else {
        horiz_vertex.y = (int)(pos->y / grid_size) * grid_size + grid_size;
    }
    // y/tan(A) will be negative if the angle is less than 180
    horiz_vertex.x = pos->x + ((pos->y - horiz_vertex.y) / alpha_tan);

    // find the vertex of the intersection of the ray with the nearest
    // vertical gridline
    if (absolute_angle > 90 && absolute_angle < 270) {
        vert_vertex.x = (int)(pos->x / grid_size) * grid_size - 1;
    }
    else {
        vert_vertex.x = (int)(pos->x / grid_size) * grid_size + grid_size;
    }
    // x*tan(A) will be negative if the angle is between 90 and 270
    vert_vertex.y = pos->y + ((pos->x - vert_vertex.x) * alpha_tan);

    // determine the intervals for subsequent grid checks
    Vector2<double> horiz_interval;
    Vector2<double> vert_interval;

    horiz_interval.y = grid_size;
    horiz_interval.x = abs(horiz_interval.y / alpha_tan);

    vert_interval.x = grid_size;
    vert_interval.y = abs(vert_interval.x * alpha_tan);

    if (absolute_angle < 180) {
        vert_interval.y = 0 - vert_interval.y;
        horiz_interval.y = 0 - horiz_interval.y;
    }
    if (absolute_angle > 90 && absolute_angle < 270) {
        horiz_interval.x = 0 - horiz_interval.x;
        vert_interval.x = 0 - vert_interval.x;
    }

    bool found_horiz_wall = false;
    bool found_vert_wall = false;
    bool skip_horiz_wall = false;
    bool skip_vert_wall = false;
    int horiz_x_check;
    int horiz_y_check;
    int vert_x_check;
    int vert_y_check;

    // the first wall found is not necessarily the closest,
    // continue until both are found
    // TODO: clean up the skipping logic to use only found_x_wall
    while (!(found_horiz_wall && found_vert_wall)
            && !(skip_horiz_wall && skip_vert_wall)) {
        horiz_x_check = (int)(horiz_vertex.x / grid_size);
        horiz_y_check = (int)(horiz_vertex.y / grid_size);
        vert_x_check = (int)(vert_vertex.x / grid_size);
        vert_y_check = (int)(vert_vertex.y / grid_size);

        if (!skip_horiz_wall && !found_horiz_wall){
            // if the absolute angle is close to perpendicular with the wall,
            // the horizontal angle (for example) will be close to parallel
            // with its vertical lines, and the next gridlines to check may
            // fall well outside the map's bounds. in these cases, we'll only
            // want to check vertical lines.
            if (horiz_x_check > max_x 
                || horiz_y_check > max_y
                || horiz_x_check < 0
                || horiz_y_check < 0
                ){
                skip_horiz_wall = true;
            }
            else if (level_array[horiz_x_check][horiz_y_check]){
                found_horiz_wall = true;
                skip_horiz_wall = true;
            }
            else {
                horiz_vertex.x += horiz_interval.x;
                horiz_vertex.y += horiz_interval.y;
            }
        }

        if (!skip_vert_wall && !found_vert_wall){
            if (vert_x_check > max_x 
                || vert_y_check > max_y
                || vert_x_check < 0
                || vert_y_check < 0
                ){
                skip_vert_wall = true;
            }
            else if (level_array[vert_x_check][vert_y_check]){
                found_vert_wall = true;
                skip_vert_wall = true;
            }
            else {
                vert_vertex.x += vert_interval.x;
                vert_vertex.y += vert_interval.y;
            }
        }
    }

    double horiz_distance;
    double vert_distance;
    // TODO (?): replace distance calculation with precalculated tables per
    // http://permadi.com/1996/05/ray-casting-tutorial-8/
    if (found_horiz_wall) {
        horiz_distance = std::sqrt(std::pow(pos->x - horiz_vertex.x, 2.0) + std::pow(pos->y - horiz_vertex.y, 2.0));
    }
    else {
        horiz_distance = std::numeric_limits<double>::max();
    }
    if (found_vert_wall) {
        vert_distance = std::sqrt(std::pow(pos->x - vert_vertex.x, 2.0) + std::pow(pos->y - vert_vertex.y, 2.0));
    }
    else {
        vert_distance = std::numeric_limits<double>::max();
    }

    return std::min(horiz_distance, vert_distance);
}

