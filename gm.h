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
typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
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
#define PLAYER_SIZE 10

#define HEIGHT 1000
#define WIDTH 1500

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
extern int map_x, map_y, map_s;
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
void	put_pixel(t_data *data, int x, int y, unsigned int color);
void	draw_line(t_line line, t_data *img, unsigned int color);
void	set_background(t_data *img);
void    draw_map(t_vars *vars);
void    draw_block(t_data *img, int xx, int yy, int size, unsigned int b);
void    draw_player(t_vars *vars);