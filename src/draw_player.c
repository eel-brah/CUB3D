/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:50:38 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/15 03:52:54 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

void fill_circ(t_vars *vars, t_circ *circ) {
  t_line line;

  line.x1 = circ->xc + circ->x;
  line.y1 = circ->yc + circ->y;
  line.x2 = circ->xc - circ->x;
  line.y2 = circ->yc + circ->y;
  draw_line(vars, line, PLAYER_COLOR);
  line.y1 = circ->yc - circ->y;
  line.y2 = circ->yc - circ->y;
  draw_line(vars, line, PLAYER_COLOR);
  line.x1 = circ->xc + circ->y;
  line.y1 = circ->yc + circ->x;
  line.x2 = circ->xc - circ->y;
  line.y2 = circ->yc + circ->x;
  draw_line(vars, line, PLAYER_COLOR);
  line.y1 = circ->yc - circ->x;
  line.y2 = circ->yc - circ->x;
  draw_line(vars, line, PLAYER_COLOR);
}

void put_cpixels(t_vars *vars, t_circ *circ) {
  put_pixel(vars, circ->xc + circ->x, circ->yc + circ->y, PLAYER_COLOR);
  put_pixel(vars, circ->xc - circ->x, circ->yc + circ->y, PLAYER_COLOR);
  put_pixel(vars, circ->xc + circ->x, circ->yc - circ->y, PLAYER_COLOR);
  put_pixel(vars, circ->xc - circ->x, circ->yc - circ->y, PLAYER_COLOR);
  put_pixel(vars, circ->xc + circ->y, circ->yc + circ->x, PLAYER_COLOR);
  put_pixel(vars, circ->xc - circ->y, circ->yc + circ->x, PLAYER_COLOR);
  put_pixel(vars, circ->xc + circ->y, circ->yc - circ->x, PLAYER_COLOR);
  put_pixel(vars, circ->xc - circ->y, circ->yc - circ->x, PLAYER_COLOR);
  fill_circ(vars, circ);
}

void draw_player(t_vars *vars, int xc, int yc, int r) {
  t_circ circ;
  int d;

  circ.xc = xc;
  circ.yc = yc;
  circ.x = 0;
  circ.y = r;
  d = 3 - 2 * r;
  put_cpixels(vars, &circ);
  while (circ.y >= circ.x) {
    if (d > 0) {
      circ.y--;
      d = d + 4 * (circ.x - circ.y) + 10;
    } else
      d = d + 4 * circ.x + 6;
    circ.x++;
    put_cpixels(vars, &circ);
  }
}
