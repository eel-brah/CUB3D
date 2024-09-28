/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:12 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/28 12:02:14 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_and_clear(t_vars *vars)
{
	ft_printf("\033[4;35m\033[1;95mCUB3D\033[0m \033[0;95mClosed\033[0m\n");
	free(vars->rays);
	free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	// free and close fds
	// destory images
	exit(0);
}


// bool	check_wall_dis(t_vars *vars) // door has walls on the side
// {
// 	int i;
// 	float angle;
// 	int end;
// 	int new_x;
// 	int new_y;


// 	angle = vars->player->pa + PI;
// 	i = BLOCK_SIZE;
// 	end = BLOCK_SIZE * 1.5;
// 	while (i < end)
// 	{
// 		new_x = vars->player->x + (cos(angle + vars->player->rspeed) * i);
// 		new_y = vars->player->y + (sin(angle + vars->player->rspeed) * i);
// 		if (!(new_x >= 0 && new_y >= 0 && new_x < WIDTH && new_y < HEIGHT) || (new_x >= 0 && new_y >= 0 && new_x < WIDTH && new_y < HEIGHT 
// 			&& (vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] == '1' || vars->map->map[(new_y / BLOCK_SIZE) * vars->map->cols + (new_x / BLOCK_SIZE)] == 'C')))
// 			return 0;
// 		i++;
// 	}
// 	return 1;
// }

// void print_map(t_vars *vars)
// {
// 	int i = 0;
// 	int j = 0;
// 	while(j < vars->map->rows)
// 	{
// 		i = 0;
// 		while(i < vars->map->cols)
// 		{
// 			printf("%i ", vars->map->map[j * vars->map->cols + i]);
// 			i++;
// 		}
// 		printf("\n");
// 		j++;
// 	}
// 	printf("\n");
// 	printf("\n");
// 	j = 0;
// 	while(j < vars->map->rows)
// 	{
// 		i = 0;
// 		while(i < vars->map->cols)
// 		{
// 			printf("%i ", map[j * vars->map->cols + i]);
// 			i++;
// 		}
// 		printf("\n");
// 		j++;
// 	}
// }


int render(t_vars *vars)
{
	move_rotate_player(vars);
	cast_rays(vars);
	draw_wall(vars);
	if (vars->status->mm)
		draw_minimap_player(vars);
	if (vars->player->rotate)
		player_rotation(vars, vars->player->ra);
	if (vars->player->rotate2)
	{
		player_rotation(vars, vars->player->ra);
		vars->player->rotate2 = 0;
	}
	animate(vars);
	return 0;
}

bool setup(t_vars *vars)
{
	if (!init(vars))
	{
		ft_putendl_fd("MLX faild", 2);
		free_map(vars->map);
		return false;
	}
	if (!open_texture(vars))
	{
		write(2, "Texture opening failed\n", 24);
		free_map(vars->map);
		mlx_destroy_image(vars->mlx, vars->img->img);
		mlx_destroy_window(vars->mlx, vars->win);
		// destory images
		return false;
	}
	init_ray(vars);
	init_player(vars);
	mlx_hook(vars->win, 6, 0, mouse_move, vars);
    mlx_hook(vars->win, 2, 0, key_press, vars);
    mlx_hook(vars->win, 3, 0, key_realese, vars);
	mlx_hook(vars->win, 17, 0, close_and_clear, vars);
    mlx_hook(vars->win, 4, 0, mouse_hook, vars);
	mlx_loop_hook(vars->mlx, render, vars);
	return true;
}


int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data		img;
	t_player	player;
	t_ray		ray;
	t_status	status;
	t_map		*map;

	if (argc < 2)
	{
		write(2, "Error\nUsage: ./cub3d map.cub\n", 30);
		return (-1);
	}
	map = parse(argv[1]);
	if (!map)
	{
		write(2, "Parsing Failed\n", 16);
		return (-1);
	}
	vars.img = &img;
	vars.player = &player;
	vars.ray = &ray;
	status.mm = 1;
	vars.status = &status;
	vars.map = map;
	// print_map(&vars);
	if (!setup(&vars))
		return 1;
	mlx_loop(vars.mlx);
	free_map(map);
}
