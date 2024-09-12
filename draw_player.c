#include "gm.h"

void draw_dct(float x, float y, t_data *img, unsigned int color)
{
	t_line line;
	line.x1 = x;
	line.y1 = y;
	line.x2 = line.x1+pdx*5;
	line.y2 = line.y1+pdy*5;
	draw_line(line, img, color);
}

void draw_player(t_vars *vars)
{
	int		x;
	int		y;

	y = ppz_y-PLAYER_SIZE/2;
	while (y < ppz_y+PLAYER_SIZE/2)
	{
		x = ppz_x-PLAYER_SIZE/2;
		while (x < ppz_x+PLAYER_SIZE/2)
		{
			put_pixel(vars->img, x, y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
	draw_dct(ppz_x, ppz_y, vars->img, PLAYER_COLOR);
	draw_dct(ppz_x, ppz_y-1, vars->img, PLAYER_COLOR);
	draw_dct(ppz_x, ppz_y+1, vars->img, PLAYER_COLOR);
	// draw_rays3d(vars->img);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}


// void clear_player(t_data *img)
// {
// 	int		x;
// 	int		y;

// 	draw_dct(ppz_x, ppz_y, img, 0x00bec1c4, 1);
// 	draw_dct(ppz_x, ppz_y-1, img, 0x00bec1c4, 1);
// 	draw_dct(ppz_x, ppz_y+1, img, 0x00bec1c4, 1);
	
// 	y = ppz_y;
// 	while (y < ppz_y+PLAYER_SIZE)
// 	{
// 		x = ppz_x;
// 		while (x < ppz_x+PLAYER_SIZE)
// 		{
// 			if (x % map_s == 0 || y % map_s == 0 || (y+1) % map_s == 0 || (x+1) % map_s == 0)
// 				put_pixel(img, x, y, BACKGROUND);
// 			else
// 				put_pixel(img, x, y, 0x00bec1c4);
// 			x++;
// 		}
// 		y++;
// 	}
	
// }