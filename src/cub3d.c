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
	int i = 0;

	while (i < 9)
		vars->items[i++].animate = false;
	vars->cam = false;
	vars->player_animate_hit = false;
	vars->keys.a_key = false;
	vars->keys.d_key = false;
	vars->keys.s_key = false;
	vars->keys.w_key = false;
	vars->keys.up_key = false;
	vars->keys.down_key = false;
	vars->keys.left_key = false;
	vars->keys.right_key = false;
	vars->player->rotate = false;
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

// void	open_close_door2(t_vars *vars) // door has walls on the side
// {
// 	float dis = vars->rays[vars->ray->rays_num/2].hit_dis;
// 	bool door = vars->rays[vars->ray->rays_num/2].is_door_close || vars->rays[vars->ray->rays_num/2].is_door_open;
// 	int xy;
	
// 	if (door && dis < 50)
// 	{
// 		printf("KKKKKKKK\n");
// 		xy = (int)vars->rays[vars->ray->rays_num/2].y_whpoint / BLOCK_SIZE * vars->map->cols + (int)vars->rays[vars->ray->rays_num/2].x_whpoint / BLOCK_SIZE;
// 		if (vars->map->map[xy] == 'C')
// 			vars->map->map[xy] = 'O';
// 		else if (vars->map->map[xy] == 'O')
// 			vars->map->map[xy] = 'C';
// 	}
// }


int	key_realese(int keysym, t_vars *vars)
{
	if (keysym == 259)
	{
		if (vars->cam)
			vars->player->pa -= PI;
		vars->cam = false;
	}
	// if (keysym == 8)
	// {
	// 	vars->animate = false;
	// 	vars->animate_ax = false;
	// 	// anime_axe(vars);
	// }
	if (keysym == UP_KEY)
		vars->keys.up_key = false;
	if (keysym == UP_W_KEY)
		vars->keys.w_key = false;
	if (keysym == DOWN_S_KEY)
		vars->keys.s_key = false;
	if (keysym == DOWN_KEY)
		vars->keys.down_key = false;
	if (keysym == LEFT_A_KEY)
		vars->keys.a_key = false;
	if (keysym == RIGHT_D_KEY)
		vars->keys.d_key = false;
	if (keysym == LEFT_KEY)
		vars->keys.left_key = false;
	if (keysym == RIGHT_KEY)
		vars->keys.right_key = false;
	return 0;
}
// int anime_sword(t_vars *vars)
// {
// 	static unsigned int i = 0;
// 	static unsigned int j = 0;


// 	if(i % 3 == 0)
// 	{
// 		printf("alo %i\n",j);
// 		if (j == 0)
// 			mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->sword[j].img, 0, 0);
// 		if (j == 3)
// 		{
// 			vars->current = vars->sword[j];
// 			vars->animate_sw = false;
// 			// vars->last = vars->sword;
// 			j = 0;
// 			i = 0;
// 			return 1;
// 		}
// 		j++;
		
// 	}
// 	i++;
// 	return (1);
// }

int animation(t_vars *vars, t_item *item)
{
	static unsigned int i = 0;
	static unsigned int j = 0;
	static unsigned int k = 1; // reset if vars->cam false

	if (vars->cam)
	{
		if (vars->rays[vars->ray->rays_num/2].hit_dis < 50)
		{
			vars->player_animate_hit = false;
			return 1;
		}
		if (vars->player_animate_hit && vars->player_animate_shield )
		{
			vars->player_animate_hit = false;
			vars->player_animate_shield = false;
		}
		else if (vars->player_animate_hit)
		{
			if (i % 3 == 0)
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
				mlx_put_image_to_window(vars->mlx, vars->win, vars->player_cam[k].img, 0, 0);
				k++;
				if (k == 7)
				{
					k = 1;
					vars->player_animate_hit = false;
				}
			}
		}
		else if (vars->player_animate_shield)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->player_cam_shield.img, 0, 0);

		}
		else
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->player_cam[0].img, 0, 0);
		}
	}
	if(!vars->cam && i % 2 == 0)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
		mlx_put_image_to_window(vars->mlx, vars->win, item->item[j].img, 0, 0);
		if (j == 3)
		{
			item->animate = false;
			printf("alo here her \n");
			vars->current = item->item[j];
			j = 0;
			i = 0;
			return 1;
		}
		j++;
		
	}
	i++;
	if (i == 1000000000)
		i = 0;
	return (1);
}


