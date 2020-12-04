/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:00:56 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/22 14:22:39 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int index;

	index = 0;
	if (s == NULL || fd < 0 || fd > OPEN_MAX)
		return ;
	while (s[index])
	{
		write(fd, &s[index], 1);
		index++;
	}
	write(fd, "\n", 1);
}
