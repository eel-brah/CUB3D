/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:35:39 by amokhtar          #+#    #+#             */
/*   Updated: 2025/02/10 14:17:33 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

static bool	set_player_info(t_map *map, int i, int j, char c)
{
	if (i == 0 || j == 0 || i == map->max_line - 1 || j == map->max_col - 1)
		return (write(2, "Palyer in Walls", 16), free_map(map), exit(1), false);
	if (map->map[((i - 1) * (map->max_col)) + j] == 'V' \
	|| map->map[((i + 1) * (map->max_col)) + j] == 'V'
		|| map->map[(i * (map->max_col)) + (j - 1)] == 'V' \
		|| map->map[(i * (map->max_col)) + j + 1] == 'V')
		return (write(2, "Palyer in Walls", 16), free_map(map), exit(1), false);
	map->player_x_pos = j;
	map->player_y_pos = i;
	if (c == 'E')
		map->player_face = 0;
	else if (c == 'W')
		map->player_face = PI;
	else if (c == 'N')
		map->player_face = PI * 1.5;
	else if (c == 'S')
		map->player_face = PI * 0.5;
	return (true);
}

bool	check(t_map *map, int i, int j, char *ermsg)
{
	if (i == 0 || j == 0 || i == map->max_line - 1 || j == map->max_col - 1)
		return (write(2, ermsg, 16), free_map(map), exit(1), false);
	if (map->map[((i - 1) * (map->max_col)) + j] == 'V' \
	|| map->map[((i + 1) * (map->max_col)) + j] == 'V'
		|| map->map[(i * (map->max_col)) + j - 1] == 'V' \
		|| map->map[(i * (map->max_col)) + j + 1] == 'V')
		return (write(2, ermsg, 16), free_map(map), exit(1), false);
	return (true);
}

static bool	check_doors(t_map *map, int i, int j, char *ermsg)
{
	check(map, i, j, ermsg);
	if (!((map->map[((i - 1) * (map->max_col)) + j] == '1' \
	&& map->map[((i + 1) * (map->max_col)) + j] == '1') \
	|| (map->map[(i * (map->max_col)) + j - 1] == '1' \
	&& map->map[(i * (map->max_col)) + j + 1] == '1')))
		return (write(2, "doors", 5), free_map(map), exit(1), false);
	return (true);
}

bool	check_walls(t_map *map, char *ermsg, int line)
{
	int		i;
	int		j;

	i = 0;
	while (i < line)
	{
		j = -1;
		while (++j < map->max_col)
		{
			if (map->map[(i * (map->max_col)) + j] == 'E' \
			|| map->map[(i * (map->max_col)) + j] == 'W' || \
			map->map[(i * (map->max_col)) + j] == 'S' \
			|| map->map[(i * (map->max_col)) + j] == 'N')
			{
				set_player_info(map, i, j, map->map[(i * (map->max_col)) + j]);
				map->map[(i * (map->max_col)) + j] = '0';
			}
			if (map->map[(i * (map->max_col)) + j] == '0')
				check(map, i, j, ermsg);
			if (map->map[(i * (map->max_col)) + j] == 'C')
				check_doors(map, i, j, ermsg);
		}
		i++;
	}
	return (true);
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
