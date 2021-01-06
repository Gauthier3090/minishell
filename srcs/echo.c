/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:46:38 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/04 23:58:54 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	echo(t_minishell *shell)
{
	int	i;
	int	n_flag;

	n_flag = FALSE;
	i = 1;
	if (ft_strlen_tab(shell->tab) > 1)
	{
		while (shell->tab[i] && !ft_strcmp(shell->tab[i], "-n"))
		{
			n_flag = TRUE;
			i++;
		}
		if (ft_strcmp(shell->variable, "-n"))
		{
			ft_putstr_fd(shell->variable, 1);
			if (shell->value)
			{
				ft_putchar_fd('=', 1);
				ft_putstr_fd(shell->value, 1);
			}
		}
	}
	if (n_flag == FALSE)
		ft_putchar_fd('\n', 1);
}
