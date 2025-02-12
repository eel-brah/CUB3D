/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:12 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/10 14:16:40 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

int	clear_and_close(t_vars *vars)
{
	ft_printf("\033[4;35m\033[1;95mCUB3D\033[0m \033[0;95mClosed\033[0m\n");
	free(vars->rays);
	free_texture(vars, vars->texture);
	free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	render(t_vars *vars)
{
	move_rotate_player(vars);
	cast_rays(vars);
	draw_wall(vars);
	if (vars->status->mm)
		draw_minimap_player(vars);
	if (vars->player->rotate)
		player_rotation(vars, vars->player->ra);
	animate(vars);
	return (1);
}

bool	setup(t_vars *vars)
{
	ft_printf("\033[4;35m\033[1;95mCUB3D\033[0m \033[0;95mLoading...\033[0m\n");
	if (!init(vars))
	{
		ft_putendl_fd("MLX faild", 2);
		free_map(vars->map);
		return (false);
	}
	if (!load_images(vars))
	{
		write(2, "Texture opening failed\n", 24);
		clear_and_close(vars);
		return (false);
	}
	init_ray(vars);
	init_player(vars);
	mlx_hook(vars->win, 2, 1L<<0, key_press, vars);
	mlx_hook(vars->win, 3, 1L<<1, key_realese, vars);
	mlx_hook(vars->win, 4, 1L<<2, mouse_hook, vars);
	mlx_hook(vars->win, 6, 1L<<6, mouse_move, vars);
	mlx_hook(vars->win, 17, 1L<<17, clear_and_close, vars);
	mlx_loop_hook(vars->mlx, render, vars);
	return (true);
}

bool	parse_map(int argc, char **argv, t_vars *vars)
{
	t_map	*map;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3d map.cub\n", 30);
		return (0);
	}
	map = parse(argv[1]);
	if (!map)
	{
		write(2, "Parsing Failed\n", 16);
		return (0);
	}
	vars->map = map;
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data		img;
	t_player	player;
	t_ray		ray;
	t_status	status;

	if (!parse_map(argc, argv, &vars))
		return (1);
	vars.img = &img;
	vars.player = &player;
	vars.ray = &ray;
	vars.status = &status;
	if (!setup(&vars))
		return (1);
	mlx_loop(vars.mlx);
	clear_and_close(&vars);
}
