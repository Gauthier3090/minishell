/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:52:15 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/15 16:56:55 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	**ft_redirection_pipe_left_more(char **redir_tab,
		char **tab_command, int *i)
{
	char	*tmp;

	if (ft_strlen_tab(tab_command) == 1)
	{
		if (!(tmp = ft_strdup(tab_command[0])))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(tmp = ft_strdup(redir_tab[0])))
			exit(EXIT_FAILURE);
	}
	free(redir_tab[0]);
	if (!(redir_tab[0] = ft_strjoin("cat", redir_tab[*i])))
		exit(EXIT_FAILURE);
	free(redir_tab[*i]);
	if (!(redir_tab[*i] = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	free(tmp);
	return (redir_tab);
}

char	**ft_redirection_pipe_left(char **redir_tab, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	**tab_command;

	if (!(tab_command = ft_split(redir_tab[0], ' ')))
		exit(EXIT_FAILURE);
	if (*i >= 2)
	{
		if (!(tmp = ft_strdup(redir_tab[*i - 1])))
			exit(EXIT_FAILURE);
		if (!(tmp2 = ft_strdup(redir_tab[0])))
			exit(EXIT_FAILURE);
		free(redir_tab[0]);
		if (!(redir_tab[0] = ft_strjoin(tmp2, redir_tab[*i])))
			exit(EXIT_FAILURE);
		free(tmp2);
		free(redir_tab[*i]);
		if (!(redir_tab[*i] = ft_strdup(tmp)))
			exit(EXIT_FAILURE);
		free(tmp);
	}
	else
		redir_tab = ft_redirection_pipe_left_more(redir_tab, tab_command, i);
	free_tab(tab_command);
	return (redir_tab);
}

char	**ft_redirection_pipe_big_left_more(char **redir_tab,
		char **tab, int *i)
{
	int		k;
	char	*tmp;

	k = 1;
	if (!(tmp = ft_strdup(redir_tab[0])))
		exit(EXIT_FAILURE);
	free(redir_tab[0]);
	if (!(redir_tab[0] = ft_strjoin("cat", redir_tab[*i])))
		exit(EXIT_FAILURE);
	free(redir_tab[*i]);
	if (!(redir_tab[*i] = ft_strjoin(tmp, tab[k])))
		exit(EXIT_FAILURE);
	while (tab[++k])
	{
		redir_tab[*i] = realloc_str(redir_tab[*i], " ");
		redir_tab[*i] = realloc_str(redir_tab[*i], tab[k]);
	}
	free(tmp);
	return (redir_tab);
}

char	**ft_redirection_pipe_big_left(char **redir_tab, char **tab, int *i)
{
	int		k;

	if (*i >= 2)
	{
		k = 0;
		free(redir_tab[*i]);
		if (!(redir_tab[*i] = ft_strdup(redir_tab[1])))
			exit(EXIT_FAILURE);
		while (tab[++k])
		{
			redir_tab[*i] = realloc_str(redir_tab[*i], " ");
			redir_tab[*i] = realloc_str(redir_tab[*i], tab[k]);
		}
	}
	else
		redir_tab = ft_redirection_pipe_big_left_more(redir_tab, tab, i);
	return (redir_tab);
}

char	**ft_redirection_pipe_right(char **redir_tab, int *i)
{
	char	**tab;
	char	*command;
	char	*tmp;
	int		append;

	append = FALSE;
	if (redir_tab[*i][0] == '>')
	{
		redir_tab[*i][0] = ' ';
		append = TRUE;
	}
	if (!(tab = ft_split(redir_tab[*i], ' ')))
		exit(EXIT_FAILURE);
	if (ft_strlen_tab(tab) > 1)
		redir_tab[0] = ft_redirection_command(tab, redir_tab);
	command = ft_redirection_command_append(append);
	tmp = realloc_str(command, tab[0]);
	free(redir_tab[*i]);
	if (!(redir_tab[*i] = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	free(tmp);
	free_tab(tab);
	return (redir_tab);
}
