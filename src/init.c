/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:55 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/28 12:08:45 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_bools(t_vars *vars)
{
	int i;

	i = 0;
	while (i < 9)
		vars->items[i++].animate = false;
	vars->cam = false;
	vars->player_animate_hit = false;
	vars->keys.a_key = false;
	vars->keys.d_key = false;
	vars->keys.s_key = false;
	vars->keys.w_key = false;
	vars->keys.up_key = false;
	vars->keys.down_key = false;
	vars->keys.left_key = false;
	vars->keys.right_key = false;
	vars->player->rotate = false;
}

bool	init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return false;
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!vars->win)
		return false;
	vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img->img)
	{
		mlx_destroy_window(vars->mlx, vars->mlx);
		return false;
	}
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bpp, &vars->img->line_length, &vars->img->endian);
	init_bools(vars);
	return true;
}