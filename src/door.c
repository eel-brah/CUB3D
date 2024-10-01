/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:21:21 by eel-brah          #+#    #+#             */
/*   Updated: 2024/10/01 13:30:30 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	check_door_in_map(char *map, int xy)
{
	if (map[xy] == 'C')
	{
		map[xy] = 'O';
		return (1);
	}
	else if (map[xy] == 'O')
	{
		map[xy] = 'C';
		return (1);
	}
	return (0);
}

void	open_close_door(t_vars *vars)
{
	int	i;
	int	xy;
	int	new_x;
	int	new_y;

	i = BLOCK_SIZE + vars->player->r;
	while (i < BLOCK_SIZE * 2)
	{
		new_x = vars->player->x
			+ (cos(vars->player->pa + vars->player->rspeed) * i);
		new_y = vars->player->y
			+ (sin(vars->player->pa + vars->player->rspeed) * i);
		if (new_x > 0 && new_y > 0 && new_x < WIDTH && new_y < HEIGHT)
		{
			xy = (new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE);
			if (check_door_in_map(vars->map->map, xy))
				return ;
		}
		i++;
	}
}

int	door_check(t_vars *vars, float tx, float ty)
{
	bool	flag;
	int		xy;

	flag = ty >= 0 && ty < vars->map->rows && tx >= 0 && tx < vars->map->cols;
	xy = ty * vars->map->cols + tx;
	if (flag && vars->map->map[xy] == '1')
		return (1);
	if (flag && vars->map->map[xy] == 'O')
		return (3);
	return (0);
}
