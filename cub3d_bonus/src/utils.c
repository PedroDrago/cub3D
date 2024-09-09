/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:06:41 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/03 19:08:38 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
