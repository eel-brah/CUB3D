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

void    draw_block(t_data *img, int xx, int yy, int size, unsigned int b)
{
	int		x;
	int		y;

	if (b)
		b = 0x00bec1c4;

	y = yy + 1;
	while (y < yy+size - 1)
	{
		x = xx + 1;
		while (x < xx+size - 1)
		{
			put_pixel(img, x, y, b);
			x++;
		}
		y++;
	}
}