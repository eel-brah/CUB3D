#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef OS_MAC
#include "include_macos/cub3d.h"
#define IS_LINUX false
#else
#include "include/cub3d.h"
#define IS_LINUX true
#endif

#endif
