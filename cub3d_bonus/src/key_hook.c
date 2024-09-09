/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:01:13 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 21:01:16 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int	get_cam_pos(t_game *game, t_vector_i *pos)
{
	t_vector_i player;

	player.x = game->camera.pos.x;
	player.y = game->camera.pos.y;
	if (game->map.map[player.x + 1][player.y] == 'C' || game->map.map[player.x + 1][player.y] == 'O')
	{
		pos->x = player.x + 1;
		pos->y = player.y;
	}
	else if (game->map.map[player.x - 1][player.y] == 'C' || game->map.map[player.x - 1][player.y] == 'O')
	{
		pos->x = player.x - 1;
		pos->y = player.y;
	}
	else if (game->map.map[player.x][player.y + 1] == 'C' || game->map.map[player.x][player.y + 1] == 'O')
	{
		pos->x = player.x;
		pos->y = player.y + 1;
	}
	else if (game->map.map[player.x][player.y - 1] == 'C' || game->map.map[player.x][player.y - 1] == 'O')
	{
		pos->x = player.x;
		pos->y = player.y - 1;
	}
	else
		return (0);
	return (1);
}

int	toggle_door(t_game *game)
{
	t_vector_i pos;
	t_vector_i dim;
	char **copy_map;

	pos.x = (int)(game->camera.pos.x);
	pos.y = (int)(game->camera.pos.y);

	printf("AAAA\n");
	if (!get_cam_pos(game, &pos))
		return (1);
	if (game->map.map[pos.x][pos.y] == 'O')
	{
		game->map.map[pos.x][pos.y] = 'C';
		game->map.mini_map[pos.x][pos.y] = 'C';
	}
	else if (game->map.map[pos.x][pos.y] == 'C')
	{
		copy_map = duplicate_map_bordered(game->map.map, game->map.height, game->map.width);
		if (!copy_map)
			return (0);
		dim.x = game->map.height + 2;
		dim.y = game->map.width + 1;
		ft_floodfill(copy_map, 0, 0, dim);
		if ((copy_map[(int)pos.x][(int)pos.y + 1] == '2')
				|| (copy_map[(int)pos.x][(int)pos.y - 1] == '2')
				|| (copy_map[(int)pos.x + 1][(int)pos.y] == '2')
				|| (copy_map[(int)pos.x - 1][(int)pos.y] == '2'))
		{
			free_split(copy_map);
			return (1);
		}
		free_split(copy_map);
		game->map.map[pos.x][pos.y] = 'O';
		game->map.mini_map[pos.x][pos.y] = 'O';
	}
	return (1);
}

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
	if (key == SPACE)
		if (!toggle_door(game))
			clean_exit(game);
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
