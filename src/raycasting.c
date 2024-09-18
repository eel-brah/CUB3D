#include "../include/cub3d.h"

void init_ray(t_ray *ray)
{
	ray->fov = deg2rad(66);
	ray->rays_num = WIDTH;
}

bool	wall_hit_cord_h(t_player *player, t_hitpoint *hitpoints, float angle)
{
	float	y;
	float	x;
	float	xstep;
	float	ystep;
	bool	up;
	bool	right;
	float	yc;

	up = !(angle > 0 && angle < PI);
	// up = angle > PI;
	right = angle < PI / 2.0f || angle > 1.5f * PI;

	y = floor(player->y / BLOCK_SIZE) * BLOCK_SIZE + !up * BLOCK_SIZE;
	x = player->x + (y - player->y) / tan(angle);

	ystep = BLOCK_SIZE * ((up * -1) + (!up * 1));
	xstep = BLOCK_SIZE / tan(angle);
	xstep *= ((!right && xstep > 0) * -1 + !(!right && xstep > 0) * 1);
	xstep *= ((right && xstep < 0) * -1 + !(right && xstep < 0) * 1);
	
	while (!isit_outob(x, y))
    {
		yc = y - (up * 1); 
        if(isit_wall(x, yc))
        {
            hitpoints->h_x = x;
            hitpoints->h_y = yc;
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
	float	xc;

	up = !(angle > 0 && angle < PI);
	right = angle < PI / 2.0f || angle > 1.5f * PI;

	x = floor(player->x / BLOCK_SIZE) * BLOCK_SIZE + right * BLOCK_SIZE;
	y = player->y + (x - player->x) * tan(angle);

	xstep = BLOCK_SIZE * ((!right * -1) + (right * 1));
	ystep = BLOCK_SIZE * tan(angle); 
	ystep *= ((up && ystep > 0) * -1 + !(up && ystep > 0) * 1);
	ystep *= ((!up && ystep < 0) * -1 + !(!up && ystep < 0) * 1);
	
	while (!isit_outob(x, y))
    {
		xc = x - (!right * 1); 
        if(isit_wall(xc, y))
        {
            hitpoints->v_x = xc;
            hitpoints->v_y = y;
            return 1;
        }
        x += xstep;
        y += ystep;
    }
    return 0;
}
void	wall_hit_cord(t_player *player, t_rays *ray, float angle)
{
	t_hitpoint	hitpoints;
	hitpoints.h_x = 0;
	hitpoints.h_y = 0;
	hitpoints.v_x = 0;
	hitpoints.v_y = 0;
	bool		h_found;
	bool		v_found;
	float		vd;
	float		hd;

	h_found = wall_hit_cord_h(player, &hitpoints, angle);
	v_found = wall_hit_cord_v(player, &hitpoints, angle);

	vd = v_found * distance(player->x, player->y, hitpoints.v_x, hitpoints.v_y) + !v_found * FLT_MAX;
    hd = h_found * distance(player->x, player->y, hitpoints.h_x, hitpoints.h_y) + !h_found * FLT_MAX;
	ray->x_whpoint = (hd > vd) * hitpoints.v_x + !(hd > vd) * hitpoints.h_x;
	ray->y_whpoint = (hd > vd) * hitpoints.v_y + !(hd > vd) * hitpoints.h_y;
	ray->hit_dis = (hd > vd) * vd + !(hd > vd) * hd;
	// if (ray->hit_dis == 0){
	// 	printf("v{%f %f} h{%f %f}\n", hitpoints.v_x, hitpoints.v_y, hitpoints.h_x, hitpoints.h_y);
	// 	printf("h{%f %f %f %f}\n", player->x, player->y, ray->x_whpoint, ray->y_whpoint);

	// }
	// else{
	// 	printf("== %f %f %f\n", ray->x_whpoint, ray->y_whpoint, ray->hit_dis);
	// }

// 	v{850.000000 316.297607} h{740.000000 350.000000}
// h{740.000000 350.000000}
	// if (hd > vd)
	// {
	// 	ray->x_whpoint = hitpoints.v_x;
	// 	ray->y_whpoint = hitpoints.v_y;
	// }
	// else
	// {
	// 	ray->x_whpoint = hitpoints.h_x;
	// 	ray->y_whpoint = hitpoints.h_y;
	// }
}

void color_sealing_floor(int x, int top, int bottom, t_data *img)
{
	int i = 0;
	while(i < top)
		put_pixel(img, x, i++, SEALING_COLOR);
	i = HEIGHT;
	while(i > bottom)
		put_pixel(img, x, i--, FLOOR_COLOR);
}

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void draw_wall(t_vars *vars)
{
	float wall_height;
	float proj_wall_dis;
	int top;
	int bottom;
	int y;
	float wall_dis;

	proj_wall_dis = (WIDTH / 2) / tan(vars->ray->fov / 2);

	int i = 0;
	while (i < vars->ray->rays_num)
	{
		wall_dis = vars->rays[i].hit_dis * cos(vars->rays[i].angle - vars->player->pa);
		wall_height = (BLOCK_SIZE / wall_dis) * proj_wall_dis;
		top = HEIGHT / 2 - wall_height / 2;
		top = (top < 0) * 0 + !(top < 0) * top;
		bottom = HEIGHT / 2 + wall_height / 2;
		bottom = (bottom > HEIGHT) * HEIGHT + !(bottom > HEIGHT) * bottom;
		y = top;
		// printf("{%f %f %i}\n", vars->rays[i].hit_dis, cos(vars->rays[i].angle - vars->player->pa), bottom);
		while (y < bottom)
			put_pixel(vars->img, i, y++, WALL_COLOR);
		// create_trgb(100, 24, 28, 20)
		color_sealing_floor(i, top, bottom, vars->img);
		i++;
	}
}

void cast_rays(t_vars *vars)
{

	float	angle;
	int		i;

	angle = vars->player->pa - vars->ray->fov / 2;
	
	vars->rays = malloc(sizeof(t_rays) * vars->ray->rays_num);
	i = 0;
	while (i < vars->ray->rays_num)
	{
		angle += (angle < 0) * (2 * PI);
		angle -= (angle > 2 * PI) * (2 * PI);
        wall_hit_cord(vars->player, (vars->rays)+i, angle);
		vars->rays[i].angle = angle;
		angle += vars->ray->fov / vars->ray->rays_num;
		i++;
	}
}

void	draw_rays(t_vars *vars)
{	
	t_line	line;
	int	i;

	line.x1 = vars->player->x * MMS;
	line.y1 = vars->player->y * MMS;
	i = 0;
	while (i < vars->ray->rays_num)
	{
        line.x2 = vars->rays[i].x_whpoint * MMS;
        line.y2 = vars->rays[i].y_whpoint * MMS;
		draw_line(line, vars->img, 0x0000ffff);
		i++;
	}
}