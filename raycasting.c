#include "gm.h"

void init_rays(t_rays *rays)
{
	rays->fov = deg2rad(66);
	rays->rays_num = round(WIDTH / 1);
}

bool	wall_hit_cord_h(t_player *player, t_hitpoint *hitpoints, float angle)
{
	float	y;
	float	x;
	float	xstep;
	float	ystep;
	bool	up;
	bool	right;

	up = !(angle > 0 && angle < PI);
	// up = angle > PI;
	right = angle < PI / 2.0f || angle > 1.5f * PI;

	y = floor(player->y / BLOCK_SIZE) * BLOCK_SIZE + !up * BLOCK_SIZE;
	x = player->x + (y - player->y) / tan(angle);

	ystep = BLOCK_SIZE * ((up * -1) + (!up * 1));
	xstep = BLOCK_SIZE / tan(angle);
	xstep *= ((!right && xstep > 0) * -1 + !(!right && xstep > 0) * 1);
	xstep *= ((right && xstep < 0) * -1 + !(right && xstep < 0) * 1);

	float yc;
	
	while (!isit_outob(x, y))
    {
		yc = y - (up * 1); 
        if(isit_wall(x, yc))
        {
            hitpoints->h_x = x;
            hitpoints->h_y = y;
            return 1;
        }
        x += xstep;
        y += ystep;
    }
    return 0;
}

bool	wall_hit_cord_v(t_player *player, t_hitpoint *hitpoints, float angle)
{
	float	y;
	float	x;
	float	xstep;
	float	ystep;
	bool	up;
	bool	right;

	up = !(angle > 0 && angle < PI);
	right = angle < PI / 2.0f || angle > 1.5f * PI;

	x = floor(player->x / BLOCK_SIZE) * BLOCK_SIZE + right * BLOCK_SIZE;
	y = player->y + (x - player->x) * tan(angle);

	xstep = BLOCK_SIZE * ((!right * -1) + (right * 1));
	ystep = BLOCK_SIZE * tan(angle); 
	ystep *= ((up && ystep > 0) * -1 + !(up && ystep > 0) * 1);
	ystep *= ((!up && ystep < 0) * -1 + !(!up && ystep < 0) * 1);

	float xc;
	
	while (!isit_outob(x, y))
    {
		xc = x - (!right * 1); 
        if(isit_wall(xc, y))
        {
            hitpoints->v_x = x;
            hitpoints->v_y = y;
            return 1;
        }
        x += xstep;
        y += ystep;
    }
    return 0;
}
void	wall_hit_cord(t_player *player, t_rays *rays, float angle)
{
	t_hitpoint	hitpoints;
	bool		h_found;
	bool		v_found;
	float		vd;
	float		hd;

	h_found = wall_hit_cord_h(player, &hitpoints, angle);
	v_found = wall_hit_cord_v(player, &hitpoints, angle);

	vd = v_found * distance(player->x, player->y, hitpoints.v_x, hitpoints.v_y) + !v_found * FLT_MAX;
    hd = h_found * distance(player->x, player->y, hitpoints.h_x, hitpoints.h_y) + !h_found * FLT_MAX;
	rays->x_whpoint = (hd > vd) * hitpoints.v_x + !(hd > vd) * hitpoints.h_x;
	rays->y_whpoint = (hd > vd) * hitpoints.v_y + !(hd > vd) * hitpoints.h_y;
	rays->hit_dis = (hd > vd) * vd + !(hd > vd) * hd;
	// if (hd > vd)
	// {
	// 	rays->x_whpoint = hitpoints.v_x;
	// 	rays->y_whpoint = hitpoints.v_y;
	// }
	// else
	// {
	// 	rays->x_whpoint = hitpoints.h_x;
	// 	rays->y_whpoint = hitpoints.h_y;
	// }
}

void cast_rays(t_player *player, t_data *img, t_rays *rays)
{
	t_line	line;
	float	angle;
	int		i;

	angle = player->pa - rays->fov / 2;
	line.x1 = player->x;
	line.y1 = player->y;

	i = 0;
	while (i < rays->rays_num)
	{
		angle += (angle < 0) * (2 * PI);
		angle -= (angle > 2 * PI) * (2 * PI);
        wall_hit_cord(player, rays, angle);
        line.x2 = rays->x_whpoint;
        line.y2 = rays->y_whpoint;
		draw_line(line, img, 0x0000ffff);
		angle += rays->fov / rays->rays_num;
		i++;
	}
}