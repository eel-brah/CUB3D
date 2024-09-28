/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:03:19 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/28 12:06:13 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

void init_ray(t_vars *vars)
{
	vars->ray->fov = deg2rad(66);
	vars->ray->rays_num = WIDTH;
}

int	isit_wall(t_vars *vars, float x, float y)
{
	int		ty;
	int		tx;
	bool	flag;

	ty = floor(y/BLOCK_SIZE);
	tx = floor(x/BLOCK_SIZE);
	flag = ty >= 0 && ty < vars->map->rows && tx >= 0 && tx < vars->map->cols;
	if ( flag && (vars->map->map[ty * vars->map->cols + tx] == '0' || vars->map->map[ty * vars->map->cols + tx] == 'O'))
		return 0;
	if (flag && vars->map->map[ty * vars->map->cols + tx] == 'C')
		return 2;
	return 1;
}

void	wall_hit_cord(t_vars *vars, t_player *player, t_rays *ray, float angle)
{
	t_hitpoint	hitpoints;
	bool		h_found;
	bool		v_found;
	float		vd;
	float		hd;
	
	hitpoints.h_x = 0;
	hitpoints.h_y = 0;
	hitpoints.v_x = 0;
	hitpoints.v_y = 0;
	hitpoints.v_is_door = 0;
	hitpoints.h_is_door = 0;
	h_found = wall_hit_cord_h(vars, player, &hitpoints, angle);
	v_found = wall_hit_cord_v(vars, player, &hitpoints, angle);
	vd = v_found * distance(player->x, player->y, hitpoints.v_x, hitpoints.v_y) + !v_found * FLT_MAX;
    hd = h_found * distance(player->x, player->y, hitpoints.h_x, hitpoints.h_y) + !h_found * FLT_MAX;
	ray->x_whpoint = (hd > vd) * hitpoints.v_x + !(hd > vd) * hitpoints.h_x;
	ray->y_whpoint = (hd > vd) * hitpoints.v_y + !(hd > vd) * hitpoints.h_y;
	ray->hit_dis = (hd > vd) * vd + !(hd > vd) * hd;
	ray->is_vertical = (hd > vd) * 1;
	ray->is_vertical = (hd > vd) * 1;
	ray->is_door = (hd > vd) * hitpoints.v_is_door + !(hd > vd) * hitpoints.h_is_door;
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
        wall_hit_cord(vars, vars->player, (vars->rays)+i, angle);
		vars->rays[i].angle = angle;
		angle += vars->ray->fov / vars->ray->rays_num;
		i++;
	}
}

// void	draw_rays(t_vars *vars)
// {	
// 	t_line	line;
// 	int	i;

// 	line.x1 = vars->player->x * MMSF;
// 	line.y1 = vars->player->y * MMSF;
// 	i = 0;
// 	while (i < vars->ray->rays_num)
// 	{
//         line.x2 = vars->rays[i].x_whpoint * MMSF;
//         line.y2 = vars->rays[i].y_whpoint * MMSF;
// 		draw_line(vars, line, 0x0000ffff);
// 		i++;
// 	}
// }
