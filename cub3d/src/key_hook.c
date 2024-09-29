#include "../includes/cub3d.h"

int	key_hook_down(int key, t_game *game)
{
	if (key == ESC)
	{
		game->should_end = 1;
		return (0);
	}
	if (key == W)
		game->keys[I_W] = 1;
	if (key == A)
		game->keys[I_A] = 1;
	if (key == S)
		game->keys[I_S] = 1;
	if (key == D)
		game->keys[I_D] = 1;
	if (key == LEFT)
		game->keys[I_LEFT] = 1;
	if (key == RIGHT)
		game->keys[I_RIGHT] = 1;
	return (0);
}

int	key_hook_up(int key, t_game *game)
{
	if (key == ESC)
		return (1);
	if (key == W)
		game->keys[I_W] = 0;
	if (key == A)
		game->keys[I_A] = 0;
	if (key == S)
		game->keys[I_S] = 0;
	if (key == D)
		game->keys[I_D] = 0;
	if (key == LEFT)
		game->keys[I_LEFT] = 0;
	if (key == RIGHT)
		game->keys[I_RIGHT] = 0;
	return (0);
}

void	zero_keys_array(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 20)
		game->keys[i] = 0;
}
