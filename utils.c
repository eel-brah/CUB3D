#include "gm.h"

float deg2rad(float deg)
{
    return deg * (PI / 180.0f);
}

float rad2deg(float rad)
{
    return rad * (180.0f / PI);
}

// float fov = deg2rad(66);
// int rays_num = 360;
// float ray_angle += fov/rays_num;

// float dis_ab = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));