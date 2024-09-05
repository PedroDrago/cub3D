/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:09:39 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 21:09:40 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_initial_pos_i(char **map, t_vector_i *pos, int height, int width)
{
	int	x;
	int	y;

	x = 0;
	printf("h: %i | w: %i\n", height, width);
	while (x < height)
	{
		y = 0;
		while (y < width)
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E'
				|| map[x][y] == 'W')
			{
				pos->x = x;
				pos->y = y;
				return (1);
			}
			y++;
		}
		x++;
	}
	printf("Exiting at get_initial_pos_i\n");
	exit(1);
	return (0);
}

int	get_initial_pos(char **map, t_vector_d *pos)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E'
				|| map[x][y] == 'W')
			{
				pos->x = x + 0.5;
				pos->y = y + 0.5;
				return (1);
			}
			y++;
		}
		x++;
	}
	printf("Exiting at get_initial_pos\n");
	exit(1);
	return (0);
}
