/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:15:05 by amokhtar          #+#    #+#             */
/*   Updated: 2024/10/03 14:39:49 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_texture1(t_vars *vars)
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

bool	load_texture(t_vars *vars)
{
	if (!load_texture1(vars))
		return (false);
	mlx_get_data(&vars->north);
	mlx_get_data(&vars->west);
	mlx_get_data(&vars->south);
	mlx_get_data(&vars->east);
	return (true);
}
// free after malloc

bool	alloc_and_set_text(t_vars *vars)
{
	int	i;

	i = 0;
	vars->texture = malloc(sizeof(void *) * 58);
	if (!vars->texture)
		return (write(2, "Malloc failed\n", 15), false);
	while (i < 58)
	{
		vars->texture[i] = NULL;
		i++;
	}
	return (true);
}

bool	load_images(t_vars *vars)
{
	if (!alloc_and_set_text(vars))
		return (false);
	if (!load_weapons_player(vars))
		return (false);
	if (!load_door(vars))
		return (false);
	if (!load_texture(vars))
		return (false);
	return (true);
}
