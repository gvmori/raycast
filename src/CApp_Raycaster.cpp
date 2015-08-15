#include "include/CApp.h"

void CApp::Raycast() {
    // RENDER WALLS
    // foreach x in view:
    //     cast ray
    //     find distance to wall
    //     determine projection height
    //     render projection

    Vector2<double>* pos = player.GetPosition();
    Vector3<double>* rot = player.GetRotation();
    short grid_size = (short)config.grid_size;
    double angle_increment = (double)(config.fov)/(double)config.view_width;
    int dist_to_proj_plane = (int)((config.view_width / 2) / tan(config.fov * config.fov));

    for (int i=0; i < config.view_width; i++){
        double distance = FindDistance(i, angle_increment, pos, rot, grid_size); 
        // std::cout << "dist: " << distance << std::endl;
        int wall_size = (int)ceil(((grid_size / distance) * dist_to_proj_plane));
        // std::cout << "wallsize: " << wall_size << std::endl;
        // TODO: figure out top bound based on current player height instead of view height
        //       calculate first half outside loop
        int top = (config.view_height / 2) - (wall_size / 2);
        // std::cout << "top: " << top << std::endl;
        wall_size = std::min((int)config.view_height, (int)wall_size + top);
        DrawLine(i, top, wall_size, SDL_MapRGB(screen_format, 255, 0, 0));
    }

    // TODO: remove this once controls are in
    // player.SetRotation(rot->pitch, rot->roll, rot->yaw + .1);
    // player.SetPosition(pos->x - 1, pos->y - 1);
}

