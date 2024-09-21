#include "../include/cub3d.h"

void init_player(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	player->x = vars->map->player_x_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->y = vars->map->player_y_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->r = PLAYER_SIZE;
	// player->pa = PI * 1.5f;
	player->pa = 0;
	player->steps = 6;
	player->rspeed = deg2rad(5);
}

void draw_dirc_line(t_vars *vars, float x, float y, t_player *player)
{
	t_line	line;

	line.x1 = x * MMS;
	line.y1 = y * MMS;
	line.x2 = (x+cos(player->pa)*player->r) * MMS;
	line.y2 = (y+sin(player->pa)*player->r) * MMS;
	draw_line(vars, line, DIRC_LINE);
}

int	isit_outob(t_vars *vars, float x, float y)
{
	if (x > 0 && x < vars->map->width && y < vars->map->height && y > 0)
		return 0;
	return 1;
}
bool	isit_wall(t_vars *vars, float x, float y)
{
	if (isit_outob(vars, x, y))
		return true;
	// if (vars->map->map[((int)floor(y/BLOCK_SIZE))][((int)floor(x/BLOCK_SIZE))]==0)
	if (vars->map->map[((int)floor(y/BLOCK_SIZE))* vars->map->cols +((int)floor(x/BLOCK_SIZE))] == '0')
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
	if (!isit_wall(vars, tmp_x, tmp_y))
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


void	fix_minimap_y(t_vars *vars, t_mini *minimap)
{
	if (minimap->ymax - minimap->y < minimap->height)
	{
		if (minimap->player_poz_y > (vars->map->rows /2) )
			minimap->y = minimap->ymax - minimap->height;
		else
			minimap->ymax = minimap->y + minimap->height;
	}
}
void	fix_minimap_x(t_vars *vars, t_mini *minimap)
{
	if (minimap->xmax - minimap->x < minimap->width) // calc 12 for small maps
	{
		if (minimap->player_poz_x > (vars->map->cols / 2) )
			minimap->x = minimap->xmax - minimap->width;
		else
			minimap->xmax = minimap->x + minimap->width;
	}
}
void draw_player(t_vars *vars, t_mini *minimap)
{
	fix_minimap_y(vars, minimap);
	fix_minimap_x(vars, minimap);
	draw_circle(vars, (vars->player->x-minimap->x*BLOCK_SIZE) * MMS, (vars->player->y-minimap->y*BLOCK_SIZE) * MMS, vars->player->r * MMS);
	draw_dirc_line(vars, (vars->player->x-minimap->x*BLOCK_SIZE), (vars->player->y-minimap->y*BLOCK_SIZE), vars->player);
}

void    draw_minimap(t_vars *vars, t_mini *minimap)
{
	int	y;
	int	x;
	unsigned int	color;
	if (minimap->height < 12 || minimap->width < 12)
	{
		y = 0;
		while (y < 12*BLOCK_SIZE* MMS)
		{
			x = 0;
			while (x < 12*BLOCK_SIZE* MMS)
				put_pixel(vars, x++, y, 0x00ffff00);
			y++;
		}
	}
	
	fix_minimap_y(vars, minimap);
	y = minimap->y;
	
	while (y < minimap->ymax )
	{
		fix_minimap_y(vars, minimap);
		x = minimap->x;
		// printf("%i %i\n", minimap->x, minimap->xmax);
		while (x < minimap->xmax)
		{
			// printf("LL\n");
			fix_minimap_x(vars, minimap);
			color = (vars->map->map[y * vars->map->cols + x]=='0') * MMC;
			draw_block(vars, (x - minimap->x)*BLOCK_SIZE*MMS, (y - minimap->y)*BLOCK_SIZE*MMS, BLOCK_SIZE*MMS, color);
			x++;
		}
		y++;
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
	draw_line(vars, line, BORDER_COLOR);
	line.y1 = 1;
	line.y2 = 1;
	draw_line(vars, line, BORDER_COLOR);

	line.x1 = 0;
	line.x2 = 12 * BLOCK_SIZE * MMS;
	line.y1 = 12 * BLOCK_SIZE * MMS;
	line.y2 = 12 * BLOCK_SIZE * MMS;
	draw_line(vars, line, BORDER_COLOR);
	line.y1 = 12 * BLOCK_SIZE * MMS + 1;
	line.y2 = 12 * BLOCK_SIZE * MMS + 1;
	draw_line(vars, line, BORDER_COLOR);
	
	line.x1 = 12 * BLOCK_SIZE * MMS;
	line.x2 = 12 * BLOCK_SIZE * MMS;
	line.y1 = 0;
	line.y2 = 12 * BLOCK_SIZE * MMS + 2;
	draw_line(vars, line, BORDER_COLOR);
	line.x1 = 12 * BLOCK_SIZE * MMS+1;
	line.x2 = 12 * BLOCK_SIZE * MMS+1;
	draw_line(vars, line, BORDER_COLOR);
	
	line.x1 = 0;
	line.x2 = 0;
	line.y1 = 0;
	line.y2 = 12 * BLOCK_SIZE * MMS + 2;
	draw_line(vars, line, BORDER_COLOR);
	line.x1 = 1;
	line.x2 = 1;
	draw_line(vars, line, BORDER_COLOR);
}

void	calc_map_wh(t_vars *vars, t_mini *minimap)
{
	minimap->height = (vars->map->rows >= 12) * 12 + !(vars->map->rows >= 12) * vars->map->rows;
	minimap->width = (vars->map->cols >= 12) * 12 + !(vars->map->cols >= 12) * vars->map->cols;
}

void draw_minimap_player(t_vars *vars)
{
	t_mini	minimap;
	
	calc_map_wh(vars, &minimap);
	minimap.player_poz_x = floor(vars->player->x / BLOCK_SIZE);
	minimap.player_poz_y =  floor(vars->player->y / BLOCK_SIZE);
	
	minimap.y = (minimap.player_poz_y - (minimap.height / 2)) * (minimap.height >= 12);
	minimap.y = (minimap.y > 0) * minimap.y;

	minimap.ymax = minimap.player_poz_y + (minimap.height / 2) + (minimap.height % 2) * 1;
	minimap.ymax = (minimap.ymax < vars->map->rows) * minimap.ymax + !(minimap.ymax < vars->map->rows) * (vars->map->rows);

	minimap.x = (minimap.player_poz_x - (minimap.width / 2)) * (minimap.width >= 12);
	minimap.x = (minimap.x > 0) * minimap.x;
	minimap.xmax = minimap.player_poz_x + (minimap.width / 2) + (minimap.width % 2) * 1;
	minimap.xmax = (minimap.xmax < vars->map->cols) * minimap.xmax + !(minimap.xmax < vars->map->cols) * (vars->map->cols );
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

void    draw_block(t_vars *vars, int x, int y, int size, unsigned int color)
{
	float		bx;
	float		by;

	by = y ;
	while (by < y + size - 1 * MMS)
	{
		bx = x ;
		while (bx < x + size - 1 * MMS)
		{
			put_pixel(vars, roundf(bx), roundf(by), color);
			bx++;
		}
		by++;
	}
}