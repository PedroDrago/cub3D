#include "../../includes/cub3d.h"

char	*split_string(char *str, int start, int end)
{
	int		i;
	char	*new_str;

	new_str = malloc(sizeof(char) * (end - start + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (start <= end)
		new_str[i++] = str[start++];
	new_str[i] = '\0';
	return (new_str);
}

int	is_in_charset(char c, const char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

int	count_words(char *str, const char *charset)
{
	int	end;
	int	count;

	end = 0;
	count = 0;
	while (str[end])
	{
		while (is_in_charset(str[end], charset))
			end++;
		if (!str[end])
			break ;
		while (!is_in_charset(str[end], charset) && str[end] != '\0')
			end++;
		count++;
	}
	return (count);
}

char	**free_all(char **splited, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(splited[i]);
	free(splited);
	return (NULL);
}

char	**ft_split_charset(char *str, const char *charset)
{
	char	**splited;
	int		end;
	int		start;
	int		j;

	splited = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	start = 0;
	end = 0;
	j = 0;
	while (str[end])
	{
		while (is_in_charset(str[end], charset))
			end++;
		start = end;
		if (!str[end])
			break ;
		while (!is_in_charset(str[end], charset) && str[end] != '\0')
			end++;
		splited[j++] = split_string(str, start, end - 1);
		if (!splited[j - 1])
			return (free_all(splited, j));
	}
	splited[j] = NULL;
	return (splited);
}
