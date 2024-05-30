#ifndef STRUCTS_H
#define STRUCTS_H

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

typedef struct s_data
{
	t_vector_d pos;
	t_vector_d plane;
	t_vector_d dir;
	double     time;
	double     oldTime;
	double     moveSpeed;
	double     rotSpeed;
} t_data;

typedef struct s_image
{
	void *img;
	char *addr;
	int   bits_per_pixel;
	int   line_length;
	int   endian;
	int   x;
	int   y;
	int   width;
	int   height;
} t_image;

typedef struct s_line
{
	int          height;
	int          start;
	int          end;
	unsigned int color;
} t_line;

typedef struct s_ray
{
	t_vector_i map;
	t_vector_d camera;
	t_vector_d dir;
	// length of ray from current position to next x or y-side
	t_vector_d side_dist;
	t_vector_d delta_dist;
	double     perp_wall_dist;
	// what direction to step in x or y-direction (either +1 or -1)
	t_vector_d step;
	// was there a wall hit?
	int hit;
	// was a NS or a EW wall hit?
	int side;

} t_ray;

typedef struct s_player
{
} t_player;

typedef struct s_map
{
	char **map;
} t_map;

typedef struct s_game
{
	t_data     data;
	t_player   player;
	t_vector_d camera;
	t_ray      ray;
	double     time;
	double     old_time;
	void      *mlx;
	void      *win;
} t_game;

#endif
