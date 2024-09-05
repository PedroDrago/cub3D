/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:39:01 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 20:40:04 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	if (ft_strlen(line) == 0)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*remove_linebreak(char *line)
{
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}

void	destroy_map_data(t_map *map_data)
{
	free_split(map_data->map);
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->mini_map = NULL;
	map->file_width = 0;
	map->file_height = 0;
	map->width = 0;
	map->height = 0;
	map->map_file_array = NULL;
	map->east_path = NULL;
	map->west_path = NULL;
	map->south_path = NULL;
	map->north_path = NULL;
	map->ceiling_rgb = NULL;
	map->floor_rgb = NULL;
}
