/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_weapons2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:16:25 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/30 12:20:23 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_diamond(t_vars *vars)
{
	vars->items[5].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/1.xpm" ,&vars->items[5].item[0].width, &vars->items[5].item[0].height);
	if (!vars->items[5].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[5].item[0].img;
	vars->items[5].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/3.xpm" ,&vars->items[5].item[1].width, &vars->items[5].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[5].item[1].img;
	vars->items[5].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/4.xpm" ,&vars->items[5].item[2].width, &vars->items[5].item[2].height);
	if (!vars->items[5].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[5].item[2].img;
	vars->items[5].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/4.xpm" ,&vars->items[5].item[3].width, &vars->items[5].item[3].height);
	if (!vars->items[5].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[5].item[3].img;
	return (true);
}

bool	load_apple(t_vars *vars)
{
	vars->items[6].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/1.xpm" ,&vars->items[6].item[0].width, &vars->items[6].item[0].height);
	if (!vars->items[6].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[6].item[0].img;
	vars->items[6].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/3.xpm" ,&vars->items[6].item[1].width, &vars->items[6].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[6].item[1].img;
	vars->items[6].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/4.xpm" ,&vars->items[6].item[2].width, &vars->items[6].item[2].height);
	if (!vars->items[6].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[6].item[2].img;
	vars->items[6].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/4.xpm" ,&vars->items[6].item[3].width, &vars->items[6].item[3].height);
	if (!vars->items[6].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[6].item[3].img;
	return (true);
}

bool	load_potion(t_vars *vars)
{
	vars->items[7].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/1.xpm" ,&vars->items[7].item[0].width, &vars->items[7].item[0].height);
	if (!vars->items[7].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[7].item[0].img;
	vars->items[7].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/3.xpm" ,&vars->items[7].item[1].width, &vars->items[7].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[7].item[1].img;
	vars->items[7].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/4.xpm" ,&vars->items[7].item[2].width, &vars->items[7].item[2].height);
	if (!vars->items[7].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[7].item[2].img;
	vars->items[7].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/4.xpm" ,&vars->items[7].item[3].width, &vars->items[7].item[3].height);
	if (!vars->items[7].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[7].item[3].img;
	return (true);
}

bool	load_food(t_vars *vars)
{
	vars->items[8].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/1.xpm" ,&vars->items[8].item[0].width, &vars->items[8].item[0].height);
	if (!vars->items[8].item[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[8].item[0].img;
	vars->items[8].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/3.xpm" ,&vars->items[8].item[1].width, &vars->items[8].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[8].item[1].img;
	vars->items[8].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/4.xpm" ,&vars->items[8].item[2].width, &vars->items[8].item[2].height);
	if (!vars->items[8].item[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[8].item[2].img;
	vars->items[8].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/4.xpm" ,&vars->items[8].item[3].width, &vars->items[8].item[3].height);
	if (!vars->items[8].item[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->items[8].item[3].img;
	return (true);
}
bool	load_weapons(t_vars *vars)
{
	if (!load_sword(vars))
		return (false);
	if (!load_axe(vars))
		return (false);
	if (!load_pickaxe(vars))
		return (false);
	if (!load_bow(vars))
		return (false);
	if (!load_totem(vars))
		return (false);
	if(!load_diamond(vars))
		return (false);
	if(!load_apple(vars))
		return (false);
	if(!load_potion(vars))
		return (false);
	if(!load_food(vars))
		return (false);
	if(!load_player(vars))
		return (false);
	return (true);
}
