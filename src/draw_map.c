#include "../include/cub3d.h"

void    draw_map(t_vars *vars)
{
	for (int y = 0; y < MAP_COLS; y++)
	{
		for (int x = 0; x < MAP_ROWS; x++)
		{
			if (map[y*MAP_ROWS+x]==1)
				draw_block(vars->img, x*BLOCK_SIZE*MMS, y*BLOCK_SIZE*MMS, BLOCK_SIZE*MMS, 0);
			else
				draw_block(vars->img, x*BLOCK_SIZE*MMS, y*BLOCK_SIZE*MMS, BLOCK_SIZE*MMS, 1);
		}
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

void    draw_block(t_data *img, int x, int y, int size, unsigned int b)
{
	float		bx;
	float		by;

	if (b)
		b = 0x00bec1c4;

	by = y ;
	while (by < y + size - 1 * MMS)
	{
		bx = x ;
		while (bx < x + size - 1 * MMS)
		{
			put_pixel(img, roundf(bx), roundf(by), b);
			bx++;
		}
		by++;
	}
}