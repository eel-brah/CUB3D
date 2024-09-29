/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:44 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/29 13:24:53 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


unsigned int	get_color_from_img(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	// return (160 << 24 | *(unsigned int*)dst);
	return (*(unsigned int*)dst);
}

void	color_sealing_floor(int x, int top, int bottom, t_vars *vars)
{
	int	i;

	i = 0;
	while(i <= top)
		put_pixel(vars, x, i++, vars->map->c_color);
	i = HEIGHT;
	while(i >= bottom)
		put_pixel(vars, x, i--, vars->map->f_color);
}

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

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

t_data	*get_texture(t_vars *vars, int i)
{
	if (vars->rays[i].is_door)
		return (&vars->door);
	else
	{
		if (vars->rays[i].is_vertical)
		{
			if (vars->rays[i].x_whpoint > vars->player->x)
				return (&vars->east);
			else
				return (&vars->west);
		}
		else
		{
			if (vars->rays[i].y_whpoint > vars->player->y)
				return (&vars->south);
			else
				return (&vars->north);
		}
	}
	return (&vars->east);
}

void draw_wall(t_vars *vars)
{
	float wall_height;
	float proj_wall_dis;
	int top;
	int bottom;
	int y;
	float wall_dis;
	t_data *data;
	float x;
	int i = 0;
	float dist_top;

	proj_wall_dis = (WIDTH / 2) / tan(vars->ray->fov / 2);
	while (i < vars->ray->rays_num)
	{
		wall_dis = vars->rays[i].hit_dis * cos(vars->rays[i].angle - vars->player->pa);
		wall_height = (BLOCK_SIZE / wall_dis) * proj_wall_dis;
		top = HEIGHT / 2 - wall_height / 2;
		top = (top < 0) * 0 + !(top < 0) * top;
		bottom = HEIGHT / 2 + wall_height / 2;
		bottom = (bottom > HEIGHT) * HEIGHT + !(bottom > HEIGHT) * bottom;
		y = top;
		data = get_texture(vars, i);
		x = get_image_x(vars, i, data->width);
		while (y < bottom)
		{
			dist_top = (y + (float)((wall_height / 2) - (HEIGHT / 2)));
			put_pixel(vars, i, y, get_color_from_img(data, x, (dist_top * (data->height / wall_height))));
			y++;
		}
		color_sealing_floor(i, top, bottom, vars);
		i++;
	}
}

// create_trgb(100, 24, 28, 20)

void	open_close_door(t_vars *vars) // door has walls on the side
{
	int	i;
	
	i = BLOCK_SIZE + vars->player->r;
	while (i < BLOCK_SIZE * 2)
	{
		int new_x = vars->player->x + (cos(vars->player->pa + vars->player->rspeed) * i);
		int new_y = vars->player->y + (sin(vars->player->pa + vars->player->rspeed) * i);
		if (new_x > 0 && new_y > 0 && new_x < WIDTH && new_y < HEIGHT)
		{
			int d = vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)];
			if (d == 'C')
			{
				vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] = 'O';
				break;
			}
			else if (d == 'O')
			{
				vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] = 'C';
				break ;
			}
		}
		i++;
	}
}
