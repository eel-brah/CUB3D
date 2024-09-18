/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:05 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/17 16:37:56 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	get_color(char **spl)
{
	unsigned int	color;
	int				tmp;

	tmp = ft_atoi_over(spl[0]);
	if (tmp < 0 || tmp > 255)
		return (300);
	color = ft_atoi_over(spl[0]) << 24;
	tmp = ft_atoi_over(spl[1]);
	if (tmp < 0 || tmp > 255)
		return (300);
	color += ft_atoi_over(spl[1]) << 16;
	tmp = ft_atoi_over(spl[2]);
	if (tmp < 0 || tmp > 255)
		return (300);
	color += ft_atoi_over(spl[2]) << 8;
	color += 0xff;
	return (color);
}

bool	is_all_num(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (arr && arr[j])
	{
		tmp = ft_strtrim(arr[j], "	 ");
		i = 0;
		while (tmp[i])
		{
			if (tmp[i] > '9' || tmp[i] < '0')
				return (free(tmp), false);
			i++;
		}
		free(tmp);
		j++;
	}
	return (true);
}

int	len_2d(char **sp)
{
	int	i;

	i = 0;
	while (sp && sp[i])
		i++;
	return (i);
}

bool	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i + 1] && line[i] != '\n'))
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	fill_wall(t_map *map, char *line, int *count)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		if (map->no)
			return (exit_err(map, NULL, line, "Duplicate Path"), exit(1), false);
		map->no = ft_strtrim(line + 2, " 	\n");
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		if (map->so)
			return (exit_err(map, NULL, line, "Duplicate Path"), exit(1), false);
		map->so = ft_strtrim(line + 2, " 	\n");
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		if (map->we)
			return (exit_err(map, NULL, line, "Duplicate Path"), exit(1), false);
		map->we = ft_strtrim(line + 2, " 	\n");
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		if (map->ea)
			return (exit_err(map, NULL, line, "Duplicate Path"), exit(1), false);
		map->ea = ft_strtrim(line + 2, " 	\n");
	}
	else if (line[0] == 'C' && line[1])
	{
		if (map->c != 300)
			return (exit_err(map, NULL, line, "Duplicate Color"), exit(1), false);
		fill_color(map, line);
	}
	else if (line [0] == 'F' && line[1] && map->f == 300)
	{
		if (map->f != 300)
			return (exit_err(map, NULL, line, "Duplicate Color"), exit(1), false);
		fill_color(map, line);
	}
	else if (line[0] == '0' || line[0] == '1')
	{
		if (!map->ea || !map->so || !map->no || !map->we)
			return (exit_err(map, NULL, line, "Missing Path"), exit(1), false);
		if (map->c == 300 || map->f == 300)
			return (exit_err(map, NULL, line, "Missing Color"), exit(1), false);
	}
	else
		return (exit_err(map, NULL, line, "Inavlide Map"), exit(1), false);
	free(line);
	(*count)++;
	return (true);
}
