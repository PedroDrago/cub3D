#include "../includes/cub3d.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
	t_game	game;
	t_data square;
	int x = 0;
	int y = 0;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	square.img = mlx_new_image(game.mlx, S_WIDTH, S_HEIGHT);
	square.addr = mlx_get_data_addr(square.img, &square.bits_per_pixel, &square.line_length, &square.endian);
	draw_square(&square, x, y);
	x += SQUARE_SIDE;
	y += SQUARE_SIDE;
	draw_square(&square, x, y);
	mlx_put_image_to_window(game.mlx, game.win, square.img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
