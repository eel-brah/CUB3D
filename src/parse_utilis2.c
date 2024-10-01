/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:38:26 by amokhtar          #+#    #+#             */
/*   Updated: 2024/10/01 15:01:11 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_empty(t_map *map, char *line, int *player, int i)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'E' || line[j] == 'W')
			(*player)++;
		if (line[j] == ' ')
			map->map[(i * (map->max_col)) + j] = 'V';
		else
			map->map[(i * (map->max_col)) + j] = line[j];
		j++;
	}
	while (j < map->max_col)
	{
		map->map[(i * (map->max_col)) + j] = 'V';
		j++;
	}
}

void	*fill_array(t_map *map, int player)
{
	int		i;
	t_list	*tmp;

	map->rows = map->max_line;
	map->cols = map->max_col;
	i = 0;
	map->map = malloc(sizeof(char) * ((map->max_line * map->max_col) + 1));
	if (!map->map)
		return (perror("malloc"), free_map(map), exit(1), NULL);
	tmp = map->lst;
	while (i < map->max_line)
	{
		set_empty(map, tmp->content, &player, i);
		tmp = tmp->next;
		i++;
	}
	map->map[(--i * (map->max_col)) + map->max_col] = '\0';
	if (player == 0 || player > 1)
	{
		write(2, "Error\nNb Player\n", 16);
		return (free_map(map), exit(1), NULL);
	}
	return (NULL);
}

void	exit_err(t_map *map, char *tmp, char *line, char *msg)
{
	free_map(map);
	free(tmp);
	free(line);
	close(map->fd);
	write (2, "Error\n", 6);
	while (msg && *msg)
	{
		write(2, msg, 1);
		msg++;
	}
	exit(1);
}

void	store_map(t_map *map, char *line, char *tmp, bool *flag)
{
	t_list	*tmp1;
	int		len;

	len = ft_strlen(tmp);
	if (ft_strlen(tmp) >= 0 && (tmp[0] != '1' || tmp[len - 1] != '1'))
		exit_err(map, tmp, line, "Not End By Wall\n");
	if (!check_line(line))
		exit_err(map, tmp, line, "Other caractere that not allowd\n");
	free(tmp);
	*flag = false;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	if (map->max_col < len)
		map->max_col = len;
	tmp1 = ft_lstnew(line);
	if (!tmp1)
		exit_err(map, NULL, line, "malloc failed\n");
	ft_lstadd_back(&map->lst, tmp1);
	map->max_line++;
}

bool	fill_map(t_map *map, int fd, bool flag, int count)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, " 	\n");
		if (ft_strlen(tmp) == 0 && flag)
		{
			free(line);
			free(tmp);
			continue ;
		}
		if (count < 6)
		{
			free(line);
			line = tmp;
			fill_wall(map, line, &count);
		}
		else
			store_map(map, line, tmp, &flag);
	}
	return (close(fd), true);
}
