/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:03:07 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/15 03:53:06 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

void wall_collision_calc(t_player *player, int i, t_cols *cols) {
  if (i == 0) {
    cols->ty = floor((cols->y - player->r) / BLOCK_SIZE);
    cols->tx = floor(cols->x / BLOCK_SIZE);
  } else if (i == 1)
    cols->ty = floor((cols->y + player->r) / BLOCK_SIZE);
  else if (i == 2)
    cols->tx = floor((cols->x + player->r) / BLOCK_SIZE);
  else if (i == 3)
    cols->ty = floor(cols->y / BLOCK_SIZE);
  else if (i == 4)
    cols->tx = floor((cols->x - player->r) / BLOCK_SIZE);
  else if (i == 5)
    cols->ty = floor((cols->y - player->r) / BLOCK_SIZE);
  else if (i == 6)
    cols->tx = floor((cols->x + player->r) / BLOCK_SIZE);
  else if (i == 7) {
    cols->ty = floor((cols->y + player->r) / BLOCK_SIZE);
    cols->tx = floor((cols->x - player->r) / BLOCK_SIZE);
  }
}

bool wall_collision(t_vars *vars, float x, float y) {
  t_cols cols;
  int i;

  cols.x = x;
  cols.y = y;
  i = 0;
  while (i < 8) {
    wall_collision_calc(vars->player, i, &cols);
    if (cols.ty >= 0 && cols.ty < vars->map->rows && cols.tx >= 0 &&
        cols.tx < vars->map->cols) {
      if (vars->map->map[cols.ty * vars->map->cols + cols.tx] == '1' ||
          vars->map->map[cols.ty * vars->map->cols + cols.tx] == 'C')
        return (true);
    }
    i++;
  }
  return (false);
}

void player_movement(t_vars *vars, int dirc, int sp) {
  t_player *player;
  float xs;
  float ys;

  player = vars->player;
  xs = cos(player->pa + deg2rad(sp)) * player->steps * dirc;
  ys = sin(player->pa + deg2rad(sp)) * player->steps * dirc;
  if (!wall_collision(vars, player->x + xs, player->y + ys)) {
    player->x += xs;
    player->y += ys;
  } else if (!wall_collision(vars, player->x + xs, player->y))
    player->x += xs;
  else if (!wall_collision(vars, player->x, player->y + ys))
    player->y += ys;
}

void player_rotation(t_vars *vars, float dirc) {
  t_player *player;

  player = vars->player;
  player->pa += dirc * player->rspeed;
  if (player->pa < 0)
    player->pa += 2 * PI;
  else if (player->pa > 2 * PI)
    player->pa -= 2 * PI;
}

void move_rotate_player(t_vars *vars) {
  if (vars->keys.w_key == true || vars->keys.up_key == true)
    player_movement(vars, 1, 0);
  if (vars->keys.s_key == true || vars->keys.down_key == true)
    player_movement(vars, -1, 0);
  if (vars->keys.a_key == true)
    player_movement(vars, -1, 90);
  if (vars->keys.d_key == true)
    player_movement(vars, 1, 90);
  if (vars->keys.left_key == true)
    player_rotation(vars, -1);
  if (vars->keys.right_key == true)
    player_rotation(vars, 1);
}
