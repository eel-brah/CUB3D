/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:44 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/28 12:02:47 by eel-brah         ###   ########.fr       */
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

void color_sealing_floor(int x, int top, int bottom, t_vars *vars)
{
	int i = 0;
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

void draw_wall(t_vars *vars)
{
	float wall_height;
	float proj_wall_dis;
	int top;
	int bottom;
	int y;
	float wall_dis;
	t_data data;

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
		if (vars->rays[i].is_door)
			data = vars->door;
		else
		{
			if (vars->rays[i].is_vertical)
			{
				if (vars->rays[i].x_whpoint > vars->player->x)
					data = vars->east;
				else
					data = vars->west;
			}
			else
			{
				if (vars->rays[i].y_whpoint > vars->player->y)
					data = vars->south;
				else
					data = vars->north;
			}
		}
		float h;
		if (vars->rays[i].is_vertical)
			h = fmod(vars->rays[i].y_whpoint, BLOCK_SIZE);
		else
			h = fmod(vars->rays[i].x_whpoint, BLOCK_SIZE);
		h /= BLOCK_SIZE;
		h *= data.width;
		float dist_top;
		while (y < bottom)
		{
			dist_top =(y + (float)((wall_height / 2) - (HEIGHT / 2)));
			unsigned int a = get_color_from_img(&data, h, (dist_top * (data.height / wall_height)));
			put_pixel(vars, i, y, a);
			y++;
		}
		// create_trgb(100, 24, 28, 20)
		color_sealing_floor(i, top, bottom, vars);
		i++;
	}
}

void	open_close_door(t_vars *vars) // door has walls on the side
{
	int i;
	
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
