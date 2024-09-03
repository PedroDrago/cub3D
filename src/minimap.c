/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:14:36 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/03 20:14:37 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_data *image, int y, int x, unsigned int color,
		int square_side)
{
	int	i;
	int	j;

	i = y;
	while (i < (y + square_side))
	{
		j = x;
		while (j < (x + square_side))
		{
			my_mlx_pixel_put(image, j, i, color);
			j++;
		}
		i++;
	}
}

int	get_square_size(t_map *map)
{
	int	width;
	int	height;

	width = S_WIDTH / map->width;
	height = S_HEIGHT / map->height;
	if (width < height)
		return (width);
	return (height);
}

void	draw_map(t_game *game, t_data *tile)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	square_side;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	square_side = get_square_size(&game->map);
	square_side /= 3;
	while (game->map.mini_map[i])
	{
		j = 0;
		x = 0;
		while (game->map.mini_map[i][j])
		{
			if (game->map.mini_map[i][j] == ' '
				|| game->map.mini_map[i][j] == '0')
				draw_square(tile, y, x, RGB_WHITE, square_side);
			else if (game->map.mini_map[i][j] == '1')
				draw_square(tile, y, x, RGB_PURPLE, square_side);
			else
				draw_square(tile, y, x, RGB_GREEN, square_side);
			j++;
			x += square_side;
		}
		y += square_side;
		i++;
	}
}
