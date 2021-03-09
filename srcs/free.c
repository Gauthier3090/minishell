/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:29:15 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/09 14:23:12 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int		free_tab_ret(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (TRUE);
}

void	ft_free_args(t_minishell *shell)
{
	shell->variable ? free(shell->variable) : 0;
	shell->value ? free(shell->value) : 0;
	shell->arg ? free(shell->arg) : 0;
	shell->index = -1;
	shell->index_tab = 0;
	ft_memset(shell->redir, 0, sizeof(shell->redir));
	shell->arg = NULL;
	shell->variable = NULL;
	shell->value = NULL;
	shell->redir_tab = NULL;
	ft_memset(shell->pipe, 0, sizeof(shell->pipe));
	shell->j = 0;
	shell->z = 0;
}

void	ft_free_redir_arg(t_minishell *shell, char *arg)
{
	free_tab(shell->redir_tab);
	free(arg);
}

void	ft_free_failed(t_minishell *shell, char *arg)
{
	free(arg);
	free_tab(shell->pipe_tab);
	free_tab(shell->redir_tab);
	ft_free_args(shell);
}
