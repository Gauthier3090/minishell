/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:50:38 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/07 15:00:51 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static int	size_words(char *s, char c)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**split_words(char *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		count;

	count = count_words(s, c);
	if (!(tab = ft_calloc(sizeof(char *), count + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (count > ++i)
	{
		if (!(tab[i] = ft_calloc(sizeof(char), size_words(&s[j], c) + 1)))
		{
			free_tab(tab);
			return (NULL);
		}
		while (s[j] == c)
			j++;
		k = -1;
		while (s[j] != c && s[j] != '\0')
			tab[i][++k] = s[j++];
	}
	return (tab);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (!(tab = split_words((char *)s, c)))
		return (NULL);
	return (tab);
}
