#include "../../includes/cub3d.h"

int	check_extension(char *file)
{
	char *dot;

	dot = ft_strrchr(file, '.');
	if (dot && !ft_strncmp(dot, ".cub", 5))
		return 1;
	return 0;
}

int read_map_file(t_map *map_data, char *file_path)
{
	int fd;
	int i;
	char *line;

	map_data->map_file_array = malloc(sizeof(char *) * (map_data->file_height + 1));
	if (!map_data->map_file_array)
		return(0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		free(map_data->map_file_array);
		return 0;
	}
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		map_data->map_file_array[i++] = line; // Does not need free cause we save the pointer instead of copying it
		line = get_next_line(fd);
	}
	map_data->map_file_array[i] = NULL;
	close(fd);
	return 1;
}

int files_exist(t_map *map)
{
	int fd;

	fd = open(map->north_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(map->south_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(map->east_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(map->west_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
