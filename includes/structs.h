#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_data;

typedef struct s_vector_d
{
	double x;
	double y;
} t_vector_d;

typedef struct s_vector_i
{
	int x;
	int y;
} t_vector_i;

typedef struct s_line
{
	int          height;
	int          start;
	int          end;
	unsigned int color;
} t_line;

typedef struct s_ray
{
	t_vector_d dir;
	t_vector_d camera;
	t_vector_i map;
	t_vector_d side_dist;
	t_vector_d delta_dist;
	double     wall_dist;
	t_vector_i step;
	int        hit;
	int        side;
} t_ray;

typedef struct s_map
{
	char       **map;
	char		**mini_map;
	int          width;
	int          height;
	char       **map_file_array;
	int          file_height;
	int          file_width;
	char        *north_path;
	char        *south_path;
	char        *west_path;
	char        *east_path;
	char        *floor_rgb;
	char        *ceiling_rgb;
	unsigned int floor_color;
	unsigned int ceiling_color;
} t_map;

typedef struct s_camera
{
	double     mov_speed;
	double     rot_speed;
	t_vector_d pos;
	t_vector_d dir;
	t_vector_d plane;
} t_camera;

typedef struct s_game
{
	int      keys[20];
	t_data textures[4];
	int      texture_index;
	t_camera camera;
	t_map    map;
	void    *mlx;
	void    *win;
	int	should_end;
} t_game;

#endif
