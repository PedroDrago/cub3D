NAME = cub3D

SRC = src/main.c
OBJ = $(SRC:.c=.o)
LINKS = -lX11 -lXext

MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

RED=\e[31m
GREEN=\e[32m
ENDCOLOR=\e[0m

CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb3
DEV_FLAGS = -Wall -Wextra -ggdb3

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(DEV_FLAGS) $(OBJ) $(MINILIBX) $(LIBFT) $(LINKS) -o $(NAME)
	@echo "$(RED)[ATTENTION] REMOVE DEV_FLAGS BEFORE SHIPPING"

$(LIBFT):
	make -C libft/

$(MINILIBX):
	make -C $(MINILIBX_DIR)

.c.o:
	$(CC) $(DEV_FLAGS) -c $< -o $@

exec: $(NAME)
	./$(NAME)

debug: $(NAME)
	lldb ./$(NAME)

clean:
	rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: clean fclean re all exec debug
