/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:35:44 by ldavids           #+#    #+#             */
/*   Updated: 2019/11/05 14:36:41 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_total(const char *s, char c)
{
	size_t	word;
	int		i;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			word++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (word);
}

static void		*ft_free(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char		**ft_split_tab(char **tab, const char *s, char c)
{
	int		i;
	int		j;
	int		start;
	int		sp;

	sp = ft_total(s, c);
	i = 0;
	j = 0;
	while (j < sp)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (!(tab[j] = ft_substr(s, start, i - start)))
			return (ft_free(tab));
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	int		sp;
	char	**tab;

	if (!s)
		return (NULL);
	sp = ft_total(s, c);
	if (!(tab = malloc((sizeof(char*) * sp + 1))))
		return (NULL);
	if (!(tab = ft_split_tab(tab, s, c)))
		return (NULL);
	return (tab);
}
