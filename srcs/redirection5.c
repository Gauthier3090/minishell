/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:56:39 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/08 22:39:08 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_redirection_command_append(int append)
{
	char	*command;

	if (!append)
	{
		if (!(command = ft_strdup("tee ")))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(command = ft_strdup("tee -a ")))
			exit(EXIT_FAILURE);
	}
	return (command);
}

char	**ft_create_command_pipe(char **redir_tab, int redirection_read)
{
	int		i;
	char	*command;

	i = -1;
	while (++i < ft_strlen_tab(redir_tab))
	{
		if (i < ft_strlen_tab(redir_tab) - 1)
		{
			if (!(command = ft_strdup(" | ")))
				exit(EXIT_FAILURE);
			redir_tab[i] = realloc_str(redir_tab[i], command);
		}
		else if (!redirection_read)
		{
			if (!(command = ft_strdup(" | grep -q \"\"")))
				exit(EXIT_FAILURE);
			redir_tab[i] = realloc_str(redir_tab[i], command);
		}
		free(command);
		command = NULL;
	}
	return (redir_tab);
}

int		count_tee(char **redir_tab)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (redir_tab[++i])
	{
		if (!ft_strncmp(redir_tab[i], "tee", 3))
			len++;
	}
	return (len);
}

char	**check_pipe_multiple_tee(char **redir_tab,
		char **tab, t_minishell *shell)
{
	int		k;
	char	*tmp;

	if (!(tmp = ft_strdup(tab[count_tee(redir_tab) - 2])))
		exit(EXIT_FAILURE);
	free(redir_tab[0]);
	if (!(redir_tab[0] = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	free(tmp);
	k = ft_strlen_tab(redir_tab) - 1;
	redir_tab[k] = realloc_str(redir_tab[k], "|");
	redir_tab[k] = realloc_str(redir_tab[k], tab[ft_strlen_tab(tab) - 1]);
	shell->redirection_read = TRUE;
	return (redir_tab);
}

char	**check_pipe(char **redir_tab, t_minishell *shell)
{
	char	**tab;
	char	*tmp;
	int		k;

	tab = ft_split(redir_tab[0], '|');
	if (shell->redir_right && count_tee(redir_tab) > 0 && !shell->redir_left)
		shell->redirection_read = FALSE;
	else if (count_tee(redir_tab) == 1 && ft_strlen_tab(tab) > 1)
	{
		k = ft_strlen_tab(redir_tab) - 1;
		if (!(tmp = ft_strdup(tab[0])))
			exit(EXIT_FAILURE);
		free(redir_tab[0]);
		if (!(redir_tab[0] = ft_strdup(tmp)))
			exit(EXIT_FAILURE);
		free(tmp);
		redir_tab[k] = realloc_str(redir_tab[k], "|");
		redir_tab[k] = realloc_str(redir_tab[k], tab[ft_strlen_tab(tab) - 1]);
		shell->redirection_read = TRUE;
	}
	else if (ft_strlen_tab(tab) > 1 && count_tee(redir_tab) != 0)
		redir_tab = check_pipe_multiple_tee(redir_tab, tab, shell);
	free_tab(tab);
	return (redir_tab);
}
