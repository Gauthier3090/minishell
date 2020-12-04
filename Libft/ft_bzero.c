/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:12:31 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/24 10:31:53 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	unsigned int	index;
	unsigned char	*memo;

	memo = str;
	index = 0;
	while (n > index)
	{
		memo[index] = 0;
		index++;
	}
	return (str);
}
