#include "../include/cub3d.h"

#define MAX_ROTATION_SPEED 20.0f
#define SENSITIVITY 0.001f  // Adjust this value to change rotation sensitivit

int	key_realese(int keysym, t_vars *vars)
{
	if (keysym == 259)
	{
		if (vars->cam)
			vars->player->pa -= PI;
		vars->cam = false;
	}
	else if (keysym == UP_KEY)
		vars->keys.up_key = false;
	else if (keysym == UP_W_KEY)
		vars->keys.w_key = false;
	else if (keysym == DOWN_S_KEY)
		vars->keys.s_key = false;
	else if (keysym == DOWN_KEY)
		vars->keys.down_key = false;
	else if (keysym == LEFT_A_KEY)
		vars->keys.a_key = false;
	else if (keysym == RIGHT_D_KEY)
		vars->keys.d_key = false;
	else if (keysym == LEFT_KEY)
		vars->keys.left_key = false;
	else if (keysym == RIGHT_KEY)
		vars->keys.right_key = false;
	else if (keysym == 35)
		vars->status->full_map = false;
	return 0;
}

void	cam_preparation(t_vars *vars)
{
	if (!vars->cam)
		vars->player->pa += PI;
	vars->cam = true;
	vars->keys.up_key = false;
	vars->keys.w_key = false;
	vars->keys.s_key = false;
	vars->keys.down_key = false;
	vars->keys.a_key = false;
	vars->keys.d_key = false;
	vars->keys.left_key = false;
	vars->keys.right_key = false;
	vars->player->rotate = false;
}

void	key_press_mv(int keysym, t_vars* vars)
{
	if (keysym == UP_KEY)
		vars->keys.up_key = true;
	else if (keysym == UP_W_KEY)
		vars->keys.w_key = true;
	else if (keysym == DOWN_S_KEY)
		vars->keys.s_key = true;
	else if (keysym == DOWN_KEY)
		vars->keys.down_key = true;
	else if (keysym == LEFT_A_KEY)
		vars->keys.a_key = true;
	else if (keysym == RIGHT_D_KEY)
		vars->keys.d_key = true;
	else if (keysym == LEFT_KEY)
		vars->keys.left_key = true;
	else if (keysym == RIGHT_KEY)
		vars->keys.right_key = true;
}
int	key_press(int keysym, t_vars *vars)
{
	if (keysym == 259)
		cam_preparation(vars);
	else if (!vars->cam)
	{	
		key_press_mv(keysym, vars);
		if (keysym == 49)
			open_close_door(vars);
		else if (keysym == 46)
			vars->status->mm = !(vars->status->mm);
		else if (keysym == 35)
			vars->status->full_map = true;
	}
	if (keysym == ESC_KEY)
		close_and_clear(vars);
	return 1;
}

int mouse_move(int x, int y, t_vars *vars)
{
    (void)y;
    static int last_x = -1;
    float delta_x;
    float normalized_rotation;
	if (!vars->cam)
{
    if (last_x == -1)
    {
        last_x = x;
        return 1;
    }
	if (vars->player->mouse && x >= WIDTH - 100)
	{
		vars->player->rotate = 1;
		vars->player->rotate2 = 0;
		vars->player->ra = 0.02 * MAX_ROTATION_SPEED;
	}
	else if (vars->player->mouse && x <=  100)
	{
		vars->player->rotate = 1;
		vars->player->rotate2 = 0;
		vars->player->ra = -0.02 * MAX_ROTATION_SPEED;

	}
	else if (vars->player->mouse)
	{
		// usleep(10);

		vars->player->rotate = 0;
		vars->player->rotate2 = 1;
		delta_x = x - last_x;
		if (delta_x < 5 && delta_x > -5)
			return (1);
		last_x = x;

		normalized_rotation = delta_x * SENSITIVITY;
		
		normalized_rotation = fmaxf(-1.0f, fminf(1.0f, normalized_rotation));
		// vars->player->rotate2 = 1;
		// vars->player->ra = (0.02 * (delta_x > 0) + -0.02 * !(delta_x > 0));
		vars->player->ra = normalized_rotation * 3 * MAX_ROTATION_SPEED;
		//player_rotation(vars, normalized_rotation * MAX_ROTATION_SPEED);
		// player_rotation(vars, (delta_x >= 0 ? 0.02: -0.02) * MAX_ROTATION_SPEED);
	}
	else
	{
		vars->player->rotate = 0;
		vars->player->rotate2 = 0;
	}
	}

    return 1;
}


// int	mouse_movse(int x, int y, t_vars *vars)
// {
// 	static bool first_move = true;
// 	(void)y;
// 	int	new_x;
// 	if (first_move)
// 	{
// 		vars->map->old_x = x;
// 		first_move = false;
// 	}
// 	if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
// 	{
// 		new_x = x - vars->map->old_x;
// 		vars->map->old_x = x;
// 		if (new_x != 0)
// 			player_rotation(vars, new_x > 0 ? 1 : -1);
// 	}
//     return 1;
// }

void	mouse_hook_helper(int b, t_vars *vars)
{
	static int	i = 0;

	if (!vars->cam && (b == 4 || b == 2))
	{
		i++;
		i = i % 9;
		vars->items[i].animate = true;
		vars->items[!(i == 8) * (i + 1)].animate = false;
		vars->items[(i == 0) * 8 + !(i == 0) * (i - 1)].animate = false;
	}
	else if (!vars->cam && (b == 5 || b == 1))
	{
		i--;
		i = (i == -1) * 8 + !(i == -1) * i;
		vars->items[i].animate = true;
		vars->items[!(i == 8) * (i + 1)].animate = false;
		vars->items[(i == 0) * 8 + !(i == 0) * (i - 1)].animate = false;
	}
	// i = i % 9;
}

int mouse_hook(int b, int x, int y, t_vars *vars)
{
	(void)vars;
	(void)y;
	(void)x;

	if (b == 3)
		vars->player->mouse = !(vars->player->mouse);
	else if (vars->cam && b == 1)
		vars->player_animate_hit = true;
	else if (vars->cam && b == 2)
		vars->player_animate_shield = true;
	else 
		mouse_hook_helper(b, vars);
	return 1;
}