// int anime_axe(t_vars *vars)
// {
// 	static unsigned int i = 0;
// 	static unsigned int j = 0;

// 	if(i % 3 == 0)
// 	{
// 		printf("alo %i\n",j);
// 		if (j == 0)
// 			mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
// 		mlx_put_image_to_window(vars->mlx, vars->win, vars->axe[j].img, 0, 0);
// 		if (j == 4)
// 		{
// 			vars->current = vars->axe[j];
// 			vars->animate_ax = false;
// 			j = 0;
// 			i = 0;
// 			return 1;
// 		}
// 		j++;
		
// 	}
// 	i++;
// 	return (1);
// }
bool	check_wall_dis(t_vars *vars) // door has walls on the side
{
	int i;
	float angle;
	int end;
	int new_x;
	int new_y;


	angle = vars->player->pa + PI;
	i = BLOCK_SIZE;
	end = BLOCK_SIZE * 1.5;
	while (i < end)
	{
		new_x = vars->player->x + (cos(angle + vars->player->rspeed) * i);
		new_y = vars->player->y + (sin(angle + vars->player->rspeed) * i);
		if (!(new_x >= 0 && new_y >= 0 && new_x < WIDTH && new_y < HEIGHT) || (new_x >= 0 && new_y >= 0 && new_x < WIDTH && new_y < HEIGHT 
			&& (vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] == '1' || vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] == 'C')))
			return 0;
		i++;
	}
	return 1;
}

int	key_press(int keysym, t_vars *vars)
{
	if (keysym == 259)
	{
			if (!vars->cam)
				vars->player->pa += PI;
			vars->cam = true;
			vars->keys.up_key = false;
			vars->keys.w_key = false;
			vars->keys.s_key = false;
			vars->keys.down_key = false;
			vars->keys.a_key = false;
			vars->keys.d_key = false;
			vars->keys.left_key = false;
			vars->keys.right_key = false;
			vars->player->rotate = false;
			// vars->animate_sw = false;
			// vars->animate = true;
			// anime_sword(vars);
	}

	if (!vars->cam)
	{	if (keysym == UP_KEY)
			vars->keys.up_key = true;
		if (keysym == UP_W_KEY)
			vars->keys.w_key = true;
		if (keysym == DOWN_S_KEY)
			vars->keys.s_key = true;
		if (keysym == DOWN_KEY)
			vars->keys.down_key = true;
		if (keysym == LEFT_A_KEY)
			vars->keys.a_key = true;
		if (keysym == RIGHT_D_KEY)
			vars->keys.d_key = true;
		if (keysym == LEFT_KEY)
			vars->keys.left_key = true;
		if (keysym == RIGHT_KEY)
			vars->keys.right_key = true;
		if (keysym == 49)
		{
			open_close_door(vars);
			// open_close_door2(vars);
		}
	}
	if (keysym == 46)
		vars->status->mm = !(vars->status->mm);
	if (keysym == ESC_KEY)
		close_and_clear(vars);
	return 1;
}
#define MAX_ROTATION_SPEED 20.0f
#define SENSITIVITY 0.001f  // Adjust this value to change rotation sensitivit



