#include "../includes/cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



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

void	print_split(char **splited)
{
	int i = -1;
	int len = ft_strlen(splited[0]);
	while (++i <= len + 1)
		printf("-");
	printf("\n");
	i = 0;
	while(splited[i])
		printf("!%s!\n", splited[i++]);
	i = -1;
	while (++i <= len + 1)
		printf("-");
	printf("\n");
}

//9/4

void print_map_data(t_map *map_data)
{
	printf("north_path: %s\n", map_data->north_path);
	printf("south_path: %s\n", map_data->south_path);
	printf("west_path: %s\n", map_data->west_path);
	printf("east_path: %s\n", map_data->east_path);
	printf("floor_color: %s\n", map_data->floor_color);
	printf("ceiling_color: %s\n", map_data->ceiling_color);
	print_split(map_data->map);
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


void	destroy_map_data(t_map *map_data)
{
	free_split(map_data->map);
}

int get_map_proportions(t_map *map_data, char *file_path)
{
	int fd;
	int len;
	char *line;

	len = 0;
	printf("File: !%s!\n", file_path);
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
	if (map_data->file_height < 3 || map_data->file_width < 3) //too small in height
		return 0;
	return 1;
}

int	check_extension(char *file)
{
	char *dot;

	dot = ft_strrchr(file, '.');
	if (dot && !ft_strncmp(dot, ".cub", 4))
		return 1;
	return 0;
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
	map->ceiling_color = NULL;
	map->floor_color = NULL;
}

int is_surrounded(char **map, int i, int j)
{
	if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
		return (0);
	if (map[i + 1] && map[i + 1][j] == ' ')
		return 0;
	if (map[i - 1][j] == ' ')
		return 0;
	// WARN: This approach will generate error when the map has a space character inside of it like:
	// 111111
	// 100001
	// 100 01
	// 100N01
	// 111111
	// The subject specifies that spaces are a valid part of the map, but is up to us to handle how we want.
	return (1);

}

int is_invalid_char(char c)
{
	return (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ');
}

int is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	validate_map(char **map, int height, int width)
{
	int i;
	int j;
	int has_player;

	i = 0;
	has_player = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (is_player_char(map[i][j]))
				has_player++;
			if (is_invalid_char(map[i][j]))
				return (0);
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (i == 0 || i == (height - 1) || j == 0 || j == (width - 1 ))
					return 0;
				if (!is_surrounded(map, i, j))
					return 0;
			}
			j++;
		}
		i++;
	}
	if (!has_player || has_player > 1)
		return (0);
	return (1);
}
void	get_map(t_game *game, char *file)
{
	if (!check_extension(file))
	{
		printf("Error at check_extension\n");
		exit(1);
	}
	init_map(&game->map);
	if (!get_map_proportions(&game->map, file))
	{
		printf("Error at get_map_proportions\n");
		exit(1);
	}
	if(!read_map_file(&game->map, file))
	{
		printf("Error at read_map_file\n");
		exit(1);
	}
	if (!parse_map(&game->map))
	{
		printf("Error at parse_map\n");
		exit(1);
	}
	if (!validate_map(game->map.map, game->map.height, game->map.width))
	{
		printf("Error at check_surrounded\n");
		exit(1);
	}
	free_split(game->map.map_file_array);
	game->map.map_file_array = NULL;
	print_map_data(&game->map);
}

void destroy_map(t_map *map)
{
	free_split(map->map);
}

// TODO: Adicionar validacoes do mapa

// TODO: Testar todos os cenarios de input e checar leak das saidas:
// - Falta de cada uma das texturas
// - Ma formatacao de cada uma das texturas
// - Ma formatacao do mapa
