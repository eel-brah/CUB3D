/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:35 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/15 03:53:00 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

void draw_dirc_line(t_vars *vars, float x, float y, t_player *player) {
  t_line line;

  line.x1 = x * MMSF + MMSHIFT;
  line.y1 = y * MMSF + MMSHIFT;
  line.x2 = (x + cos(player->pa) * player->r) * MMSF + MMSHIFT;
  line.y2 = (y + sin(player->pa) * player->r) * MMSF + MMSHIFT;
  draw_line(vars, line, DIRC_LINE);
}

void player(t_vars *vars, t_mini *minimap) {
  float mpx;
  float mpy;
  float mpr;

  mpx = vars->player->x - minimap->x * BLOCK_SIZE;
  mpy = vars->player->y - minimap->y * BLOCK_SIZE;
  mpr = vars->player->r;
  draw_player(vars, mpx * MMSF + MMSHIFT, mpy * MMSF + MMSHIFT, mpr * MMSF);
  draw_dirc_line(vars, mpx, mpy, vars->player);
}

void draw_minimap(t_vars *vars, t_mini *minimap, int height, int width) {
  int y;
  int x;

  if (minimap->height < height || minimap->width < width)
    draw_mm_background(height, width, vars);
  y = minimap->y;
  while (y < minimap->ymax) {
    fix_minimap_y(vars, minimap);
    x = minimap->x;
    while (x < minimap->xmax) {
      fix_minimap_x(vars, minimap);
      draw_block(vars, get_block_x(x - minimap->x), get_block_y(y - minimap->y),
                 vars->map->map[y * vars->map->cols + x]);
      x++;
    }
    y++;
  }
}

void calc_map_pos(t_vars *vars, t_mini *minimap, int hight, int width) {
  minimap->player_poz_x = floor(vars->player->x / BLOCK_SIZE);
  minimap->player_poz_y = floor(vars->player->y / BLOCK_SIZE);
  minimap->y = (minimap->player_poz_y - (minimap->height / 2)) *
               (minimap->height >= hight);
  minimap->y = (minimap->y > 0) * minimap->y;
  minimap->ymax =
      minimap->player_poz_y + (minimap->height / 2) + (minimap->height % 2) * 1;
  minimap->ymax = (minimap->ymax < vars->map->rows) * minimap->ymax +
                  !(minimap->ymax < vars->map->rows) * (vars->map->rows);
  minimap->x = (minimap->player_poz_x - (minimap->width / 2)) *
               (minimap->width >= width);
  minimap->x = (minimap->x > 0) * minimap->x;
  minimap->xmax =
      minimap->player_poz_x + (minimap->width / 2) + (minimap->width % 2) * 1;
  minimap->xmax = (minimap->xmax < vars->map->cols) * minimap->xmax +
                  !(minimap->xmax < vars->map->cols) * (vars->map->cols);
}

void draw_minimap_player(t_vars *vars) {
  t_mini minimap;
  int hight;
  int width;

  hight = (vars->status->full_map) * vars->map->rows +
          !(vars->status->full_map) * MMSIZE;
  width = (vars->status->full_map) * vars->map->cols +
          !(vars->status->full_map) * MMSIZE;
  minimap.height = (vars->map->rows >= hight) * hight +
                   !(vars->map->rows >= hight) * vars->map->rows;
  minimap.width = (vars->map->cols >= width) * width +
                  !(vars->map->cols >= width) * vars->map->cols;
  calc_map_pos(vars, &minimap, hight, width);
  fix_minimap_y(vars, &minimap);
  fix_minimap_x(vars, &minimap);
  draw_minimap(vars, &minimap, hight, width);
  player(vars, &minimap);
  draw_border(vars, hight, width);
}
