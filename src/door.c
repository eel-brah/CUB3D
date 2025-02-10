/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:21:21 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/10 14:16:51 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

bool	check_door_in_map(t_vars *vars, int xy, int x, int y)
{
	(void)x;
	if (vars->map->map[xy] == 'C')
	{
		vars->map->map[xy] = 'O';
		vars->door_up = (y / BLOCK_SIZE < vars->player->y / BLOCK_SIZE);
		vars->door_right = (x / BLOCK_SIZE > vars->player->x / BLOCK_SIZE);
		return (1);
	}
	else if (vars->map->map[xy] == 'O')
	{
		vars->map->map[xy] = 'C';
		vars->door_up = (y / BLOCK_SIZE < vars->player->y / BLOCK_SIZE);
		vars->door_right = (x / BLOCK_SIZE > vars->player->x / BLOCK_SIZE);
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
			+ (cos(vars->player->pa) * i);
		new_y = vars->player->y
			+ (sin(vars->player->pa) * i);
		if (new_x > 0 && new_y > 0 && new_x < WIDTH && new_y < HEIGHT)
		{
			xy = (new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE);
			if (check_door_in_map(vars, xy, new_x, new_y))
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
