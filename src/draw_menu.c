#include "../platform.h"

void draw_rectangle(t_vars *vars, int x_start, int width, int height,
                    int color) {
  for (int y = 0; y < height; y++)
    for (int x = x_start; x < x_start + width; x++)
      put_pixel(vars, x, y, color);
}

void put_menu_text(t_vars *vars) {
  int x = MENU_TEXT_X, y = MENU_TEXT_Y;

  menu_text menu_items[] = {{"How To Use", -30, TEXT_COLOR_2},
                            {"Exit:", 0, TEXT_COLOR},
                            {"esc", 20, TEXT_COLOR_2},
                            {"Movement:", 50, TEXT_COLOR},
                            {"WASD and Arrows/Mouse", 70, TEXT_COLOR_2},
                            {"Open/Close doors:", 100, TEXT_COLOR},
                            {"space", 120, TEXT_COLOR_2},
                            {"Show the full minimap:", 150, TEXT_COLOR},
                            {"p", 170, TEXT_COLOR_2},
                            {"Hide the minimap:", 200, TEXT_COLOR},
                            {"m", 220, TEXT_COLOR_2},
                            {"Hide/Show fps:", 250, TEXT_COLOR},
                            {"f", 270, TEXT_COLOR_2},
                            {"Hide/Show Menu:", 300, TEXT_COLOR},
                            {"Tab", 320, TEXT_COLOR_2},
                            {"Cam View:", 350, TEXT_COLOR},
                            {"ctrl to activate", 370, TEXT_COLOR_2},
                            {"Mouse right/left click", 390, TEXT_COLOR_2},
                            {"Switch items", 430, TEXT_COLOR},
                            {"Mouse clicks/scroll", 450, TEXT_COLOR_2},
                            {"Enable or disable mouse", 480, TEXT_COLOR},
                            {"Mouse scroll click", 500, TEXT_COLOR_2},
                            {NULL, 0, 0}};

  for (int i = 0; menu_items[i].text; i++)
    mlx_string_put(
        vars->mlx, vars->win, x + (menu_items[i].offset < 0 ? 30 : 0),
        y + menu_items[i].offset, menu_items[i].color, menu_items[i].text);
}

void draw_menu(t_vars *vars) {
  if (!vars->status->menu) {
    draw_rectangle(vars, WIDTH - PRE_MENU_WIDTH, PRE_MENU_WIDTH,
                   PRE_MENU_HEIGHT, MENU_COLOR);
    mlx_string_put(vars->mlx, vars->win, PRE_MENU_TEXT_X, PRE_MENU_TEXT_Y,
                   PRE_MENU_COLOR, "Usage: Tab / m");
    return;
  }
  draw_rectangle(vars, WIDTH - MENU_WIDTH, MENU_WIDTH, MENU_HEIGHT, MENU_COLOR);
  put_menu_text(vars);
}
