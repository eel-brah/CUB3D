/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:39 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/15 03:52:50 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
#define CUB3D_STRUCTS_H

typedef struct s_map {
  char *no;
  char *so;
  char *we;
  char *ea;
  unsigned int f_color;
  unsigned int c_color;
  int max_col;
  int fd;
  int max_line;
  int player_x_pos;
  int player_y_pos;
  float player_face;
  int rows;
  int cols;
  int old_x;
  char *map;
  t_list *lst;
} t_map;

typedef struct s_data {
  void *img;
  char *addr;
  int bpp;
  int line_length;
  int endian;
  int width;
  int height;
} t_data;

typedef struct s_player {
  float x;
  float y;
  float r;
  float pa;
  float steps;
  float rspeed;
  bool rotate;
  bool rotate2;
  float ra;
  float mouse;
} t_player;

typedef struct s_mini {
  int x;
  int y;
  int xmax;
  int ymax;
  int player_poz_x;
  int player_poz_y;
  int height;
  int width;
} t_mini;

typedef struct s_ray {
  float fov;
  int rays_num;
  float proj_wall_dis;
} t_ray;

typedef struct s_rays {
  float x_whpoint;
  float y_whpoint;
  float hit_dis;
  float angle;
  bool is_vertical;
  bool is_door;
} t_rays;

typedef struct s_keys {
  bool left_key;
  bool right_key;
  bool up_key;
  bool down_key;
  bool s_key;
  bool w_key;
  bool a_key;
  bool d_key;
} t_keys;

typedef struct s_wall {
  float height;
  int norm;
  int top;
  int bottom;
  t_data *texture;
} t_wall;

typedef struct s_hitpoint {
  float h_x;
  float v_x;
  float h_y;
  float v_y;
  bool v_door;
  bool h_door;
} t_hitpoint;

typedef struct s_status {
  bool mm;
  bool full_map;
  bool fps;
  bool player_animate_hit;
  bool player_animate_shield;
  t_data current;
  bool cam;
  int k;
} t_status;

typedef struct s_item {
  t_data item[4];
  bool animate;
} t_item;

typedef struct s_vars {
  void *mlx;
  void *win;
  t_data *img;
  t_item items[9];
  t_data player_cam[7];
  t_data player_cam_shield;
  t_map *map;
  t_player *player;
  t_rays *rays;
  t_ray *ray;
  t_keys keys;
  t_data north;
  t_data west;
  t_data south;
  t_data east;
  t_data door;
  t_data left_left;
  t_data left_right;
  t_data right_left;
  t_data right_right;
  t_data up_up;
  t_data up_down;
  t_data down_up;
  t_data down_down;
  bool door_up;
  bool door_right;
  int nb_text;
  void **texture;
  t_status *status;
} t_vars;

typedef struct s_line {
  int x1;
  int y1;
  int x2;
  int y2;
} t_line;

typedef struct s_delta {
  int dx;
  int dy;
  int d;
  int xs;
  int ys;
} t_delta;

typedef struct s_circ {
  int xc;
  int yc;
  int x;
  int y;
} t_circ;

typedef struct s_cols {
  float x;
  float y;
  int ty;
  int tx;
} t_cols;

typedef struct s_step {
  float x;
  float y;
} t_step;

#endif
