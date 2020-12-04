/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:08:03 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/18 12:59:47 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		index;
	char	*copy;

	index = 0;
	while (s[index])
		index++;
	if (!(copy = (char*)malloc(sizeof(char) * (index + 1))))
		return (NULL);
	index = 0;
	while (s[index])
	{
		copy[index] = s[index];
		index++;
	}
	copy[index] = '\0';
	return (copy);
}
