CC := cc
CFLAGS := -Wall -Wextra -Werror
#-fsanitize=address

PARN_DIR := .
SRC_DIR := $(PARN_DIR)/src
INCLUDE_DIR := $(PARN_DIR)/include
BUILD_DIR := $(PARN_DIR)/build
LIBFTDIR := ./libft

SRC := cub3d.c player.c draw_map.c draw_line.c draw_circel.c utils.c raycasting.c

INCLUDE := cub3d.h
INCLUDE := $(addprefix $(INCLUDE_DIR)/,$(INCLUDE))

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

LIBFT := $(LIBFTDIR)/libft.a

NAME := cub3d

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\033[1;34m$(NAME) \033[0;34mhas been compiled"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@[ -d "$(BUILD_DIR)" ] || mkdir "$(BUILD_DIR)"
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@rm -rf $(NAME) $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re lib