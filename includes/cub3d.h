/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:33:29 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 22:33:29 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define S_WIDTH 1280
# define S_HEIGHT 720
# define RGB_RED 0xFF0000
# define RGB_GREEN 0x00FF00
# define RGB_BLUE 0x0000FF
# define RGB_WHITE 0xFFFFFF
# define RGB_YELLOW 0xFFFF0
# define RGB_PURPLE 0xA020F0
# define RGB_BROWN 0x964B00
# define RGB_LIGHT_BLUE 0x87CEFA
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define I_W 0
# define I_A 1
# define I_S 2
# define I_D 3
# define I_LEFT 4
# define I_RIGHT 5
# define RATE 3

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_data;

typedef struct s_vector_d
{
	double			x;
	double			y;
}					t_vector_d;

typedef struct s_vector_i
{
	int				x;
	int				y;
}					t_vector_i;

typedef struct s_minimap_data
{
	int				i;
	int				j;
	t_vector_i		vec;
	int				square_side;
}					t_minimap_data;

typedef struct s_line
{
	int				height;
	int				start;
	int				end;
	unsigned int	color;
	t_data			*texture;
}					t_line;

typedef struct s_line_data
{
	int				y;
	int				tex_y;
	int				tex_x;
	int				color;
	int				d;
	double			wall_x;
}					t_line_data;

typedef struct s_ray
{
	t_vector_d		dir;
	t_vector_d		camera;
	t_vector_i		map;
	t_vector_d		side_dist;
	t_vector_d		delta_dist;
	double			wall_dist;
	t_vector_i		step;
	int				hit;
	int				side;
	int				x;
}					t_ray;

typedef struct s_map
{
	char			**map;
	char			**mini_map;
	int				width;
	int				height;
	char			**map_file_array;
	int				file_height;
	int				file_width;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			*floor_rgb;
	char			*ceiling_rgb;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}					t_map;

typedef struct s_camera
{
	double			mov_speed;
	double			rot_speed;
	t_vector_d		pos;
	t_vector_d		dir;
	t_vector_d		plane;
}					t_camera;

typedef struct s_game
{
	int				keys[20];
	t_data			textures[4];
	int				texture_index;
	t_camera		camera;
	t_map			map;
	void			*mlx;
	void			*win;
	int				should_end;
}					t_game;

int					get_map_proportions(t_map *map_data, char *file_path);
int					read_map_file(t_map *map_data, char *file_path);
int					parse_map(t_map *map_data);
void				print_map_data(t_map *map_data);
void				init_textures(t_game *game);
int					key_hook(int key, t_game *game);
void				rotate_right(t_camera *camera);
void				rotate_left(t_camera *camera);
void				walk_forward(t_camera *camera, char **map, char **minimap);
void				walk_backwards(t_camera *camera, char **map,
						char **minimap);
void				walk_left(t_camera *camera, char **map, char **minimap);
void				walk_right(t_camera *camera, char **map, char **minimap);
void				calculate_line(t_ray *ray, t_line *line);
void				digital_diferencial_analysis(t_game *game, t_ray *ray,
						t_line *line);
void				dda_setup(t_game *game, t_ray *ray);
void				setup_raycasting(t_game *game, t_ray *ray, int x);
void				draw_line(t_data *img, t_line line, t_ray *ray,
						t_game *game);
void				print_split(char **splited);
void				my_mlx_pixel_put(t_data *img, int x, int y,
						unsigned int color);
void				draw_background(t_data *frame, unsigned int ceil_rgb,
						unsigned int floor_rgb);
void				init_textures(t_game *game);
void				get_map(t_game *game, char *file);
void				free_split(char **splited);

void				print_split(char **splited);
void				print_map_data(t_map *map_data);
void				print_all_map_file(t_map *map_data);
int					split_len(char **splited);
void				free_split(char **splited);
void				draw_map(t_game *game, t_data *tile);

int					get_initial_pos(char **map, t_vector_d *pos);
int					get_initial_pos_i(char **map, t_vector_i *pos, int height,
						int width);
char				**ft_split_charset(char const *s, const char *charset);
int					check_extension(char *file);
int					read_map_file(t_map *map_data, char *file_path);
int					files_exist(t_map *map);
int					rgb_to_hex(char *rgb);
int					parse_data(t_map *map_data, char *line);
int					is_empty_line(char *line);
char				*remove_linebreak(char *line);
void				destroy_map_data(t_map *map_data);
void				init_map(t_map *map);
int					is_invalid_char(char c);
int					is_player_char(char c);
char				**duplicate_map(char **map, int height);
void	error_exit(int status, char *msg);
void				free_map(t_map *map);
void				destroy_map(t_map *map);
void				fill_spaces_with_zero(char **map, int height, int width);
void				destroy_all(t_game *game);
int					validate_map(char **map, int height, int width);
char				*ft_strdup_margin(const char *s);

int					is_empty_tile(char c);
int					get_diagonal_dir(t_vector_d pos, t_vector_d fut_pos);
int					clean_exit(t_game *game);
void				init_camera(t_camera *camera, t_game *game);
int					key_hook_down(int key, t_game *game);
int					key_hook_up(int key, t_game *game);
void				zero_keys_array(t_game *game);
void				set_south(t_camera *camera);
void				set_north(t_camera *camera);
void				set_east(t_camera *camera);
void				set_west(t_camera *camera);

int					game_loop(t_game *game);
#endif
