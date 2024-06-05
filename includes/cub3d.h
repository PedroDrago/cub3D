#ifndef CUB3D_H
#define CUB3D_H
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "macros.h"
#include "structs.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int  get_map_proportions(t_map *map_data, char *file_path);
int  read_map_file(t_map *map_data, char *file_path);
int  parse_map(t_map *map_data);
void print_map_data(t_map *map_data);
void init_textures(t_game *game);
int  key_hook(int key, t_game *game);
void rotate_right(t_camera *camera);
void rotate_left(t_camera *camera);
void walk_forward(t_camera *camera, char **map);
void walk_backwards(t_camera *camera, char **map);
void walk_left(t_camera *camera, char **map);
void walk_right(t_camera *camera, char **map);
void calculate_line(t_ray *ray, t_line *line);
void digital_diferencial_analysis(t_game *game, t_ray *ray, t_line *line); // this is de DDA algorithm, responsible to get the position where the ray will hit a wall
void dda_setup(t_game *game, t_ray *ray); // this setup data for the DDA algorithm
void setup_raycasting(t_game *game, t_ray *ray, int x); // this initialize some data about this current ray we'll trace
void draw_line(t_data *img, int x, t_line line);
void print_split(char **splited);
void my_mlx_pixel_put(t_data *img, int x, int y, unsigned int color);
void draw_background(t_data *frame);
void init_textures(t_game *game);
void get_map(t_game *game, char *file);
void free_split(char **splited);

#endif
