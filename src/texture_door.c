/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:13:10 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/30 12:27:54 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	open_doors1(t_vars *vars)
{
	vars->door.img = mlx_xpm_file_to_image(vars->mlx, \
	"images/texture/door/door2.xpm", &vars->door.width, &vars->door.height);
	if (!vars->door.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->door.img;
	vars->left_left.img = mlx_xpm_file_to_image(vars->mlx, \
	"images/texture/door/left_left.xpm", &vars->left_left.width, &vars->left_left.height);
	if (!vars->left_left.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->left_left.img;
	vars->left_right.img = mlx_xpm_file_to_image(vars->mlx, \
	"images/texture/door/left_right.xpm" ,&vars->left_right.width, &vars->left_right.height);
	if (!vars->left_right.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->left_right.img;
	vars->right_left.img = mlx_xpm_file_to_image(vars->mlx, \
	"images/texture/door/right_left.xpm", &vars->right_left.width, &vars->right_left.height);
	if (!vars->right_left.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->right_left.img;
	return (true);
}

bool	open_doors2(t_vars *vars)
{
	vars->right_right.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/right_right.xpm" ,&vars->right_right.width, &vars->right_right.height);
	if (!vars->right_right.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->right_right.img;
	vars->up_up.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/up_up.xpm" ,&vars->up_up.width, &vars->up_up.height);
	if (!vars->up_up.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->up_up.img;
	vars->up_down.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/up_down.xpm" ,&vars->up_down.width, &vars->up_down.height);
	if (!vars->up_down.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->up_down.img;
	vars->down_down.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/down_down.xpm" ,&vars->down_down.width, &vars->down_down.height);
	if (!vars->down_down.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->down_down.img;
	vars->down_up.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/down_up.xpm" ,&vars->down_up.width, &vars->down_up.height);
	if (!vars->down_up.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->down_up.img;
	return (true);
}

bool	open_doors3(t_vars *vars)
{
	t_data	*data;

	data = &vars->door;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->left_left;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->left_right;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->right_left;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	return (true);
}

bool	open_doors4(t_vars *vars)
{
	t_data	*data;

	data = &vars->right_right;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->up_up;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->up_down;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->down_down;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	data = &vars->down_up;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (false);
	return (true);
}

bool	open_doors(t_vars *vars)
{
	if (!open_doors1(vars))
		return (false);
	if (!open_doors2(vars))
		return (false);
	if (!open_doors3(vars))
		return (false);
	if (!open_doors4(vars))
		return (false);
	return (true);
}