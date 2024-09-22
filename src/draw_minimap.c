#include "../include/cub3d.h"

void init_player(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	player->x = vars->map->player_x_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->y = vars->map->player_y_pos * BLOCK_SIZE + BLOCK_SIZE / 2;
	player->r = PLAYER_SIZE;
	// player->pa = PI * 1.5f;
	player->pa = vars->map->player_face;
	player->steps = 6;
	player->rspeed = deg2rad(5);
}

void draw_dirc_line(t_vars *vars, float x, float y, t_player *player)
{
	t_line	line;

	line.x1 = x * MMSF + MMSHIFT;
	line.y1 = y * MMSF + MMSHIFT;
	line.x2 = (x+cos(player->pa)*player->r) * MMSF + MMSHIFT;
	line.y2 = (y+sin(player->pa)*player->r) * MMSF + MMSHIFT;
	draw_line(vars, line, DIRC_LINE);
}

int	isit_outob(float x, float y)
{
	if (x > 0 && x < WIDTH && y < HEIGHT && y > 0)
		return 0;
	return 1;
}
bool	isit_wall(t_vars *vars, float x, float y)
{
	// if (isit_outob(vars, x, y))
	// 	return true;
	int ty;
	int tx;

	ty = floor(y/BLOCK_SIZE);
	tx = floor(x/BLOCK_SIZE);
	if (ty > 0 && ty < vars->map->rows && tx > 0 && tx < vars->map->cols && vars->map->map[ty * vars->map->cols + tx] == '0')
		return false;
	// if (vars->map->map[((int)floor(y/BLOCK_SIZE))* vars->map->cols +((int)floor(x/BLOCK_SIZE))] == '0')
	// 	return false;
	return true;
}

void player_movement(t_vars *vars, int dirc, int sp)
{
	t_player	*player;
	float		tmp_x;
	float		tmp_y;

	player = vars->player;
	tmp_x = player->x + cos(player->pa + deg2rad(sp)) * player->steps * dirc;
	tmp_y = player->y + sin(player->pa + deg2rad(sp)) * player->steps * dirc;
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
	if (minimap->xmax - minimap->x < minimap->width) // calc MMSIZE for small maps
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
	draw_circle(vars, (vars->player->x-minimap->x*BLOCK_SIZE) * MMSF + MMSHIFT, (vars->player->y-minimap->y*BLOCK_SIZE) * MMSF + MMSHIFT, vars->player->r * MMSF);
	draw_dirc_line(vars, (vars->player->x-minimap->x*BLOCK_SIZE), (vars->player->y-minimap->y*BLOCK_SIZE), vars->player);
}

void    draw_minimap(t_vars *vars, t_mini *minimap)
{
	int	y;
	int	x;
	unsigned int	color;
	if (minimap->height < MMSIZE || minimap->width < MMSIZE)
	{
		y = 0;
		while (y < MMSIZE*BLOCK_SIZE* MMSF)
		{
			x = 0;
			while (x < MMSIZE*BLOCK_SIZE* MMSF)
				put_pixel(vars, x++, y, 0x00);
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
			draw_block(vars, ((x - minimap->x)*BLOCK_SIZE*MMSF)+MMSHIFT, ((y - minimap->y)*BLOCK_SIZE*MMSF)+MMSHIFT, BLOCK_SIZE*MMSF, color);
			x++;
		}
		y++;
	}
	
}

void    draw_border_lines_1(t_vars *vars, t_line line)
{
	draw_line(vars, line, BORDER_COLOR);
	line.y1 += 1;
	line.y2 += 1;
	draw_line(vars, line, BORDER_COLOR);
}
void    draw_border_lines_2(t_vars *vars, t_line line)
{
	draw_line(vars, line, BORDER_COLOR);
	line.x1 += 1;
	line.x2 += 1;
	draw_line(vars, line, BORDER_COLOR);
}

void    draw_border(t_vars *vars)
{
	t_line line;

	line.x1 = MMSHIFT;
	line.x2 = MMSIZE * BLOCK_SIZE * MMSF + MMSHIFT;
	line.y1 = MMSHIFT;
	line.y2 = MMSHIFT;
	draw_border_lines_1(vars, line);
	line.y1 = line.x2;
	line.y2 = line.x2;
	draw_border_lines_1(vars, line);
	line.x1 = line.x2;
	line.y1 = MMSHIFT;
	line.y2 = line.x2 + 2;
	draw_border_lines_2(vars, line);
	line.x1 = MMSHIFT;
	line.x2 = MMSHIFT;
	draw_border_lines_2(vars, line);
}

void	calc_map_wh(t_vars *vars, t_mini *minimap)
{
	minimap->height = (vars->map->rows >= MMSIZE) * MMSIZE + !(vars->map->rows >= MMSIZE) * vars->map->rows;
	minimap->width = (vars->map->cols >= MMSIZE) * MMSIZE + !(vars->map->cols >= MMSIZE) * vars->map->cols;
}

void draw_minimap_player(t_vars *vars)
{
	t_mini	minimap;
	
	calc_map_wh(vars, &minimap);
	minimap.player_poz_x = floor(vars->player->x / BLOCK_SIZE);
	minimap.player_poz_y =  floor(vars->player->y / BLOCK_SIZE);
	
	minimap.y = (minimap.player_poz_y - (minimap.height / 2)) * (minimap.height >= MMSIZE);
	minimap.y = (minimap.y > 0) * minimap.y;

	minimap.ymax = minimap.player_poz_y + (minimap.height / 2) + (minimap.height % 2) * 1;
	minimap.ymax = (minimap.ymax < vars->map->rows) * minimap.ymax + !(minimap.ymax < vars->map->rows) * (vars->map->rows);

	minimap.x = (minimap.player_poz_x - (minimap.width / 2)) * (minimap.width >= MMSIZE);
	minimap.x = (minimap.x > 0) * minimap.x;
	minimap.xmax = minimap.player_poz_x + (minimap.width / 2) + (minimap.width % 2) * 1;
	minimap.xmax = (minimap.xmax < vars->map->cols) * minimap.xmax + !(minimap.xmax < vars->map->cols) * (vars->map->cols );
	draw_minimap(vars, &minimap);
	draw_player(vars, &minimap);
	draw_border(vars);
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
	while (by < y + size - 1 * MMSF)
	{
		bx = x ;
		while (bx < x + size - 1 * MMSF)
		{
			put_pixel(vars, roundf(bx), roundf(by), color);
			bx++;
		}
		by++;
	}
}