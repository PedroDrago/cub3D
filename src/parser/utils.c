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

int	is_invalid_char(char c)
{
	return (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ');
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

void	exit_printing(int status, char *msg)
{
	printf("%s\n", msg);
	exit(status);
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

void	destroy_map(t_map *map)
{
	free_split(map->map);
}
