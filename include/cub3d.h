#include <mlx.h>
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <fcntl.h>
#include <float.h>
#include "../libft/include/libft.h"
#include "get_next_line.h"

# include <unistd.h>
# include <stdint.h>

#define PI 3.1415926535

#define BACKGROUND 0x00383c40
#define PLAYER_COLOR 0x00FFFF00
#define DIRC_LINE 0x0000FF00
#define PLAYER_SIZE 14
#define PLAYER_SPEED 3
#define PLAYER_RSPEED 2
#define DOOR_OPEN 1

#define MMC 0x00EAE4DD
#define DRCC 0x00A04747
#define DROC 0x00D8A25E
#define WALL_COLOR 0x00181C14
#define SEALING_COLOR 0x00ECDFCC
#define FLOOR_COLOR 0x003C3D37
#define BORDER_COLOR 0x00295F98

#define MAX_ROTATION_SPEED 20.0f
#define SENSITIVITY 0.001f

#define HEIGHT 1080
#define WIDTH 1920
#define BLOCK_SIZE 50
#define MMSF 0.3
#define MMSIZE 12
#define MMSHIFT 10

# define ESC_KEY 53
# define UP_KEY 126
# define DOWN_KEY 125
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_W_KEY 13
# define DOWN_S_KEY 1
# define RIGHT_D_KEY 2
# define LEFT_A_KEY 0

typedef struct s_map
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	unsigned int		f_color;
	unsigned int		c_color;
	int					max_col;
	int					max_line;
	int					player_x_pos;
	int					player_y_pos;
	float				player_face;
	int					rows;
	int					cols;
	int					old_x;
	char				*map;
	t_list				*lst;
}	t_map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;
typedef struct s_player
{
	float	x;
	float	y;
	float	r;
	float	pa;
	float	steps;
	float	rspeed;
	bool	rotate;
	bool	rotate2;
	float		ra;
	float		mouse;
}	t_player;
typedef	struct s_mini
{
	int x;
	int y;
	int xmax;
	int ymax;
	int player_poz_x;
	int player_poz_y;
	int	height;
	int	width;
}	t_mini;
typedef struct s_ray
{
	float	fov;
	int		rays_num;
	float	proj_wall_dis;
}	t_ray;
typedef struct s_rays
{
	float	x_whpoint;
	float	y_whpoint;
	float	hit_dis;
	float	angle;
	bool	is_vertical;
	bool	is_door;
}	t_rays;

typedef struct s_keys
{
	bool	left_key;
	bool	right_key;
	bool	up_key;
	bool	down_key;
	bool	s_key;
	bool	w_key;
	bool	a_key;
	bool	d_key;
}	t_keys;

typedef struct	s_wall
{
	float	height;
	int		top;
	int		bottom;
	t_data	*texture;
}	t_wall;

typedef struct s_hitpoint
{
    float	 h_x;
    float 	v_x;
    float 	h_y;
    float 	v_y;
	bool	v_door;
	bool	h_door;
}   t_hitpoint;

typedef struct s_status
{
	bool	mm;
	bool	full_map;
	bool	player_animate_hit;
	bool	player_animate_shield;
	t_data	current;
	bool	cam;
	int		k;
}	t_status;

typedef	struct s_item
{

	t_data	item[4];
	bool	animate;
}	t_item;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	t_item	items[9];
	t_data	player_cam[7];
	t_data	player_cam_shield;
	t_map	*map;
	t_player *player;
	t_rays	*rays;
	t_ray	*ray;
	t_keys	keys;

	t_data	north;
	t_data	west;
	t_data	south;
	t_data	east;

	t_data	door;
	t_data	left_left;
	t_data	left_right;
	t_data	right_left;
	t_data	right_right;
	t_data	up_up;
	t_data	up_down;
	t_data	down_up;
	t_data	down_down;
	
	int		nb_text;
	void	**texture;
	t_status *status;
}	t_vars;

typedef struct s_line
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
}	t_line;

typedef struct s_delta
{
	int	dx;
	int	dy;
	int	d;
	int	xs;
	int	ys;
}	t_delta;

