#include "../../includes/cub3d.h"

int	rgb_to_hex(char *rgb)
{
	unsigned int	color;
	char			**splited;

	color = 0;
	splited = ft_split(rgb, ',');
	if (!splited[0] || !splited[1] || !splited[2])
	{
		free_split(splited);
		return (-1);
	}
	color = (ft_atoi(splited[0]) << 16) | (ft_atoi(splited[1]) << 8) | ft_atoi(splited[2]);
	free_split(splited);
	return (color);
}

int	parse_texture(t_map *map_data, char *line)
{
	char	**splited;

	splited = ft_split(line, ' ');
	if (split_len(splited) != 2)
	{
		printf("[%s: %i]Error\nBad Formatting in Texture\n", __FILE__, __LINE__);
		free_split(splited);
		return (0);
	}
	if (!ft_strncmp(splited[0], "NO", 3) && (map_data->north_path == NULL))
		map_data->north_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "SO", 3) && (map_data->south_path == NULL))
		map_data->south_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "WE", 3) && (map_data->west_path == NULL))
		map_data->west_path = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "EA", 3) && (map_data->east_path == NULL))
		map_data->east_path = remove_linebreak(splited[1]);
	else
	{
		printf("[%s: %i]Error\nBad Formatting in Texture\n", __FILE__, __LINE__);
		free_split(splited);
		return (0);
	}
	free(splited[0]);
	free(splited);
	return (1);
}

int is_valid_rgb(char **rgb)
{
	int	i;
	int	j;

	i = 1;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (ft_isalpha(rgb[i][j]))
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

	validation_splited = ft_split_charset(line, " ,\n");
	if (!validation_splited || split_len(validation_splited) != 4 || !is_valid_rgb(validation_splited))
	{
		printf("[%s: %i] Error\nBad Formmatting in colors\n", __FILE__, __LINE__);
		free_split(validation_splited);
		return (0);
	}
	free_split(validation_splited);
	splited = ft_split(line, ' ');
	if (!ft_strncmp(splited[0], "F", 3) && (map_data->floor_rgb == NULL))
		map_data->floor_rgb = remove_linebreak(splited[1]);
	else if (!ft_strncmp(splited[0], "C", 3) && (map_data->ceiling_rgb == NULL))
		map_data->ceiling_rgb = remove_linebreak(splited[1]);
	else
	{
		printf("[%s: %i] Error\nBad Formmatting in colors\n", __FILE__, __LINE__);
		free_split(splited);
		return (0);
	}
	free(splited[0]);
	free(splited);
	return (1);
}

int	parse_data(t_map *map_data, char *line)
{
	if (line[0] == 'F' || line[0] == 'C')
		return (parse_colors(map_data, line));
	else
		return (parse_texture(map_data, line));
}
