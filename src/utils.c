#include "../includes/cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	count;
	char	*ptr;

	count = 0;
	ptr = (char *) s;
	while (count < n)
	{
		ptr[count] = c;
		count++;
	}
	return (s);
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

void print_map_data(t_map *map_data)
{
	printf("north_path: %s\n", map_data->north_path);
	printf("south_path: %s\n", map_data->south_path);
	printf("west_path: %s\n", map_data->west_path);
	printf("east_path: %s\n", map_data->east_path);
	printf("floor_color: %s\n", map_data->floor_rgb);
	printf("ceiling_color: %s\n", map_data->ceiling_rgb);
	print_split(map_data->map);
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
	while(splited && splited[i])
		free(splited[i++]);
	free(splited);
}

void	print_all_map_file(t_map *map_data)
{
	int	i;

	i = 0;
	while(map_data->map_file_array[i])
		printf("%s\n", map_data->map_file_array[i++]);
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
