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


void	fix_minimap_y(t_mini *minimap)
{
	if (minimap->ymax - minimap->y < minimap->height)
	{
		if (minimap->player_poz_y > (MAP_COLS /2) )
			minimap->y = minimap->ymax - minimap->height;
		else
			minimap->ymax = minimap->y + minimap->height;
	}
}
void	fix_minimap_x(t_mini *minimap)
{
	if (minimap->xmax - minimap->x < minimap->width) // calc 12 for small maps
	{
		if (minimap->player_poz_x > (MAP_ROWS / 2) )
			minimap->x = minimap->xmax - minimap->width;
		else
			minimap->xmax = minimap->x + minimap->width;
	}
}
void draw_player(t_vars *vars, t_mini *minimap)
{
	fix_minimap_y(minimap);
	fix_minimap_x(minimap);
	draw_circle(vars->img, (vars->player->x-minimap->x*BLOCK_SIZE) * MMS, (vars->player->y-minimap->y*BLOCK_SIZE) * MMS, vars->player->r * MMS);
	draw_dirc_line(vars->img, (vars->player->x-minimap->x*BLOCK_SIZE), (vars->player->y-minimap->y*BLOCK_SIZE), vars->player);
}

void    draw_minimap(t_vars *vars, t_mini *minimap)
{
	int	y;
	int	x;
	unsigned int	color;
	
	fix_minimap_y(minimap);
	y = minimap->y;
	while (y < minimap->ymax )
	{
		fix_minimap_y(minimap);
		x = minimap->x;
		while (x < minimap->xmax)
		{
			fix_minimap_x(minimap);
			color = (map[y*MAP_ROWS+x]==0) * MMC;
			draw_block(vars->img, (x - minimap->x)*BLOCK_SIZE*MMS, (y - minimap->y)*BLOCK_SIZE*MMS, BLOCK_SIZE*MMS, color);
			x++;
		}
		y++;
	}
	if (minimap->height < 12 || minimap->width < 12)
	{
		y = 0;
		while (y < 12*BLOCK_SIZE* MMS)
		{
			x = 0;
			while (x < 12*BLOCK_SIZE* MMS)
				put_pixel(vars->img, x++, y, 0);
			y++;
		}
	}
}

void    draw_border(t_vars *vars, t_mini *minimap)
{
	// int	x = 0;
	// int	y = 0;
	t_line line;

	(void)minimap;
	line.x1 = 0;
	line.x2 = 12 * BLOCK_SIZE * MMS;
	line.y1 = 0;
	line.y2 = 0;
	draw_line(line, vars->img, BORDER_COLOR);
	line.y1 = 1;
	line.y2 = 1;
	draw_line(line, vars->img, BORDER_COLOR);

	line.x1 = 0;
	line.x2 = 12 * BLOCK_SIZE * MMS;
	line.y1 = 12 * BLOCK_SIZE * MMS;
	line.y2 = 12 * BLOCK_SIZE * MMS;
	draw_line(line, vars->img, BORDER_COLOR);
	line.y1 = 12 * BLOCK_SIZE * MMS + 1;
	line.y2 = 12 * BLOCK_SIZE * MMS + 1;
	draw_line(line, vars->img, BORDER_COLOR);
	
	line.x1 = 12 * BLOCK_SIZE * MMS;
	line.x2 = 12 * BLOCK_SIZE * MMS;
	line.y1 = 0;
	line.y2 = 12 * BLOCK_SIZE * MMS + 2;
	draw_line(line, vars->img, BORDER_COLOR);
	line.x1 = 12 * BLOCK_SIZE * MMS+1;
	line.x2 = 12 * BLOCK_SIZE * MMS+1;
	draw_line(line, vars->img, BORDER_COLOR);
	
	line.x1 = 0;
	line.x2 = 0;
	line.y1 = 0;
	line.y2 = 12 * BLOCK_SIZE * MMS + 2;
	draw_line(line, vars->img, BORDER_COLOR);
	line.x1 = 1;
	line.x2 = 1;
	draw_line(line, vars->img, BORDER_COLOR);
}

void	calc_map_wh(t_vars *vars, t_mini *minimap)
{
	minimap->height = (vars->map->cols >= 12) * 12 + !(vars->map->cols >= 12) * vars->map->cols;
	minimap->width = (vars->map->rows >= 12) * 12 + !(vars->map->rows >= 12) * vars->map->rows;
}

void draw_minimap_player(t_vars *vars)
{
	t_mini	minimap;
	
	calc_map_wh(vars, &minimap);
	minimap.player_poz_x = floor(vars->player->x / BLOCK_SIZE);
	minimap.player_poz_y =  floor(vars->player->y / BLOCK_SIZE);

	minimap.y = minimap.player_poz_y - (minimap.height / 2);
	minimap.y = (minimap.y > 0) * minimap.y;
	minimap.ymax = minimap.player_poz_y + (minimap.height / 2);
	minimap.ymax = (minimap.ymax < MAP_COLS) * minimap.ymax + !(minimap.ymax < MAP_COLS) * (MAP_COLS );

	minimap.x = minimap.player_poz_x - (minimap.width / 2);
	minimap.x = (minimap.x > 0) * minimap.x;
	minimap.xmax = minimap.player_poz_x + (minimap.width / 2);
	minimap.xmax = (minimap.xmax < MAP_ROWS) * minimap.xmax + !(minimap.xmax < MAP_ROWS) * (MAP_ROWS );
	draw_minimap(vars, &minimap);
	draw_player(vars, &minimap);
	draw_border(vars, &minimap);
}

// void	set_background(t_data *img)
// {
// 	int		x;
// 	int		y;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			put_pixel(img, x, y, BACKGROUND);
// 			x++;
// 		}
// 		y++;
// 	}
// }

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