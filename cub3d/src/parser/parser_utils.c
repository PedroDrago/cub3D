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

void	init_map(t_map *map)
{
	map->map = NULL;
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
