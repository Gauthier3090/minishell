/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:29:54 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/18 14:18:16 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index1;
	int		index2;
	char	*newstr;

	index1 = 0;
	index2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[index1])
		index1++;
	while (s2[index2])
		index2++;
	if (!(newstr = (char*)malloc(((index1 + index2) * sizeof(char)) + 1)))
		return (NULL);
	index1 = 0;
	index2 = 0;
	while (s1[index1])
	{
		newstr[index1] = s1[index1];
		index1++;
	}
	while (s2[index2])
		newstr[index1++] = s2[index2++];
	newstr[index1] = '\0';
	return (newstr);
}
