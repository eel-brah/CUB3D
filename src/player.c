/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:03:07 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/28 12:08:15 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_rotate_player(t_vars *vars)
{
	if (vars->keys.w_key == true || vars->keys.up_key == true)
		player_movement(vars, 1, 0);
	if (vars->keys.s_key == true || vars->keys.down_key == true)
		player_movement(vars, -1, 0);
	if (vars->keys.a_key == true)
		player_movement(vars, -1, 90);
	if (vars->keys.d_key == true)
		player_movement(vars, 1, 90);
	if (vars->keys.left_key == true)
		player_rotation(vars, -1);
	if (vars->keys.right_key == true)
		player_rotation(vars, 1);
}

bool	wall_collision(t_vars *vars, float x, float y)
{
	int ty;
	int tx;
	t_player * player = vars->player;

	int i = 0;
	while (i < 8)
	{
		if (i == 0)
		{
			ty = floor((y - player->r)/BLOCK_SIZE);
			tx = floor((x)/BLOCK_SIZE);
		}
		else if (i == 1)
			ty = floor((y + player->r)/BLOCK_SIZE);
		else if (i == 2)
			tx = floor((x + player->r)/BLOCK_SIZE);
		else if (i == 3)
			ty = floor((y)/BLOCK_SIZE);
		else if (i == 4)
			tx = floor((x - player->r)/BLOCK_SIZE);
		else if (i == 5)
			ty = floor((y - player->r)/BLOCK_SIZE);
		else if (i == 6)
			tx = floor((x + player->r)/BLOCK_SIZE);
		else if (i == 7)
		{
			ty = floor((y + player->r)/BLOCK_SIZE);
			tx = floor((x - player->r)/BLOCK_SIZE);
		}
		if (ty >= 0 && ty < vars->map->rows && tx >= 0 && tx < vars->map->cols)
		{
			if (vars->map->map[ty * vars->map->cols + tx] == '1' || vars->map->map[ty * vars->map->cols + tx] == 'C')
				return true;
		}
		i++;
	}
	return false;
}

void init_player(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	vars->current = vars->items[0].item[3];
	player->x = vars->map->player_x_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->y = vars->map->player_y_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->r = PLAYER_SIZE;
	player->pa = vars->map->player_face;
	player->steps = 2;
	player->rspeed = deg2rad(2);
	vars->player->rotate = 0;
	vars->player->rotate2 = 0;
	vars->player->mouse = 1;
}

void player_movement(t_vars *vars, int dirc, int sp)
{
	t_player	*player;
	float		xs;
	float		ys;

	player = vars->player;
	xs = cos(player->pa + deg2rad(sp)) * player->steps * dirc;
	ys = sin(player->pa + deg2rad(sp)) * player->steps * dirc;
	if (!wall_collision(vars, player->x + xs, player->y + ys))
	{
		player->x += xs;
		player->y += ys;
	}
	else if (!wall_collision(vars, player->x + xs, player->y))
		player->x += xs;
	else if (!wall_collision(vars, player->x, player->y + ys))
		player->y += ys;
}

void player_rotation(t_vars *vars, float dirc)
{
	t_player	*player;

	player = vars->player;
	player->pa += dirc * player->rspeed;

	if (player->pa < 0)
		player->pa += 2 * PI;
	else if (player->pa > 2 * PI)
		player->pa -= 2 * PI;
}