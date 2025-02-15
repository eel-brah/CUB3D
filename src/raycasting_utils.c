/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:03:10 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/15 03:53:09 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

void wall_hit_h_calc(float angle, float *xstep, float *ystep, bool *is_up) {
  bool up;
  bool right;

  up = !(angle > 0 && angle < PI);
  right = angle < PI / 2.0f || angle > 1.5f * PI;
  *ystep = BLOCK_SIZE * ((up * -1) + (!up * 1));
  *xstep = BLOCK_SIZE / tan(angle);
  *xstep *= ((!right && *xstep > 0) * -1 + !(!right && *xstep > 0) * 1);
  *xstep *= ((right && *xstep < 0) * -1 + !(right && *xstep < 0) * 1);
  *is_up = up;
}

bool wall_hit_cord_h(t_vars *vars, t_player *player, t_hitpoint *hitpoints,
                     float angle) {
  float y;
  float x;
  t_step step;
  bool up;
  int a;

  wall_hit_h_calc(angle, &step.x, &step.y, &up);
  y = floor(player->y / BLOCK_SIZE) * BLOCK_SIZE + !up * BLOCK_SIZE;
  x = player->x + (y - player->y) / tan(angle);
  while (1) {
    a = isit_wall(vars, x, y - (up * 1));
    if (a) {
      hitpoints->h_door = (a == 2);
      hitpoints->h_x = x;
      hitpoints->h_y = y;
      return (1);
    }
    x += step.x;
    y += step.y;
  }
  return (0);
}

void wall_hit_v_calc(float angle, float *xstep, float *ystep, bool *is_right) {
  bool up;
  bool right;

  up = !(angle > 0 && angle < PI);
  right = angle < PI / 2.0f || angle > 1.5f * PI;
  *xstep = BLOCK_SIZE * ((!right * -1) + (right * 1));
  *ystep = BLOCK_SIZE * tan(angle);
  *ystep *= ((up && *ystep > 0) * -1 + !(up && *ystep > 0) * 1);
  *ystep *= ((!up && *ystep < 0) * -1 + !(!up && *ystep < 0) * 1);
  *is_right = right;
}

bool wall_hit_cord_v(t_vars *vars, t_player *player, t_hitpoint *hitpoints,
                     float angle) {
  float y;
  float x;
  t_step step;
  int a;
  bool right;

  wall_hit_v_calc(angle, &step.x, &step.y, &right);
  x = floor(player->x / BLOCK_SIZE) * BLOCK_SIZE + right * BLOCK_SIZE;
  y = player->y + (x - player->x) * tan(angle);
  while (1) {
    a = isit_wall(vars, x - (!right * 1), y);
    if (a) {
      hitpoints->v_door = (a == 2);
      hitpoints->v_x = x;
      hitpoints->v_y = y;
      return (1);
    }
    x += step.x;
    y += step.y;
  }
  return (0);
}
