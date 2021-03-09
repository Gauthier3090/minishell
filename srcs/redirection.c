/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/09 06:38:15 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


#include "../includes/header.h"

int		ft_pipe_malloc_more(t_minishell *shell, char *str, int x, int z)
{
	if (!(shell->pipe_tab[x] = ft_substr(str, z, \
		ft_strlen(str) - z)))
		exit(EXIT_FAILURE);
	shell->pipe_tab[x + 1] = NULL;
	return (TRUE);
}

int		ft_pipe_malloc(t_minishell *shell, char *str)
{
	int		x;
	int		z;

	x = 0;
	z = 0;
	if (!(shell->pipe_tab = malloc((shell->z + 2) * sizeof(char*))))
		exit(EXIT_FAILURE);
	while (x < shell->z)
	{
		if (!(shell->pipe_tab[x] = ft_substr(str, z, \
			(shell->pipe[x]) - z)))
			exit(EXIT_FAILURE);
		z = shell->pipe[x] + 1;
		x++;
	}
	if (!(ft_pipe_malloc_more(shell, str, x, z)))
		return (FALSE);
	return (FALSE);
}

int		ft_split_pipe(t_minishell *shell, char c)
{
	int		y;

	while (shell->input[++shell->j])
	{
		if ((shell->input[shell->j] == c) && !ft_double_quotes_check(shell->input,
		shell->j, shell) && !ft_voided_char_input(shell->j, shell))
		{
			shell->pipe[shell->z] = shell->j;
			shell->z++;
			y = 1;
			while (shell->input && (shell->input[shell->j + y] == ' ' ||
			shell->input[shell->j + y] == '\t' ||
			shell->input[shell->j + y] == '\v'))
				y++;
			if (shell->input[shell->j + y] == c)
			{
				shell->ret = ft_putstr_error(
				"bash: syntax error near unexpected token `|'\n", NULL, 2);
				ft_free_args(shell);
				shell->z = 0;
				return (FALSE);
			}
		}
	}
	ft_pipe_malloc(shell, shell->input);
	return (TRUE);
}

void	ft_check_redirection_simple(t_minishell *shell, char *str, int *y)
{
	shell->redir[shell->index_tab] = shell->index;
	shell->index_tab++;
	*y = 1;
	while (str && (str[shell->index + *y] == ' ' ||
		str[shell->index + *y] == '\t' || \
		str[shell->index + *y] == '\v'))
		(*y)++;
}

void	ft_check_redirection_more(t_minishell *shell, char *str, int *y)
{
	shell->redir[shell->index_tab] = shell->index;
	shell->index_tab++;
	shell->index += 2;
	*y = 1;
	while (str && (str[shell->index + *y] == ' ' ||
	str[shell->index + *y] == '\t' ||
	str[shell->index + *y] == '\v'))
		(*y)++;
}

int		ft_redirection_malloc(t_minishell *shell, char *str)
{
	int		x;
	int		z;

	x = 0;
	z = 0;
	if (!(shell->redir_tab = malloc((shell->index_tab + 2) * sizeof(char*))))
		exit(EXIT_FAILURE);
	while (x < shell->index_tab)
	{
		if (!(shell->redir_tab[x] = ft_whitespace(ft_substr(str, z,
		(shell->redir[x]) - z), shell)))
			exit(EXIT_FAILURE);
		z = shell->redir[x] + 1;
		x++;
	}
	if (!(shell->redir_tab[x] = ft_whitespace(ft_substr(str, z,
	ft_strlen(str) - z), shell)))
		exit(EXIT_FAILURE);
	shell->redir_tab[x + 1] = NULL;
	return (FALSE);
}


int		ft_split_redirection(t_minishell *shell, char *str, int c, int c2)
{
	int		y;

	shell->index = 0;
	while (str[++shell->index])
	{
		if ((((str[shell->index] == c \
		&& (ft_voided_char_input(shell->index, shell) == FALSE)\
		&& str[shell->index + 1] == c \
		&& (ft_voided_char_input(shell->index + 1, shell) == FALSE))) ||
		((str[shell->index] == c2 &&\
		(ft_voided_char_input(shell->index, shell) == FALSE) &&
		str[shell->index + 1] == c2 \
		&& (ft_voided_char_input(shell->index + 1, shell) == FALSE))
		&& (ft_double_quotes_check(str,
		shell->index, shell) == FALSE))))
			ft_check_redirection_more(shell, str, &y);
		else if (str[shell->index] == c && \
		(ft_voided_char_input(shell->index, shell) == FALSE)
		&& ft_double_quotes_check(str, shell->index, shell) == FALSE)
			ft_check_redirection_simple(shell, str, &y);
	}
	ft_redirection_malloc(shell, str);
	return (TRUE);
}

