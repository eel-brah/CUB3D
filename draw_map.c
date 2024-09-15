#include "gm.h"

void    draw_map(t_vars *vars)
{
	for (int y = 0; y < MAP_COLS; y++)
	{
		for (int x = 0; x < MAP_ROWS; x++)
		{
			if (map[y*MAP_ROWS+x]==1)
				draw_block(vars->img, x*BLOCK_SIZE, y*BLOCK_SIZE, BLOCK_SIZE, 0);
			else
				draw_block(vars->img, x*BLOCK_SIZE, y*BLOCK_SIZE, BLOCK_SIZE, 1);
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
	int		bx;
	int		by;

	if (b)
		b = 0x00bec1c4;

	by = y + 1;
	while (by < y+size - 1)
	{
		bx = x + 1;
		while (bx < x+size - 1)
		{
			put_pixel(img, bx, by, b);
			bx++;
		}
		by++;
	}
}