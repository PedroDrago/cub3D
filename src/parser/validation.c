#include "../../includes/cub3d.h"

int	validate_characters(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
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

void	ft_floodfill(char **map, int i, int j, int height, int width)
{
	if (i < 0 || i >= height || j < 0 || j >= width || map[i][j] != '0')
		return ;
	map[i][j] = '2';
	ft_floodfill(map, i + 1, j, height, width);
	ft_floodfill(map, i - 1, j, height, width);
	ft_floodfill(map, i, j + 1, height, width);
	ft_floodfill(map, i, j - 1, height, width);
}

char	**duplicate_map_bordered(char **map, int height, int width)
{
	char	**copy_map;
	int		i;
	int		j;

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
	while (map[j])
		copy_map[i++] = ft_strdup_margin(map[j++]);
	copy_map[i] = malloc(sizeof(char) * (width + 1));
	if (!copy_map[i])
		return (NULL);
	j = 0;
	while (j < width + 1)
		copy_map[i][j++] = '0';
	copy_map[++i] = NULL;
	return (copy_map);
}

int	validate_map(char **map, int height, int width)
{
	char		**copy_map;
	t_vector_i	pos;

	pos.x = 0;
	pos.y = 0;
	if (!validate_characters(map))
	{
		printf("[%s:%i] Error\nInvalid Characters\n", __FILE__, __LINE__);
		return (0);
	}
	copy_map = duplicate_map_bordered(map, height, width);
	if (!copy_map)
		return (0);
	get_initial_pos_i(copy_map, &pos, height, width);
	ft_floodfill(copy_map, 0, 0, height, width);
	if ((copy_map[(int)pos.x][(int)pos.y + 1] == '2') || (copy_map[(int)pos.x][(int)pos.y - 1] == '2') || (copy_map[(int)pos.x + 1][(int)pos.y] == '2') || (copy_map[(int)pos.x - 1][(int)pos.y] == '2'))
	{
		printf("[%s:%i] Error\nMap must be Surroundede\n", __FILE__, __LINE__);
		free_split(copy_map);
		return (0);
	}
	free_split(copy_map);
	return (1);
}
