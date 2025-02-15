/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_weapons2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:16:25 by amokhtar          #+#    #+#             */
/*   Updated: 2025/02/15 03:52:46 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

bool load_diamond(t_vars *vars) {
  if (!mlx_xpm(vars, &vars->items[5].item[0], "images/6-diamond/1.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[5].item[0].img;
  if (!mlx_xpm(vars, &vars->items[5].item[1], "images/6-diamond/2.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[5].item[1].img;
  if (!mlx_xpm(vars, &vars->items[5].item[2], "images/6-diamond/3.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[5].item[2].img;
  if (!mlx_xpm(vars, &vars->items[5].item[3], "images/6-diamond/4.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[5].item[3].img;
  return (true);
}

bool load_apple(t_vars *vars) {
  if (!mlx_xpm(vars, &vars->items[6].item[0], "images/7-apple/1.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[6].item[0].img;
  if (!mlx_xpm(vars, &vars->items[6].item[1], "images/7-apple/2.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[6].item[1].img;
  if (!mlx_xpm(vars, &vars->items[6].item[2], "images/7-apple/3.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[6].item[2].img;
  if (!mlx_xpm(vars, &vars->items[6].item[3], "images/7-apple/4.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[6].item[3].img;
  return (true);
}

bool load_potion(t_vars *vars) {
  if (!mlx_xpm(vars, &vars->items[7].item[0], "images/8-potion/1.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[7].item[0].img;
  if (!mlx_xpm(vars, &vars->items[7].item[1], "images/8-potion/2.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[7].item[1].img;
  if (!mlx_xpm(vars, &vars->items[7].item[2], "images/8-potion/3.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[7].item[2].img;
  if (!mlx_xpm(vars, &vars->items[7].item[3], "images/8-potion/4.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[7].item[3].img;
  return (true);
}

bool load_food(t_vars *vars) {
  if (!mlx_xpm(vars, &vars->items[8].item[0], "images/9-food/1.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[8].item[0].img;
  if (!mlx_xpm(vars, &vars->items[8].item[1], "images/9-food/2.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[8].item[1].img;
  if (!mlx_xpm(vars, &vars->items[8].item[2], "images/9-food/3.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[8].item[2].img;
  if (!mlx_xpm(vars, &vars->items[8].item[3], "images/9-food/4.xpm"))
    return (false);
  vars->texture[vars->nb_text++] = vars->items[8].item[3].img;
  return (true);
}

void load_items(t_vars *vars) {
  for (int j = 0; j < 9; j++) {
    for (int i = 0; i < 4; i++)
      mlx_get_data(&vars->items[j].item[i]);
  }
}
bool load_weapons_player(t_vars *vars) {
  if (!load_sword(vars))
    return (false);
  if (!load_axe(vars))
    return (false);
  if (!load_pickaxe(vars))
    return (false);
  if (!load_bow(vars))
    return (false);
  if (!load_totem(vars))
    return (false);
  if (!load_diamond(vars))
    return (false);
  if (!load_apple(vars))
    return (false);
  if (!load_potion(vars))
    return (false);
  if (!load_food(vars))
    return (false);
  if (!load_player(vars))
    return (false);

  load_items(vars);
  return (true);
}
