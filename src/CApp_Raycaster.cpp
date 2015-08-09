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
        int distance = FindDistance(i, angle_increment, pos, rot, grid_size); 
        std::cout << "dist: " << distance << std::endl;
        // int wall_size = (grid_size / distance) * dist_to_proj_plane;
        int wall_size = (int)ceil(((grid_size / (double)distance) * dist_to_proj_plane));
        std::cout << "wallsize: " << wall_size << std::endl;
        // TODO: figure out top bound
        //       add top to wall_size

        int top = (config.view_height / 2) - (wall_size / 2);
        wall_size = std::min((int)config.view_height, (int)wall_size + top);
        // int top = (view_height / 2) - (wall_size / 2);

        DrawLine(i, top, wall_size, SDL_MapRGB(screen_format, 255, 0, 0));
    }

    player.SetRotation(rot->pitch, rot->roll, rot->yaw + .1);

    // int y_max = config.view_height;
    // for (int i=0; i < config.view_width; i++){
    //     DrawLine(i, 0, y_max);
    // }
}

// given the column of the player's view, determine the shortest distance to a
// wall
// adapted from http://permadi.com/1996/05/ray-casting-tutorial-7/
// TODO -- will also need the texture + column of intersection for rendering
// textures
int CApp::FindDistance(
    int view_x, 
    double angle_increment,
    Vector2<double>* pos,
    Vector3<double>* rot,
    short grid_size
) {
    double relative_angle = (double)(angle_increment * view_x); 
    // TODO -- can precalculate yaw + fov/2 for all traces
    double absolute_angle = fmod((rot->yaw + (config.fov/2) - relative_angle), 360);

    // std::cout << "ABS ANGLE: " <<  absolute_angle << std::endl;
    // std::cout << "REL ANGLE: " << relative_angle << std::endl;

    Vector2<double> A;
    // east is 0 -- looking north is 0-179
    if (absolute_angle < 180) {
        A.y = (int)(pos->y / grid_size) * grid_size - 1; 
    }
    // looking south, 180-359
    else {
        A.y = (int)(pos->y / grid_size) * grid_size + grid_size; 
    }

    // TODO: precalculate
    double A_tan = tan(DegToRad(absolute_angle));
    A.x = pos->x + ((pos->y - A.y) / A_tan);
    std::cout << "ax: " << A.x << " ay: " << A.y << std::endl;

    // TODO: clean this up!
    // refactor so the code can be used on both horiz&vert?
    bool found_wall = false;
    Vector2<int> wall;
    if (level_array[(int)(A.x/grid_size)][(int)(A.y/grid_size)]){
        wall.x = (int)A.x;
        wall.y = (int)A.y;
        found_wall = true;
    }

    if (!found_wall){
        double abs_tan = tan(DegToRad(absolute_angle));

        Vector2<int> iterdiff;
        // TODO: precalculate or cache
        iterdiff.x = (grid_size/abs_tan);
        iterdiff.y = grid_size;
        if (absolute_angle < 180) {
            iterdiff.y = iterdiff.y * -1;
        }
        
        std::cout << "iterx: " << iterdiff.x << std::endl;
        std::cout << "itery: " << iterdiff.y << std::endl;
        while (!found_wall){ 
            A.x += iterdiff.x;
            A.y += iterdiff.y;
            // std::cout << "ax: " << A.x << " ax mod: " << (int)(A.x/grid_size) << " ay: " << A.y  <<  std::endl;

            if (level_array[(int)(A.x/grid_size)][(int)(A.y/grid_size)]) {
                std::cout << "wall found at: " << (int)(A.x/grid_size) << "," << (int)(A.y/grid_size) << std::endl;
                wall.x = A.x;
                wall.y = A.y;
                found_wall = true;
            } 
        }
    }

    // TODO: account for fisheye
    // return std::min(
    int distx = abs((int)((pos->x - wall.x) / cos(DegToRad(absolute_angle))));
    int disty = abs((int)((pos->y - wall.y) / cos(DegToRad(absolute_angle))));
    // std::cout << "distx: " << distx << " disty: " << disty << std::endl;

    return std::min(distx, disty);
    // );
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
