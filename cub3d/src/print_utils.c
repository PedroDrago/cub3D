/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:07:21 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/03 19:07:37 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_split(char **splited)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(splited[0]);
	while (++i <= len + 1)
		printf("-");
	printf("\n");
	i = 0;
	while (splited[i])
		printf("!%s!\n", splited[i++]);
	i = -1;
	while (++i <= len + 1)
		printf("-");
	printf("\n");
}

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited && splited[i])
		free(splited[i++]);
	free(splited);
}

void	print_all_map_file(t_map *map_data)
{
	int	i;

	i = 0;
	while (map_data->map_file_array[i])
		printf("%s\n", map_data->map_file_array[i++]);
}

void	print_map_data(t_map *map_data)
{
	printf("north_path: %s\n", map_data->north_path);
	printf("south_path: %s\n", map_data->south_path);
	printf("west_path: %s\n", map_data->west_path);
	printf("east_path: %s\n", map_data->east_path);
	printf("floor_color: %s\n", map_data->floor_rgb);
	printf("ceiling_color: %s\n", map_data->ceiling_rgb);
	print_split(map_data->map);
}
