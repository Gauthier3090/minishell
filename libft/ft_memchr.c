/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:33:21 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/18 14:11:33 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	d;
	size_t			index;

	index = 0;
	d = (unsigned char)c;
	dest = (unsigned char*)str;
	while (n > index)
	{
		if (dest[index] == d)
			return (&dest[index]);
		index++;
	}
	return (NULL);
}
