/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/15 17:15:04 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_redirection_command(char **tab, char **redir_tab)
{
	int		i;
	char	*str;

	i = 0;
	while (tab[++i])
	{
		str = realloc_str(redir_tab[0], tab[i]);
		if (!(redir_tab[0] = ft_strdup(str)))
			exit(EXIT_FAILURE);
		free(str);
		if (!(str = ft_strjoin(redir_tab[0], " ")))
			exit(EXIT_FAILURE);
		free(redir_tab[0]);
		if (!(redir_tab[0] = ft_strdup(str)))
			exit(EXIT_FAILURE);
		free(str);
	}
	return (redir_tab[0]);
}

char	**ft_redirection_pipe_more(char **redir_tab, int *i)
{
	char	**tab;

	redir_tab[*i][0] = ' ';
	if (!(tab = ft_split(redir_tab[*i], ' ')))
		exit(EXIT_FAILURE);
	if (ft_strlen_tab(tab) < 2)
		redir_tab = ft_redirection_pipe_left(redir_tab, i);
	else
		redir_tab = ft_redirection_pipe_big_left(redir_tab, tab, i);
	free_tab(tab);
	return (redir_tab);
}

char	*ft_redirection_pipe(char **redir_tab)
{
	char	*str;
	int		redirection_read;
	int		i;

	i = 0;
	redirection_read = TRUE;
	while (redir_tab[++i])
	{
		if (redir_tab[i][0] == '<')
			redir_tab = ft_redirection_pipe_more(redir_tab, &i);
		else
		{
			redirection_read = FALSE;
			redir_tab = ft_redirection_pipe_right(redir_tab, &i);
		}
	}
	redir_tab = ft_create_command_pipe(redir_tab, redirection_read);
	str = tabtostr(redir_tab, FALSE);
	return (str);
}

int		ft_redirection_malloc(t_minishell *shell)
{
	int		x;
	int		z;

	x = 0;
	z = 0;
	if (!(shell->redir_tab = malloc((shell->index_tab + 2) * sizeof(char*))))
		exit(EXIT_FAILURE);
	while (x < shell->index_tab)
	{
		if (!(shell->redir_tab[x] = ft_whitespace(ft_substr(shell->input, z,
		(shell->redir[x]) - z))))
			exit(EXIT_FAILURE);
		z = shell->redir[x] + 1;
		x++;
	}
	if (!(shell->redir_tab[x] = ft_whitespace(ft_substr(shell->input, z,
	ft_strlen(shell->input) - z))))
		exit(EXIT_FAILURE);
	shell->redir_tab[x + 1] = NULL;
	return (FALSE);
}

int		ft_redirection(t_minishell *shell, t_struct *glo)
{
	shell->index = 0;
	if (ft_count_redirection(shell->input) == FALSE)
	{
		ft_free_args(shell);
		return (FALSE);
	}
	shell->input = ft_create_redirection(shell->input);
	if (ft_check_redirection(shell, '>', '<') == FALSE)
		return (FALSE);
	if (shell->index_tab == 0)
		return (TRUE);
	ft_redirection_malloc(shell);
	shell->input ? free(shell->input) : 0;
	shell->input = ft_redirection_pipe(shell->redir_tab);
	shell->index_tab = 0;
	free_tab(shell->redir_tab);
	ft_pipe_main(shell, glo);
	ft_free_args(shell);
	return (FALSE);
}
