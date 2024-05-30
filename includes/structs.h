#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_data
{
	double posX;
	double posY;
	double planeX;
	double planeY;
	double dirX;
	double dirY;
	double time;
	double oldTime;
	double moveSpeed;
	double rotSpeed;
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

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player
{
} t_player;

typedef struct s_map
{
	char **map;
} t_map;

typedef struct s_ray
{
	t_vector dir;
} t_ray;
typedef struct s_game
{
	t_data   data;
	t_player player;
	t_vector camera;
	t_ray    ray;
	double   time;
	double   old_time;
	void    *mlx;
	void    *win;
} t_game;

#endif
