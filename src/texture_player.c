/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:21:53 by amokhtar          #+#    #+#             */
/*   Updated: 2024/09/30 12:22:12 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_player1(t_vars *vars)
{
	vars->player_cam[0].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/shield1.xpm" ,&vars->player_cam[0].width, &vars->player_cam[0].height);
	if (!vars->player_cam[0].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[0].img;
	vars->player_cam[1].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit1.xpm" ,&vars->player_cam[1].width, &vars->player_cam[1].height);
	if (!vars->player_cam[1].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[1].img;
	vars->player_cam[2].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit2.xpm" ,&vars->player_cam[2].width, &vars->player_cam[2].height);
	if (!vars->player_cam[2].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[2].img;
	vars->player_cam[3].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit3.xpm" ,&vars->player_cam[3].width, &vars->player_cam[3].height);
	if (!vars->player_cam[3].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[3].img;
	return (true);
}
bool	load_player(t_vars *vars)
{
	if (!load_player1(vars))
		return (false);
	vars->player_cam[4].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit4.xpm" ,&vars->player_cam[4].width, &vars->player_cam[4].height);
	if (!vars->player_cam[4].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[4].img;
	vars->player_cam[5].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit5.xpm" ,&vars->player_cam[5].width, &vars->player_cam[5].height);
	if (!vars->player_cam[5].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[5].img;
	vars->player_cam[6].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit6.xpm" ,&vars->player_cam[6].width, &vars->player_cam[6].height);
	if (!vars->player_cam[6].img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam[6].img;
	vars->player_cam_shield.img = mlx_xpm_file_to_image(vars->mlx, "images/cam/shield2.xpm" ,&vars->player_cam_shield.width, &vars->player_cam_shield.height);
	if (!vars->player_cam_shield.img)
		return (false);
	vars->texture[vars->nb_text++] = vars->player_cam_shield.img;
	return (true);
}