char	*ft_redirection_right(char **redir_tab, char *str, int *i, int *k, char *arg)
{
	char	*command;
	char	**tab;

	if (redir_tab[*k][0] == '>')
	{
		redir_tab[*k][0] = ' ';
		if (!(command = ft_strdup("tee -a ")))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(command = ft_strdup("tee ")))
			exit(EXIT_FAILURE);
	}
	tab = split_input(redir_tab[*k]);
	if (ft_strlen_tab(tab) == 1)
		command = realloc_str(command, redir_tab[*k]);
	else
		command = realloc_str(command, tab[0]);
	if (*k == 1 && *i == 0)
		str = ft_strjoin(arg, "|");
	else if (*k == 1 && *i >= 1)
	{
		str = realloc_str(str, "|");
		str = realloc_str(str , arg);
		str = realloc_str(str, "|");
	}
	else
		str = realloc_str(str, "|");
	str = realloc_str(str, command);
	free(command);
	free_tab(tab);
	return (str);
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

char	*ft_redirection_arg(char **redir_tab, t_minishell *shell)
{
	int		i;
	int		j;
	char	**tab;
	char	*arg;

	i = 0;
	arg = NULL;
	while (redir_tab[++i])
	{
		if (redir_tab[i][0] == '>')
		{
			shell->double_right = TRUE;
			redir_tab[i][0] = ' ';
		}
		tab = split_input(redir_tab[i]);
		if (ft_strlen_tab(tab) > 1)
		{
			j = 0;
			while (tab[++j])
			{
				if (!arg)
					arg = ft_strdup(tab[j]);
				else
				{
					arg = realloc_str(arg, " ");
					arg = realloc_str(arg, tab[j]);
				}
			}	
		}
		free_tab(tab);
		if (redir_tab[i][0] == ' ' && shell->double_right)
			redir_tab[i][0] = '>';
	}
	if (arg)
		redir_tab[0] = realloc_str(redir_tab[0], arg);
	free(arg);
	return (ft_strdup(redir_tab[0]));
}

int		ft_redirection(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	char	*arg;

	glo->x = 0;
	if (!check_redirection(shell->input))
		return (TRUE);
	if (ft_count_redirection(shell->input, shell) == FALSE)
	{
		ft_free_args(shell);
		return (FALSE);
	}
	ft_split_pipe(shell, '|');
	i = -1;
	while (shell->pipe_tab[++i])
	{
		if (check_redirection(shell->pipe_tab[i]))
		{
			ft_split_redirection(shell, shell->pipe_tab[i], '>', '<');
			arg = ft_redirection_arg(shell->redir_tab, shell);
			j = -1;
			k = 0;
			while (shell->pipe_tab[i][++j])
			{
				if (shell->pipe_tab[i][j] == '>')
				{
					k++;
					str = ft_redirection_right(shell->redir_tab, str, &i, &k, arg);
					j++;
					shell->redirection_read = FALSE;
				}
			}
			shell->index_tab = 0;
			free_tab(shell->redir_tab);
			free(arg);
		}
		else if (i > 0)
		{
			str = realloc_str(str, "|");
			str = realloc_str(str, shell->pipe_tab[i]);
			shell->redirection_read = TRUE;
		}
		else
		{
			str = ft_strdup(shell->pipe_tab[i]);
			shell->redirection_read = TRUE;
		}
	}
	if (!shell->redirection_read)
		str = realloc_str(str, "| grep -q \"\"");
	shell->input ? free(shell->input) : 0;
	shell->input = ft_strdup(str);
	ft_putendl_fd(shell->input, 1);
	free(str);
	/*ft_pipe_main(shell, glo);*/
	ft_free_args(shell);
	free_tab(shell->pipe_tab);
	return (FALSE);
}
