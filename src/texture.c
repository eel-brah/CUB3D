#include "../include/cub3d.h"

bool	load_sword(t_vars *vars)
{
	vars->items[0].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/1.xpm" ,&vars->items[0].item[0].width, &vars->items[0].item[0].height);
	if (!vars->items[0].item[0].img)
		return (false);
	vars->items[0].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/2.xpm" ,&vars->items[0].item[1].width, &vars->items[0].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[0].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/3.xpm" ,&vars->items[0].item[2].width, &vars->items[0].item[2].height);
	if (!vars->items[0].item[2].img)
		return (false);
	vars->items[0].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/1-sword/4.xpm" ,&vars->items[0].item[3].width, &vars->items[0].item[3].height);
	if (!vars->items[0].item[3].img)
		return (false);
	return (true);
}

bool	load_axe(t_vars *vars)
{
	vars->items[1].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/1.xpm" ,&vars->items[1].item[0].width, &vars->items[1].item[0].height);
	if (!vars->items[0].item[0].img)
		return (false);
	vars->items[1].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/3.xpm" ,&vars->items[1].item[1].width, &vars->items[1].item[1].height);
	if (!vars->items[1].item[1].img)
		return (false);
	vars->items[1].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/4.xpm" ,&vars->items[1].item[2].width, &vars->items[1].item[2].height);
	if (!vars->items[1].item[2].img)
		return (false);
	vars->items[1].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/2-axe/4.xpm" ,&vars->items[1].item[3].width, &vars->items[1].item[3].height);
	if (!vars->items[1].item[3].img)
		return (false);
	return (true);
}

bool	load_pickaxe(t_vars *vars)
{
	vars->items[2].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/1.xpm" ,&vars->items[2].item[0].width, &vars->items[2].item[0].height);
	if (!vars->items[2].item[0].img)
		return (false);
	vars->items[2].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/3.xpm" ,&vars->items[2].item[1].width, &vars->items[2].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[2].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/4.xpm" ,&vars->items[2].item[2].width, &vars->items[2].item[2].height);
	if (!vars->items[2].item[2].img)
		return (false);
	vars->items[2].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/3-pickaxe/4.xpm" ,&vars->items[2].item[3].width, &vars->items[2].item[3].height);
	if (!vars->items[2].item[3].img)
		return (false);
	return (true);
}

bool	load_bow(t_vars *vars)
{
	vars->items[3].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/1.xpm" ,&vars->items[3].item[0].width, &vars->items[3].item[0].height);
	if (!vars->items[3].item[0].img)
		return (false);
	vars->items[3].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/3.xpm" ,&vars->items[3].item[1].width, &vars->items[3].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[3].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/4.xpm" ,&vars->items[3].item[2].width, &vars->items[3].item[2].height);
	if (!vars->items[3].item[2].img)
		return (false);
	vars->items[3].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/4-bow/4.xpm" ,&vars->items[3].item[3].width, &vars->items[3].item[3].height);
	if (!vars->items[3].item[3].img)
		return (false);
	return (true);
}

bool	load_totem(t_vars *vars)
{
	vars->items[4].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/1.xpm" ,&vars->items[4].item[0].width, &vars->items[4].item[0].height);
	if (!vars->items[4].item[0].img)
		return (false);
	vars->items[4].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/3.xpm" ,&vars->items[4].item[1].width, &vars->items[4].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[4].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/4.xpm" ,&vars->items[4].item[2].width, &vars->items[4].item[2].height);
	if (!vars->items[4].item[2].img)
		return (false);
	vars->items[4].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/5-totem/4.xpm" ,&vars->items[4].item[3].width, &vars->items[4].item[3].height);
	if (!vars->items[4].item[3].img)
		return (false);
	return (true);
}

bool	load_diamond(t_vars *vars)
{
	vars->items[5].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/1.xpm" ,&vars->items[5].item[0].width, &vars->items[5].item[0].height);
	if (!vars->items[5].item[0].img)
		return (false);
	vars->items[5].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/3.xpm" ,&vars->items[5].item[1].width, &vars->items[5].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[5].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/4.xpm" ,&vars->items[5].item[2].width, &vars->items[5].item[2].height);
	if (!vars->items[5].item[2].img)
		return (false);
	vars->items[5].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/6-diamond/4.xpm" ,&vars->items[5].item[3].width, &vars->items[5].item[3].height);
	if (!vars->items[5].item[3].img)
		return (false);
	return (true);
}

bool	load_apple(t_vars *vars)
{
	vars->items[6].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/1.xpm" ,&vars->items[6].item[0].width, &vars->items[6].item[0].height);
	if (!vars->items[6].item[0].img)
		return (false);
	vars->items[6].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/3.xpm" ,&vars->items[6].item[1].width, &vars->items[6].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[6].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/4.xpm" ,&vars->items[6].item[2].width, &vars->items[6].item[2].height);
	if (!vars->items[6].item[2].img)
		return (false);
	vars->items[6].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/7-apple/4.xpm" ,&vars->items[6].item[3].width, &vars->items[6].item[3].height);
	if (!vars->items[6].item[3].img)
		return (false);
	return (true);
}

bool	load_potion(t_vars *vars)
{
	vars->items[7].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/1.xpm" ,&vars->items[7].item[0].width, &vars->items[7].item[0].height);
	if (!vars->items[7].item[0].img)
		return (false);
	vars->items[7].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/3.xpm" ,&vars->items[7].item[1].width, &vars->items[7].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[7].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/4.xpm" ,&vars->items[7].item[2].width, &vars->items[7].item[2].height);
	if (!vars->items[7].item[2].img)
		return (false);
	vars->items[7].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/8-potion/4.xpm" ,&vars->items[7].item[3].width, &vars->items[7].item[3].height);
	if (!vars->items[7].item[3].img)
		return (false);
	return (true);
}

