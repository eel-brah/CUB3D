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

typedef enum face
{
	NORHT,
	WEST,
	EAST,
	SOUTH
}	t_player_face;

typedef struct s_map
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	unsigned int		f;
	unsigned int		c;
	int					max_col;
	int					max_line;
	int					player_x_pos;
	int					player_y_pos;
	t_player_face		player_face;
	int					rows;
	int					cols;
	int					height;
	int					width;
	char				*map;
	t_list				*lst;
}	t_map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;
typedef struct s_player
{
	float	x;
	float	y;
	float	r;
	float	pa;
	float	steps;
	float	rspeed;
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
}	t_ray;
typedef struct s_rays
{
	float	x_whpoint;
	float	y_whpoint;
	float	hit_dis;
	float	angle;
	bool	is_vertical;
}	t_rays;
typedef struct s_hitpoint
{
    float h_x;
    float v_x;
    float h_y;
    float v_y;
}   t_hitpoint;

typedef struct s_status
{
	bool	mm;
}	t_status;

// typedef struct s_map
// {
// 	int	rows;
// 	int	cols;
// 	int	height;
// 	int	width;
// }	t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	t_map	*map;
	t_player *player;
	t_rays	*rays;
	t_ray	*ray;
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



#define PI 3.1415926535

#define BACKGROUND 0x00383c40
#define PLAYER_COLOR 0x00FFFF00
#define DIRC_LINE 0x0000FF00
#define PLAYER_SIZE 18

#define MMC 0x00EAE4DD
#define WALL_COLOR 0x00181C14
#define SEALING_COLOR 0x00ECDFCC
#define FLOOR_COLOR 0x003C3D37
#define BORDER_COLOR 0x00295F98


#define MAP_ROWS 32
#define MAP_COLS 14
#define BLOCK_SIZE 50
#define MMSF 0.3
#define MMS 12

# define ESC_KEY 53
# define UP_KEY 126
# define DOWN_KEY 125
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_W_KEY 13
# define DOWN_S_KEY 1
# define RIGHT_D_KEY 2
# define LEFT_A_KEY 0

extern float ppz_x, ppz_y, pdx, pdy, pa;
extern int map[];
	// 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	// 1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
	// 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
	// 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	// 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
	// 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
	// 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
	// 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
	// 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
	// 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

// Functions
// Utils
void	put_pixel(t_vars *vars, int x, int y, unsigned int color);
void	draw_line(t_vars *vars, t_line line, unsigned int color);
void	draw_circle(t_vars *vars, int xc, int yc, int r);
float	deg2rad(float deg);
float	rad2deg(float rad);

// Map
// void	set_background(t_data *img);
void	draw_minimap(t_vars *vars, t_mini *minimap);
void	draw_block(t_vars *vars, int x, int y, int size, unsigned int b);

void draw_minimap_player(t_vars *vars);

// Player
void	init_player(t_vars *vars);
void	draw_player(t_vars *vars, t_mini *minimap);
void	player_movement(t_vars *vars, int dirc, int sp);
void	player_rotation(t_vars *vars, int dirc);
bool	isit_wall(t_vars *vars, float x, float y);
int		isit_outob(t_vars *vars, float x, float y);

void	draw(t_vars *vars);

// Raycasting
void	init_ray(t_vars *vars);
void	cast_rays(t_vars *vars);
float	distance(float x1, float y1, float x2, float y2);
void	draw_rays(t_vars *vars);

// Walls
void draw_wall(t_vars *vars);


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