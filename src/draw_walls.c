/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:08:14 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/27 11:45:03 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


unsigned int	get_colorr(t_data *data, int x, int y)
{
	char	*dst;

	// printf("x %d y %d\n", x,y);
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	// dst = 100 << 24;
	// return (160 << 24 | *(unsigned int*)dst);
	return (*(unsigned int*)dst);
}

void color_sealing_floor(int x, int top, int bottom, t_vars *vars)
{
	int i = 0;
	while(i < top)
		put_pixel(vars, x, i++, vars->map->c_color);
	i = HEIGHT;
	while(i > bottom)
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
		int	xx;
		if (vars->rays[i].is_door)
		{
			data = vars->door;
		}
		else
		{
			if (vars->rays[i].is_vertical)
			{
				// For vertical intersections, we use the x-coordinate to determine east or west
				if (vars->rays[i].x_whpoint > vars->player->x)
					data = vars->east;
				else
					data = vars->west;
			}
			else
			{
				// For horizontal intersections, we use the y-coordinate to determine north or south
				if (vars->rays[i].y_whpoint > vars->player->y)
					data = vars->south;
				else
					data = vars->north;
			}
		}
		float h;
		xx= 0;
		if (vars->rays[i].is_vertical)
			h = (int)((int)vars->rays[i].y_whpoint) % BLOCK_SIZE;
		else
			h = (int)((int)vars->rays[i].x_whpoint) % BLOCK_SIZE;
		h /= BLOCK_SIZE;
		h *= data.width;
		float dist_top;
		while (y < bottom)
		{
			// ss = (y - top) * ((float )data.height /wall_height);
			dist_top =(y + (float)((wall_height / 2) - (HEIGHT / 2)));
			// 64 ---> form mlx_xpm_file_to_image
			// printf("x %d y %d\n",xx ,(int)((dist_top) * (data.height / wall_height)));
			// if (y - top == 0)
			unsigned int a = get_colorr(&data, (int)h, (int)((dist_top) * (data.height / wall_height)));
			put_pixel(vars, i, y, a);
			y++;
		}
		// create_trgb(100, 24, 28, 20)
		color_sealing_floor(i, top, bottom, vars);
		i++;
	}
}
