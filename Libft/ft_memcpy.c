/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:56:06 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/18 15:35:56 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				index;
	unsigned char		*csrc;
	unsigned char		*cdest;

	csrc = (unsigned char*)src;
	cdest = (unsigned char*)dest;
	index = 0;
	if (n == 0 || dest == src)
		return (dest);
	while (n > index)
	{
		cdest[index] = csrc[index];
		index++;
	}
	return (cdest);
}
