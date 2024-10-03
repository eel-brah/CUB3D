/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_border.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:52:17 by eel-brah          #+#    #+#             */
/*   Updated: 2024/10/02 12:51:15 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_border_lines_1(t_vars *vars, t_line line)
{
	draw_line(vars, line, BORDER_COLOR);
	line.y1 += 1;
	line.y2 += 1;
	draw_line(vars, line, BORDER_COLOR);
}

void	draw_border_lines_2(t_vars *vars, t_line line)
{
	draw_line(vars, line, BORDER_COLOR);
	line.x1 += 1;
	line.x2 += 1;
	draw_line(vars, line, BORDER_COLOR);
}

void	draw_border(t_vars *vars, int height, int width)
{
	t_line	line;
	float	k;

	k = BLOCK_SIZE * MMSF;
	line.x1 = MMSHIFT;
	line.x2 = width * k + MMSHIFT;
	line.y1 = MMSHIFT;
	line.y2 = MMSHIFT;
	draw_border_lines_1(vars, line);
	line.y1 = height * k + MMSHIFT;
	line.y2 = height * k + MMSHIFT;
	draw_border_lines_1(vars, line);
	line.x1 = width * k + MMSHIFT;
	line.y1 = MMSHIFT;
	line.y2 = height * k + MMSHIFT + 2;
	draw_border_lines_2(vars, line);
	line.x1 = MMSHIFT;
	line.x2 = MMSHIFT;
	draw_border_lines_2(vars, line);
}

void	draw_mm_background(int height, int width, t_vars *vars)
{
	int	y;
	int	x;
	int	my;
	int	mx;

	y = MMSHIFT;
	my = height * BLOCK_SIZE * MMSF + MMSHIFT;
	mx = width * BLOCK_SIZE * MMSF + MMSHIFT;
	while (y < my)
	{
		x = MMSHIFT;
		while (x < mx)
			put_pixel(vars, x++, y, MMOC);
		y++;
	}
}
