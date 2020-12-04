/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:09:52 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/04 15:38:33 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned	int sign;

	if (fd < 0 || fd > FOPEN_MAX)
		return ;
	sign = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -n;
	}
	if (sign >= 10)
		ft_putnbr_fd(sign / 10, fd);
	ft_putchar_fd(sign % 10 + '0', fd);
}
