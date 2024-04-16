#include "../includes/cub3d.h"
#include <stdio.h>

int	key_hook(int key, t_game *game)
{
	printf("%i\n", key);
	if (key == ESC)
	{
		exit(1);
	}
	return (0);
	(void) game;
}
// NOTE: Ideia: Hashmap com todas as teclas do jogo como keys, e os values seriam ponteiros da função especifica a ser executada em cada tecla. Seria o mais otimizado possivel, porem sera que vale a pena?



void	init_player(t_game *game, t_player *player)
{
	player->image.img = mlx_new_image(game->mlx, 50, 50);
	player->image.addr = mlx_get_data_addr(player->image.img, &player->image.bits_per_pixel, &player->image.line_length, &player->image.endian);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	test(int key, t_game *game)
{
	static int	x;
	static int	y;
	int	factor;

	mlx_clear_window(game->mlx, game->win);
	printf("%i\n", key);
	factor = 15;
	if (key == 119)
		y -= factor;
	if (key == 97)
		x -= factor;
	if (key == 115)
		y += factor;
	if (key == 100)
		x += factor;
	if (key == 65307)
		exit(1);
	mlx_put_image_to_window(game->mlx, game->win, game->player->image.img, x, y);
	return (1);
}
int main(int argc, char *argv[])
{
	t_game	game;
	t_player player;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Cub3D");
	/*mlx_key_hook(game.win, key_hook, &game);*/
	game.player = &player;
	mlx_hook(game.win, 2, (1L<<0), test, &game);
	init_player(&game, &player);
	int	x = 0;
	while (x < 100)
	{

		int	y = 0;
		while (y < 100)
			my_mlx_pixel_put(&player.image, x, y++, 0x00FF0000);
		x++;
	}
	mlx_loop(game.mlx);

	(void) argc;
	(void) argv;
	return 0;
}
