#include "../include/cub3d.h"
void put8pixels(t_vars *vars, int xc, int yc, int x, int y)
{
    t_line line;

    line.x1 = xc+x;
    line.y1 = yc+y;
    line.x2 = xc-x;
    line.y2 = yc+y;
    draw_line(vars, line, PLAYER_COLOR);
    line.y1 = yc-y;
    line.y2 = yc-y;
    draw_line(vars, line, PLAYER_COLOR);
    line.x1 = xc+y;
    line.y1 = yc+x;
    line.x2 = xc-y;
    line.y2 = yc+x;
    draw_line(vars, line, PLAYER_COLOR);
    line.y1 = yc-x;
    line.y2 = yc-x;
    draw_line(vars, line, PLAYER_COLOR);

    put_pixel(vars, xc+x, yc+y, PLAYER_COLOR);
    put_pixel(vars, xc-x, yc+y, PLAYER_COLOR);
    put_pixel(vars, xc+x, yc-y, PLAYER_COLOR);
    put_pixel(vars, xc-x, yc-y, PLAYER_COLOR);
    put_pixel(vars, xc+y, yc+x, PLAYER_COLOR);
    put_pixel(vars, xc-y, yc+x, PLAYER_COLOR);
    put_pixel(vars, xc+y, yc-x, PLAYER_COLOR);
    put_pixel(vars, xc-y, yc-x, PLAYER_COLOR);
}

void draw_circle(t_vars *vars, int xc, int yc, int r)
{
    int x;
    int y;
    int d;

    x = 0;
    y = r;
    d = 3 - 2 * r;
    put8pixels(vars, xc, yc, x, y);
    while (y >= x)
    {
        if (d > 0)
        {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        x++;
        put8pixels(vars, xc, yc, x, y);
    }
}