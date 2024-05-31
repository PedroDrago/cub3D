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

int  get_map_proportions(t_map *map_data, char *file_path);
int  read_map_file(t_map *map_data, char *file_path);
int  parse_map(t_map *map_data);
void print_map_data(t_map *map_data);

#endif
