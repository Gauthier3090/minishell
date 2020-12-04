/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:19:46 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/04 22:18:23 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
