#include "../includes/cub3d.h"

int	key_hook(int key, t_game *game)
{
	/*printf("%i\n", key);*/
	if (key == ESC)
	{
		exit(1);
	}
	return (0);
}

// NOTE: Ideia: Hashmap com todas as teclas do jogo como keys, e os values seriam ponteiros da função especifica a ser executada em cada tecla. Seria o mais otimizado possivel, porem sera que vale a pena?

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(int argc, char *argv[])
{
	t_game	game;
	t_image bluestone;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Cub3D");
	mlx_key_hook(game.win, key_hook, &game);
	bluestone.img = mlx_xpm_file_to_image(game.mlx, "./assets/bluestone.xpm", &bluestone.x, &bluestone.y);
	bluestone.addr = mlx_get_data_addr(bluestone.img, &bluestone.bits_per_pixel, &bluestone.line_length, &bluestone.endian);
	mlx_put_image_to_window(game.mlx, game.win, bluestone.img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
