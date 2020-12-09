/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:19:46 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/09 16:13:26 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] && s2[i])
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void *new;

	if (!ptr)
		return (NULL);
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	if (!(new = ft_calloc(1, size)))
		return (NULL);
	new = ft_strcpy(new, ptr);
	free(ptr);
	return (new);
}

void	ft_print_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		ft_putendl_fd(tab[i], 1);
}
