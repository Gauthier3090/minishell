/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:25:04 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/16 16:56:44 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		count;
	char	*s;
	char	ch;
	int		swi;

	swi = 0;
	s = (char*)str;
	ch = (char)c;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ch)
		{
			count = i;
			swi = 1;
		}
		i++;
	}
	if (s[i] == ch)
		return (s + i);
	if (swi == 0)
		return (NULL);
	return (s + count);
}
