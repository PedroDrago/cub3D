#include "../includes/cub3d.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
		printf("[parse_texture -> parser.c] Error\nBad Formatting in Texture\n");
		free_split(splited);
		return 0;
	}
	if (!ft_strncmp(splited[0], "NO", 3) && (map_data->north_path == NULL))
		map_data->north_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "SO", 3) && (map_data->south_path == NULL))
		map_data->south_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "WE", 3) && (map_data->west_path == NULL))
		map_data->west_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "EA", 3) && (map_data->east_path == NULL))
		map_data->east_path =remove_linebreak(splited[1]);
	else
	{
		printf("[parse_textures -> parser.c] Error\nBad Formatting in Texture\n");
		free_split(splited);
		return 0;
	}
	free(splited[0]);
	free(splited);
	return 1;
}

int is_valid_rgb(char **rgb)
{
	int i;
	int j;

	i = 1;
	while (rgb[i])
	{
		j = 0;
		while(rgb[i][j])
		{
			if (isalpha(rgb[i][j]))
				return (0);
			j++;
		}
		j = ft_atoi(rgb[i]);
		if (j < 0 || j > 255)
			return (0);
		i++;
	}
	return (1);
}

int	parse_colors(t_map *map_data, char *line)
{
	char	**splited;
	char	**validation_splited;

	validation_splited = ft_split_charset(line, " ,\n");  //NOTE: just for validating the format
	if (!validation_splited || split_len(validation_splited) != 4 || !is_valid_rgb(validation_splited))
	{
		printf("[parse_colors -> parser.c] Error\nBad Formmatting in colors\n");
		free_split(validation_splited);
		return 0;
	}
	free_split(validation_splited);
	splited = ft_split(line, ' ');
	if (!ft_strncmp(splited[0], "F", 3) && (map_data->floor_rgb == NULL))
		map_data->floor_rgb = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "C", 3) && (map_data->ceiling_rgb == NULL))
		map_data->ceiling_rgb = remove_linebreak(splited[1]); 
	else
	{
		printf("[parse_colors -> parser.c] Error\n Bad Formmatting in colors\n");
		free_split(splited);
		return 0;
	}
	free(splited[0]);
	free(splited);
	return 1;
}

int parse_data(t_map *map_data, char *line)
{
	if (line[0] == 'F' || line[0] == 'C')
		return parse_colors(map_data, line);
	else
		return parse_texture(map_data, line);
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

unsigned int rgb_to_hex(char *rgb, int *sig)
{
	unsigned int color;
	char **splited;

	color = 0;
	splited = ft_split(rgb, ',');
	if (!splited[0] || !splited[1] || !splited[2])
	{ // WARN: if any of these indexes are NULL it means RGB lacks data (it should not happen, because it should be validated prior, in parser
		free_split(splited);
		*sig = -1;
		return 0;
	}
	color = (ft_atoi(splited[0]) << 16) | (ft_atoi(splited[1]) << 8) | ft_atoi(splited[2]);
	free_split(splited);
	return color;
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
		return 0;
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
		printf("Error\nMissing some information in map file\n");
		return 0;
	}
	while(is_empty_line(map_data->map_file_array[i]))
		i++;
	if (!get_map_array(map_data, i))
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


int	validate_characters(char **map)
{
	int i;
	int j;
	int player;

	i = 0;
	player = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != 'S' && map[i][j] != '0' && map[i][j] != '1')
				return (0);
			if (is_player_char(map[i][j]))
				player++;
			if (player > 1)
				return (0);
			j++;
		}
		i++;
	}
	if (player < 1)
		return (0);
	return (1);
}

char	*ft_strdup_margin(const char *s)
{
	char	*ret;
	int		count;
	int		count2;

	ret = (char *) malloc (sizeof(char) * ft_strlen(s) + 1 + 2);
	if (!ret)
		return (NULL);
	ret[0] = '0';
	count = 1;
	count2 = 0;
	while (s[count2])
	{
		ret[count++] = s[count2++];
	}
	ret[count++] = '0';
	ret[count] = '\0';
	return (ret);
}

