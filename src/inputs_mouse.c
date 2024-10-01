/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:05:54 by eel-brah          #+#    #+#             */
/*   Updated: 2024/10/01 13:54:18 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	mouse_move_check(int x, int *last_x, t_vars *vars)
{
	if (vars->status->cam || !vars->player->mouse)
	{
		*last_x = x;
		return (1);
	}
	else if (*last_x == -1)
	{
		*last_x = x;
		return (1);
	}
	return (0);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	static int	last_x = -1;
	float		a;

	(void)y;
	if (mouse_move_check(x, &last_x, vars))
		return (1);
	else if (x >= WIDTH - 100)
	{
		vars->player->rotate = 1;
		vars->player->ra = 0.025 * MAX_ROTATION_SPEED;
	}
	else if (x <= 100)
	{
		vars->player->rotate = 1;
		vars->player->ra = -0.025 * MAX_ROTATION_SPEED;
	}
	else
	{
		vars->player->rotate = 0;
		a = fmaxf(-1.0f, fminf(1.0f, (x - last_x) * SENSITIVITY));
		player_rotation(vars, a * 3 * MAX_ROTATION_SPEED);
		last_x = x;
		render(vars);
	}
	return (1);
}

void	mouse_hook_helper(int b, t_vars *vars)
{
	static int	i = 0;

	if (b == 4 || b == 2)
	{
		i++;
		i = i % 9;
		vars->items[i].animate = true;
		vars->items[!(i == 8) * (i + 1)].animate = false;
		vars->items[(i == 0) * 8 + !(i == 0) * (i - 1)].animate = false;
	}
	else if (b == 5 || b == 1)
	{
		i--;
		i = (i == -1) * 8 + !(i == -1) * i;
		vars->items[i].animate = true;
		vars->items[!(i == 8) * (i + 1)].animate = false;
		vars->items[(i == 0) * 8 + !(i == 0) * (i - 1)].animate = false;
	}
}

int	mouse_hook(int b, int x, int y, t_vars *vars)
{
	(void)vars;
	(void)y;
	(void)x;
	if (b == 3)
	{
		vars->player->mouse = !(vars->player->mouse);
		vars->player->rotate = 0;
	}
	else if (vars->status->cam && b == 1)
		vars->status->player_animate_hit = true;
	else if (vars->status->cam && b == 2)
		vars->status->player_animate_shield = true;
	else if (!vars->status->cam)
		mouse_hook_helper(b, vars);
	return (1);
}
