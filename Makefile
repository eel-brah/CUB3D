CC := cc
CFLAGS := -Wall -Wextra -Werror



SRC := main.c draw_player.c draw_map.c draw_line.c
OBJ := $(SRC:%.c=%.o)

NAME := t

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re