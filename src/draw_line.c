#include "../include/cub3d.h"

void	put_pixel(t_vars *vars, int x, int y, unsigned int color)
{
	char	*dst;

	t_data *data = vars->img;

	if (x >= 0 && x < vars->map->width && y >= 0 && y < vars->map->height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	absv(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

void	slop(t_line line, t_delta *delta)
{
	delta->dx = line.x2 - line.x1;
	delta->dy = line.y2 - line.y1;
	if (delta->dx >= 0)
		delta->xs = 1;
	else
		delta->xs = -1;
	if (delta->dy >= 0)
		delta->ys = 1;
	else
		delta->ys = -1;
	delta->dx = absv(delta->dx);
	delta->dy = absv(delta->dy);
}

void	draw_line_1(t_delta delta, t_line line,
			t_vars *vars, unsigned int color)
{
	int	i;

	delta.d = 2 * delta.dy - delta.dx;
	i = 0;
	while (i < delta.dx)
	{
		put_pixel(vars, line.x1, line.y1, color);
		line.x1 += delta.xs;
		if (delta.d < 0)
			delta.d += (2 * delta.dy);
		else
		{
			delta.d += 2 * (delta.dy - delta.dx);
			line.y1 += delta.ys;
		}
		i++;
	}
}

void	draw_line_2(t_delta delta, t_line line,
			t_vars *vars, unsigned int color)
{
	int	i;

	delta.d = 2 * delta.dx - delta.dy;
	i = 0;
	while (i < delta.dy)
	{
		put_pixel(vars, line.x1, line.y1, color);
		line.y1 += delta.ys;
		if (delta.d < 0)
			delta.d += (2 * delta.dx);
		else
		{
			delta.d += 2 * (delta.dx - delta.dy);
			line.x1 += delta.xs;
		}
		i++;
	}
}
void	draw_line(t_vars *vars, t_line line, unsigned int color)
{
	t_delta	delta;

	slop(line, &delta);
	if (delta.dx > delta.dy)
		draw_line_1(delta, line, vars, color);
	else
		draw_line_2(delta, line, vars, color);
}

