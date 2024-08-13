
#include "../../includes/cub3d.h"
#include <stdio.h>

void fill_spaces_with_zero(char **map, int height, int width)
{
	int i;
	int j;
	i = 0;
	while(i < height)
	{
		j = 0;
		while(j < width)
		{
			if (map[i][j] == ' ')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

char *get_spaced_line(char *line, int len)
{
	char *spaced_line;
	int i;

	spaced_line = malloc(sizeof(char) * (len + 1));
	if (!spaced_line)
		return(NULL);
	i = 0;
	while(line[i])
	{
		spaced_line[i] = line[i];
		i++;
	}
	while(i < len - 1)
		spaced_line[i++] = ' ';
	spaced_line[i] = '\0';
	return spaced_line;
}


int get_map_array(t_map *map_data, int start)
{
	int	tmp;
	int len;
	int	i;

	map_data->height = 0;
	map_data->width = 0;
	tmp = start;
	i = 0;
	while (map_data->map_file_array[tmp])
	{
		len = ft_strlen(map_data->map_file_array[tmp]);
		if (len > map_data->width)
			map_data->width = len;
		map_data->height++;
		tmp++;
	}
	if (map_data->height < 3 || map_data->width < 4)
	{
		printf("[%s: %i] Error\nMap too small\n", __FILE__, __LINE__);
		return 0;
	}
	map_data->map = malloc(sizeof(char *) * (map_data->height + 1));
	if (!map_data->map)
		return 0;
	while(i < map_data->height)
	{
		len = ft_strlen(map_data->map_file_array[start]);
		if (len < map_data->width)
		{
			map_data->map_file_array[start] = remove_linebreak(map_data->map_file_array[start]);
			map_data->map[i] = get_spaced_line(map_data->map_file_array[start], map_data->width);
		}
		else
			map_data->map[i] = remove_linebreak(ft_strdup(map_data->map_file_array[start]));
		i++;
		start++;
	}
	map_data->map[i] = NULL;
	return 1;
}


int parse_map(t_map *map_data)
{
	int i;
	int data_count;

	i = 0;
	data_count = 0;
	while(map_data->map_file_array[i] && data_count < 6)
	{
		if (!is_empty_line(map_data->map_file_array[i]) && data_count < 6)
		{
			if (!parse_data(map_data, map_data->map_file_array[i]))
				return 0;
			data_count++;
		}
		i++;
	}
	if (map_data->north_path == NULL || map_data->south_path == NULL || map_data->west_path == NULL || map_data->east_path == NULL || map_data->floor_rgb == NULL || map_data->ceiling_rgb == NULL)
	{
		printf("[%s: %i] Error\nMissing some information in map file\n", __FILE__, __LINE__);
		return 0;
	}
	while(is_empty_line(map_data->map_file_array[i]))
		i++;
	if (!get_map_array(map_data, i))
		return 0;
	return 1;
}



int get_map_proportions(t_map *map_data, char *file_path)
{
	int fd;
	int len;
	char *line;

	len = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return 0;
	line = get_next_line(fd);
	while(line)
	{
		map_data->file_height++;
		len = ft_strlen(line);
		if (len > map_data->file_width)
			map_data->file_width = len;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return 1;
}
