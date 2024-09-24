#include "../include/cub3d.h"



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
	player->x = vars->map->player_x_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->y = vars->map->player_y_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->r = PLAYER_SIZE;
	// player->pa = PI * 1.5f;
	player->pa = vars->map->player_face;
	player->steps = 2;
	player->rspeed = deg2rad(2);
}

int	isit_wall(t_vars *vars, float x, float y)
{
	// if (isit_outob(vars, x, y))
	// 	return true;
	int ty;
	int tx;
	bool	flag;

	ty = floor(y/BLOCK_SIZE);
	tx = floor(x/BLOCK_SIZE);
	flag = ty >= 0 && ty < vars->map->rows && tx >= 0 && tx < vars->map->cols;
	if ( flag && (vars->map->map[ty * vars->map->cols + tx] == '0' || vars->map->map[ty * vars->map->cols + tx] == 'O'))
		return 0;
	if (flag && vars->map->map[ty * vars->map->cols + tx] == 'C')
		return 2;
	// if (vars->map->map[((int)floor(y/BLOCK_SIZE))* vars->map->cols +((int)floor(x/BLOCK_SIZE))] == '0')
	// 	return false;
	return 1;
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
	{
		player->x += xs;
		// player->y = BLOCK_SIZE * round(player->y / BLOCK_SIZE);
		// player->y = BLOCK_SIZE * floor((player->y+player->r) / BLOCK_SIZE) + player->r;
		// if (dirc == -1)
		// 	player->y = BLOCK_SIZE * floor((player->y+player->r) / BLOCK_SIZE) + player->r;
		// if (dirc == 1)
		// 	player->y = BLOCK_SIZE * ceil((player->y-player->r) / BLOCK_SIZE) - player->r;
	}
	else if (!wall_collision(vars, player->x, player->y + ys))
	{
		// if ((int)(player->x+player->r) % BLOCK_SIZE != 0)
		// {
		// 	int t = ceil((player->x+player->r)/BLOCK_SIZE);
		// 	player->x = (BLOCK_SIZE * t) - player->r;
		// }
		// printf("%f %f\n", player->x+player->r,(player->x+player->r)/BLOCK_SIZE);
		player->y += ys;
		// if (dirc == -1)
		// 	player->x = BLOCK_SIZE * floor((player->x+player->r) / BLOCK_SIZE) + player->r;
		// if (dirc == 1)
		// 	player->x = BLOCK_SIZE * ceil((player->x-player->r) / BLOCK_SIZE) - player->r;
	}

	// else
	// {
	// 	
	// }
	// draw(vars); // draw only it it moves
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
	// draw(vars);
}