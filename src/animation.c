/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:20 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/28 12:09:27 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool    is_wall_away(t_vars *vars)
{
    if (vars->rays[vars->ray->rays_num/2].hit_dis < 50)
	{
		vars->player_animate_hit = false;
		vars->cam = false;
		vars->player->pa -= PI;
		return 0;
	}
    return 1;
}

void    cam_animation_helper(t_vars *vars)
{
    if (vars->player_animate_shield)
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
void	can_animation(int i , t_vars *vars)
{
	static unsigned int k = 1; // reset if vars->cam false

	if (!is_wall_away(vars))
        return;
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
			mlx_put_image_to_window(vars->mlx, vars->win, vars->player_cam[k++].img, 0, 0);
			if (k == 7)
			{
				k = 1;
				vars->player_animate_hit = false;
			}
		}
	}
	else 
        cam_animation_helper(vars);
}

int animation(t_vars *vars, t_item *item)
{
	static unsigned int i = 0;
	static unsigned int j = 0;
	
	if (vars->cam)
		can_animation(i, vars);
	else if(!vars->cam && i % 2 == 0)
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

void	animate(t_vars *vars)
{
	int	i;

	i = 0;
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
		animation(vars, &vars->items[0]);
}