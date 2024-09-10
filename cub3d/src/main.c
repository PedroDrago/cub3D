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

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc < 2)
		return (1);
	game.should_end = 0;
	game.is_shooting = 0;
	zero_keys_array(&game);
	ft_bzero(game.keys, 20);
	get_map(&game, argv[1]);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	init_camera(&game.camera, &game);
	init_textures(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_hook_down, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &key_hook_up, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask, clean_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
