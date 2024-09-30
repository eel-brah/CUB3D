/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:03:19 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/30 17:11:47 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray(t_vars *vars)
{
	vars->ray->fov = deg2rad(66);
	vars->ray->rays_num = WIDTH;
	vars->ray->proj_wall_dis = (WIDTH / 2) / tan(vars->ray->fov / 2);
}

int	isit_wall(t_vars *vars, float x, float y)
{
	int		ty;
	int		tx;
	bool	flag;
	int		xy;

	ty = floor(y / BLOCK_SIZE);
	tx = floor(x / BLOCK_SIZE);
	flag = ty >= 0 && ty < vars->map->rows && tx >= 0 && tx < vars->map->cols;
	xy = ty * vars->map->cols + tx;
	if (flag && (vars->map->map[xy] == '0' || vars->map->map[xy] == 'O'))
		return (0);
	if (flag && vars->map->map[xy] == 'C')
		return (2);
	return (1);
}

void	wall_hit_cord(t_vars *vars, t_player *player, t_rays *ray, float angle)
{
	t_hitpoint	hitpoints;
	bool		h_found;
	bool		v_found;
	float		vd;
	float		hd;

	ft_memset(&hitpoints, 0, sizeof(t_hitpoint));
	h_found = wall_hit_cord_h(vars, player, &hitpoints, angle);
	v_found = wall_hit_cord_v(vars, player, &hitpoints, angle);
	vd = v_found * distance(player->x, player->y, hitpoints.v_x,
			hitpoints.v_y) + !v_found * FLT_MAX;
	hd = h_found * distance(player->x, player->y, hitpoints.h_x,
			hitpoints.h_y) + !h_found * FLT_MAX;
	ray->x_whpoint = (hd > vd) * hitpoints.v_x + !(hd > vd) * hitpoints.h_x;
	ray->y_whpoint = (hd > vd) * hitpoints.v_y + !(hd > vd) * hitpoints.h_y;
	ray->hit_dis = (hd > vd) * vd + !(hd > vd) * hd;
	ray->is_vertical = (hd > vd) * 1;
	ray->is_vertical = (hd > vd) * 1;
	ray->is_door = (hd > vd) * hitpoints.v_door + !(hd > vd) * hitpoints.h_door;
}

void	cast_rays(t_vars *vars)
{
	float	angle;
	int		i;

	angle = vars->player->pa - vars->ray->fov / 2;
	free(vars->rays);
	vars->rays = malloc(sizeof(t_rays) * vars->ray->rays_num);
	if (!vars->rays)
		clear_and_close(vars);
	i = 0;
	while (i < vars->ray->rays_num)
	{
		angle += (angle < 0) * (2 * PI);
		angle -= (angle > 2 * PI) * (2 * PI);
		wall_hit_cord(vars, vars->player, (vars->rays) + i, angle);
		vars->rays[i].angle = angle;
		angle += vars->ray->fov / vars->ray->rays_num;
		i++;
	}
}