int mouse_move(int x, int y, t_vars *vars)
{
    (void)y;
    static int last_x = -1;
    float delta_x;
    float normalized_rotation;
	if (!vars->cam)
{
    if (last_x == -1)
    {
        last_x = x;
        return 1;
    }
	if (vars->player->mouse && x >= WIDTH - 100)
	{
		vars->player->rotate = 1;
		vars->player->rotate2 = 0;
		vars->player->ra = 0.02;
	}
	else if (vars->player->mouse && x <=  100)
	{
		vars->player->rotate = 1;
		vars->player->rotate2 = 0;
		vars->player->ra = -0.02;

	}
	else if (vars->player->mouse)
	{
		// usleep(10);

		vars->player->rotate = 0;
		vars->player->rotate2 = 1;
		delta_x = x - last_x;
		if (delta_x < 5 && delta_x > -5)
			return (1);
		last_x = x;

		normalized_rotation = delta_x * SENSITIVITY;
		
		normalized_rotation = fmaxf(-1.0f, fminf(1.0f, normalized_rotation));
		// vars->player->rotate2 = 1;
		// vars->player->ra = (0.02 * (delta_x > 0) + -0.02 * !(delta_x > 0));
		vars->player->ra = normalized_rotation *3;
		//player_rotation(vars, normalized_rotation * MAX_ROTATION_SPEED);
		// player_rotation(vars, (delta_x >= 0 ? 0.02: -0.02) * MAX_ROTATION_SPEED);
	}
	else
	{
		vars->player->rotate = 0;
		vars->player->rotate2 = 0;
	}
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
	static int	i = 0;

	printf("%i %i %i   i : %i \n",b ,x, y,i);
	// printf("=============\n");
	// if (b == 3)
	// {
	// 	vars->cam = !(vars->cam);
	// }
	if (b == 3)
		vars->player->mouse = !(vars->player->mouse);
	if (vars->cam && b == 1)
	{
		vars->player_animate_hit = true;
	}
	else if (vars->cam && b == 2)
	{
		vars->player_animate_shield = true;
	}
	if (!vars->cam && (b == 4 || b == 2))
	{
		i++;
		i = i % 9;
		vars->items[i].animate =true;

		vars->items[!(i == 8) * (i+1)].animate =false;
		vars->items[(i == 0) * 8 + !(i == 0) * (i-1)].animate =false;
	}
	else if (!vars->cam && (b == 5 || b == 1))
	{
		i--;
		if (i == -1)
			i = 8;
		vars->items[i].animate =true;

		vars->items[!(i == 8) * (i+1)].animate =false;
		vars->items[(i == 0) * 8 + !(i == 0) * (i-1)].animate =false;
	}
	
	// i = i % 9;
	return 1;
}
int mouse_hook_move(int x, int y, t_vars *vars)
{
	(void)vars;
	printf(" [%i %i]\n" ,x, y);
	return 1;
}

bool	load_sword(t_vars *vars)
{
	vars->items[0].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/1.xpm" ,&vars->items[0].item[0].width, &vars->items[0].item[0].height);
	if (!vars->items[0].item[0].img)
		return (false);
	vars->items[0].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/2.xpm" ,&vars->items[0].item[1].width, &vars->items[0].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[0].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/3.xpm" ,&vars->items[0].item[2].width, &vars->items[0].item[2].height);
	if (!vars->items[0].item[2].img)
		return (false);
	vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	if (!vars->items[0].item[3].img)
		return (false);
	return (true);
}

