#include "../include/cub3d.h"

void init_player(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->r = PLAYER_SIZE;
	player->pa = PI * 1.5f;
	player->steps = 6;
	player->rspeed = deg2rad(5);
}

void draw_dirc_line(t_data *img, float x, float y, t_player *player)
{
	t_line	line;

	line.x1 = x * MMS;
	line.y1 = y * MMS;
	line.x2 = (x+cos(player->pa)*player->r) * MMS;
	line.y2 = (y+sin(player->pa)*player->r) * MMS;
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
	draw(vars); // draw only it it moves
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

void draw_player(t_vars *vars, t_mini *minimap)
{
	if (minimap->ymax - minimap->y < 12)
	{
		if (minimap->player_poz_y > (MAP_COLS /2) )
			minimap->y = minimap->ymax - 12;
		else
			minimap->ymax = minimap->y + 12;
	}
	if (minimap->xmax - minimap->x < 12)
	{
		if (minimap->player_poz_x > (MAP_ROWS /2) )
			minimap->x = minimap->xmax - 12;
		else
			minimap->xmax = minimap->x + 12;
	}
	draw_circle(vars->img, (vars->player->x-minimap->x*BLOCK_SIZE) * MMS, (vars->player->y-minimap->y*BLOCK_SIZE) * MMS, vars->player->r * MMS);
	draw_dirc_line(vars->img, (vars->player->x-minimap->x*BLOCK_SIZE), (vars->player->y-minimap->y*BLOCK_SIZE), vars->player);
}

void    draw_minimap(t_vars *vars, t_mini *minimap)
{
	int	y;
	int	x;
	unsigned int	color;
	if (minimap->ymax - minimap->y < 12)
	{
		if (minimap->player_poz_y > (MAP_COLS /2) )
			minimap->y = minimap->ymax - 12;
		else
			minimap->ymax = minimap->y + 12;
	}
	y = minimap->y;
	while (y < minimap->ymax )
	{
		if (minimap->ymax - minimap->y < 12)
		{
			if (minimap->player_poz_y > (MAP_COLS /2) )
				minimap->y = minimap->ymax - 12;
			else
				minimap->ymax = minimap->y + 12;
		}
		x = minimap->x;
		while (x < minimap->xmax)
		{
			if (minimap->xmax - minimap->x < 12)
			{
				if (minimap->player_poz_x > (MAP_ROWS /2) )
					minimap->x = minimap->xmax - 12;
				else
					minimap->xmax = minimap->x + 12;
			}	
			color = (map[y*MAP_ROWS+x]==0) * MMC;

			draw_block(vars->img, (x-minimap->x)*BLOCK_SIZE*MMS, (y - minimap->y)*BLOCK_SIZE*MMS, BLOCK_SIZE*MMS, color);
			x++;
		}
		y++;
	}
}

void pre_minimap_player(t_vars *vars)
{
	t_mini	minimap;
	minimap.player_poz_x = floor(vars->player->x / BLOCK_SIZE);
	minimap.player_poz_y =  floor(vars->player->y / BLOCK_SIZE);

	minimap.y = minimap.player_poz_y - 6;
	minimap.y = (minimap.y > 0) * minimap.y;
	minimap.ymax = minimap.player_poz_y + 6;
	minimap.ymax = (minimap.ymax < MAP_COLS) * minimap.ymax + !(minimap.ymax < MAP_COLS) * (MAP_COLS );

	minimap.x = minimap.player_poz_x - 6;
	minimap.x = (minimap.x > 0) * minimap.x;
	minimap.xmax = minimap.player_poz_x + 6;
	minimap.xmax = (minimap.xmax < MAP_ROWS) * minimap.xmax + !(minimap.xmax < MAP_ROWS) * (MAP_ROWS );

	draw_minimap(vars, &minimap);
	draw_player(vars, &minimap);
}

void	set_background(t_data *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, BACKGROUND);
			x++;
		}
		y++;
	}
}

void    draw_block(t_data *img, int x, int y, int size, unsigned int color)
{
	float		bx;
	float		by;

	by = y ;
	while (by < y + size - 1 * MMS)
	{
		bx = x ;
		while (bx < x + size - 1 * MMS)
		{
			put_pixel(img, roundf(bx), roundf(by), color);
			bx++;
		}
		by++;
	}
}