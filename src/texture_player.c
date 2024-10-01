/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:21:53 by amokhtar          #+#    #+#             */
/*   Updated: 2024/10/01 18:31:56 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	mlx_xpm(t_vars *var, t_data *data, char *s)
{
	data->img = mlx_xpm_file_to_image(var->mlx, s, &data->width, &data->height);
	if (!data->img)
		return (false);
	return (true);
}

void	mlx_get_data(t_data *data)
{
	data->addr = mlx_get_data_addr(data->img, \
	&data->bpp, &data->line_length, &data->endian);
}

bool	load_player1(t_vars *vars)
{
	if (!mlx_xpm(vars, &vars->player_cam[0], "images/cam/shield1.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[0].img;
	if (!mlx_xpm(vars, &vars->player_cam[1], "images/cam/hit1.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[1].img;
	if (!mlx_xpm(vars, &vars->player_cam[2], "images/cam/hit2.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[2].img;
	if (!mlx_xpm(vars, &vars->player_cam[3], "images/cam/hit3.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[3].img;
	return (true);
}

bool	load_player(t_vars *vars)
{
	if (!load_player1(vars))
		return (false);
	if (!mlx_xpm(vars, &vars->player_cam[4], "images/cam/hit4.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[4].img;
	if (!mlx_xpm(vars, &vars->player_cam[5], "images/cam/hit5.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[5].img;
	if (!mlx_xpm(vars, &vars->player_cam[6], "images/cam/hit6.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[6].img;
	if (!mlx_xpm(vars, &vars->player_cam_shield, "images/cam/shield2.xpm"))
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam_shield.img;
	return (true);
}

void	free_texture(t_vars *vars, void **data)
{
	int	i;

	i = 0;
	while (data && data[i])
	{
		mlx_destroy_image(vars->mlx, data[i]);
		i++;
	}
	free(data);
}
