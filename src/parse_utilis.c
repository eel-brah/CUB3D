/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:34:44 by amokhtar          #+#    #+#             */
/*   Updated: 2025/02/10 14:17:46 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

static void	failed_malloc_in_color(t_map *map, char *line, char *tmp1)
{
	close(map->fd);
	perror("malloc");
	free_map(map);
	free(line);
	free(tmp1);
	exit(1);
}

static void	free_in_color(t_map *map, char *line, char **tmp, char *tmp1)
{
	close(map->fd);
	free_map(map);
	free(line);
	free(tmp1);
	free_2d(tmp);
	write(2, "Error\nerror in color\n", 21);
	exit(1);
}

static void	set_color(t_map *map, unsigned int color, char c)
{
	if (c == 'F')
		map->f_color = color;
	else if (c == 'C')
		map->c_color = color;
}

static bool	nb_semicolone(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == ',')
			count++;
		if (count > 2)
			return (true);
		i++;
	}
	if (count < 2)
		return (true);
	return (false);
}

void	fill_color(t_map *map, char *line)
{
	char			**tmp;
	char			*tmp1;
	int				len;
	unsigned int	color;

	tmp = NULL;
	tmp1 = ft_strtrim(line + 1, " \n");
	if (!tmp1)
		failed_malloc_in_color(map, line, NULL);
	if (nb_semicolone(tmp1))
		free_in_color(map, line, tmp, tmp1);
	tmp = ft_split(tmp1, ',');
	if (!tmp)
		failed_malloc_in_color(map, line, tmp1);
	len = len_2d(tmp);
	if (len < 3 || len > 3)
		free_in_color(map, line, tmp, tmp1);
	if (!is_all_num(tmp))
		free_in_color(map, line, tmp, tmp1);
	color = get_color(tmp);
	if (color == 300)
		free_in_color(map, line, tmp, tmp1);
	set_color(map, color, line[0]);
	free(tmp1);
	free_2d(tmp);
}