// given the column of the player's view, determine the shortest distance to a
// wall
// adapted from http://permadi.com/1996/05/ray-casting-tutorial-7/
// TODO -- will also need the texture + column of intersection for rendering
// textures?
double CApp::FindDistance(
    int view_x, 
    double angle_increment,
    Vector2<double>* pos,
    Vector3<double>* rot,
    short grid_size
) {

    double relative_angle = (double)(angle_increment * view_x); 
    // TODO -- can precalculate yaw + fov/2 for all traces
    double absolute_angle = fmod((rot->yaw + (config.fov/2) - relative_angle), 360);

    if (absolute_angle <= .001
        || (absolute_angle - 90) <= .001
        || (absolute_angle - 180) <= .001
        || (absolute_angle - 270) <= .001
       ) {
        relative_angle += .005;
        absolute_angle   += .005;
    }
    // std::cout << "ABS ANGLE: " <<  absolute_angle << std::endl;
    // std::cout << "REL ANGLE: " << relative_angle << std::endl;
    std::cout << "FACING: " << rot->yaw << std::endl;
    std::cout << "POS X: " << pos->x << " POS Y: " << pos->y << std::endl;

    // TODO: precalculate or cache
    double alpha_tan = tan(DegToRad(absolute_angle));

    // std::cout << "TAN: " << alpha_tan << std::endl;

    // find nearest horizontal intersection
    Vector2<double> horiz_vertex;
    if (absolute_angle < 180) {
        horiz_vertex.y = (int)(pos->y / grid_size) * grid_size - 1;
    }
    else {
        horiz_vertex.y = (int)(pos->y / grid_size) * grid_size + grid_size;
    }
    horiz_vertex.x = pos->x + (pos->y - horiz_vertex.y) / alpha_tan;

    // find nearest vertical intersection
    Vector2<double> vert_vertex;
    if (absolute_angle > 90 && absolute_angle < 270){
        vert_vertex.x = (int)(pos->x / grid_size) * grid_size - 1;
    }
    else {
        vert_vertex.x = (int)(pos->x / grid_size) * grid_size + grid_size;
    }
    vert_vertex.y = pos->y + (pos->x - vert_vertex.x) * alpha_tan;

    bool found_horiz_wall = false;
    bool found_vert_wall = false;
    bool skip_horiz_wall = false;
    bool skip_vert_wall = false;

    // if (vert_vertex.y < 0 || vert_vertex.y > ((10 * grid_size) - pos->y)) {
    //     skip_vert_wall = true;
    // }
    // if (horiz_vertex.x < 0 || horiz_vertex.x > ((10 * grid_size) - pos->x)) {
    //     skip_horiz_wall = true;
    // }

    vert_vertex.y = std::max(0.0, vert_vertex.y);
    vert_vertex.y = std::min(vert_vertex.y, (double)(grid_size * 10 - 1));
    vert_vertex.x = std::max(0.0, vert_vertex.x);
    vert_vertex.x = std::min(vert_vertex.x, (double)(grid_size * 10 - 1));

    horiz_vertex.y = std::max(0.0, horiz_vertex.y);
    horiz_vertex.y = std::min(horiz_vertex.y, (double)(grid_size * 10 - 1));
    horiz_vertex.x = std::max(0.0, horiz_vertex.x);
    horiz_vertex.x = std::min(horiz_vertex.x, (double)(grid_size * 10 - 1));

    // check for walls
    // both can be true, will need distance to determine which is closest

    // std::cout << "check horiz wall: " << (int)horiz_vertex.x << ", " << (int)horiz_vertex.y << std::endl;
    if (!skip_horiz_wall &&
        level_array[(int)(horiz_vertex.x / grid_size)][(int)(horiz_vertex.y / grid_size)]
        ) {
        // std::cout << "found horiz wall: " << (int)horiz_vertex.x << ", " << (int)horiz_vertex.y << std::endl;
        found_horiz_wall = true;
    }
    // std::cout << "check vert wall: " << (int)vert_vertex.x << ", " << (int)vert_vertex.y << std::endl;
    if (!skip_vert_wall &&
        level_array[(int)(vert_vertex.x / grid_size)][(int)(vert_vertex.y / grid_size)]
        ) {
        // std::cout << "found vert wall: " << (int)vert_vertex.x << ", " << (int)vert_vertex.y << std::endl;
        found_vert_wall = true;
    }

    if (!found_horiz_wall && !found_vert_wall) {
        
        Vector2<int> horiz_interval;
        Vector2<int> vert_interval;
        // determine interval for next horiz
        horiz_interval.x = (grid_size / alpha_tan);
        horiz_interval.y = grid_size;

        // determine interval for next vert
        vert_interval.x = grid_size;
        vert_interval.y = (grid_size * alpha_tan);
        // vert_interval.y = sin(DegToRad(absolute_angle) / cos(DegToRad(absolute_angle))) * grid_size;

        // move left if ray is facing left
        if (absolute_angle > 90 && absolute_angle < 270) {
            horiz_interval.x *= -1;
            vert_interval.x *= -1;
        }
        // move up if ray is facing up
        if (absolute_angle < 180) {
            horiz_interval.y *= -1;
            vert_interval.y *= -1;
        }

        // std::cout << "horiz_interval.x: " << horiz_interval.x << " horiz_interval.y: " << horiz_interval.y << std::endl;
        // std::cout << "vert_interval.x: " << vert_interval.x << " vert_interval.y: " << vert_interval.y << std::endl;
        // while !wall
        //     increment horiz, check for wall
        //     increment vert, check for wall
        // std::cout << "enter loop" << std::endl;
        while (!found_horiz_wall && !found_vert_wall
                && !(skip_vert_wall || skip_horiz_wall)
            ) {

            if (!skip_horiz_wall) {
                horiz_vertex.x += horiz_interval.x;
                horiz_vertex.y += horiz_interval.y;
                horiz_vertex.y = std::max(0.0, horiz_vertex.y);
                horiz_vertex.y = std::min(horiz_vertex.y, (double)(grid_size * 10 - 1));
                horiz_vertex.x = std::max(0.0, horiz_vertex.x);
                horiz_vertex.x = std::min(horiz_vertex.x, (double)(grid_size * 10 - 1));
                // std::cout << "check horiz wall: " << (int)(horiz_vertex.x / grid_size) << ", " << (int)(horiz_vertex.y / grid_size) << std::endl;
                // if (horiz_vertex.x < 0 || horiz_vertex.y < 0 || horiz_vertex.y > ((10 * grid_size) - pos->y) || horiz_vertex.x > ((10 * grid_size) - pos->x)) {
                //     skip_horiz_wall = true;
                // }
                if (level_array[(int)(horiz_vertex.x / grid_size)][(int)(horiz_vertex.y / grid_size)]) {
                    // std::cout << "found horiz wall: " << (int)horiz_vertex.x << ", " << (int)horiz_vertex.y << std::endl;
                    found_horiz_wall = true;
                }

            }

            if (!skip_vert_wall) {
                vert_vertex.x += vert_interval.x;
                vert_vertex.y += vert_interval.y;
                vert_vertex.y = std::max(0.0, vert_vertex.y);
                vert_vertex.y = std::min(vert_vertex.y, (double)(grid_size * 10 - 1));
                vert_vertex.x = std::max(0.0, vert_vertex.x);
                vert_vertex.x = std::min(vert_vertex.x, (double)(grid_size * 10 - 1));
                // std::cout << "check vert wall: " << (int)(vert_vertex.x / grid_size) << ", " << (int)(vert_vertex.y / grid_size) << std::endl;
                // if (vert_vertex.x < 0 || vert_vertex.y < 0 || vert_vertex.y > ((10 * grid_size) - pos->y) || vert_vertex.x > ((10 * grid_size) - pos->x)) {
                //     skip_vert_wall = true;
                // }
                if (level_array[(int)(vert_vertex.x / grid_size)][(int)(vert_vertex.y / grid_size)]) {
                // std::cout << "found vert wall: " << (int)vert_vertex.x << ", " << (int)vert_vertex.y << std::endl;
                    found_vert_wall = true;
                }
            }
        }
    }

    double horiz_distance;
    double vert_distance;
    if (found_horiz_wall){
        horiz_distance = sqrt(pow((pos->x - horiz_vertex.x), 2) + pow((pos->y - horiz_vertex.y), 2));
        // double dif = (pos->x - horiz_vertex.x);
        // if (dif < 0) { dif *= - 1; } 
        // horiz_distance = dif / cos(DegToRad(absolute_angle));
    } 
    else {
        horiz_distance = std::numeric_limits<double>::max();
    }

    if (found_vert_wall){
        vert_distance = sqrt(pow((pos->x - vert_vertex.x), 2) + pow((pos->y - vert_vertex.y), 2));
        // double dif = (pos->x - vert_vertex.x);
        // if (dif < 0) { dif *= - 1; } 
        // vert_distance = dif / cos(DegToRad(absolute_angle));
    } 
    else {
        vert_distance = std::numeric_limits<double>::max();
    }

    // std::cout << "horiz distance: " << horiz_distance << " vert_distance: " << vert_distance << std::endl;
    
    return std::min(horiz_distance, vert_distance);
}

constexpr double pi() { 
    return acos(-1); 
}

double CApp::DegToRad(double degrees){
    return (degrees * pi() / 180);
}

double CApp::RadToDeg(double degrees){
    return (degrees * 180 / pi());
}

