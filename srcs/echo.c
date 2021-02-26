/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:46:38 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/25 17:34:03 by ldavids          ###   ########.fr       */
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
	shell->ret = 0;
	if (ft_strlen_tab(shell->tab) > 1)
	{
		n_flag = check_flag(shell, &i);
		if (ft_strcmp(shell->variable, "-n"))
		{
			ft_putstr_fd(shell->variable, 1);
			if (shell->value)
			{
				ft_putchar_fd('=', 1);
				ft_putstr_fd(shell->value, 1);
			}
			if (shell->tab[shell->i + 1])
				ft_putchar_fd(' ', 1);
		}
		if (n_flag == FALSE && !shell->tab[shell->i + 1])
			ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd('\n', 1);
}
