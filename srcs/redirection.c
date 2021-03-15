/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/15 16:00:06 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_redirection_left_right(t_minishell *shell, int *j, int *k, char *arg)
{
	if (shell->pipe_tab[shell->index_redir][*j] == '>')
	{
		(*k)++;
		shell->str = ft_redirection_right(shell, &shell->index_redir, k, arg);
		shell->redirection_read = FALSE;
		(*j)++;
	}
	if (shell->pipe_tab[shell->index_redir][*j] == '<' && !shell->delete_redir)
	{
		(*k)++;
		if (!(shell->str = ft_redirection_left(shell, arg, k,
		&shell->index_redir)))
		{
			ft_free_failed(shell, arg);
			return (FALSE);
		}
		shell->redirection_read = TRUE;
		(*j)++;
	}
	if (shell->pipe_tab[shell->index_redir][*j] == '<' && shell->delete_redir)
	{
		(*k)++;
		(*j)++;
	}
	return (TRUE);
}

int		ft_redirection_loop(t_minishell *shell, int i, char *arg)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	shell->index_redir = i;
	while (shell->pipe_tab[i][++j])
	{
		j = ft_redirection_quotes(shell, i, j);
		if (!(ft_redirection_left_right(shell, &j, &k, arg)))
			return (FALSE);
		shell->index_tab = 0;
	}
	return (TRUE);
}

void	ft_redirection_command(t_minishell *shell, int i)
{
	if (i > 0)
	{
		shell->str = realloc_str(shell->str, "|");
		shell->str = realloc_str(shell->str, shell->pipe_tab[i]);
		shell->redirection_read = TRUE;
	}
	else
	{
		shell->str = ft_strdup(shell->pipe_tab[i]);
		shell->redirection_read = TRUE;
	}
}

int		ft_redirection_split_pipe(t_minishell *shell)
{
	if (ft_count_redirection(shell->input, shell) == FALSE)
	{
		ft_free_args(shell);
		return (FALSE);
	}
	ft_split_pipe(shell, '|');
	ft_pipe_malloc(shell, shell->input);
	return (TRUE);
}

int		ft_redirection(t_minishell *shell, t_struct *glo)
{
	int		i;
	char	*arg;

	if (ft_redirection_backslash(shell))
		return (TRUE);
	if (!(ft_redirection_split_pipe(shell)))
		return (FALSE);
	i = -1;
	while (shell->pipe_tab[++i])
	{
		if (check_redirection(shell->pipe_tab[i]))
		{
			shell->pipe_tab[i] = ft_create_redirection(shell->pipe_tab[i],\
			shell);
			ft_split_redirection(shell, shell->pipe_tab[i], '>', '<');
			arg = ft_redirection_arg(shell->redir_tab, shell);
			if (!(ft_redirection_loop(shell, i, arg)))
				return (FALSE);
			ft_free_redir_arg(shell, arg);
		}
		else
			ft_redirection_command(shell, i);
	}
	ft_redirection_pipe(shell, glo);
	return (FALSE);
}
