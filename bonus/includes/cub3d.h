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
# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include "../../minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef SENSE
#  define SENSE 8
# endif
# define SOUTH 0
# define NORTH 1
# define EAST 2
# define WEST 3
# define OPEN 4
# define CLOSED 5
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
# define SPACE 32
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define ESC 65307
# define I_W 0
# define I_A 1
# define I_S 2
# define I_D 3
# define I_LEFT 4
# define I_RIGHT 5
# define I_OPEN 6
# define I_CLOSED 7
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

typedef struct s_sprite
{
	t_data			frame1;
	t_data			frame2;
	t_data			frame3;
	t_data			frame4;
}					t_sprite;

typedef struct s_game
{
	char			*open_door_texture;
	char			*closed_door_texture;
	int				keys[20];
	t_data			textures[6];
	t_sprite		weapon_sprites;
	int				texture_index;
	t_camera		camera;
	t_map			map;
	void			*mlx;
	void			*win;
	int				is_shooting;
	int				should_end;
}					t_game;

void				set_south(t_camera *camera);
void				set_north(t_camera *camera);
void				set_east(t_camera *camera);
void				set_west(t_camera *camera);
int					get_initial_pos(char **map, t_vector_d *pos);
void				free_split(char **splited);
void				walk_forward(t_camera *cam, char **map, char **minimap);
void				walk_backwards(t_camera *cam, char **map, char **minimap);
void				walk_left(t_camera *cam, char **map, char **minimap);
void				walk_right(t_camera *cam, char **map, char **minimap);
void				rotate_left(t_camera *camera);
void				rotate_right(t_camera *camera);
int					clean_exit(t_game *game);
void				draw_background(t_data *frame, unsigned int ceil_rgb,
						unsigned int floor_rgb);
void				setup_raycasting(t_game *game, t_ray *ray, int x);
void				calculate_line(t_ray *ray, t_line *line);
void				digital_diferencial_analysis(t_game *game, t_ray *ray,
						t_line *line);
void				draw_line(t_data *img, t_line line, t_ray *ray,
						t_game *game);
void				zero_keys_array(t_game *game);
void				get_map(t_game *game, char *file);
void				init_camera(t_camera *camera, t_game *game);
void				init_textures(t_game *game);
int					game_loop(t_game *game);
int					key_hook_down(int key, t_game *game);
int					key_hook_up(int key, t_game *game);
int					is_empty_tile(char c);
int					split_len(char **splited);
char				**ft_split_charset(char *str, const char *charset);
char				*remove_linebreak(char *line);
int					check_extension(char *file);
void				error_exit(int status, char *msg);
void				init_map(t_map *map);
int					get_map_proportions(t_map *map_data, char *file_path);
int					read_map_file(t_map *map_data, char *file_path);
int					parse_map(t_map *map_data);
void				free_map(t_map *map);
void				fill_spaces_with_zero(char **map, int height, int width);
int					validate_map(char **map, int height, int width);
int					rgb_to_hex(char *rgb);
int					files_exist(t_map *map);
int					is_empty_line(char *line);
int					parse_data(t_map *map_data, char *line);
int					is_player_char(char c);
char				*ft_strdup_margin(const char *s);
int					get_initial_pos_i(char **map, t_vector_i *pos, int height,
						int width);
char				**duplicate_map_bordered(char **map, int height, int width);
char				**duplicate_map(char **map, int height);
void				ft_floodfill(char **map, int i, int j,
						t_vector_i dimensions);
void				draw_map(t_game *game, t_data *tile);
void				draw_weapon(t_game *game, t_data *frame);
int					toggle_door(t_game *game);
void				slowly_rotate_right(t_camera *camera);
void				slowly_rotate_left(t_camera *camera);
void				my_mlx_pixel_put(t_data *img, int x, int y,
						unsigned int color);
#endif
