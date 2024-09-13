#include <mlx.h>
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;
typedef struct s_player
{
	float x;
	float y;
	float r;
	float rota;
	float ms;
	float rs;
} t_player;
typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	t_player *player;
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
#define PLAYER_SIZE 8

#define MAP_ROWS 32
#define MAP_COLS 14
#define BLOCK_SIZE 40

#define HEIGHT BLOCK_SIZE * MAP_COLS
#define WIDTH BLOCK_SIZE * MAP_ROWS

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
void	put_pixel(t_data *data, int x, int y, unsigned int color);
void	draw_line(t_line line, t_data *img, unsigned int color);
void	draw_circle(t_data *img, int xc, int yc, int r);
float	deg2rad(float deg);
float	rad2deg(float rad);

// Map
void	set_background(t_data *img);
void	draw_map(t_vars *vars);
void	draw_block(t_data *img, int xx, int yy, int size, unsigned int b);

// Player
void	init_player(t_vars *vars);
void	draw_player(t_vars *vars);
void	player_movement(t_vars *vars, int dirc);
void	player_rotation(t_vars *vars, int dirc);

void	draw(t_vars *vars);
