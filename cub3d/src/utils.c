#include "../includes/cub3d.h"

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited && splited[i])
		free(splited[i++]);
	free(splited);
}

int	split_len(char **splited)
{
	int	len;

	len = 0;
	while (splited[len])
		len++;
	return (len);
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
