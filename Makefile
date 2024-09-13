CC := cc
CFLAGS := -Wall -Wextra -Werror



SRC := main.c player.c draw_map.c draw_line.c draw_circel.c utils.c
INCLUDE := gm.h
OBJ := $(SRC:%.c=%.o)

NAME := t

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re