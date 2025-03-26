/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:11:56 by eel-brah          #+#    #+#             */
/*   Updated: 2025/03/26 08:51:53 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "cub3d_defines.h"
#include "cub3d_libs.h"
#include "cub3d_structs.h"

// Raycasting
void init_ray(t_vars *vars);
void cast_rays(t_vars *vars);
float distance(float x1, float y1, float x2, float y2);
bool wall_hit_cord_v(t_vars *vars, t_player *player, t_hitpoint *hitpoints,
                     float angle);
bool wall_hit_cord_h(t_vars *vars, t_player *player, t_hitpoint *hitpoints,
                     float angle);
int isit_wall(t_vars *vars, float x, float y);

// Walls
void draw_wall(t_vars *vars);
void wall_hit_cord(t_vars *vars, t_player *player, t_rays *ray, float angle);
void open_close_door(t_vars *vars);
t_data *get_texture(t_vars *vars, int i);
int door_check(t_vars *vars, float tx, float ty);

// Player
void init_player(t_vars *vars);
void player_movement(t_vars *vars, int dirc, int sp);
void player_rotation(t_vars *vars, float dirc);
void move_rotate_player(t_vars *vars);

// Drawing
int render(t_vars *vars);
int animation(t_vars *vars, t_item *item);
void animate(t_vars *vars);

// Minimap
void draw_minimap_player(t_vars *vars);
void draw_minimap(t_vars *vars, t_mini *minimap, int height, int width);
void draw_block(t_vars *vars, int x, int y, char c);
void player(t_vars *vars, t_mini *minimap);
void draw_border(t_vars *vars, int height, int width);
void draw_mm_background(int height, int width, t_vars *vars);
void draw_block(t_vars *vars, int x, int y, char c);
void fix_minimap_y(t_vars *vars, t_mini *minimap);
void fix_minimap_x(t_vars *vars, t_mini *minimap);
int get_block_x(float x);
int get_block_y(float y);

// Utils
void put_pixel(t_vars *vars, int x, int y, unsigned int color);
void draw_line(t_vars *vars, t_line line, unsigned int color);
void draw_player(t_vars *vars, int xc, int yc, int r);
float deg2rad(float deg);
unsigned int create_trgb(int t, int r, int g, int b);
unsigned int get_color_from_img(t_data *data, int x, int y);

// Init & Close
bool init(t_vars *vars);
int clear_and_close(t_vars *vars);

// Inputs
int key_realese(int keysym, t_vars *vars);
int key_press(int keysym, t_vars *vars);
int mouse_move(int x, int y, t_vars *vars);
int mouse_hook(int b, int x, int y, t_vars *vars);

// Parsing
unsigned int get_color(char **spl);
bool is_all_num(char **arr);
int len_2d(char **sp);
bool check_line(char *line);
bool fill_wall(t_map *map, char *line, int *count);
void fill_color(t_map *map, char *line);
void free_map(t_map *map);
bool fill_map(t_map *map, int fd, bool flag, int count);
void *fill_array(t_map *map, int player);
bool check_walls(t_map *map, char *errormsg, int line);
void free_2d(char **tmp);
void free_linked(t_list *lst);
int ft_atoi_over(const char *str);
void exit_err(t_map *map, char *tmp, char *line, char *msg);
t_map *parse(char *file);
bool load_images(t_vars *vars);
bool load_door(t_vars *vars);
bool load_weapons_player(t_vars *vars);
bool load_sword(t_vars *vars);
bool load_axe(t_vars *vars);
bool load_pickaxe(t_vars *vars);
bool load_bow(t_vars *vars);
bool load_totem(t_vars *vars);
bool load_door(t_vars *vars);
bool load_player(t_vars *vars);
void mlx_get_data(t_data *data);
bool mlx_xpm(t_vars *var, t_data *data, char *s);
void free_texture(t_vars *vars, void **data);
bool parse_map(int argc, char **argv, t_vars *vars);

// menu
void	draw_menu(t_vars *vars);
#endif
