/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:37:58 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/22 15:23:56 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	index;

	index = 0;
	if (s == NULL)
		return (NULL);
	if (!(newstr = (char*)malloc((sizeof(char) * len + 1))))
		return (NULL);
	if (!(start > ft_strlen(s)))
	{
		while (len > index && s[start + index])
		{
			newstr[index] = s[start + index];
			index++;
		}
	}
	newstr[index] = '\0';
	return (newstr);
}
