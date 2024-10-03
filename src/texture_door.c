/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:13:10 by amokhtar          #+#    #+#             */
/*   Updated: 2024/10/03 14:41:10 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_door1(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->left_left,
			"images/texture/door/left_left.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->left_left.img;
	if (!mlx_xpm(vars, &vars->left_right,
			"images/texture/door/left_right.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->left_right.img;
	if (!mlx_xpm(vars, &vars->right_left,
			"images/texture/door/right_left.xpm"))
		return (false);
	return (vars->texture[vars->nb_text++] = vars->right_left.img, true);
}

bool	load_door2(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->right_right,
			"images/texture/door/r_right.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->right_right.img;
	if (!mlx_xpm(vars, &vars->up_up, "images/texture/door/up_up.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->up_up.img;
	if (!mlx_xpm(vars, &vars->up_down, "images/texture/door/up_down.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->up_down.img;
	if (!mlx_xpm(vars, &vars->down_down,
			"images/texture/door/down_down.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->down_down.img;
	if (!mlx_xpm(vars, &vars->down_up, "images/texture/door/down_up.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->down_up.img;
	return (true);
}

void	load_door3(t_vars *vars)
{
	mlx_get_data(&vars->left_left);
	mlx_get_data(&vars->left_right);
	mlx_get_data(&vars->right_left);
}

void	load_door4(t_vars *vars)
{
	mlx_get_data(&vars->right_right);
	mlx_get_data(&vars->up_up);
	mlx_get_data(&vars->up_down);
	mlx_get_data(&vars->down_down);
	mlx_get_data(&vars->down_up);
}

bool	load_door(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->door, "images/texture/door/door2.xpm"))
		return (false);	
	vars->texture[vars->nb_text++] = vars->door.img;
	mlx_get_data(&vars->door);
	if (DOOR_OPEN)
	{
		if (!load_door1(vars))
			return (false);
		if (!load_door2(vars))
			return (false);
		load_door3(vars);
		load_door4(vars);
	}
	return (true);
}
