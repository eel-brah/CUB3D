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
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!vars->win)
	{
		ft_putendl_fd("MLX faild", 2);
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


int	close_and_clear(t_vars *vars)
{
	ft_printf("\033[4;35m\033[1;95mCUB3D\033[0m \033[0;95mClosed\033[0m\n");
	free(vars->rays);
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	// free and close fds
	exit(0);
}


// void    open_door(t_window *window)
// {
//     int    new_x;
//     int    new_y;
//     int    i;

//     i = 0;
//     while (i < 100)
//     {
//         new_x = window->player.x + (cos(window->player.rotation_angle) * i);
//         new_y = window->player.y + (sin(window->player.rotation_angle) * i);
//         if (new_x > 0 && new_y > 0 && new_x < window->width && new_y \
//             < window->height && \
//             window->map->v_map[new_y / BLOCK_SIZE][new_x / BLOCK_SIZE] == 'D')
//         {
//             window->map->v_map[new_y / BLOCK_SIZE][new_x / BLOCK_SIZE] = 'C';
//             break ;
//         }
//         i++;
//     }
// }

// void    close_door(t_window *window)
// {
//     int    new_x;
//     int    new_y;
//     int    i;

//     i = BLOCK_SIZE + 1;
//     while (i < 100)
//     {
//         new_x = window->player.x + (cos(window->player.rotation_angle + 3) * i);
//         new_y = window->player.y + (sin(window->player.rotation_angle + 3) * i);
//         if (new_x > 0 && new_y > 0 && new_x < window->width \
//             && new_y < window->height && \
//             window->map->v_map[new_y / BLOCK_SIZE][new_x / BLOCK_SIZE] == 'C')
//         {
//             window->map->v_map[new_y / BLOCK_SIZE][new_x / BLOCK_SIZE] = 'D';
//             break ;
//         }
//         i++;
//     }
// }

void	open_close_door(t_vars *vars) // door has walls on the side
{
	int i;
	
	i = BLOCK_SIZE + vars->player->r;
	while (i < BLOCK_SIZE * 2)
	{
		int new_x = vars->player->x + (cos(vars->player->pa + vars->player->rspeed) * i);
		int new_y = vars->player->y + (sin(vars->player->pa + vars->player->rspeed) * i);
		if (new_x > 0 && new_y > 0 && new_x < WIDTH && new_y < HEIGHT)
		{
			int d = vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)];
			if (d == 'C')
			{
				vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] = 'O';
				break;
			}
			else if (d == 'O')
			{
				vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] = 'C';
				break ;
			}
		}
		i++;
	}
}

int	key_press(int keysym, t_vars *vars)
{
	printf("%i\n", keysym);
	if (keysym == UP_W_KEY || keysym == UP_KEY)
		player_movement(vars, 1, 0);
	else if (keysym == DOWN_S_KEY || keysym == DOWN_KEY)
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
		// draw(vars); // remove this
	}
	else if (keysym == 49)
	{
		open_close_door(vars);
		// draw(vars); // remove this
	}
	else if (keysym == ESC_KEY)
		close_and_clear(vars);
	return 1;
}
#define MAX_ROTATION_SPEED 20.0f
#define SENSITIVITY 0.001f  // Adjust this value to change rotation sensitivity

int mouse_move(int x, int y, t_vars *vars)
{
    (void)y;  // We're not using the y coordinate
    static int last_x = -1;
    float delta_x;
    float normalized_rotation;

    if (last_x == -1)
    {
        last_x = x;
        return 1;
    }
	if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
	{
		// Calculate the change in x position
		delta_x = x - last_x;
		last_x = x;

		// Apply sensitivity and normalize
		normalized_rotation = delta_x * SENSITIVITY;
		
		// Clamp the value between -1 and 1
		normalized_rotation = fmaxf(-1.0f, fminf(1.0f, normalized_rotation));

		// Apply the rotation
		player_rotation(vars, normalized_rotation * MAX_ROTATION_SPEED);
	}

    return 1;
}

int	mouse_movse(int x, int y, t_vars *vars)
{
	static bool first_move = true;
	(void)y;
	int	new_x;
	if (first_move)
	{
		vars->map->old_x = x;
		first_move = false;
	}
	if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
	{
		new_x = x - vars->map->old_x;
		vars->map->old_x = x;
		if (new_x != 0)
			player_rotation(vars, new_x > 0 ? 1 : -1);
	}
    return 1;
}

bool setup(t_vars *vars)
{
	init(vars);
	if (!open_texture(vars))
	{
		printf("something not \n");
		return false;
	}
	init_ray(vars);
	// init_map(vars->map);
	init_player(vars);
    // set_background(vars->img);
	return true;
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

int mouse_hook(int b, int x, int y, t_vars *vars)
{
	(void)vars;
	printf("%i %i %i\n",b ,x, y);
	return 1;
}
int mouse_hook_move(int x, int y, t_vars *vars)
{
	(void)vars;
	printf(" [%i %i]\n" ,x, y);
	return 1;
}

bool	open_texture(t_vars *vars)
{
	t_data	*data;

	vars->door.img = mlx_xpm_file_to_image(vars->mlx, "images/door.xpm" ,&vars->door.width, &vars->door.height);
	if (!vars->door.img)
		return (false);
	vars->north.img = mlx_xpm_file_to_image(vars->mlx, vars->map->no,&vars->north.width, &vars->north.height);
	if (!vars->north.img)
		return (false);
	vars->west.img = mlx_xpm_file_to_image(vars->mlx, vars->map->we,&vars->west.width, &vars->west.height);
	if (!vars->west.img)
		return (false);
	vars->south.img = mlx_xpm_file_to_image(vars->mlx, vars->map->so,&vars->south.width, &vars->south.height);
	if (!vars->south.img)
		return (false);
	vars->east.img = mlx_xpm_file_to_image(vars->mlx, vars->map->ea,&(vars->east.width), &(vars->east.height));
	if (!vars->east.img)
		return (false);
	data = &vars->door;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->north;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->west;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->south;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->east;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);

	return (true);
}
int render(t_vars *vars)
{
	cast_rays(vars);
	draw_wall(vars);
	if (vars->status->mm)
		draw_minimap_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return 0;
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
	printf("F= %u\n", map->f_color);
	printf("C= %u\n", map->c_color);
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
	setup(&vars); // check if faild
	
	
    mlx_hook(vars.win, 2, 0, key_press, &vars);
	mlx_hook(vars.win, 17, 0, close_and_clear, &vars);
    // mlx_hook(vars.win, 6, 0, mouse_movse, &vars);
    mlx_hook(vars.win, 6, 0, mouse_move, &vars);
	// render(&vars);
	mlx_loop_hook(vars.mlx, render, &vars);
    // mlx_hook(vars.win, 4, 0, mouse_hook, &vars);
    // mlx_hook(vars.win, 6, 0, mouse_hook_move, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_loop_hook(vars.mlx, movement, vars);
	mlx_loop(vars.mlx);
	free_map(map);
}
