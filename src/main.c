/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:01:03 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 21:01:04 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int mouse_hook(int x, int y, t_game *game)
{
	int	delta;

	delta = x - S_WIDTH / 2;
	game->camera.dir.x = game->camera.dir.x * cos(-delta * 0.001)
		- game->camera.dir.y * sin(-delta * 0.001);
	game->camera.dir.y = game->camera.dir.x * sin(-delta * 0.001)
		+ game->camera.dir.y * cos(-delta * 0.001);
	game->camera.plane.x = game->camera.plane.x * cos(-delta * 0.001)
		- game->camera.plane.y * sin(-delta * 0.001);
	game->camera.plane.y = game->camera.plane.x * sin(-delta * 0.001)
		+ game->camera.plane.y * cos(-delta * 0.001);
	mlx_mouse_move(game->mlx, game->win, S_WIDTH / 2, S_HEIGHT / 2);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	(void) argc;
	game.should_end = 0;
	zero_keys_array(&game);
	ft_bzero(game.keys, 20);
	get_map(&game, argv[1]);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	init_camera(&game.camera, &game);
	init_textures(&game);
	mlx_mouse_move(game.mlx, game.win, S_WIDTH / 2, S_HEIGHT / 2);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, MotionNotify, PointerMotionMask, &mouse_hook, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_hook_down, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &key_hook_up, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask, clean_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
