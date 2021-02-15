/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/15 15:51:50 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_redirection_pipe(char **redir_tab)
{
	char	*command;
	char	*tmp;
	char	*tmp2;
	char	*str;
	char	**tab;
	char	**tab_command;
	int		append;
	int		redirection_read;
	int		i;
	int		k;

	i = 0;
	append = FALSE;
	redirection_read = TRUE;
	tab_command = ft_split(redir_tab[0], ' ');
	while (redir_tab[++i])
	{
		tmp = NULL;
		if (redir_tab[i][0] == '<')
		{
			redir_tab[i][0] = ' ';
			if (!(tab = ft_split(redir_tab[i], ' ')))
				exit(EXIT_FAILURE);
			if (ft_strlen_tab(tab) < 2)
			{
				if (i >= 2)
				{
					tmp = ft_strdup(redir_tab[i - 1]);
					tmp2 = ft_strdup(redir_tab[0]);
					free(redir_tab[0]);
					redir_tab[0] = ft_strjoin(tmp2, redir_tab[i]);
					free(tmp2);
					free(redir_tab[i]);
					redir_tab[i] = ft_strdup(tmp);
					free(tmp);
				}
				else if (ft_strlen_tab(tab_command) == 1)
				{
					tmp = ft_strdup(tab_command[0]);
					free(redir_tab[0]);
					redir_tab[0] = ft_strjoin("cat", redir_tab[i]);
					free(redir_tab[i]);
					redir_tab[i] = ft_strdup(tmp);
					free(tmp);
				}
				else
				{
					tmp = ft_strdup(redir_tab[0]);
					free(redir_tab[0]);
					redir_tab[0] = ft_strjoin("cat", redir_tab[i]);
					free(redir_tab[i]);
					redir_tab[i] = ft_strdup(tmp);
					free(tmp);
				}
			}
			else
			{
				if (i >= 2)
				{
					k = 0;
					free(redir_tab[i]);
					redir_tab[i] = ft_strdup(redir_tab[1]);
					while (tab[++k])
					{
						redir_tab[i] = realloc_str(redir_tab[i], " ");
						redir_tab[i] = realloc_str(redir_tab[i], tab[k]);
					}
					free(tmp);
				}
				else
				{
					k = 1;
					tmp = ft_strdup(redir_tab[0]);
					free(redir_tab[0]);
					redir_tab[0] = ft_strjoin("cat", redir_tab[i]);
					free(redir_tab[i]);
					redir_tab[i] = ft_strjoin(tmp, tab[k]);
					while (tab[++k])
					{
						redir_tab[i] = realloc_str(redir_tab[i], " ");
						redir_tab[i] = realloc_str(redir_tab[i], tab[k]);
					}
					free(tmp);
				}
			}
			free_tab(tab);
		}
		else
		{
			redirection_read = FALSE;
			if (redir_tab[i][0] == '>')
			{
				redir_tab[i][0] = ' ';
				append = TRUE;
			}
			if (!(tab = ft_split(redir_tab[i], ' ')))
				exit(EXIT_FAILURE);
			if (ft_strlen_tab(tab) > 1)
				redir_tab[0] = ft_redirection_command(tab, redir_tab);
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
			tmp = realloc_str(command, tab[0]);
			free(redir_tab[i]);
			if (!(redir_tab[i] = ft_strdup(tmp)))
				exit(EXIT_FAILURE);
			free(tmp);
			free_tab(tab);
			append = FALSE;
		}
	}
	free_tab(tab_command);
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
