/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:14:36 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 21:09:31 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_data *image, t_vector_i vec
		, unsigned int color, int square_side)
{
	int	i;
	int	j;

	i = vec.y;
	while (i < (vec.y + square_side))
	{
		j = vec.x;
		while (j < (vec.x + square_side))
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

void	set_minimap_data(t_minimap_data *data, t_game *game)
{
	data->i = 0;
	data->j = 0;
	data->vec.x = 0;
	data->vec.y = 0;
	data->square_side = get_square_size(&game->map);
	data->square_side /= 3;
}

void	draw_map(t_game *game, t_data *tile)
{
	t_minimap_data	data;

	set_minimap_data(&data, game);
	while (game->map.mini_map[data.i])
	{
		data.j = 0;
		data.vec.x = 0;
		while (game->map.mini_map[data.i][data.j])
		{
			if (game->map.mini_map[data.i][data.j] == ' '
				|| game->map.mini_map[data.i][data.j] == '0'
				|| game->map.mini_map[data.i][data.j] == 'O')
				draw_square(tile, data.vec, RGB_WHITE, data.square_side);
			else if (game->map.mini_map[data.i][data.j] == '1')
				draw_square(tile, data.vec, RGB_PURPLE, data.square_side);
			else if (game->map.mini_map[data.i][data.j] == 'C')
				draw_square(tile, data.vec, RGB_BROWN, data.square_side);
			else
				draw_square(tile, data.vec, RGB_GREEN, data.square_side);
			data.j++;
			data.vec.x += data.square_side;
		}
		data.vec.y += data.square_side;
		data.i++;
	}
}
