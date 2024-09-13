#include "gm.h"

void init_player(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->r = PLAYER_SIZE;
	player->rota = PI / 2;
	player->ms = 4;
	player->rs = deg2rad(5);
	draw_player(vars);
}

void draw_dirc_line(t_data *img, t_player *player)
{
	t_line	line;

	line.x1 = player->x;
	line.y1 = player->y;
	line.x2 = player->x+cos(player->rota)*player->r;
	line.y2 = player->y+sin(player->rota)*player->r;
	draw_line(line, img, DIRC_LINE);
}

void player_movement(t_vars *vars, int dirc)
{
	t_player	*player;

	player = vars->player;
	player->x += cos(player->rota) * player->ms * dirc;
	player->y += sin(player->rota) * player->ms * dirc;
	draw(vars);
}

void player_rotation(t_vars *vars, int dirc)
{
	t_player	*player;

	player = vars->player;
	player->rota += dirc * player->rs;
	draw(vars);
}

void draw_player(t_vars *vars)
{
	draw_circle(vars->img, vars->player->x, vars->player->y, vars->player->r);
	draw_dirc_line(vars->img, vars->player);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
