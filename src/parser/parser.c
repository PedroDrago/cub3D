/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:26:39 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 20:26:40 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	part1(t_game *game, char *file)
{
	if (!check_extension(file))
		error_exit(1, "Error\nWrong extension\n");
	init_map(&game->map);
	if (!get_map_proportions(&game->map, file))
		error_exit(1, "Error\nFile not found\n");
	if (!read_map_file(&game->map, file))
		error_exit(1, "Error\nInternal Error\n");
	if (!parse_map(&game->map))
	{
		free_map(&game->map);
		error_exit(1, "Error\nInvalid Map\n");
	}
	fill_spaces_with_zero(game->map.map, game->map.height, game->map.width);
	if (!validate_map(game->map.map, game->map.height, game->map.width))
	{
		free_map(&game->map);
		error_exit(1, "Error\nInvalid Map\n");
	}
	free_split(game->map.map_file_array);
	game->map.map_file_array = NULL;
}

void	part2(t_game *game)
{
	int	hold;

	game->map.floor_color = rgb_to_hex(game->map.floor_rgb);
	hold = rgb_to_hex(game->map.floor_rgb);
	if (hold < 0)
	{
		free_map(&game->map);
		error_exit(1, "Error\nInvalid color formatting\n");
	}
	game->map.floor_color = hold;
	hold = rgb_to_hex(game->map.ceiling_rgb);
	if (hold < 0)
	{
		free_map(&game->map);
		error_exit(1, "Error\nInvalid color formatting\n");
	}
	game->map.ceiling_color = hold;
	free(game->map.floor_rgb);
	free(game->map.ceiling_rgb);
	game->map.floor_rgb = NULL;
	game->map.ceiling_rgb = NULL;
}

void	part3(t_game *game)
{
	game->map.mini_map = duplicate_map(game->map.map, game->map.height);
	if (!files_exist(&game->map))
	{
		free_map(&game->map);
		error_exit(1,"Error\n Invalid File\n");
	}
}

void	get_map(t_game *game, char *file)
{
	part1(game, file);
	part2(game);
	part3(game);
}