bool	load_food(t_vars *vars)
{
	vars->items[8].item[0].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/1.xpm" ,&vars->items[8].item[0].width, &vars->items[8].item[0].height);
	if (!vars->items[8].item[0].img)
		return (false);
	vars->items[8].item[1].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/3.xpm" ,&vars->items[8].item[1].width, &vars->items[8].item[1].height);
	if (!vars->items[0].item[1].img)
		return (false);
	vars->items[8].item[2].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/4.xpm" ,&vars->items[8].item[2].width, &vars->items[8].item[2].height);
	if (!vars->items[8].item[2].img)
		return (false);
	vars->items[8].item[3].img = mlx_xpm_file_to_image(vars->mlx, "images/9-food/4.xpm" ,&vars->items[8].item[3].width, &vars->items[8].item[3].height);
	if (!vars->items[8].item[3].img)
		return (false);
	return (true);
}

bool	load_player(t_vars *vars)
{
	vars->player_cam[0].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/shield1.xpm" ,&vars->player_cam[0].width, &vars->player_cam[0].height);
	if (!vars->player_cam[0].img)
		return (false);
	vars->player_cam[1].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit1.xpm" ,&vars->player_cam[1].width, &vars->player_cam[1].height);
	if (!vars->player_cam[1].img)
		return (false);
	vars->player_cam[2].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit2.xpm" ,&vars->player_cam[2].width, &vars->player_cam[2].height);
	if (!vars->player_cam[2].img)
		return (false);
	vars->player_cam[3].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit3.xpm" ,&vars->player_cam[3].width, &vars->player_cam[3].height);
	if (!vars->player_cam[3].img)
		return (false);
	vars->player_cam[4].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit4.xpm" ,&vars->player_cam[4].width, &vars->player_cam[4].height);
	if (!vars->player_cam[4].img)
		return (false);
	vars->player_cam[5].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit5.xpm" ,&vars->player_cam[5].width, &vars->player_cam[5].height);
	if (!vars->player_cam[5].img)
		return (false);
	vars->player_cam[6].img = mlx_xpm_file_to_image(vars->mlx, "images/cam/hit6.xpm" ,&vars->player_cam[6].width, &vars->player_cam[6].height);
	if (!vars->player_cam[6].img)
		return (false);
	vars->player_cam_shield.img = mlx_xpm_file_to_image(vars->mlx, "images/cam/shield2.xpm" ,&vars->player_cam_shield.width, &vars->player_cam_shield.height);
	if (!vars->player_cam_shield.img)
		return (false);
	return (true);
}

bool	load_weapons(t_vars *vars)
{
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
	if(!load_diamond(vars))
		return (false);
	if(!load_apple(vars))
		return (false);
	if(!load_potion(vars))
		return (false);
	if(!load_food(vars))
		return (false);
	if(!load_player(vars))
		return (false);
	return (true);
}

bool	open_texture(t_vars *vars)
{
	t_data	*data;

	
	if (!load_weapons(vars))
		return (false);
	vars->door.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/door2.xpm" ,&vars->door.width, &vars->door.height);
	if (!vars->door.img)
		return (false);
	vars->left_left.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/left_left.xpm" ,&vars->left_left.width, &vars->left_left.height);
	if (!vars->left_left.img)
		return (false);
	vars->left_right.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/left_right.xpm" ,&vars->left_right.width, &vars->left_right.height);
	if (!vars->left_right.img)
		return (false);
	vars->right_left.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/right_left.xpm" ,&vars->right_left.width, &vars->right_left.height);
	if (!vars->right_left.img)
		return (false);
	vars->right_right.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/right_right.xpm" ,&vars->right_right.width, &vars->right_right.height);
	if (!vars->right_right.img)
		return (false);
	vars->up_up.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/up_up.xpm" ,&vars->up_up.width, &vars->up_up.height);
	if (!vars->up_up.img)
		return (false);
	vars->up_down.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/up_down.xpm" ,&vars->up_down.width, &vars->up_down.height);
	if (!vars->up_down.img)
		return (false);
	vars->down_down.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/down_down.xpm" ,&vars->down_down.width, &vars->down_down.height);
	if (!vars->down_down.img)
		return (false);
	vars->down_up.img = mlx_xpm_file_to_image(vars->mlx, "images/texture/door/down_up.xpm" ,&vars->down_up.width, &vars->down_up.height);
	if (!vars->down_up.img)
		return (false);

	vars->north.img = mlx_xpm_file_to_image(vars->mlx, vars->map->no,&vars->north.width, &vars->north.height);
	if (!vars->north.img)
		return (false);
	vars->west.img = mlx_xpm_file_to_image(vars->mlx, vars->map->we,&vars->west.width, &vars->west.height);
	if (!vars->west.img)
		return (false);
	vars->south.img = mlx_xpm_file_to_image(vars->mlx, vars->map->so,&vars->south.width, &vars->south.height);
	if (!vars->south.img)
		return (false);
	vars->east.img = mlx_xpm_file_to_image(vars->mlx, vars->map->ea,&(vars->east.width), &(vars->east.height));
	if (!vars->east.img)
		return (false);
	data = &vars->door;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->left_left;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->left_right;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->right_left;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->right_right;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->up_up;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->up_down;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->down_down;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->down_up;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);

	data = &vars->north;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->west;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->south;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);
	data = &vars->east;
	data->addr = mlx_get_data_addr(data->img,&data->bpp, &data->line_length, &data->endian);

	return (true);
}