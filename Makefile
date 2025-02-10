CC := cc
CFLAGS := #-Wall -Wextra -Werror -g

OS := $(shell uname)

ifeq ($(OS), Darwin)  # macOS
    MLX_FLAGS := -lmlx -framework OpenGL -framework AppKit
		INCLUDE_DIR := ./include_macos
		MLX_LIB := ./minilibx_opengl
else  # Linux
    MLX_FLAGS := -Lminilibx-linux -lmlx -lX11 -lXext -lm
		INCLUDE_DIR := ./include
		MLX_LIB := ./minilibx-linux
endif

PARN_DIR := .
SRC_DIR := $(PARN_DIR)/src
INCLUDE_DIR := $(PARN_DIR)/include
BUILD_DIR := $(PARN_DIR)/build
LIBFTDIR := ./libft

SRC := cub3d.c player.c draw_line.c draw_circel.c utils.c raycasting.c get_next_line.c \
		parse.c parse_utilis.c  parse_utilis1.c parse_utilis2.c parse_utilis3.c parse_utilis4.c wall.c wall_texture.c door.c texture.c \
		inputs_key.c inputs_mouse.c animation.c init.c raycasting_utils.c minimap.c minimap_border.c minimap_utils.c texture_door.c texture_weapons1.c texture_weapons2.c \
		texture_player.c 

INCLUDE := cub3d.h get_next_line.h cub3d_defines.h cub3d_libs.h cub3d_structs.h

INCLUDE := $(addprefix $(INCLUDE_DIR)/,$(INCLUDE))

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

LIBFT := $(LIBFTDIR)/libft.a

NAME := cub3d

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	@echo "\033[1;34m$(NAME) \033[0;34mhas been compiled"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@[ -d "$(BUILD_DIR)" ] || mkdir "$(BUILD_DIR)"
	@$(MAKE) -C $(LIBFTDIR)
	@echo "\033[0;34mCompiling \033[1;34mminilibx"
	@$(MAKE) -C $(MLX_LIB)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(MAKE) clean -C $(MLX_LIB)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@rm -rf $(NAME) $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re lib
