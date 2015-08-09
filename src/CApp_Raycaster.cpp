#include "include/CApp.h"

void CApp::Raycast() {
    // RENDER WALLS
    // foreach x in view:
    //     cast ray
    //     find distance to wall
    //     determine projection height
    //     render projection

    Vector2* pos = player.GetPosition();
    Vector3* rot = player.GetRotation();
    short grid_size = (short)config.grid_size;
    double angle_increment = (double)(config.fov)/(double)config.view_width;
    int dist_to_proj_plane = (int)((config.fov / 2) / tan(config.view_width * config.view_width));

    for (int i=0; i < config.view_width; i++){
        int distance = FindDistance(i, angle_increment, pos, rot, grid_size); 
        std::cout << "dist: " << distance << std::endl;
        int wall_size = (int)((grid_size / distance) * dist_to_proj_plane);
        std::cout << "wallsize: " << wall_size << std::endl;
        DrawLine(i, 0, wall_size);
    }

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
    Vector2* pos,
    Vector3* rot,
    short grid_size
) {
    Vector2 A;

    double relative_angle = (double)(angle_increment * view_x);
    double absolute_angle = fmod((relative_angle + rot->yaw), 360);

    // east is 0 -- looking north is 0-179
    if (absolute_angle < 180) {
        A.y = (pos->y / grid_size) * grid_size - 1; 
    }
    // looking south, 180-359
    else {
        A.y = (pos->y / grid_size) * grid_size + grid_size; 
    }

    A.x = pos->x + ((pos->y - A.y) / tan(rot->yaw));
    
    // TODO: clean this up!
    // refactor so the code can be used on both horiz&vert!
    bool found_wall = false;
    int wall_x;
    int wall_y;
    std::cout << "HERE" << std::endl;
    if (level_array[(int)A.x][(int)A.y]){
        wall_x = (int)A.x;
        wall_y = (int)A.y;
        found_wall = true;
    }
    else if (absolute_angle > 180){
        grid_size = grid_size * -1;
    }

    std::cout << "HERE2" << std::endl;
    if (!found_wall){
        std::cout << "HERE3" << std::endl;
        Vector2 iterdiff;
        iterdiff.x = (int)(grid_size/tan(absolute_angle));
        iterdiff.y = grid_size;
        while (!found_wall){
            int next_x = (int)A.x + iterdiff.x;
            int next_y = (int)A.y + iterdiff.y;
            std::cout << A.x << " " << next_x << " " << A.y << " " << next_y <<  std::endl;

            if (level_array[(int)(next_x/grid_size)][(int)(next_y/grid_size)]) {
                wall_x = next_x;
                wall_y = next_y;
                found_wall = true;
            }
            else {
                A.x = next_x;
                A.y = next_y;
            }
        }
    }

    // TODO: account for fisheye
    return std::min(
        (int)((pos->x - wall_x) / cos(absolute_angle)),
        (int)((pos->y - wall_y) / cos(absolute_angle))
    );
}
