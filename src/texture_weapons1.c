/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_weapons1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:15:53 by amokhtar          #+#    #+#             */
/*   Updated: 2025/02/10 08:58:58 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_sword(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->items[0].item[0], "images/1-sword/1.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[0].img;
	if (!mlx_xpm(vars, &vars->items[0].item[1], "images/1-sword/2.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[1].img;
	if (!mlx_xpm(vars, &vars->items[0].item[2], "images/1-sword/3.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[2].img;
	if (!mlx_xpm(vars, &vars->items[0].item[3], "images/1-sword/4.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[0].item[3].img;
	return (true);
}

bool	load_axe(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->items[1].item[0], "images/2-axe/1.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[0].img;
	if (!mlx_xpm(vars, &vars->items[1].item[1], "images/2-axe/2.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[1].img;
	if (!mlx_xpm(vars, &vars->items[1].item[2], "images/2-axe/3.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[2].img;
	if (!mlx_xpm(vars, &vars->items[1].item[3], "images/2-axe/4.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[1].item[3].img;
	return (true);
}

bool	load_pickaxe(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->items[2].item[0], "images/3-pickaxe/1.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[0].img;
	if (!mlx_xpm(vars, &vars->items[2].item[1], "images/3-pickaxe/3.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[1].img;
	if (!mlx_xpm(vars, &vars->items[2].item[2], "images/3-pickaxe/3.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[2].img;
	if (!mlx_xpm(vars, &vars->items[2].item[3], "images/3-pickaxe/4.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[2].item[3].img;
	return (true);
}

bool	load_bow(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->items[3].item[0], "images/4-bow/1.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[0].img ;
	if (!mlx_xpm(vars, &vars->items[3].item[1], "images/4-bow/2.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[1].img;
	if (!mlx_xpm(vars, &vars->items[3].item[2], "images/4-bow/3.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[2].img;
	if (!mlx_xpm(vars, &vars->items[3].item[3], "images/4-bow/4.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[3].item[3].img;
	return (true);
}

bool	load_totem(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->items[4].item[0], "images/5-totem/1.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[0].img;
	if (!mlx_xpm(vars, &vars->items[4].item[1], "images/5-totem/2.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[1].img;
	if (!mlx_xpm(vars, &vars->items[4].item[2], "images/5-totem/3.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[2].img;
	if (!mlx_xpm(vars, &vars->items[4].item[3], "images/5-totem/4.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->items[4].item[3].img;
	return (true);
}

