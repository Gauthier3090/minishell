/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:54:01 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/04 15:38:56 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int index;

	index = 0;
	if (s == NULL || fd < 0 || fd > FOPEN_MAX)
		return ;
	while (s[index])
	{
		write(fd, &s[index], 1);
		index++;
	}
}
