/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:13:09 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/21 08:04:14 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
#define CUB3D_DEFINES_H

#define PI 3.1415926535

// Player
#define PLAYER_SIZE 10
#define PLAYER_SPEED 3
#define PLAYER_RSPEED 2

// Door
#define DOOR_OPEN 1

// Colors
#define PLAYER_COLOR 0x00FFFF00
#define DIRC_LINE 0x0000FF00
#define MMOC 0x001E3E62
#define DRCC 0x00A04747
#define DROC 0x00D8A25E
#define WALL_COLOR 0x00181C14
#define SEALING_COLOR 0x00ECDFCC
#define FLOOR_COLOR 0x003C3D37
#define BORDER_COLOR 0x00295F98

// Mouse speed
#define MAX_ROTATION_SPEED 20.0f
#define SENSITIVITY 0.001f

// Window
#define HEIGHT 1080
#define WIDTH 1920

// Map
#define BLOCK_SIZE 32
#define MMSF 0.5
#define MMSIZE 12
#define MMSHIFT 10

// Keys
#define ESC_KEY 53
#define UP_KEY 126
#define DOWN_KEY 125
#define RIGHT_KEY 124
#define LEFT_KEY 123
#define UP_W_KEY 13
#define DOWN_S_KEY 1
#define RIGHT_D_KEY 2
#define LEFT_A_KEY 0
#define P_KEY 35
#define M_KEY 46
#define F_KEY 3
#define CMD_KEY 259
#define SPACE_KEY 49
#define TAB_KEY 48

// Mouse
#define RIGHT_CLICK 2
#define LEFT_CLICK 1
#define SCROLL_CLICK 3
#define SCROLL_DOWN 4
#define SCROLL_UP 5


#define PRE_MENU_WIDTH 125
#define PRE_MENU_HEIGHT 25
#define PRE_MENU_TEXT_X (WIDTH - 100)
#define PRE_MENU_TEXT_Y 15
#define MENU_WIDTH 190
#define MENU_HEIGHT 570
#define MENU_TEXT_X (WIDTH - 165)
#define MENU_TEXT_Y 50
#define DEF_COLOR 0xf72585
#define DEF_COLOR_2 0x4cc9f0
#define TEXT_COLOR 0x114869
#define TEXT_COLOR_2 0x669bbc
#define MENU_COLOR 0x191c1f
#define PRE_MENU_COLOR 0x999999
#endif
