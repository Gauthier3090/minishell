/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:24:19 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/24 11:47:58 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t c)
{
	size_t	add;
	size_t	i;
	size_t	total;

	i = 0;
	add = 0;
	total = 0;
	while (dest[add])
		++add;
	while (src[i])
		++i;
	if (c <= add)
		return (total = i + c);
	else
		total = add + i;
	i = 0;
	while (src[i] && (c > (1 + add)))
	{
		dest[add] = src[i];
		add++;
		i++;
	}
	dest[add] = '\0';
	return (total);
}
