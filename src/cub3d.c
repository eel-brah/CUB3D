#include "../include/cub3d.h"

int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
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
		ft_putendl_fd("MLX faild", 2);
		exit(1);
	}
	vars->win = mlx_new_window(vars->mlx, vars->map->width, vars->map->height, "CUB3D");
	if (!vars->win)
	{
		ft_putendl_fd("MLX faild", 2);
		exit(1);
	}
	vars->img->img = mlx_new_image(vars->mlx, vars->map->width, vars->map->height);
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
	// set_background(vars->img);
	cast_rays(vars);
	draw_wall(vars);
	if (vars->status->mm)
	{
		draw_minimap_player(vars);
		// draw_minimap(vars);
		// draw_rays(vars);
		// draw_player(vars);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int	key_press(int keysym, t_vars *vars)
{
	printf("%i\n", keysym);
	if (keysym == UP_W_KEY)
		player_movement(vars, 1, 0);
	else if (keysym == DOWN_S_KEY)
		player_movement(vars, -1, 0);
	else if (keysym == LEFT_A_KEY)
		player_movement(vars, -1, 90);
	else if (keysym == RIGHT_D_KEY)
		player_movement(vars, 1, 90);
	else if (keysym == LEFT_KEY)
		player_rotation(vars, -1);
	else if (keysym == RIGHT_KEY)
		player_rotation(vars, 1);
	else if (keysym == 46)
	{
		vars->status->mm = !(vars->status->mm);
		draw(vars); // remove this
	}
	else if (keysym == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->rays);
		exit(0);
	}
	return 1;
}

void setup(t_vars *vars)
{
	init(vars);
	init_ray(vars);
	// init_map(vars->map);
	init_player(vars);
    // set_background(vars->img);
	cast_rays(vars);
	draw_wall(vars);
	if (vars->status->mm)
	{
		draw_minimap_player(vars);
		// draw_minimap(vars);
		// draw_rays(vars);
		// draw_player(vars);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

void print_map(t_vars *vars)
{
	int i = 0;
	int j = 0;
	while(j < vars->map->rows)
	{
		i = 0;
		while(i < vars->map->cols)
		{
			printf("%i ", vars->map->map[j * vars->map->cols + i]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("\n");
	printf("\n");
	j = 0;
	while(j < vars->map->rows)
	{
		i = 0;
		while(i < vars->map->cols)
		{
			printf("%i ", map[j * vars->map->cols + i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data		img;
	t_player	player;
	t_ray		ray;
	t_status	status;
	// t_map		map;

	t_map	*map;

	map = NULL;
	if (argc >= 2)
	{
		map = parse(argv[1]);
		//free_map(map);
	}
	else
	{
		write(2, "Error\nnb argument \n", 19);
		return (-1);
	}
	printf("NO = %s\n", map->no);
	printf("SO = %s\n", map->so);
	printf("WE = %s\n", map->we);
	printf("EA= %s\n", map->ea);
	printf("F= %u\n", map->f);
	printf("C= %u\n", map->c);
	//ft_lstiter(map->lst, print_all);
	// int i =0;
	// while (i < map->max_line)
	// {
	// 	printf("%s\n", map->map[i]);
	// 	i++;
	// }
	vars.img = &img;
	vars.player = &player;
	vars.ray = &ray;
	status.mm = 1;
	vars.status = &status;
	vars.map = map;

	print_map(&vars);

	setup(&vars);
    mlx_hook(vars.win, 2, 1L<<0, key_press, &vars);
	// mlx_loop_hook(vars.mlx, movement, vars);
	mlx_loop(vars.mlx);
	free_map(map);
}
