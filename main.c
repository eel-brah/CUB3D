#include "gm.h"

// Globals
float ppz_x, ppz_y, pdx, pdy, pa;
int map_x = 32, map_y = 14, map_s = 47;
int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
	1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

};

void	init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		// ft_putendl_fd("MLX faild", 2);
		exit(1);
	}
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FDF");
	if (!vars->win)
	{
		// ft_putendl_fd("MLX faild", 2);
		exit(1);
	}
	vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img->img)
	{
		mlx_destroy_window(vars->mlx, vars->mlx);
		exit(1);
	}
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bpp, &vars->img->line_length, &vars->img->endian);
}

void draw(t_vars *vars)
{
	set_background(vars->img);
	draw_map(vars);
	draw_player(vars);
}

int	key_catcher(int keysym, t_vars *vars)
{
	printf("%i\n", keysym);
	if (keysym == UP_W_KEY)
	{
		ppz_x += pdx;
			ppz_y += pdy;
		draw(vars);
	}
	else if (keysym == DOWN_S_KEY)
	{
		ppz_x -= pdx;
		ppz_y -= pdy;
		draw(vars);
	}
	else if (keysym == RIGHT_D_KEY)
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa)*5;
		pdy = sin(pa)*5;
		draw(vars);
	}
	else if (keysym == LEFT_A_KEY)
	{
		pa += 0.1;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa)*5;
		pdy = sin(pa)*5;
		draw(vars);
	}
	else if (keysym == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	
	return 1;
}

void draw_rays3d(t_data *img)
{
	int r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo;

	int px = ppz_x+PLAYER_SIZE/2;
	int py = ppz_y+PLAYER_SIZE/2;
	ra = pa;
	for (r = 0; r<1 ; r++)
	{
		dof=0;
		float atan = -1/tan(ra);
		if(ra>PI)
		{
			ry = (((int)py>>6)<<6)-0.0001;
			rx = (py-ry)*atan+px;
			yo = -64;
			xo = (-yo)*atan;
		}
		if(ra<PI)
		{
			ry = (((int)ppz_y>>6)<<6)+64;
			rx = (py-ry)*atan+px;
			yo= 64;
			xo = (-yo)*atan;
		}
		if(ra==0 || ra==PI)
		{
			rx=px;
			ry = py;
			dof= 8;
		}
		while (dof<8)
		{
			mx=(int)(rx)>>6;
			my=(int)(ry)>>6;
			mp=my*map_x+mx;
			if (mp<map_x*map_y && map[mp]==1)
				dof=8;
			else
			{		
				rx+=xo;
				ry+=yo;
				dof+=1;
			}
		}
		t_line line;
		line.x1 = px;
		line.y1 = py;
		line.x2 = rx;
		line.y2 = ry;
		draw_line(line, img, 0x00ff0000);
	}
}

int	main(void)
{
	t_vars vars;
	t_data	img;

	vars.img = &img;

	init(&vars);
    set_background(vars.img);
	draw_map(&vars);
	ppz_x = 300;
	ppz_y = 250;
	pa = 90;
	pdx=cos(pa)*5;
	pdy=sin(pa)*5;
	draw_player(&vars);
    mlx_hook(vars.win, 2, 1L<<0, key_catcher, &vars);
	// mlx_loop_hook(vars.mlx, movement, vars);
	mlx_loop(vars.mlx);
}
