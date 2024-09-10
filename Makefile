NAME = cub3D
BONUS_NAME = cub3D_bonus

SRC = cub3d/src/main.c cub3d/src/walk.c cub3d/src/turn.c cub3d/src/movement_utils.c cub3d/src/raycasting.c cub3d/src/render.c cub3d/src/utils.c cub3d/src/textures.c cub3d/src/parser/ft_split_charset.c cub3d/src/parser/file.c cub3d/src/parser/metadata.c cub3d/src/parser/parser.c cub3d/src/parser/read.c cub3d/src/parser/parser_utils.c cub3d/src/parser/validation.c cub3d/src/exits.c cub3d/src/dda.c cub3d/src/parser/parser_utils2.c cub3d/src/parser/read2.c cub3d/src/camera.c cub3d/src/game_loop.c cub3d/src/key_hook.c cub3d/src/position.c cub3d/src/directions.c

BONUS_SRC = bonus/src/main.c bonus/src/minimap.c bonus/src/walk.c bonus/src/turn.c bonus/src/movement_utils.c bonus/src/raycasting.c bonus/src/render.c bonus/src/utils.c bonus/src/textures.c bonus/src/parser/ft_split_charset.c bonus/src/parser/file.c bonus/src/parser/metadata.c bonus/src/parser/parser.c bonus/src/parser/read.c bonus/src/parser/parser_utils.c bonus/src/parser/validation.c bonus/src/exits.c bonus/src/dda.c bonus/src/parser/parser_utils2.c bonus/src/parser/read2.c bonus/src/camera.c bonus/src/game_loop.c bonus/src/key_hook.c bonus/src/position.c bonus/src/directions.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
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

bonus: $(BONUS_NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(DEV_FLAGS) $(OBJ) $(MINILIBX) $(LIBFT) $(LINKS) -o $(NAME)
	@echo "$(RED)[ATTENTION] REMOVE DEV_FLAGS BEFORE SHIPPING$(ENDCOLOR)"

$(BONUS_NAME): $(LIBFT) $(MINILIBX) $(BONUS_OBJ)
	$(CC) $(DEV_FLAGS) $(BONUS_OBJ) $(MINILIBX) $(LIBFT) $(LINKS) -o $(BONUS_NAME)
	@echo "$(RED)[ATTENTION] REMOVE DEV_FLAGS BEFORE SHIPPING$(ENDCOLOR)"

$(LIBFT):
	make -C libft/

$(MINILIBX):
	make -C $(MINILIBX_DIR)

.c.o:
	$(CC) $(DEV_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft/

clean_bonus:
	rm -f $(BONUS_OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

fclean_bonus: clean_bonus
	rm -f $(BONUS_NAME)
	make fclean -C libft/

re: fclean all

re_bonus: fclean bonus

.PHONY: clean clean_bonus fclean fclean_bonus we re_bonus all bonus
