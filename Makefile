NAME = cub3D
BONUS_NAME = cub3D_BONUS

SRC = cub3d/src/main.c cub3d/src/walk.c cub3d/src/turn.c cub3d/src/movement_utils.c cub3d/src/raycasting.c cub3d/src/render.c cub3d/src/utils.c cub3d/src/textures.c cub3d/src/parser/ft_split_charset.c cub3d/src/parser/file.c cub3d/src/parser/metadata.c cub3d/src/parser/parser.c cub3d/src/parser/read.c cub3d/src/parser/parser_utils.c cub3d/src/parser/validation.c cub3d/src/exits.c cub3d/src/print_utils.c cub3d/src/dda.c cub3d/src/parser/parser_utils2.c cub3d/src/parser/read2.c cub3d/src/camera.c cub3d/src/game_loop.c cub3d/src/key_hook.c cub3d/src/position.c cub3d/src/directions.c

BONUS_SRC = cub3d_bonus/src/main.c cub3d_bonus/src/minimap.c cub3d_bonus/src/walk.c cub3d_bonus/src/turn.c cub3d_bonus/src/movement_utils.c cub3d_bonus/src/raycasting.c cub3d_bonus/src/render.c cub3d_bonus/src/utils.c cub3d_bonus/src/textures.c cub3d_bonus/src/parser/ft_split_charset.c cub3d_bonus/src/parser/file.c cub3d_bonus/src/parser/metadata.c cub3d_bonus/src/parser/parser.c cub3d_bonus/src/parser/read.c cub3d_bonus/src/parser/parser_utils.c cub3d_bonus/src/parser/validation.c cub3d_bonus/src/exits.c cub3d_bonus/src/print_utils.c cub3d_bonus/src/dda.c cub3d_bonus/src/parser/parser_utils2.c cub3d_bonus/src/parser/read2.c cub3d_bonus/src/camera.c cub3d_bonus/src/game_loop.c cub3d_bonus/src/key_hook.c cub3d_bonus/src/position.c cub3d_bonus/src/directions.c


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

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(DEV_FLAGS) $(OBJ) $(MINILIBX) $(LIBFT) $(LINKS) -o $(NAME)
	@echo "$(RED)[ATTENTION] REMOVE DEV_FLAGS BEFORE SHIPPING$(ENDCOLOR)"

bonus: $(LIBFT) $(MINILIBX) $(BONUS_OBJ)
	$(CC) $(DEV_FLAGS) $(BONUS_OBJ) $(MINILIBX) $(LIBFT) $(LINKS) -o $(BONUS_NAME)
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
	rm -f $(BONUS_OBJ)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make fclean -C libft/

re: fclean all

exec2: re $(NAME)
	./cub3D ./maps/default.cub
.PHONY: clean fclean re all exec debug
