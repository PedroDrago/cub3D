/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 01:58:34 by pdrago            #+#    #+#             */
/*   Updated: 2023/12/10 00:24:37 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_is_sep(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	ft_split_count(char const *str, const char *charset)
{
	int	index;
	int	splits;

	if (str == 0 || str[0] == 0)
		return (0);
	index = 1;
	splits = 0;
	if (!ft_is_sep(str[0], charset))
		splits++;
	while (str[index] != '\0')
	{
		if (!ft_is_sep(str[index], charset)
			&& ft_is_sep(str[index - 1], charset))
			splits++;
		index++;
	}
	return (splits);
}

static char	**ft_free_all(char **str_tab, int max)
{
	int	index;

	index = 0;
	while (index < max && str_tab[index] != 0)
	{
		free(str_tab[index]);
		index++;
	}
	free(str_tab);
	return (0);
}

static int	ft_next_split_count(char const *str, const char *charset, int index)
{
	int	count;

	count = 0;
	while (ft_is_sep(str[index], charset) && str[index] != '\0')
		index++;
	while (str[index] != '\0' && !ft_is_sep(str[index], charset))
	{
		count++;
		index++;
	}
	return (count);
}

static char	**ft_split_split(char const *s, const char *charset, char **tab_str)
{
	int		char_s;
	int		tab_count;
	int		char_tab;

	char_s = 0;
	tab_count = -1;
	while (++tab_count < ft_split_count(s, charset))
	{
		char_tab = 0;
		tab_str[tab_count] = (char *)malloc(sizeof(char)
				* ft_next_split_count(s, charset, char_s) + 1);
		if (!(tab_str[tab_count]))
			return (ft_free_all(tab_str, tab_count));
		while (s[char_s] != '\0' && ft_is_sep(s[char_s], charset))
			char_s++;
		while (s[char_s] != '\0' && !ft_is_sep(s[char_s], charset))
			tab_str[tab_count][char_tab++] = s[char_s++];
		tab_str[tab_count][char_tab] = '\0';
	}
	tab_str[tab_count] = 0;
	return (tab_str);
}

char	**ft_split_charset(char const *s, const char *charset)
{
	char	**tab_str;

	if (s == 0 || charset == 0)
		return (0);
	tab_str = (char **)malloc(sizeof(*tab_str)
			* (ft_split_count(s, charset) + 1));
	if (!(tab_str))
		return (0);
	tab_str = ft_split_split(s, charset, tab_str);
	return (tab_str);
}
