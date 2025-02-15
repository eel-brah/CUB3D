/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:20 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/15 03:50:16 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

bool is_wall_away(t_vars *vars) {
  if (vars->rays[vars->ray->rays_num / 2].hit_dis < 80) {
    vars->status->player_animate_hit = false;
    vars->status->cam = false;
    vars->player->pa -= PI;
    return (0);
  }
  return (1);
}

void combine_images(char *bg_data, char *fg_data, int width, int height) {
  int *bg = (int *)bg_data;
  int *fg = (int *)fg_data;
  int len = width * height;

  for (int i = 0; i < len; i++) {
    if (fg[i] != 0xFF000000)
      bg[i] = fg[i];
  }
}
void cam_animation_helper(t_vars *vars) {
  if (vars->status->player_animate_shield) {
    combine_images(vars->img->addr, vars->player_cam_shield.addr, WIDTH,
                   HEIGHT);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
  } else {
    combine_images(vars->img->addr, vars->player_cam[0].addr, WIDTH, HEIGHT);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
  }
}

void cam_animation(int i, t_vars *vars) {
  if (!is_wall_away(vars))
    return;
  if (vars->status->player_animate_hit && vars->status->player_animate_shield) {
    vars->status->player_animate_hit = false;
    vars->status->player_animate_shield = false;
  } else if (vars->status->player_animate_hit) {
    if (i % 3 == 0) {
      combine_images(vars->img->addr, vars->player_cam[vars->status->k++].addr,
                     WIDTH, HEIGHT);
      mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
      if (vars->status->k == 7) {
        vars->status->k = 1;
        vars->status->player_animate_hit = false;
      }
    }
  } else
    cam_animation_helper(vars);
}

int animation(t_vars *vars, t_item *item) {
  static unsigned int i = 0;
  static unsigned int j = 0;

  if (vars->status->cam)
    cam_animation(i, vars);
  else if (i % 2 == 0) {

    combine_images(vars->img->addr, item->item[j].addr, WIDTH, HEIGHT);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    if (j == 3) {
      item->animate = false;
      vars->status->current = item->item[j];
      j = 0;
      i = 0;
      return (1);
    }
    j++;
  }
  i++;
  if (i == 1000000000)
    i = 0;
  return (1);
}
void animate(t_vars *vars) {
  int i;

  i = 0;
  while (!vars->status->cam && i < 9) {
    if (vars->items[i].animate) {
      animation(vars, &vars->items[i]);
      break;
    }
    i++;
  }
  if (!vars->status->cam && i == 9) {
    combine_images(vars->img->addr, vars->status->current.addr, WIDTH, HEIGHT);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
  } else if (vars->status->cam)
    animation(vars, &vars->items[0]);
}
