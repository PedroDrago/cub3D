# ifndef CUB3D_H
# define CUB3D_H
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

# define ESC 65307

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

typedef struct s_player
{
	t_image	image;
	int	x;
	int	y;
}	t_player;

typedef struct s_game
{
	t_player *player;
	void	*mlx;
	void	*win;
}	t_game;
# endif
