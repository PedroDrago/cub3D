/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:04:37 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 20:49:10 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clear_textures(t_game *game)
{
	mlx_destroy_image(game->mlx, game->textures[NORTH].img);
	mlx_destroy_image(game->mlx, game->textures[SOUTH].img);
	mlx_destroy_image(game->mlx, game->textures[EAST].img);
	mlx_destroy_image(game->mlx, game->textures[WEST].img);
	mlx_destroy_image(game->mlx, game->textures[CLOSED].img);
	mlx_destroy_image(game->mlx, game->weapon_sprites.frame1.img);
	mlx_destroy_image(game->mlx, game->weapon_sprites.frame2.img);
	mlx_destroy_image(game->mlx, game->weapon_sprites.frame3.img);
	mlx_destroy_image(game->mlx, game->weapon_sprites.frame4.img);
	mlx_destroy_image(game->mlx, game->lucas.img);
	mlx_destroy_image(game->mlx, game->frame.img);
}

void	free_map(t_map *map)
{
	free_split(map->map);
	free_split(map->mini_map);
	free_split(map->map_file_array);
	free(map->north_path);
	free(map->south_path);
	free(map->west_path);
	free(map->east_path);
	free(map->ceiling_rgb);
	free(map->floor_rgb);
}

void	mlx_clean(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	clear_textures(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	clean_exit(t_game *game)
{
	mlx_clean(game);
	free_map(&game->map);
	exit(1);
}
