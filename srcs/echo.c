/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:46:38 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/18 14:37:12 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		check_flag(t_minishell *shell, int *i)
{
	int	n_flag;

	n_flag = FALSE;
	while (shell->tab[*i] && !ft_strcmp(shell->tab[*i], "-n"))
	{
		n_flag = TRUE;
		(*i)++;
	}
	return (n_flag);
}

void	echo(t_minishell *shell)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = FALSE;
	if (ft_strlen_tab(shell->tab) > 1)
	{
		n_flag = check_flag(shell, &i);
		if (ft_strcmp(shell->variable, "-n"))
		{
			ft_putstr_fd(shell->variable, 1);
			if (shell->tab[shell->i + 1])
				ft_putchar_fd(' ', 1);
			if (shell->value)
			{
				ft_putchar_fd('=', 1);
				ft_putstr_fd(shell->value, 1);
			}
		}
	}
	if (n_flag == FALSE && !shell->tab[shell->i + 1])
		ft_putchar_fd('\n', 1);
	shell->ret = 0;
}
