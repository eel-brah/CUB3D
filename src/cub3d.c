/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:02:12 by eel-brah          #+#    #+#             */
/*   Updated: 2025/03/26 09:33:29 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

int clear_and_close(t_vars *vars) {
  ft_printf("\033[4;35m\033[1;95mCUB3D\033[0m \033[0;95mClosed\033[0m\n");
  free(vars->rays);
  free_texture(vars, vars->texture);
  free_map(vars->map);
  mlx_destroy_image(vars->mlx, vars->img->img);
  mlx_destroy_window(vars->mlx, vars->win);
  exit(0);
}

double calc_fps() {
  static double lastTime;
  struct timeval currentTV;
  double currentTime;
  double deltaTime;
  double fps = 0;

  gettimeofday(&currentTV, NULL);
  currentTime = currentTV.tv_sec * 1000.0 + currentTV.tv_usec / 1000.0;

  if (lastTime != 0) {
    deltaTime = (currentTime - lastTime) / 1000.0;
    fps = 1.0 / deltaTime;
    // printf("FPS: %.2f\r", fps);
    // fflush(stdout);
  }
  lastTime = currentTime;
  return fps;
}

void drow_fps(t_vars *vars, double fps) {
  char fps_str[32];
  int text_width;
  int box_width;
  int box_height;

  snprintf(fps_str, sizeof(fps_str), "FPS: %.1f", fps);
  text_width = ft_strlen(fps_str) * 5;
  box_width = text_width + 20;
  box_height = 25;

  int x = 5;
  int y = HEIGHT - box_height - 10;

  for (int i = 0; i < box_height; i++) {
    for (int j = 0; j < box_width; j++) {
      put_pixel(vars, x + j, y + i, 0);
    }
  }

  mlx_string_put(vars->mlx, vars->win, x + (box_width - text_width) / 2 - 4,
                 y + box_height / 2 + 2, 0xFFFFFF, fps_str);
}

int render(t_vars *vars) {
  double fps;

  if (vars->status->fps)
    fps = calc_fps();

  move_rotate_player(vars);
  cast_rays(vars);
  draw_wall(vars);
  if (vars->status->mm)
    draw_minimap_player(vars);
  if (vars->player->rotate)
    player_rotation(vars, vars->player->ra);
  animate(vars);

  if (IS_LINUX)
    printf("JJJJ\n");
  if (IS_LINUX) {
    if (vars->status->fps)
      drow_fps(vars, fps);
    draw_menu(vars);
  }
  return (1);
}

bool setup(t_vars *vars) {
  ft_printf("\033[4;35m\033[1;95mCUB3D\033[0m \033[0;95mLoading...\033[0m\n");
  if (!init(vars)) {
    ft_putendl_fd("MLX faild", 2);
    free_map(vars->map);
    return (false);
  }
  if (!load_images(vars)) {
    write(2, "Texture opening failed\n", 24);
    clear_and_close(vars);
    return (false);
  }
  init_ray(vars);
  init_player(vars);
  mlx_hook(vars->win, 2, 1L << 0, key_press, vars);
  mlx_hook(vars->win, 3, 1L << 1, key_realese, vars);
  mlx_hook(vars->win, 4, 1L << 2, mouse_hook, vars);
  mlx_hook(vars->win, 6, 1L << 6, mouse_move, vars);
  mlx_hook(vars->win, 17, 1L << 17, clear_and_close, vars);
  mlx_loop_hook(vars->mlx, render, vars);
  return (true);
}

bool parse_map(int argc, char **argv, t_vars *vars) {
  t_map *map;

  if (argc == 2 && ft_strncmp(argv[1], "-h", 3) == 0) {
    write(1, "Usage: ./cub3d map.cub\n", 23);
    write(1, "Options:\n", 9);
    write(1, "  -h          Display help\n", 27);
    write(1, "  map.cub     Path to the map file\n", 35);
    write(1, "\nControls:\n", 11);
    write(1, "  Move Forward      W\n", 22);
    write(1, "  Move Backward     S\n", 22);
    write(1, "  Strafe Left       A\n", 22);
    write(1, "  Strafe Right      D\n", 22);
    write(1, "  Look Left/Right   Arrow Keys / Mouse\n", 39);
    write(1, "  Open/Close Doors  Space\n", 26);
    write(1, "  Show/Hide Minimap M\n", 22);
    write(1, "  Show full Minimap P\n", 22);
    write(1, "  Show/Hide FPS     F\n", 22);
    write(1, "  Cam View          CTRL + Mouse Clicks\n", 40);
    write(1, "  Toggle Menu       Tab\n", 24);
    write(1, "  Switch Items      Mouse Click / Scroll\n", 41);
    write(1, "  Enable/Disable Mouse Scroll Click\n", 36);
    return (0);
  }

  if (argc != 2) {
    write(2, "Usage: ./cub3d map.cub\n", 23);
    return (0);
  }

  map = parse(argv[1]);
  if (!map) {
    write(2, "Parsing Failed\n", 16);
    return (0);
  }

  vars->map = map;
  return (1);
}

int main(int argc, char **argv) {
  t_vars vars;
  t_data img;
  t_player player;
  t_ray ray;
  t_status status;

  if (!parse_map(argc, argv, &vars))
    return (1);
  vars.img = &img;
  vars.player = &player;
  vars.ray = &ray;
  vars.status = &status;
  if (!setup(&vars))
    return (1);
  mlx_loop(vars.mlx);
  clear_and_close(&vars);
}
