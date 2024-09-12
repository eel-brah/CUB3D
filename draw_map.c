#include "gm.h"

void    draw_map(t_vars *vars)
{
	for (int y = 0; y < map_y; y++)
	{
		for (int x = 0; x < map_x; x++)
		{
			if (map[y*map_x+x]==1)
				draw_block(vars->img, x*map_s, y*map_s, map_s, 0);
			else
				draw_block(vars->img, x*map_s, y*map_s, map_s, 1);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
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