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
