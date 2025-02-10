/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:13:09 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/10 09:32:54 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

# define PI 3.1415926535

// Player
# define PLAYER_SIZE 10
# define PLAYER_SPEED 3
# define PLAYER_RSPEED 2

// Door
# define DOOR_OPEN 1

// Colors
# define PLAYER_COLOR 0x00FFFF00
# define DIRC_LINE 0x0000FF00
# define MMOC 0x001E3E62
# define DRCC 0x00A04747
# define DROC 0x00D8A25E
# define WALL_COLOR 0x00181C14
# define SEALING_COLOR 0x00ECDFCC
# define FLOOR_COLOR 0x003C3D37
# define BORDER_COLOR 0x00295F98

// Mouse speed
# define MAX_ROTATION_SPEED 20.0f
# define SENSITIVITY 0.001f

// Window
# define HEIGHT 1080
# define WIDTH 1920

// Map
# define BLOCK_SIZE 32
# define MMSF 0.5
# define MMSIZE 12
# define MMSHIFT 10

// Keys
# define ESC_KEY 65307
# define UP_KEY 65362
# define DOWN_KEY 65364
# define RIGHT_KEY 65363
# define LEFT_KEY 65361
# define UP_W_KEY 119
# define DOWN_S_KEY 115
# define RIGHT_D_KEY 100
# define LEFT_A_KEY 97
# define P_KEY 112
# define M_KEY 109
# define CMD_KEY 65507
# define SPACE_KEY 32

// Mouse
# define RIGHT_CLICK 3
# define LEFT_CLICK 1
# define SCROLL_CLICK 2
# define SCROLL_DOWN 4
# define SCROLL_UP 5

// # define ESC_KEY 53
// # define UP_KEY 126
// # define DOWN_KEY 125
// # define RIGHT_KEY 124
// # define LEFT_KEY 123
// # define UP_W_KEY 13
// # define DOWN_S_KEY 1
// # define RIGHT_D_KEY 2
// # define LEFT_A_KEY 0
// # define P_KEY 35
// # define M_KEY 46
// # define CMD_KEY 259
// # define SPACE_KEY 49


// Mouse
// # define RIGHT_CLICK 2
// # define LEFT_CLICK 1
// # define SCROLL_CLICK 3
#endif
