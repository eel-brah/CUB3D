/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:05:47 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/29 11:37:14 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_realese(int keysym, t_vars *vars)
{
	if (keysym == 259)
	{
		if (vars->status->cam)
			vars->player->pa -= PI;
		vars->status->cam = false;
	}
	else if (keysym == UP_KEY)
		vars->keys.up_key = false;
	else if (keysym == UP_W_KEY)
		vars->keys.w_key = false;
	else if (keysym == DOWN_S_KEY)
		vars->keys.s_key = false;
	else if (keysym == DOWN_KEY)
		vars->keys.down_key = false;
	else if (keysym == LEFT_A_KEY)
		vars->keys.a_key = false;
	else if (keysym == RIGHT_D_KEY)
		vars->keys.d_key = false;
	else if (keysym == LEFT_KEY)
		vars->keys.left_key = false;
	else if (keysym == RIGHT_KEY)
		vars->keys.right_key = false;
	else if (keysym == 35)
		vars->status->full_map = false;
	return 0;
}

void	cam_preparation(t_vars *vars)
{
	if (!vars->status->cam)
		vars->player->pa += PI;
	vars->status->cam = true;
	vars->status->k = 1;
	vars->status->player_animate_hit = false;
	vars->keys.up_key = false;
	vars->keys.w_key = false;
	vars->keys.s_key = false;
	vars->keys.down_key = false;
	vars->keys.a_key = false;
	vars->keys.d_key = false;
	vars->keys.left_key = false;
	vars->keys.right_key = false;
	vars->player->rotate = false;
}

void	key_press_mv(int keysym, t_vars* vars)
{
	if (keysym == UP_KEY)
		vars->keys.up_key = true;
	else if (keysym == UP_W_KEY)
		vars->keys.w_key = true;
	else if (keysym == DOWN_S_KEY)
		vars->keys.s_key = true;
	else if (keysym == DOWN_KEY)
		vars->keys.down_key = true;
	else if (keysym == LEFT_A_KEY)
		vars->keys.a_key = true;
	else if (keysym == RIGHT_D_KEY)
		vars->keys.d_key = true;
	else if (keysym == LEFT_KEY)
		vars->keys.left_key = true;
	else if (keysym == RIGHT_KEY)
		vars->keys.right_key = true;
}

int	key_press(int keysym, t_vars *vars)
{
	if (keysym == 259)
		cam_preparation(vars);
	else if (!vars->status->cam)
	{	
		key_press_mv(keysym, vars);
		if (keysym == 49)
			open_close_door(vars);
		else if (keysym == 46)
			vars->status->mm = !(vars->status->mm);
		else if (keysym == 35)
			vars->status->full_map = true;
	}
	if (keysym == ESC_KEY)
		close_and_clear(vars);
	return 1;
}
