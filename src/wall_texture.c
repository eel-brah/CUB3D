/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:24:25 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/30 11:47:06 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_data	*horizontal_texture(t_vars *vars, int i)
{
	int		x;
	int		y;
	bool	right;

	x = floor(vars->rays[i].x_whpoint / BLOCK_SIZE);
	y = floor(vars->rays[i].y_whpoint / BLOCK_SIZE);
	right = vars->player->pa < PI / 2.0f || vars->player->pa > 1.5f * PI;
	if (vars->rays[i].y_whpoint > vars->player->y)
	{
		if (DOOR_OPEN && door_check(vars, x, y - 1) == 3 && door_check(vars, x, y - 2) == 1)
		{
			if (right)
				return (&vars->right_right);
			return (&vars->right_left);
		}
		return (&vars->south);
	}
	else if (DOOR_OPEN && door_check(vars, x, y) == 3 && door_check(vars, x, y + 1) == 1)
	{
		if (right)
			return (&vars->left_left);
		return (&vars->left_right);
	}
	return (&vars->north);
}

t_data	*vertical_texture(t_vars *vars, int i)
{
	int		x;
	int		y;
	bool	up;

	x = floor(vars->rays[i].x_whpoint / BLOCK_SIZE);
	y = floor(vars->rays[i].y_whpoint / BLOCK_SIZE);
	up = !(vars->player->pa > 0 && vars->player->pa < PI);
	if (vars->rays[i].x_whpoint > vars->player->x)
	{
		if (DOOR_OPEN && door_check(vars, x - 1, y) == 3 && door_check(vars, x - 2, y) == 1)
		{
			if (up)
				return (&vars->down_down);
			return (&vars->down_up);
		}
		return (&vars->east);
	}
	else if (DOOR_OPEN && door_check(vars, x, y) == 3 && door_check(vars, x + 1, y) == 1)
	{
		if (up)
			return (&vars->up_down);
		return (&vars->up_up);
	}
	return (&vars->west);
}

t_data	*get_texture(t_vars *vars, int i)
{
	if (vars->rays[i].is_door)
		return (&vars->door);
	else
	{
		if (vars->rays[i].is_vertical)
			return (vertical_texture(vars, i));
		else
			return (horizontal_texture(vars, i));
	}
	return (&vars->east);
}
