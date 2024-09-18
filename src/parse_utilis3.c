/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:35:39 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/18 13:04:42 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	set_player_info(t_map *map, int i, int j, char c)
{
	if (i == 0 || j == 0 || i == map->max_line - 1 || j == map->max_col - 1)
		return (write(2, "Palyer in Walls", 16), free_map(map), exit(1), false);
	if (map->map[((i - 1) * (map->max_col)) + j] == 'V' || map->map[((i + 1) * (map->max_col)) + j] == 'V'
		|| map->map[(i * (map->max_col)) + (j - 1)] == 'V' || map->map[(i * (map->max_col)) + j + 1] == 'V')
		return (write(2, "Palyer in Walls", 16), free_map(map), exit(1), false);
	map->player_x_pos = j;
	map->player_y_pos = i;
	if (c == 'E')
		map->player_face = EAST;
	else if (c == 'W')
		map->player_face = WEST;
	else if (c == 'N')
		map->player_face = NORHT;
	else if (c == 'S')
		map->player_face = SOUTH;
	return (true);
}

bool	check_walls(t_map *map, char *ermsg, int line)
{
	int		i;
	int		j;

	i = 0;
	while (i < line)
	{
		j = 0;
		while (j < map->max_col)
		{
			if (map->map[(i * (map->max_col)) + j] == 'E' || map->map[(i * (map->max_col)) + j] == 'W'
			|| map->map[(i * (map->max_col)) + j] == 'S' || map->map[(i * (map->max_col)) + j] == 'N')
			{
				set_player_info(map, i, j, map->map[(i * (map->max_col)) + j]);
				map->map[(i * (map->max_col)) + j] = '0';
			}
			if (map->map[(i * (map->max_col)) + j] == '0')
			{
				if (i == 0 || j == 0 || i == line - 1 || j == map->max_col - 1)
					return (write(2, ermsg, 16), free_map(map), exit(1), false);
				if (map->map[((i - 1) * (map->max_col)) + j] == 'V' || map->map[((i + 1) * (map->max_col)) + j] == 'V'
					|| map->map[(i * (map->max_col)) + j - 1] == 'V' || map->map[(i * (map->max_col)) + j + 1] == 'V')
					return (write(2, ermsg, 16), free_map(map), exit(1), false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	// while (map->map && map->map[i])
	// {
	// 	free(map->map[i]);
	// 	i++;
	// }
	free(map->map);
	free_linked(map->lst);
	free(map);
}

int	ft_atoi_over(const char *str)
{
	long int	nb;

	nb = 0;
	while (*str && *str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str++ - '0');
		if (nb > 255 || nb < 0)
			return (300);
	}
	return (nb);
}