bool	load_axe(t_vars *vars)
{
	vars->items[1].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/1.xpm" ,&vars->items[1].item[0].width, &vars->items[1].item[0].height);
	if (!vars->items[0].item[0].img)
		return (false);
	vars->items[1].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/3.xpm" ,&vars->items[1].item[1].width, &vars->items[1].item[1].height);
	if (!vars->items[1].item[1].img)
		return (false);
	vars->items[1].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/4.xpm" ,&vars->items[1].item[2].width, &vars->items[1].item[2].height);
	if (!vars->items[1].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[1].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/4.xpm" ,&vars->items[1].item[3].width, &vars->items[1].item[3].height);
	if (!vars->items[1].item[3].img)
		return (false);
	return (true);
}

bool	load_pickaxe(t_vars *vars)
{
	vars->items[2].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/1.xpm" ,&vars->items[2].item[0].width, &vars->items[2].item[0].height);
	if (!vars->items[2].item[0].img)
		return (false);
	vars->items[2].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/3.xpm" ,&vars->items[2].item[1].width, &vars->items[2].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[2].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/4.xpm" ,&vars->items[2].item[2].width, &vars->items[2].item[2].height);
	if (!vars->items[2].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/Axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[2].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/4.xpm" ,&vars->items[2].item[3].width, &vars->items[2].item[3].height);
	if (!vars->items[2].item[3].img)
		return (false);
	return (true);
}

bool	load_bow(t_vars *vars)
{
	vars->items[3].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/1.xpm" ,&vars->items[3].item[0].width, &vars->items[3].item[0].height);
	if (!vars->items[3].item[0].img)
		return (false);
	vars->items[3].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/3.xpm" ,&vars->items[3].item[1].width, &vars->items[3].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[3].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/4.xpm" ,&vars->items[3].item[2].width, &vars->items[3].item[2].height);
	if (!vars->items[3].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/Axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[3].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/4.xpm" ,&vars->items[3].item[3].width, &vars->items[3].item[3].height);
	if (!vars->items[3].item[3].img)
		return (false);
	return (true);
}

bool	load_totem(t_vars *vars)
{
	vars->items[4].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/1.xpm" ,&vars->items[4].item[0].width, &vars->items[4].item[0].height);
	if (!vars->items[4].item[0].img)
		return (false);
	vars->items[4].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/3.xpm" ,&vars->items[4].item[1].width, &vars->items[4].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[4].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/4.xpm" ,&vars->items[4].item[2].width, &vars->items[4].item[2].height);
	if (!vars->items[4].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/Axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[4].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/4.xpm" ,&vars->items[4].item[3].width, &vars->items[4].item[3].height);
	if (!vars->items[4].item[3].img)
		return (false);
	return (true);
}

bool	load_diamond(t_vars *vars)
{
	vars->items[5].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/1.xpm" ,&vars->items[5].item[0].width, &vars->items[5].item[0].height);
	if (!vars->items[5].item[0].img)
		return (false);
	vars->items[5].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/3.xpm" ,&vars->items[5].item[1].width, &vars->items[5].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[5].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/4.xpm" ,&vars->items[5].item[2].width, &vars->items[5].item[2].height);
	if (!vars->items[5].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/Axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[5].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/4.xpm" ,&vars->items[5].item[3].width, &vars->items[5].item[3].height);
	if (!vars->items[5].item[3].img)
		return (false);
	return (true);
}

bool	load_apple(t_vars *vars)
{
	vars->items[6].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/1.xpm" ,&vars->items[6].item[0].width, &vars->items[6].item[0].height);
	if (!vars->items[6].item[0].img)
		return (false);
	vars->items[6].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/3.xpm" ,&vars->items[6].item[1].width, &vars->items[6].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[6].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/4.xpm" ,&vars->items[6].item[2].width, &vars->items[6].item[2].height);
	if (!vars->items[6].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/Axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[6].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/4.xpm" ,&vars->items[6].item[3].width, &vars->items[6].item[3].height);
	if (!vars->items[6].item[3].img)
		return (false);
	return (true);
}

bool	load_potion(t_vars *vars)
{
	vars->items[7].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/1.xpm" ,&vars->items[7].item[0].width, &vars->items[7].item[0].height);
	if (!vars->items[7].item[0].img)
		return (false);
	vars->items[7].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/3.xpm" ,&vars->items[7].item[1].width, &vars->items[7].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[7].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/4.xpm" ,&vars->items[7].item[2].width, &vars->items[7].item[2].height);
	if (!vars->items[7].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/Axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[7].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/4.xpm" ,&vars->items[7].item[3].width, &vars->items[7].item[3].height);
	if (!vars->items[7].item[3].img)
		return (false);
	return (true);
}

bool	load_food(t_vars *vars)
{
	vars->items[8].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/1.xpm" ,&vars->items[8].item[0].width, &vars->items[8].item[0].height);
	if (!vars->items[8].item[0].img)
		return (false);
	vars->items[8].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/3.xpm" ,&vars->items[8].item[1].width, &vars->items[8].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[8].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/4.xpm" ,&vars->items[8].item[2].width, &vars->items[8].item[2].height);
	if (!vars->items[8].item[2].img)
		return (false);
	// vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/Axe/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	// if (!vars->items[0].item[3].img)
	// 	return (false);
	vars->items[8].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/4.xpm" ,&vars->items[8].item[3].width, &vars->items[8].item[3].height);
	if (!vars->items[8].item[3].img)
		return (false);
	return (true);
}

