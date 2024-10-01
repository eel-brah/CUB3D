/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:35:05 by amokhtar          #+#    #+#             */
/*   Updated: 2024/10/01 11:53:25 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_linked(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}
// TODO free map 2d

void	ft_print_error(char *s)
{
	write(2, "Error\n", 6);
	while (*s)
	{
		write(2, s, 1);
		s++;
	}
	write(2, "\n", 1);
}

void	free_2d(char **tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

static void	initial_map(t_map *map, int fd)
{
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->map = NULL;
	map->lst = NULL;
	map->max_col = 0;
	map->max_line = 0;
	map->fd = fd;
	map->c_color = 300;
	map->f_color = 300;
}

t_map	*parse(char *file)
{
	int		len;
	int		fd;
	t_map	*map;

	len = ft_strlen(file);
	if (len <= 4)
		return (write(2, "Error\nfile not end by .cub 1\n", 28), exit(1), NULL);
	if (file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (write(2, "Error\nfile not end by .cub\n", 27), exit(1), NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), write(2, "Error\n", 6), exit(1), NULL);
	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (perror("malloc"), close(fd), exit(2), NULL);
	initial_map(map, fd);
	fill_map(map, fd, true, 0);
	map->rows = map->max_line;
	map->cols = map->max_col;
	if (!map->we && !map->so && !map->no && !map->ea && map->c_color == 300 && map->f_color == 300)
        return (free_map(map), ft_print_error("Empty Map"), exit(1), NULL);
	fill_array(map, 0);
	check_walls(map, "Error\nMap Walls\n", map->max_line);
	return (map);
}

// void xx()
// {
// 	system("leaks a.out");
// }

// int main(int argc, char **argv)
// {
// 	t_map	*map;

// 	map = NULL;
// 	if (argc >= 2)
// 	{
// 		map = parse(argv[1]);
// 		//free_map(map);
// 	}
// 	else
// 	{
// 		write(2, "Error\nnb argument \n", 19);
// 		return (-1);
// 	}
// 	printf("NO = %s\n", map->no);
// 	printf("SO = %s\n", map->so);
// 	printf("WE = %s\n", map->we);
// 	printf("EA= %s\n", map->ea);
// 	printf("F= %u\n", map->f_color);
// 	printf("C= %u\n", map->c_color);
// 	//ft_lstiter(map->lst, print_all);
// 	int i =0;
// 	while (i < map->max_line)
// 	{
// 		printf("%s\n", map->map[i]);
// 		i++;
// 	}
// 	free_map(map);
// 	return (0);
// }
