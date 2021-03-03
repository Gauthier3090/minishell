/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:06:18 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/03 15:51:07 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		sigint_handler(int nothing)
{
	(void)nothing;
	ft_putstr_fd("\n", 2);
	directoryprompt();
}

void		sigint_handler2(int nothing)
{
	(void)nothing;
	ft_putstr_fd("\n", 2);
	ft_signal_hand();
}

void		do_nothing(int nothing)
{
	(void)nothing;
	ft_putstr_fd("\b\b  \b\b", 2);
}

int			ft_signal_hand(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, do_nothing);
	return (0);
}
