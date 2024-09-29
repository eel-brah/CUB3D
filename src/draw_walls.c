/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:44 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/29 18:46:20 by eel-brah         ###   ########.fr       */
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

int	door_check(t_vars *vars, float tx, float ty)
{
	bool	flag;
	int		xy;

	flag = ty >= 0 && ty < vars->map->rows && tx >= 0 && tx < vars->map->cols;
	xy = ty * vars->map->cols + tx;
	if (flag && vars->map->map[xy] == '0')
		return (0);
	if (flag && vars->map->map[xy] == 'C')
		return (2);
	if (flag && vars->map->map[xy] == 'O')
		return (3);
	return (1);
}

t_data	*get_texture(t_vars *vars, int i)
{
	int x = floor(vars->rays[i].x_whpoint/ BLOCK_SIZE);
	int y = floor(vars->rays[i].y_whpoint/ BLOCK_SIZE);
	bool	up = !(vars->player->pa > 0 && vars->player->pa < PI);
	bool right = vars->player->pa < PI / 2.0f || vars->player->pa > 1.5f * PI;
	// if (vars->map->map[(y-1) * vars->map->cols + x] == 'O' && (vars->map->map[(y-2) * vars->map->cols + x] == '1'))
	// if (door_check(vars, x-1, y) == 3 && door_check(vars, x-2, y) == 1)
	// {
	// 	return (&vars->door_right);
	// }
	// // if (vars->map->map[y * vars->map->cols + x] == 'O' && (vars->map->map[(y+1) * vars->map->cols + x] == '1'))
	// if (door_check(vars, x, y) == 3 && door_check(vars, x+1, y) == 1)
	// {
	// 	return (&vars->door_left);
	// }
	// printf("== %c %c %i %i\n", vars->map->map[(y+1) * vars->map->cols + x], vars->map->map[(y+2) * vars->map->cols + x], y , x);
	if (vars->rays[i].is_door)
		return (&vars->door);
	else
	{
		if (vars->rays[i].is_vertical)
		{
			if (vars->rays[i].x_whpoint > vars->player->x)
			{
				if (door_check(vars, x-1, y) == 3 && door_check(vars, x-2, y) == 1)
				{
					if (up)
						return (&vars->down_down);
					else
						return (&vars->up_down);
				}
				return (&vars->east);
			}
			else if (door_check(vars, x, y) == 3 && door_check(vars, x+1, y) == 1)
			{
				if (up)
					return (&vars->up_up);
				else
					return (&vars->down_up);
				
			}
			else
				return (&vars->west);
		}
		else
		{
			if (vars->rays[i].y_whpoint > vars->player->y)
			{
				if (door_check(vars, x, y-1) == 3 && door_check(vars, x, y-2) == 1)
				{
					if (right)
						return (&vars->right_right);
					else
						return (&vars->right_left);
				}
				return (&vars->south);
			}
			else if (door_check(vars, x, y) == 3 && door_check(vars, x, y+1) == 1)
			{
				if (right)
					return (&vars->left_left);
				else
					return (&vars->left_right);
			}
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
