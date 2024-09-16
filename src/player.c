#include "../include/cub3d.h"

void init_player(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->r = PLAYER_SIZE;
	player->pa = 0;
	player->steps = 6;
	player->rspeed = deg2rad(5);
}

void draw_dirc_line(t_data *img, t_player *player)
{
	t_line	line;

	line.x1 = player->x * MMS;
	line.y1 = player->y * MMS;
	line.x2 = (player->x+cos(player->pa)*player->r) * MMS;
	line.y2 = (player->y+sin(player->pa)*player->r) * MMS;
	draw_line(line, img, DIRC_LINE);
}

int	isit_outob(float x, float y)
{
	if (x > 0 && x < WIDTH && y < HEIGHT && y > 0)
		return 0;
	return 1;
}
bool	isit_wall(float x, float y)
{
	if (isit_outob(x, y))
		return true;
	if (map[((int)floor(y/BLOCK_SIZE))*MAP_ROWS+((int)floor(x/BLOCK_SIZE))]==0)
		return false;
	return true;
}

void player_movement(t_vars *vars, int dirc)
{
	t_player	*player;
	float		tmp_x;
	float		tmp_y;

	player = vars->player;
	tmp_x = player->x + cos(player->pa) * player->steps * dirc;
	tmp_y = player->y + sin(player->pa) * player->steps * dirc;
	if (!isit_wall(tmp_x, tmp_y))
	{
		player->x = tmp_x;
		player->y = tmp_y;
	}
	draw(vars);
}

void player_rotation(t_vars *vars, int dirc)
{
	t_player	*player;

	player = vars->player;
	player->pa += dirc * player->rspeed;
	if (player->pa < 0)
		player->pa += 2 * PI;
	else if (player->pa > 2 * PI)
		player->pa -= 2 * PI;
	draw(vars);
}

void draw_player(t_vars *vars)
{
	draw_circle(vars->img, vars->player->x * MMS, vars->player->y * MMS, vars->player->r * MMS);
	draw_dirc_line(vars->img, vars->player);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
