/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:05:14 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/18 15:35:15 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	checkmax(unsigned int nb, int pos)
{
	if (nb > 2147483647 && pos > 0)
		return (-1);
	if (nb > 2147483648 && pos < 0)
		return (0);
	return ((int)nb * pos);
}

int					ft_atoi(const char *str)
{
	unsigned int	nb;
	int				i;
	int				pos;

	pos = 1;
	i = 0;
	nb = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pos = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] > 47 && str[i] < 58)
			nb = (str[i++] - 48) + (nb * 10);
		else
			break ;
	}
	return (checkmax(nb, pos));
}
