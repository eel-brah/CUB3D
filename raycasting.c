#include "gm.h"

void init_rays(t_rays *rays)
{
	rays->fov = 60 * (PI / 180);
	rays->strips = 1;
	rays->rays_num = WIDTH / rays->strips;
}

float   getting_yintercept_h(t_player *player, float angle, float y)
{
    float x = player->x + (y - player->y) / tan(angle);
    // int right = angle < PI / 2 || angle > 1.5 * PI;

    return (x - !(angle > 0 && angle < PI) * BLOCK_SIZE);
}
int    getting_wallhit_cord_h(t_player *player, t_hitpoint *hitpoint, float angle)
{
    bool up;
    bool right;
    float y;
    float x;
    float ystep;
    float xstep;

    up = angle > 0 && angle < PI;
    right = angle < PI / 2.0f || angle > 1.5f * PI;
    y = roundf((player->y/BLOCK_SIZE)) * BLOCK_SIZE - !up * BLOCK_SIZE;
    x = player->x + (y - player->y) / tan(angle);

    ystep = BLOCK_SIZE * ((up * 1) + (!up * -1));
    xstep = BLOCK_SIZE / tan(angle);
    xstep *= (!right && xstep > 0) * -1 + !(!right && xstep > 0) * 1;
    xstep *= (right && xstep < 0) * -1 + !(right && xstep < 0) * 1;

    if (!up)
        y--;
    while (!isit_outob(x, y))
    {
        if(!isit_wall(x, y))
        {
            hitpoint->h_x = x;
            hitpoint->h_y = y;
            return 0;
        }
        x += xstep;
        y += ystep;
    }
    return 1;
}

int    getting_wallhit_cord_v(t_player *player, t_hitpoint *hitpoint, float angle)
{
    bool up;
    bool right;
    float y;
    float x;
    float ystep;
    float xstep;

    up = angle > 0 && angle < PI;
    right = angle < PI / 2.0f || angle > 1.5f * PI;
    x = roundf((player->x/BLOCK_SIZE)) * BLOCK_SIZE + right * BLOCK_SIZE;
    y = player->y + (x - player->x) * tan(angle);

    xstep = BLOCK_SIZE * ((right * 1) + (!right * -1));
    ystep = BLOCK_SIZE * tan(angle);
    ystep *= (up && ystep < 0) * -1 + !(up && ystep < 0) * 1;
    ystep *= (!up && ystep > 0) * -1 + !(!up && ystep > 0) * 1;

    if (!right)
        x--;
    while (!isit_outob(x, y))
    {
        if(!isit_wall(x, y))
        {
            hitpoint->v_x = x;
            hitpoint->v_y = y;
            return 0;
        }
        x += xstep;
        y += ystep;
    }
    return 1;
}

float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void getting_wallhit_cord(t_player *player, t_rays *rays, float angle)
{
    bool v_found;
    bool h_found;
    t_hitpoint  hitpoint;
    float vd;
    float hd;


    v_found = !getting_wallhit_cord_v(player, &hitpoint, angle);
    h_found = !getting_wallhit_cord_h(player, &hitpoint, angle);
    
    vd = v_found * distance(player->x, player->y, hitpoint.v_x, hitpoint.v_y) + !v_found * FLT_MAX;
    hd = h_found * distance(player->x, player->y, hitpoint.h_x, hitpoint.h_y) + !h_found * FLT_MAX;
    if (hd > vd)
    {
        rays->x_wallhit = hitpoint.v_x;
        rays->y_wallhit = hitpoint.v_y;
    }
    else
    {
        rays->x_wallhit = hitpoint.h_x;
        rays->y_wallhit = hitpoint.h_y;
    }
}

void cast_rays(t_player *player, t_data *img, t_rays *rays)
{
	t_line	line;
	float	angle;

	angle = player->pa - rays->fov / 2;
	line.x1 = player->x;
	line.y1 = player->y;

    // getting_wallhit_cord(player, rays, angle);

	for (int i = 0; i < rays->rays_num; i++) //rays->rays_num
	{
		// line.x2 = player->x + cos(angle) * 50;
		// line.y2 = player->y + sin(angle) * 50;
        getting_wallhit_cord(player, rays, angle);
        line.x2 = rays->x_wallhit;
        line.y2 = rays->y_wallhit;
		draw_line(line, img, 0x0000ffff);
		angle += rays->fov / rays->rays_num;
	}
}