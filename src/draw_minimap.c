/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:35 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/28 12:43:16 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
		return 0;
	return 1;
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
	draw_circle(vars, (vars->player->x-minimap->x*BLOCK_SIZE) * MMSF + MMSHIFT, (vars->player->y-minimap->y*BLOCK_SIZE) * MMSF + MMSHIFT, vars->player->r * MMSF);
	draw_dirc_line(vars, (vars->player->x-minimap->x*BLOCK_SIZE), (vars->player->y-minimap->y*BLOCK_SIZE), vars->player);
}

void	draw_mm_background(int height, int width, t_vars *vars)
{
	int	y;
	int	x;

	y = MMSHIFT;
	while (y < height * BLOCK_SIZE * MMSF + MMSHIFT)
	{
		x = MMSHIFT;
		while (x < width * BLOCK_SIZE * MMSF + MMSHIFT)
			put_pixel(vars, x++, y, 0x00);
		y++;
	}
}

int	get_block_x(float x)
{
	return ((x * BLOCK_SIZE * MMSF) + MMSHIFT);
}

int	get_block_y(float y)
{
	return ((y * BLOCK_SIZE * MMSF) + MMSHIFT);
}

void    draw_minimap(t_vars *vars, t_mini *minimap, int height, int width)
{
	int		y;
	int		x;
	char	color;

	if (minimap->height < height || minimap->width < width)
		draw_mm_background(height, width, vars);
	y = minimap->y;
	while (y < minimap->ymax )
	{
		fix_minimap_y(vars, minimap);
		x = minimap->x;
		while (x < minimap->xmax)
		{
			fix_minimap_x(vars, minimap);
			color = vars->map->map[y * vars->map->cols + x];
			draw_block(vars, get_block_x(x - minimap->x),
				get_block_y(y - minimap->y), BLOCK_SIZE * MMSF, color);
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

void    draw_border(t_vars *vars, int height, int width)
{
	t_line line;

	line.x1 = MMSHIFT;
	line.x2 = width * BLOCK_SIZE * MMSF + MMSHIFT;
	line.y1 = MMSHIFT;
	line.y2 = MMSHIFT;
	draw_border_lines_1(vars, line);
	line.y1 = height * BLOCK_SIZE * MMSF + MMSHIFT;
	line.y2 = height * BLOCK_SIZE * MMSF + MMSHIFT;
	draw_border_lines_1(vars, line);
	line.x1 = width * BLOCK_SIZE * MMSF + MMSHIFT;
	line.y1 = MMSHIFT;
	line.y2 = height * BLOCK_SIZE * MMSF + MMSHIFT + 2;
	draw_border_lines_2(vars, line);
	line.x1 = MMSHIFT;
	line.x2 = MMSHIFT;
	draw_border_lines_2(vars, line);
}

void	calc_map_wh(t_vars *vars, t_mini *minimap, int hight, int width)
{
	minimap->height = (vars->map->rows >= hight) * hight + !(vars->map->rows >= hight) * vars->map->rows;
	minimap->width = (vars->map->cols >= width) * width + !(vars->map->cols >= width) * vars->map->cols;
}

void	calc_map_pos(t_vars *vars, t_mini *minimap, int hight, int width)
{
	minimap->player_poz_x = floor(vars->player->x / BLOCK_SIZE);
	minimap->player_poz_y =  floor(vars->player->y / BLOCK_SIZE);
	
	minimap->y = (minimap->player_poz_y - (minimap->height / 2)) * (minimap->height >= hight);
	minimap->y = (minimap->y > 0) * minimap->y;

	minimap->ymax = minimap->player_poz_y + (minimap->height / 2) + (minimap->height % 2) * 1;
	minimap->ymax = (minimap->ymax < vars->map->rows) * minimap->ymax + !(minimap->ymax < vars->map->rows) * (vars->map->rows);

	minimap->x = (minimap->player_poz_x - (minimap->width / 2)) * (minimap->width >= width);
	minimap->x = (minimap->x > 0) * minimap->x;
	minimap->xmax = minimap->player_poz_x + (minimap->width / 2) + (minimap->width % 2) * 1;
	minimap->xmax = (minimap->xmax < vars->map->cols) * minimap->xmax + !(minimap->xmax < vars->map->cols) * (vars->map->cols );
}

void draw_minimap_player(t_vars *vars)
{
	t_mini	minimap;
	int		hight;
	int		width;

	hight = (vars->status->full_map) * vars->map->rows + !(vars->status->full_map) * MMSIZE;
	width = (vars->status->full_map) * vars->map->cols + !(vars->status->full_map) * MMSIZE;
	calc_map_wh(vars, &minimap, hight, width);
	calc_map_pos(vars, &minimap, hight, width);
	fix_minimap_y(vars, &minimap);
	fix_minimap_x(vars, &minimap);
	draw_minimap(vars, &minimap, hight, width);
	draw_player(vars, &minimap);
	draw_border(vars, hight, width);
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

void    draw_block(t_vars *vars, int x, int y, int size, char c)
{
	float			bx;
	float			by;
	unsigned int	color;

	if (c == '0')
		color = vars->map->f_color;
	else if (c == '1')
		color = 0;
	else if (c == 'C')
		color = DRCC;
	else if (c == 'O')
		color = DROC;
	by = y;
	while (by <= y + size)
	{
		bx = x;
		while (bx <= x + size)
		{
			put_pixel(vars, roundf(bx), roundf(by), color);
			bx++;
		}
		by++;
	}
}
