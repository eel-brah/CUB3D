/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:03:27 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/07 17:08:15 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	deg2rad(float deg)
{
	return (deg * (PI / 180.0f));
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_pixel(t_vars *vars, int x, int y, unsigned int color)
{
	char	*dst;
	t_data	*data;

	data = vars->img;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_color_from_img(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}
