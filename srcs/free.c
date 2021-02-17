/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:29:15 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/17 22:19:02 by ldavids          ###   ########.fr       */
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
	shell->index = 0;
	shell->index_tab = 0;
	ft_memset(shell->redir, 0, sizeof(shell->redir));
	shell->arg = NULL;
	shell->variable = NULL;
	shell->value = NULL;
	shell->redir_tab = NULL;
}
