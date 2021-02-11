/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:16:00 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/11 21:32:28 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_trim(char const *s1, char const *set)
{
	int		indexset;
	int		i;
	char	*newstr;

	i = -1;
	while (s1[++i])
	{
		indexset = 0;
		while (set[indexset])
		{
			if (s1[i] == set[indexset])
			{
				indexset = -1;
				i++;
			}
			indexset++;
			if (set[indexset] == '\0')
			{
				if (!(newstr = ft_substr(s1, i, (ft_strlen(s1) - i))))
					return (NULL);
				return (newstr);
			}
		}
	}
	return (ft_strdup(s1));
}

static void		ft_trimend_more(char *newstr, char const *set,
				int *indexstr, int *indexset)
{
	if (newstr[*indexstr] == set[*indexset])
	{
		*indexset = -1;
		(*indexstr)--;
	}
}

static char		*ft_trimend(char *newstr, char const *set)
{
	int		indexset;
	int		indexstr;
	char	*tmp;

	indexstr = ft_strlen(newstr) - 1;
	while (newstr[indexstr])
	{
		indexset = 0;
		while (set[indexset])
		{
			ft_trimend_more(newstr, set, &indexstr, &indexset);
			indexset++;
			if (set[indexset] == '\0')
			{
				if (!(tmp = ft_substr(newstr, 0, indexstr + 1)))
					return (NULL);
				free(newstr);
				return (tmp);
			}
		}
		indexstr--;
	}
	return (newstr);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;

	if (s1 == NULL)
		return (NULL);
	if (!(newstr = ft_trim(s1, set)))
		return (NULL);
	if (!(newstr = ft_trimend(newstr, set)))
		return (NULL);
	return (newstr);
}
