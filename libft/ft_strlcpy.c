/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:54:00 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/24 11:44:30 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	if (dest == NULL)
		return (0);
	while (src[count])
		count++;
	if (len == 0)
		return (count);
	while (src[i] && len > i + 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (count);
}
