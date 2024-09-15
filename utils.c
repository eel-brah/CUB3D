#include "gm.h"

float deg2rad(float deg)
{
    return deg * (PI / 180.0f);
}

float rad2deg(float rad)
{
    return rad * (180.0f / PI);
}

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

// float fov = deg2rad(66);
// int rays_num = 360;
// float ray_angle += fov/rays_num;

// float dis_ab = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));