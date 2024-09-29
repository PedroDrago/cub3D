#include "../../includes/cub3d.h"

int	get_map_proportions(t_map *map_data, char *file_path)
{
	int		fd;
	int		len;
	char	*line;

	len = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		map_data->file_height++;
		len = ft_strlen(line);
		if (len > map_data->file_width)
			map_data->file_width = len;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
