#include "../includes/cub3d.h"
#include <fcntl.h>
#include <stdio.h>


int get_map_proportions(t_map_data *map_data, char *file_path)
{
	int fd;
	int len;
	char *line;

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

int read_map_file(t_map_data *map_data, char *file_path)
{
	int fd;
	int i;
	char *line;

	map_data->map_file_array = malloc(sizeof(char *) * (map_data->file_height + 1));
	if (!map_data->map_file_array)
		return(0);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return 0;
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		map_data->map_file_array[i++] = line;
		line = get_next_line(fd);
	}
	map_data->map_file_array[i] = NULL;
	close(fd);
	return 1;

}

void print_map_data(t_map_data *map_data)
{
	int i;

	printf("file_width: %i\n", map_data->file_width);
	printf("file_height: %i\n", map_data->file_height);
	printf("---------------------------\n");
	i = 0;
	while(map_data->map_file_array[i])
		printf("%s", map_data->map_file_array[i++]);
}

int main(int argc, char *argv[])
{
	t_map_data map_data;
	map_data.file_height = 0;
	map_data.file_width = 0;
	if (argc != 2)
	{
		printf("Too much or too many arguments\n");
		exit(1);
	}
	get_map_proportions(&map_data, argv[1]);
	read_map_file(&map_data, argv[1]);
	print_map_data(&map_data);
	return 0;
}
