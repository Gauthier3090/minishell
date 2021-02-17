/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:29:15 by gpladet           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/16 18:03:27 by gpladet          ###   ########.fr       */
=======
/*   Updated: 2021/02/16 17:23:18 by ldavids          ###   ########.fr       */
>>>>>>> cd
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

void	ft_free_exec(t_struct *glo, char **bin, char *path)
{
	glo->tab ? free_tab(glo->tab) : 0;
	glo->exec ? free_tab(glo->exec) : 0;
	bin ? free_tab(bin) : 0;
	path ? free(path) : 0;
	if (glo->pipin == 1)
		exit(EXIT_SUCCESS);
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
