#include "../include/cub3d.h"

void    draw_minimap(t_vars *vars)
{
	int	y;
	int	x;
	unsigned int	color;

	y = 0;
	while (y < MAP_COLS)
	{
		x = 0;
		while (x < MAP_ROWS)
		{
			color = (map[y*MAP_ROWS+x]==0) * MMC;
			draw_block(vars->img, x*BLOCK_SIZE*MMS, y*BLOCK_SIZE*MMS, BLOCK_SIZE*MMS, color);
			x++;
		}
		y++;
	}
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