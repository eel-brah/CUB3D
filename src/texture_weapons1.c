/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_weapons1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:15:53 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/30 12:23:06 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_sword(t_vars *vars)
{
	vars->items[0].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/1.xpm" ,&vars->items[0].item[0].width, &vars->items[0].item[0].height);
	if (!vars->items[0].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[0].img;
	vars->items[0].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/2.xpm" ,&vars->items[0].item[1].width, &vars->items[0].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[1].img;
	vars->items[0].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/3.xpm" ,&vars->items[0].item[2].width, &vars->items[0].item[2].height);
	if (!vars->items[0].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[2].img;
	vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	if (!vars->items[0].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[3].img;
	return (true);
}

bool	load_axe(t_vars *vars)
{
	vars->items[1].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/1.xpm" ,&vars->items[1].item[0].width, &vars->items[1].item[0].height);
	if (!vars->items[0].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[0].img;
	vars->items[1].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/3.xpm" ,&vars->items[1].item[1].width, &vars->items[1].item[1].height);
	if (!vars->items[1].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[1].img;
	vars->items[1].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/4.xpm" ,&vars->items[1].item[2].width, &vars->items[1].item[2].height);
	if (!vars->items[1].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[2].img;
	vars->items[1].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/4.xpm" ,&vars->items[1].item[3].width, &vars->items[1].item[3].height);
	if (!vars->items[1].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[3].img;
	return (true);
}

bool	load_pickaxe(t_vars *vars)
{
	vars->items[2].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/1.xpm" ,&vars->items[2].item[0].width, &vars->items[2].item[0].height);
	if (!vars->items[2].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[0].img;
	vars->items[2].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/3.xpm" ,&vars->items[2].item[1].width, &vars->items[2].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[1].img;
	vars->items[2].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/4.xpm" ,&vars->items[2].item[2].width, &vars->items[2].item[2].height);
	if (!vars->items[2].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[2].img;
	vars->items[2].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/4.xpm" ,&vars->items[2].item[3].width, &vars->items[2].item[3].height);
	if (!vars->items[2].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[3].img;
	return (true);
}

bool	load_bow(t_vars *vars)
{
	vars->items[3].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/1.xpm" ,&vars->items[3].item[0].width, &vars->items[3].item[0].height);
	if (!vars->items[3].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[0].img ;
	vars->items[3].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/3.xpm" ,&vars->items[3].item[1].width, &vars->items[3].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[1].img;
	vars->items[3].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/4.xpm" ,&vars->items[3].item[2].width, &vars->items[3].item[2].height);
	if (!vars->items[3].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[2].img;
	vars->items[3].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/4.xpm" ,&vars->items[3].item[3].width, &vars->items[3].item[3].height);
	if (!vars->items[3].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[3].img;
	return (true);
}

bool	load_totem(t_vars *vars)
{
	vars->items[4].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/1.xpm" ,&vars->items[4].item[0].width, &vars->items[4].item[0].height);
	if (!vars->items[4].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[0].img;
	vars->items[4].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/3.xpm" ,&vars->items[4].item[1].width, &vars->items[4].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[1].img;
	vars->items[4].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/4.xpm" ,&vars->items[4].item[2].width, &vars->items[4].item[2].height);
	if (!vars->items[4].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[2].img;
	vars->items[4].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/4.xpm" ,&vars->items[4].item[3].width, &vars->items[4].item[3].height);
	if (!vars->items[4].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[3].img;
	return (true);
}
