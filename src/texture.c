/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:15:05 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/30 12:22:08 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"




bool	open_wall_text1(t_vars *vars)
{
	vars->north.img = mlx_xpm_file_to_image(vars->mlx, vars->map->no,&vars->north.width, &vars->north.height);
	if (!vars->north.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->north.img;
	vars->west.img = mlx_xpm_file_to_image(vars->mlx, vars->map->we,&vars->west.width, &vars->west.height);
	if (!vars->west.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->west.img;
	vars->south.img = mlx_xpm_file_to_image(vars->mlx, vars->map->so,&vars->south.width, &vars->south.height);
	if (!vars->south.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->south.img;
	vars->east.img = mlx_xpm_file_to_image(vars->mlx, vars->map->ea,&(vars->east.width), &(vars->east.height));
	if (!vars->east.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->east.img;
	return (true);
}
bool	open_wall_text(t_vars *vars)
{
	t_data	*data;

	if (!open_wall_text1(vars))
		return (false);
	data = &vars->north;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->west;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->south;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->east;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	return (true);
}
bool	alloc_and_set_text(t_vars *vars)
{
	int	i;

	i = 0;
	vars->texture = malloc(sizeof(void *) * 58);
	if (!vars->texture)
		return (write(2, "malloc ", 7),false); // FREE 
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
	if(!open_doors(vars))
		return (false);
	if (!open_wall_text(vars))
		return (false);
	return (true);
}
