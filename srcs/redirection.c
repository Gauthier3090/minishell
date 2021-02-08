/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/06 17:29:20 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

int		ft_check_redirection(t_minishell *shell, int c)
{
	int		y;

	while (shell->input[++shell->index])
	{
		if (shell->input[shell->index] == c &&
		ft_double_quotes_check(shell, shell->index) == FALSE)
		{
			shell->redir[shell->index_tab] = shell->index;
			shell->index_tab++;
			y = 1;
			while (shell->input && (shell->input[shell->index + y] == ' ' ||
				shell->input[shell->index + y] == '\t' || \
				shell->input[shell->index + y] == '\v'))
				y++;
			if (shell->input[shell->index + y + 1] == c)
			{
				shell->ret = ft_putstr_error("minishell: parse error near `>>'\n", NULL, 2);
				ft_free_args(shell);
				shell->index_tab = 0;
				return (FALSE);
			}
		}
	}
	return (TRUE);
}

char	*ft_redirection_pipe(char **redir_tab)
{
	char	*command;
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	while (redir_tab[++i])
	{
		if (!(command = ft_strdup("tee ")))
			exit(EXIT_FAILURE);
		tmp = realloc_str(command, redir_tab[i]);
		free(redir_tab[i]);
		if (!(redir_tab[i] = ft_strdup(tmp)))
			exit(EXIT_FAILURE);
		free(tmp);
	}
	i = -1;
	while (++i < ft_strlen_tab(redir_tab) - 1)
	{
		if (!(command = ft_strdup(" | ")))
			exit(EXIT_FAILURE);
		redir_tab[i] = realloc_str(redir_tab[i], command);
	}
	str = tabtostr(redir_tab, FALSE);
	free(command);
	return (str);
}

int		ft_redirection(t_minishell *shell, t_struct *glo)
{
	shell->index = 0;
	if (shell->input[shell->index] == '>')
	{
		ft_putstr_error("minishell: parse error near `>'\n", NULL, 1);
		return (FALSE);
	}
	if (shell->input[shell->index] == '<')
	{
		ft_putstr_error("minishell: parse error near `<'\n", NULL, 1);
		return (FALSE);
	}
	if (shell->index_tab != 0)
		return (TRUE);
	if (ft_check_redirection(shell, '>') == FALSE)
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
