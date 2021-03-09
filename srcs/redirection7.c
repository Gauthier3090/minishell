/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:14:21 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/09 14:15:37 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_redirection_left_condition(t_minishell *shell,
		char **tab, char *tmp)
{
	shell->str = realloc_str(shell->str, " | ");
	shell->str = realloc_str(shell->str, tab[0]);
	shell->str = realloc_str(shell->str, " | ");
	shell->str = realloc_str(shell->str, tmp);
}

char	**ft_redirection_left_concatenation(char **tmp, char **tab, char **tab2)
{
	int	j;

	j = 0;
	while (tab2[++j])
	{
		*tmp = realloc_str(*tmp, " ");
		*tmp = realloc_str(*tmp, tab2[j]);
	}
	free(tab[0]);
	if (!(tab[0] = ft_strjoin("cat", " ")))
		exit(EXIT_FAILURE);
	tab[0] = realloc_str(tab[0], tab2[0]);
	return (tab);
}

void	ft_redirection_left_more(t_minishell *shell, int *i, int *k)
{
	char	*tmp;
	char	**tab;
	char	**tab2;

	tab = split_input(shell->redir_tab[0]);
	tab2 = split_input(shell->redir_tab[*k]);
	if (!(tmp = ft_strdup(tab[0])))
		exit(EXIT_FAILURE);
	tab = ft_redirection_left_concatenation(&tmp, tab, tab2);
	if (*k == 1 && *i != 1)
	{
		if (!(shell->str = ft_strdup(tab[0])))
			exit(EXIT_FAILURE);
		shell->str = realloc_str(shell->str, " | ");
		shell->str = realloc_str(shell->str, tmp);
	}
	else
		ft_redirection_left_condition(shell, tab, tmp);
	free(tmp);
	free_tab(tab);
	free_tab(tab2);
}

char	*ft_redirection_left(t_minishell *shell, char *arg, int *k, int *i)
{
	char	**tab;

	if (shell->redir_tab[*k][0] == '<')
		shell->redir_tab[*k][0] = ' ';
	if (!ft_check_file(k, shell))
		return (NULL);
	tab = split_input(shell->redir_tab[0]);
	if (ft_strlen_tab(tab) == 1)
		ft_redirection_left_more(shell, i, k);
	else
	{
		if (*k == 1 && *i != 1)
		{
			shell->str = ft_strdup(arg);
			shell->str = realloc_str(shell->str, " | ");
			shell->str = realloc_str(shell->str, arg);
		}
		else
		{
			shell->str = realloc_str(shell->str, " | ");
			shell->str = realloc_str(shell->str, arg);
		}
	}
	free_tab(tab);
	return (shell->str);
}

int		ft_redirection_quotes(t_minishell *shell, int i, int j)
{
	if (shell->pipe_tab[i][j] == '"')
	{
		j++;
		while (shell->pipe_tab[i][j] != '"')
			j++;
	}
	if (shell->pipe_tab[i][j] == '\'')
	{
		j++;
		while (shell->pipe_tab[i][j] != '\'')
			j++;
	}
	return (j);
}
