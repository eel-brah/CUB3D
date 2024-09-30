/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:15:05 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/30 18:02:55 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	open_wall_text1(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->north, vars->map->no))
		return (false);
	vars->texture[vars->nb_text++] = vars->north.img;
	if (!mlx_xpm(vars, &vars->west, vars->map->we))
		return (false);
	vars->texture[vars->nb_text++] = vars->west.img;
	if (!mlx_xpm(vars, &vars->south, vars->map->so))
		return (false);
	vars->texture[vars->nb_text++] = vars->south.img;
	if (!mlx_xpm(vars, &vars->east, vars->map->ea))
		return (false);
	vars->texture[vars->nb_text++] = vars->east.img;
	return (true);
}

bool	open_wall_text(t_vars *vars)
{
	if (!open_wall_text1(vars))
		return (false);
	if (!mlx_get_data(&vars->north))
		return (false);
	if (!mlx_get_data(&vars->west))
		return (false);
	if (!mlx_get_data(&vars->south))
		return (false);
	if (!mlx_get_data(&vars->east))
		return (false);
	return (true);
}
// free after malloc

bool	alloc_and_set_text(t_vars *vars)
{
	int	i;

	i = 0;
	vars->texture = malloc(sizeof(void *) * 58);
	vars->texture = NULL;
	if (!vars->texture)
		return (write(2, "malloc failled \n", 16), false);
	while (i < 58)
	{
		vars->texture[i] = NULL;
		i++;
	}
	return (true);
}

bool	open_texture(t_vars *vars)
{
	if (!alloc_and_set_text(vars))
		return (false);
	if (!load_weapons(vars))
		return (false);
	if (!open_door(vars))
		return (false);
	if (!open_wall_text(vars))
		return (false);
	return (true);
}
