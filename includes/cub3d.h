#ifndef CUB3D_H
#define CUB3D_H
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "macros.h"
#include "structs.h"
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


# define mapWidth 24
# define mapHeight 24
# define S_WIDTH 640
# define S_HEIGHT 480
# define RGB_RED    0xFF0000
# define RGB_GREEN  0x00FF00
# define RGB_BLUE   0x0000FF
# define RGB_WHITE  0xFFFFFF
# define RGB_YELLOW 0xFFFF0
# define RGB_PURPLE 0xA020F0
# define RGB_BROWN 0x964B00
# define W 119
# define LEFT 65361
# define RIGHT 65363
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define MOV_SPEED 0.5
# define ROT_SPEED 0.1


int		get_map_proportions(t_map *map_data, char *file_path);
int		read_map_file(t_map *map_data, char *file_path);
int		parse_map(t_map *map_data);
void	print_map_data(t_map *map_data);
void	init_textures(t_game *game);
int		key_hook(int key, t_game *game);
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
void	walk_forward(t_game *game);
void	walk_backwards(t_game *game);
void	walk_left(t_game *game);
void	walk_right(t_game *game);

#endif
