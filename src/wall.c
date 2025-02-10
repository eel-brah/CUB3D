/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:44 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/10 14:18:12 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

void	color_ceiling_floor(int x, int top, int bottom, t_vars *vars)
{
	int	i;

	i = 0;
	while (i <= top)
		put_pixel(vars, x, i++, vars->map->c_color);
	i = HEIGHT;
	while (i >= bottom)
		put_pixel(vars, x, i--, vars->map->f_color);
}

float	get_image_x(t_vars *vars, int i, int width)
{
	float	x;

	if (vars->rays[i].is_vertical)
		x = fmod(vars->rays[i].y_whpoint, BLOCK_SIZE);
	else
		x = fmod(vars->rays[i].x_whpoint, BLOCK_SIZE);
	x /= BLOCK_SIZE;
	return (x *= width);
}

float	calc_wall(t_vars *vars, int i, int *top, int *bottom)
{
	float	wall_height;
	float	wall_dis;

	wall_dis = vars->rays[i].hit_dis
		* cos(vars->rays[i].angle - vars->player->pa);
	wall_height = (BLOCK_SIZE / wall_dis) * vars->ray->proj_wall_dis;
	*top = HEIGHT / 2 - wall_height / 2;
	if (*top < 0)
		*top = 0;
	*bottom = HEIGHT / 2 + wall_height / 2;
	if (*bottom > HEIGHT)
		*bottom = HEIGHT;
	return (wall_height);
}

void	draw_wall(t_vars *vars)
{
	t_wall	wall;
	float	x;
	int		y;
	int		i;
	float	ry;

	i = 0;
	while (i < vars->ray->rays_num)
	{
		wall.height = calc_wall(vars, i, &wall.top, &wall.bottom);
		wall.texture = get_texture(vars, i);
		x = get_image_x(vars, i, wall.texture->width);
		y = wall.top;
		wall.norm = (wall.height / 2.0f) - (HEIGHT / 2.0f);
		while (y < wall.bottom)
		{
			ry = y + wall.norm;
			put_pixel(vars, i, y, get_color_from_img(wall.texture, x,
					ry * (wall.texture->height / wall.height)));
			y++;
		}
		color_ceiling_floor(i, wall.top, wall.bottom, vars);
		i++;
	}
}