bool	load_player(t_vars *vars)
{
	vars->player_cam[0].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/shield1.xpm" ,&vars->player_cam[0].width, &vars->player_cam[0].height);
	if (!vars->player_cam[0].img)
		return (false);
	vars->player_cam[1].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit1.xpm" ,&vars->player_cam[1].width, &vars->player_cam[1].height);
	if (!vars->player_cam[1].img)
		return (false);
	vars->player_cam[2].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit2.xpm" ,&vars->player_cam[2].width, &vars->player_cam[2].height);
	if (!vars->player_cam[2].img)
		return (false);
	vars->player_cam[3].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit3.xpm" ,&vars->player_cam[3].width, &vars->player_cam[3].height);
	if (!vars->player_cam[3].img)
		return (false);
	vars->player_cam[4].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit4.xpm" ,&vars->player_cam[4].width, &vars->player_cam[4].height);
	if (!vars->player_cam[4].img)
		return (false);
	vars->player_cam[5].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit5.xpm" ,&vars->player_cam[5].width, &vars->player_cam[5].height);
	if (!vars->player_cam[5].img)
		return (false);
	vars->player_cam[6].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit6.xpm" ,&vars->player_cam[6].width, &vars->player_cam[6].height);
	if (!vars->player_cam[6].img)
		return (false);
	vars->player_cam_shield.img = mlx_xpm_file_to_image(vars->mlx, "images/cam/shield2.xpm" ,&vars->player_cam_shield.width, &vars->player_cam_shield.height);
	if (!vars->player_cam_shield.img)
		return (false);
	return (true);
}

bool	open_texture(t_vars *vars)
{
	t_data	*data;

	
		
	if (!load_sword(vars))
		return (false);
	if (!load_axe(vars))
		return (false);
	if (!load_pickaxe(vars))
		return (false);
	if (!load_bow(vars))
		return (false);
	if (!load_totem(vars))
		return (false);
	if(!load_diamond(vars))
		return (false);
	if(!load_apple(vars))
		return (false);
	if(!load_potion(vars))
		return (false);
	if(!load_food(vars))
		return (false);
	if(!load_player(vars))
		return (false);
	vars->door.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door2.xpm" ,&vars->door.width, &vars->door.height);
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
	// data = &vars->sword;
	// data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
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
	if (vars->keys.w_key == true || vars->keys.up_key == true)
		player_movement(vars, 1, 0);
	if (vars->keys.s_key == true || vars->keys.down_key == true)
		player_movement(vars, -1, 0);
	if (vars->keys.a_key == true)
		player_movement(vars, -1, 90);
	if (vars->keys.d_key == true)
		player_movement(vars, 1, 90);
	if (vars->keys.left_key == true)
		player_rotation(vars, -1);
	if (vars->keys.right_key == true)
		player_rotation(vars, 1);
	cast_rays(vars);
	draw_wall(vars);
	if (vars->status->mm)
		draw_minimap_player(vars);
	if (vars->player->rotate)
		player_rotation(vars, vars->player->ra * MAX_ROTATION_SPEED);
	if (vars->player->rotate2)
	{
		player_rotation(vars, vars->player->ra * MAX_ROTATION_SPEED);
		vars->player->rotate2 = 0;
	}

	
	int i = 0;
	while (!vars->cam && i < 9)
	{
		if (vars->items[i].animate)
		{
			animation(vars,&vars->items[i]);

			break;
		}
		i++;
	}
	if (!vars->cam && i == 9)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->current.img,0, 0);
	}
	else if (vars->cam)
	{
		// mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
		 animation(vars, &vars->items[0]);
	}
	// if (vars->cam)
	// 	animation(vars, &vars->items[0]);
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
    mlx_hook(vars.win, 6, 0, mouse_move, &vars);
    mlx_hook(vars.win, 2, 0, key_press, &vars);
    mlx_hook(vars.win, 3, 0, key_realese, &vars);
	mlx_hook(vars.win, 17, 0, close_and_clear, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
    // mlx_hook(vars.win, 6, 0, mouse_movse, &vars);
    mlx_hook(vars.win, 4, 0, mouse_hook, &vars);
	mlx_loop_hook(vars.mlx, render, &vars);
	// mlx_loop_hook(vars.mlx, animation, &vars);
	// render(&vars);
    // mlx_hook(vars.win, 6, 0, mouse_hook_move, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_loop_hook(vars.mlx, movement, vars);
	mlx_loop(vars.mlx);
	free_map(map);
}
