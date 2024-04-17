# ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
	int		width;
	int		height;
}	t_image;

typedef struct s_map
{
	t_image	bluestone;
} 	t_map;

typedef struct s_player
{
	t_image	image;
	int	x;
	int	y;
}	t_player;

typedef struct s_game
{
	t_player player;
	t_map	map;
	void	*mlx;
	void	*win;
}	t_game;

#endif
