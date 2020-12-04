/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:15:00 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/16 16:41:02 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*s;
	char	ch;

	i = 0;
	s = (char*)str;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return (s + i);
		i++;
	}
	if (s[i] == ch)
		return (s + i);
	return (NULL);
}
