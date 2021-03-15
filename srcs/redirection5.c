/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:06:42 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/15 15:25:16 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_command_tee(char *c)
{
	char	*command;

	if (*c == '>')
	{
		*c = ' ';
		if (!(command = ft_strdup("tee -a ")))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(command = ft_strdup("tee ")))
			exit(EXIT_FAILURE);
	}
	return (command);
}

char	*ft_redirection_right(t_minishell *shell, int *i, int *k, char *arg)
{
	char	*command;
	char	**tab;

	command = ft_command_tee(&(shell->redir_tab[*k][0]));
	tab = split_input(shell->redir_tab[*k]);
	if (ft_strlen_tab(tab) == 1)
		command = realloc_str(command, shell->redir_tab[*k]);
	else
		command = realloc_str(command, tab[0]);
	if (*k == 1 && *i == 0)
		shell->str = ft_strjoin(arg, "|");
	else if (*k == 1 && *i >= 1)
	{
		shell->str = realloc_str(shell->str, "|");
		shell->str = realloc_str(shell->str, arg);
		shell->str = realloc_str(shell->str, "|");
	}
	else
		shell->str = realloc_str(shell->str, "|");
	shell->str = realloc_str(shell->str, command);
	free(command);
	free_tab(tab);
	shell->delete_redir = TRUE;
	return (shell->str);
}

int		check_redirection(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		else if (str[i] == '>' || str[i] == '<')
			return (TRUE);
	}
	return (FALSE);
}

char	**delete_redirection(char **redir_tab, int i, t_minishell *shell)
{
	if (redir_tab[i][0] == '>')
	{
		shell->double_right = TRUE;
		redir_tab[i][0] = ' ';
	}
	if (redir_tab[i][0] == '<')
	{
		shell->double_left = TRUE;
		redir_tab[i][0] = ' ';
	}
	return (redir_tab);
}

char	*create_arg(char **redir_tab, char *arg, int i, t_minishell *shell)
{
	char	**tab;
	int		j;

	redir_tab = delete_redirection(redir_tab, i, shell);
	tab = split_input(redir_tab[i]);
	if (ft_strlen_tab(tab) > 1)
	{
		j = 0;
		while (tab[++j])
		{
			if (!arg)
			{
				if (!(arg = ft_strdup(tab[j])))
					exit(EXIT_FAILURE);
			}
			else
			{
				arg = realloc_str(arg, " ");
				arg = realloc_str(arg, tab[j]);
			}
		}
	}
	free_tab(tab);
	return (arg);
}
