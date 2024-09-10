/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:39:01 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/04 20:39:35 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_invalid_char(char c)
{
	return (c != '1'
		&& c != '0'
		&& c != 'N'
		&& c != 'S'
		&& c != 'O'
		&& c != 'C'
		&& c != 'E'
		&& c != 'W'
		&& c != ' ');
}

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

char	**duplicate_map(char **map, int height)
{
	char	**copy_map;
	int		i;

	copy_map = malloc(sizeof(char *) * (height + 1));
	if (!copy_map)
		return (NULL);
	i = -1;
	while (++i < height)
		copy_map[i] = ft_strdup(map[i]);
	copy_map[i] = NULL;
	return (copy_map);
}

void	error_exit(int status, char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(status);
}

void	destroy_map(t_map *map)
{
	free_split(map->map);
}
