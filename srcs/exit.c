/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:51:37 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/23 15:53:34 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	exit_shell(char **tab, t_minishell *shell)
{
	shell->ret = 0;
	if (ft_strlen_tab(tab) > 2)
	{
		shell->ret = ft_putstr_error("exit: too many arguments\n", NULL, 1);
		return (FALSE);
	}
	else if (tab[1] && !ft_strisdigit(tab[1]))
		shell->ret = 255;
	else if (tab[1])
	{
		shell->ret = ft_atoi(tab[1]);
		if (shell->ret < 0)
		{
			shell->ret = (shell->ret * (-1)) % 256;
			shell->ret = 256 - shell->ret;
		}
		else if (shell->ret > 255)
			shell->ret = shell->ret % 256;
	}
	exit(shell->ret);
}
