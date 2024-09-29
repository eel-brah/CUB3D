/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:50:43 by eel-brah          #+#    #+#             */
/*   Updated: 2024/09/29 11:56:52 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_block(t_vars *vars, int x, int y, char c)
{
	int				bx;
	int				mx;
	int				my;
	unsigned int	color;

	if (c == '0')
		color = vars->map->f_color;
	else if (c == '1')
		color = 0;
	else if (c == 'C')
		color = DRCC;
	else if (c == 'O')
		color = DROC;
	mx = x + BLOCK_SIZE * MMSF;
	my = y + BLOCK_SIZE * MMSF;
	while (y <= my)
	{
		bx = x;
		while (bx <= mx)
		{
			put_pixel(vars, bx, y, color);
			bx++;
		}
		y++;
	}
}

void	fix_minimap_y(t_vars *vars, t_mini *minimap)
{
	if (minimap->ymax - minimap->y < minimap->height)
	{
		if (minimap->player_poz_y > (vars->map->rows / 2))
			minimap->y = minimap->ymax - minimap->height;
		else
			minimap->ymax = minimap->y + minimap->height;
	}
}

void	fix_minimap_x(t_vars *vars, t_mini *minimap)
{
	if (minimap->xmax - minimap->x < minimap->width)
	{
		if (minimap->player_poz_x > (vars->map->cols / 2))
			minimap->x = minimap->xmax - minimap->width;
		else
			minimap->xmax = minimap->x + minimap->width;
	}
}

int	get_block_x(float x)
{
	return ((x * BLOCK_SIZE * MMSF) + MMSHIFT);
}

int	get_block_y(float y)
{
	return ((y * BLOCK_SIZE * MMSF) + MMSHIFT);
}