void ft_floodfill(char **map, int i, int j, int height, int width)
{
	if (i < 0 || i >= height || j < 0 || j >= width || map[i][j] != '0')
		return;
	map[i][j] = '2';
	ft_floodfill(map, i + 1, j, height, width);
	ft_floodfill(map, i - 1, j, height, width);
	ft_floodfill(map, i, j + 1, height, width);
	ft_floodfill(map, i, j - 1, height, width);
}

char **duplicate_map_bordered(char **map, int height, int width)
{
	char **copy_map;
	int i;
	int j;

	copy_map = malloc(sizeof(char *) * (height + 3)); 
	if (!copy_map)
		return (NULL);
	copy_map[0] = malloc(sizeof(char) * (width + 1));
	if (!copy_map[0])
		return (NULL);
	i = 0;
	while (i < width + 1)
		copy_map[0][i++] = '0';
	i = 1;
	j = 0;
	while(map[j])
		copy_map[i++] = ft_strdup_margin(map[j++]);
	copy_map[i] = malloc(sizeof(char) * (width + 1));
	if (!copy_map[i])
		return (NULL);
	j = 0;
	while (j < width + 1)
		copy_map[i][j++] = '0';
	copy_map[++i] = NULL;
	return copy_map;
}

int validate_map(char **map, int height, int width)
{
	char **copy_map;
	t_vector_i pos;

	pos.x = 0;
	pos.y = 0;
	if (!validate_characters(map))
		return (0);
	copy_map = duplicate_map_bordered(map, height, width);
	if (!copy_map)
		return (0);
	get_initial_pos_i(copy_map, &pos);
	ft_floodfill(copy_map, 0, 0, height, width);
	if ((copy_map[(int)pos.x][(int)pos.y + 1] == '2') || (copy_map[(int)pos.x][(int)pos.y - 1] == '2') || (copy_map[(int)pos.x + 1][(int)pos.y] == '2') || (copy_map[(int)pos.x - 1][(int)pos.y] == '2'))
	{
		free_split(copy_map);
		return (0);
	}
	return (1);
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

char **duplicate_map(char **map, int height, int width)
{
	char **copy_map;
	int i;

	copy_map = malloc(sizeof(char *) * (height + 1));
	if (!copy_map)
		return (NULL);
	i = -1;
	while (++i < height)
		copy_map[i] = ft_strdup(map[i]);
	copy_map[i] = NULL;
	return copy_map;
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

void	get_map(t_game *game, char *file)
{
	if (!check_extension(file))
		exit_printing(1, "Error at check_extension");
	init_map(&game->map);
	if (!get_map_proportions(&game->map, file))
		exit_printing(1, "Error at get_map_proportions");
	if(!read_map_file(&game->map, file))
		exit_printing(1, "Error at read_map_file\n");
	if (!parse_map(&game->map))
	{
		free_map(&game->map);
		exit(1);
	}
	fill_spaces_with_zero(game->map.map, game->map.height, game->map.width);
	if (!validate_map(game->map.map, game->map.height, game->map.width))
	{
		free_map(&game->map);
		printf("Error at validate_map\n");
		exit(1);
	}
	free_split(game->map.map_file_array);
	game->map.map_file_array = NULL;
	print_map_data(&game->map);
	int sig = 1;
	game->map.floor_color = rgb_to_hex(game->map.floor_rgb, &sig);
	if (sig < 0)
	{
		free_map(&game->map);
		printf("Error at color formatting\n");
	}
	game->map.ceiling_color = rgb_to_hex(game->map.ceiling_rgb, &sig);
	free(game->map.floor_rgb);
	free(game->map.ceiling_rgb);
	if (!files_exist(&game->map))
	{
		free_map(&game->map);
		printf("Error at files_exist\n");
		exit(1);
	}
	game->map.mini_map = duplicate_map(game->map.map, game->map.height, game->map.width);
	print_split(game->map.mini_map);
}

void destroy_map(t_map *map)
{
	free_split(map->map);
}


// TODO: Adicionar validacoes do mapa
// - [ ] Descobrir um jeito de validar se o mapa esta cercado por paredes sem fazer com que espacos no meio do mapa gerem erro.

// TODO: Testar todos os cenarios de input e checar leak das saidas:
// - Falta de cada uma das texturas
// - Ma formatacao de cada uma das texturas
// - Ma formatacao do mapa
