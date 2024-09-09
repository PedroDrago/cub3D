NAME = cub3D

SRC = cub3d/src/main.c cub3d/src/walk.c cub3d/src/turn.c cub3d/src/movement_utils.c cub3d/src/raycasting.c cub3d/src/render.c cub3d/src/utils.c cub3d/src/textures.c cub3d/src/parser/ft_split_charset.c cub3d/src/parser/file.c cub3d/src/parser/metadata.c cub3d/src/parser/parser.c cub3d/src/parser/read.c cub3d/src/parser/parser_utils.c cub3d/src/parser/validation.c cub3d/src/exits.c cub3d/src/print_utils.c cub3d/src/dda.c cub3d/src/parser/parser_utils2.c cub3d/src/parser/read2.c cub3d/src/camera.c cub3d/src/game_loop.c cub3d/src/key_hook.c cub3d/src/position.c cub3d/src/directions.c


OBJ = $(SRC:.c=.o)
LINKS = -lX11 -lXext -lm

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
	@echo "$(RED)[ATTENTION] REMOVE DEV_FLAGS BEFORE SHIPPING$(ENDCOLOR)"

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

exec2: re $(NAME)
	./cub3D ./maps/default.cub
.PHONY: clean fclean re all exec debug
