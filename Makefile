NAME = cub3D

SRC = src/main.c
MINILIBX = minilibx-linux/libmlx.a
OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a
INCLUDES = -lX11 -lXext

CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb3

RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

exec: $(NAME)
	./$(NAME)

$(LIBFT):
	make -C libft/

clean:
	rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: clean fclean re all exec
