#include "../platform.h"

#define PRE_MENU_WIDTH 125
#define PRE_MENU_HEIGHT 25
#define MENU_WIDTH 190
#define MENU_HEIGHT 570
#define DEF_COLOR 0xf72585
#define DEF_COLOR_2 0x4cc9f0
#define TEXT_COLOR 0x114869
#define TEXT_COLOR_2 0x669bbc
#define MENU_COLOR 0x191c1f
#define PRE_MENU_COLOR 0x999999

void draw_menu(t_vars *vars) {
  if (!vars->status->menu) {
    draw_pre_menu(vars);
    pre_menu_text(vars);
    return;
  }
  draw_menu_background(vars);
  menu_text(vars);
}

void draw_pre_menu(t_vars *vars) {
  int x;
  int y;

  y = 0;
  while (y < PRE_MENU_HEIGHT) {
    x = WIDTH - PRE_MENU_WIDTH;
    while (x < WIDTH) {
      put_pixel(vars, x, y, MENU_COLOR);
      x++;
    }
    y++;
  }
}

void draw_menu_background(t_vars *vars) {
  int x;
  int y;

  y = 0;
  while (y < MENU_HEIGHT) {
    x = WIDTH - MENU_WIDTH;
    while (x < WIDTH) {
      put_pixel(vars, x, y, MENU_COLOR);
      x++;
    }
    y++;
  }
}

void pre_menu_text(t_vars *vars) {
  mlx_string_put(vars->mlx, vars->win, WIDTH - 100, 10, PRE_MENU_COLOR,
                 "Usage: Tab / m");
}

void menu_text(t_vars *vars) {
  int x;
  int y;

  x = WIDTH - 165;
  y = 50;
  mlx_string_put(vars->mlx, vars->win, x + 30, y - 30, TEXT_COLOR_2,
                 "How To Use");
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Exit:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "esc");
  y += (30 + 20);
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Movement:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2,
                 "WASD and Arrows/Mouse");
  y += (30 + 20);
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Open/Close doors:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "space");
  y += 30 + 20;
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR,
                 "Show the full minimap:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "p");
  y += 30 + 20;
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Hide the minimap:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "m");
  y += (30 + 20);
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Hide/Show fps:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "f");
  y += (30 + 20);
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Hide/Show Menu:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "Tab");
  y += (30 + 20);
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Front cam mode:");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2,
                 "ctrl to activate");
  mlx_string_put(vars->mlx, vars->win, x, y + 40, TEXT_COLOR_2,
                 "Mouse right/left clic");
  y += (30 + 40);
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Switch items");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2,
                 "Mouse clicks/scroll");
  y += (30 + 20);
  mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR,
                 "Enable or desable mouse");
  mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2,
                 "Mouse scroll click");
}
