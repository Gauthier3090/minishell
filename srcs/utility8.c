/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:12:24 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/15 16:35:16 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		init_shell_arg(t_minishell *shell)
{
	if (shell->variable && shell->value)
	{
		if (!(shell->arg = ft_strjoin(shell->variable, shell->value)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(shell->arg = ft_strdup(shell->variable)))
			exit(EXIT_FAILURE);
	}
}

int			ft_builtins(t_minishell *shell, t_struct *glo)
{
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		echo(shell);
	else if (ft_strcmp(shell->tab[0], "exit") == 0)
	{
		if (!(exit_shell(shell->tab, shell)))
			return (FALSE);
	}
	else if (ft_strcmp(shell->tab[0], "env") == 0)
		ft_env(shell->tab, shell->env, shell);
	else if (ft_strcmp(shell->tab[0], "export") == 0)
		export(shell);
	else if (ft_strcmp(shell->tab[0], "unset") == 0)
		unset(shell);
	else if (ft_strcmp(shell->tab[0], "cd") == 0)
		ft_cd(shell->input, shell->env, glo, shell);
	else if (ft_strcmp(shell->tab[0], "pwd") == 0)
		ft_pwd(shell);
	else
		ft_exec(shell, glo);
	return (TRUE);
}

int			ft_no_path(t_minishell *shell, t_struct *glo)
{
	ft_putstr_fd(glo->exec[0], 2);
	shell->ret = ft_putstr_error(": command not found\n", NULL, 127);
	free_tab(glo->exec);
	return (1);
}
