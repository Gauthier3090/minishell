/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:06:18 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/16 14:45:05 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		sigint_handler(int nothing)
{
	(void)nothing;
	ft_putstr_fd("\n", 1);
	directoryprompt();
}

void		sigint_handler2(int nothing)
{
	(void)nothing;
	ft_putstr_fd("\n", 1);
	ft_signal_hand();
}

void		do_nothing(int nothing)
{
	(void)nothing;
	write(1, " \b\b \b", 5);
	write(1, " \b\b \b", 3);
}

void		ft_signal_hand(void)
{
	signal(SIGQUIT, do_nothing);
	if (signal(SIGINT, sigint_handler) != 0)
		return ;
}
