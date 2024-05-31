#include "../includes/cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int get_map_proportions(t_map *map_data, char *file_path)
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
		map_data->map_file_array[i++] = line;
		line = get_next_line(fd);
	}
	map_data->map_file_array[i] = NULL;
	close(fd);
	return 1;

}

void print_map_data(t_map *map_data)
{
	int i;

	printf("file_width: %i\n", map_data->file_width);
	printf("file_height: %i\n", map_data->file_height);
	printf("north_path: %s\n", map_data->north_path);
	printf("south_path: %s\n", map_data->south_path);
	printf("west_path: %s\n", map_data->west_path);
	printf("east_path: %s\n", map_data->east_path);
	printf("floor_color: %s\n", map_data->floor_color);
	printf("ceiling_color: %s\n", map_data->ceiling_color);
	printf("---------------------------\n");
	i = 0;
	while(map_data->map[i])
		printf("%s\n", map_data->map[i++]);
}

int is_empty_line(char *line)
{
	int i;
	if (ft_strlen(line) == 0)
		return 1;
	i = 0;
	while(line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return 0;
		i++;
	}
	return 1;
}

int	split_len(char **splited)
{
	int	len;

	len = 0;
	while (splited[len])
		len++;
	return len;
}

void	free_split(char **splited)
{
	int	i;
	
	i = 0;
	while(splited[i])
		free(splited[i++]);
	free(splited);
}

char *remove_linebreak(char *line)
{
	line[ft_strlen(line) - 1] = '\0';
	return line;
}

int	parse_texture(t_map *map_data, char *line)
{
	char	**splited;

	splited = ft_split(line, ' ');
	if (split_len(splited) != 2)
	{
		free_split(splited);
		return 0;
	}
	if (!ft_strncmp(splited[0], "NO", 3))
		map_data->north_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "SO", 3))
		map_data->south_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "WE", 3))
		map_data->west_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "EA", 3))
		map_data->east_path =remove_linebreak(splited[1]);
	else
	{
		free_split(splited);
		return 0;
	}
	free(splited[0]);
	free(splited);
	return 1;
}

int	parse_colors(t_map *map_data, char *line)
{
	char	**splited;

	splited = ft_split(line, ' ');
	if (split_len(splited) != 2)
	{
		free_split(splited);
		return 0;
	}
	if (!ft_strncmp(splited[0], "F", 3))
		map_data->floor_color = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "C", 3))
		map_data->ceiling_color = remove_linebreak(splited[1]); 
	else
	{
		free_split(splited);
		return 0;
	}
	free(splited[0]);
	free(splited);
	return 1;
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
	map_data->map = malloc(sizeof(char *) * (map_data->height + 1));
	if (!map_data->map)
		return 0;
	while(i < map_data->height) // WARN: <= ?
	{
		len = ft_strlen(map_data->map_file_array[start]);
		printf("len: %i | width: %i\n", len, map_data->width);
		if (len < map_data->width)
		{
			map_data->map_file_array[start] = remove_linebreak(map_data->map_file_array[start]);
			map_data->map[i] = get_spaced_line(map_data->map_file_array[start], map_data->width);
		}
		else
			map_data->map[i] = remove_linebreak(ft_strdup(map_data->map_file_array[start])); // WARN: dupping to make freeing easy later avoiding double frees with map file array;
		i++;
		start++;
	}
	map_data->map[i] = NULL;
	return 1;
}

void	print_all_map_file(t_map *map_data)
{
	int	i;

	i = 0;
	while(map_data->map_file_array[i])
		printf("%s\n", map_data->map_file_array[i++]);
}

int get_map_data(t_map *map_data)
{
	int i;
	int data_count;

	i = 0;
	data_count = 0;
	while(map_data->map_file_array[i] && data_count < 6)
	{
		if (!is_empty_line(map_data->map_file_array[i]) && data_count < 4)
		{
			if (!parse_texture(map_data, map_data->map_file_array[i]))
				return 0;
			data_count++;
		}
		else if (!is_empty_line(map_data->map_file_array[i]) && data_count < 6)
		{
			if (!parse_colors(map_data, map_data->map_file_array[i]) && data_count < 6)
				return 0;
			data_count++;
		}
		i++;
	}
	while(is_empty_line(map_data->map_file_array[i]))
		i++;
	if (!get_map_array(map_data, i))
		return 0;
	return 1;
}

int parse_map(t_map *map_data)
{
	if (!get_map_data(map_data))
		return 0;
	return 1;
}
int main(int argc, char *argv[])
{
	t_map map_data;
	map_data.file_height = 0;
	map_data.file_width = 0;
	if (argc != 2)
	{
		printf("Too much or too many arguments\n");
		exit(1);
	}
	get_map_proportions(&map_data, argv[1]);
	read_map_file(&map_data, argv[1]);
	parse_map(&map_data);
	print_map_data(&map_data);
	return 0;
}
