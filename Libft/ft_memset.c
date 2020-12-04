/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:17:05 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/22 15:17:57 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int	index;
	unsigned char	*memo;

	memo = (unsigned char*)str;
	index = 0;
	while (n > index)
	{
		memo[index] = (unsigned char)c;
		index++;
	}
	return (str);
}