typedef struct	s_circ
{
	int	xc;
	int	yc;
	int	x;
	int	y;
}	t_circ;

typedef	struct s_cols
{
	float	x;
	float	y;
	int		ty;
	int		tx;
}	t_cols;

typedef	struct s_step
{
	float	x;
	float	y;
}	t_step;

// Functions

bool	init(t_vars	*vars);
int		clear_and_close(t_vars *vars);
int render(t_vars *vars);


// Utils
void			put_pixel(t_vars *vars, int x, int y, unsigned int color);
void			draw_line(t_vars *vars, t_line line, unsigned int color);
void			draw_circle(t_vars *vars, int xc, int yc, int r);
float			deg2rad(float deg);
unsigned int	create_trgb(int t, int r, int g, int b);
unsigned int	get_color_from_img(t_data *data, int x, int y);

// Minimap
void 	draw_minimap_player(t_vars *vars);
void    draw_minimap(t_vars *vars, t_mini *minimap, int height, int width);
void	draw_block(t_vars *vars, int x, int y, char c);
void	draw_player(t_vars *vars, t_mini *minimap);
void	draw_border(t_vars *vars, int height, int width);
void	draw_mm_background(int height, int width, t_vars *vars);
void	draw_block(t_vars *vars, int x, int y, char c);
void	fix_minimap_y(t_vars *vars, t_mini *minimap);
void	fix_minimap_x(t_vars *vars, t_mini *minimap);
int		get_block_x(float x);
int		get_block_y(float y);

// Player
void	init_player(t_vars *vars);
void	player_movement(t_vars *vars, int dirc, int sp);
void	player_rotation(t_vars *vars, float dirc);
void	move_rotate_player(t_vars *vars);

int		isit_wall(t_vars *vars, float x, float y);

// Inputs
int	key_realese(int keysym, t_vars *vars);
int	key_press(int keysym, t_vars *vars);
int mouse_move(int x, int y, t_vars *vars);
int mouse_hook(int b, int x, int y, t_vars *vars);

// Raycasting
void	init_ray(t_vars *vars);
void	cast_rays(t_vars *vars);
float	distance(float x1, float y1, float x2, float y2);
// void	draw_rays(t_vars *vars);
bool	wall_hit_cord_v(t_vars *vars, t_player *player, t_hitpoint *hitpoints, float angle);
bool	wall_hit_cord_h(t_vars *vars, t_player *player, t_hitpoint *hitpoints, float angle);


// Walls
void 	draw_wall(t_vars *vars);
void	wall_hit_cord(t_vars *vars, t_player *player, t_rays *ray, float angle);
void	open_close_door(t_vars *vars);
t_data	*get_texture(t_vars *vars, int i);
int	door_check(t_vars *vars, float tx, float ty);

// Parsing
unsigned int	get_color(char **spl);
bool			is_all_num(char **arr);
int				len_2d(char **sp);
bool			check_line(char *line);
bool			fill_wall(t_map *map, char *line, int *count);
void			fill_color(t_map *map, char *line);
void			free_map(t_map *map);
bool			fill_map(t_map *map, int fd, bool flag, int count);
void			*fill_array(t_map *map, int player);
bool			check_walls(t_map *map, char *errormsg, int line);
void			free_2d(char **tmp);
void			free_linked(t_list *lst);
int				ft_atoi_over(const char *str);
void			exit_err(t_map *map, char *tmp, char *line, char *msg);
t_map			*parse(char *file);
bool			open_texture(t_vars *vars);
bool	open_door(t_vars *vars);
bool	load_weapons(t_vars *vars);
bool	load_sword(t_vars *vars);
bool	load_axe(t_vars *vars);
bool	load_pickaxe(t_vars *vars);
bool	load_bow(t_vars *vars);
bool	load_totem(t_vars *vars);
bool	open_door(t_vars *vars);
bool	load_player(t_vars *vars);
bool	mlx_get_data(t_data *data);
bool	mlx_xpm(t_vars *var, t_data *data, char *s);
void	free_texture(t_vars *vars, void **data);
// animation
int 	animation(t_vars *vars, t_item *item);
void	animate(t_vars *vars);