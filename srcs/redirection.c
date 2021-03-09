/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/09 11:20:42 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if ((shell->input[shell->j] == c) && !ft_double_quotes_check(
		shell->input, shell->j, shell)
		&& !ft_voided_char_input(shell->j, shell))
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
				shell->ret = ft_putstr_error(ERROR_PIPE, NULL, 2);
				ft_free_args(shell);
				shell->z = 0;
				return (FALSE);
			}
		}
	}
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

int		quotes_check(char *str, t_minishell *shell)
{
	if (str[shell->index] == '"')
	{
		shell->index++;
		while (str[shell->index] != '"')
			shell->index++;
		return (TRUE);
	}
	if (str[shell->index] == '\'')
	{
		shell->index++;
		while (str[shell->index] != '\'')
			shell->index++;
		return (TRUE);
	}
	return (FALSE);
}

int		ft_split_redirection(t_minishell *shell, char *str, int c, int c2)
{
	int		y;

	shell->index = -1;
	while (str[++shell->index])
	{
		if (str[shell->index] == '"' || str[shell->index] == '\'')
			quotes_check(str, shell);
		if ((((str[shell->index] == c \
		&& (ft_voided_char_input(shell->index, shell) == FALSE)\
		&& str[shell->index + 1] == c \
		&& (ft_voided_char_input(shell->index + 1, shell) == FALSE))) ||
		((str[shell->index] == c2 &&\
		(ft_voided_char_input(shell->index, shell) == FALSE) &&
		str[shell->index + 1] == c2 \
		&& (ft_voided_char_input(shell->index + 1, shell) == FALSE)))))
			ft_check_redirection_more(shell, str, &y);
		else if (str[shell->index] == c && \
		(ft_voided_char_input(shell->index, shell) == FALSE))
			ft_check_redirection_simple(shell, str, &y);
	}
	ft_redirection_malloc(shell, str);
	return (TRUE);
}

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

char	*ft_redirection_arg(char **redir_tab, t_minishell *shell)
{
	int		i;
	char	*arg;
	char	*tmp;

	i = 0;
	arg = NULL;
	while (redir_tab[++i])
	{
		arg = create_arg(redir_tab, arg, i, shell);
		if (redir_tab[i][0] == ' ' && shell->double_right)
			redir_tab[i][0] = '>';
		if (redir_tab[i][0] == ' ' && shell->double_left)
			redir_tab[i][0] = '<';
	}
	if (arg)
	{
		if (!(tmp = ft_strdup(arg)))
			exit(EXIT_FAILURE);
		free(arg);
		if (!(arg = ft_strjoin(redir_tab[0], tmp)))
			exit(EXIT_FAILURE);
		free(tmp);
		return (arg);
	}
	return (ft_strdup(redir_tab[0]));
}

int		ft_strlen_redirection(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '<')
			len++;
	}
	return (len);
}

char	*ft_create_redirection_quotes(char *str, char *new_str, int *i, int *j)
{
	if (str[*i] == '"')
	{
		new_str[++(*j)] = str[(*i)++];
		while (str[*i] != '"')
			new_str[++(*j)] = str[(*i)++];
	}
	if (str[*i] == '\'')
	{
		new_str[++(*j)] = str[(*i)++];
		while (str[*i] != '\'')
			new_str[++(*j)] = str[(*i)++];
	}
	return (new_str);
}

char	*ft_create_redirection(char *str, t_minishell *shell)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen_redirection(str);
	if (!(new_str = ft_calloc(ft_strlen(str) + len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (str[++i])
	{
		new_str = ft_create_redirection_quotes(str, new_str, &i, &j);
		if (str[i] == '<' && ft_voided_char_input(i, shell) == FALSE)
		{
			new_str[++j] = str[i];
			new_str[++j] = '<';
		}
		else
			new_str[++j] = str[i];
	}
	free(str);
	return (new_str);
}

int		ft_check_file(int *k, t_minishell *shell)
{
	int		fd;
	char	**tab;
	char	**tab2;

	tab = split_input(shell->redir_tab[0]);
	tab2 = split_input(shell->redir_tab[*k]);
	if ((fd = open(tab2[0], O_RDONLY, 0777)) < 0)
	{
		shell->ret = ft_putstr_error(ERROR_FILE_NOT_FOUND, tab2[0], 1);
		free_tab(tab);
		free_tab(tab2);
		return (FALSE);
	}
	close(fd);
	free_tab(tab);
	free_tab(tab2);
	return (TRUE);
}

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

int		ft_redirection(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		j;
	int		k;
	char	*arg;

	if (!check_redirection(shell->input))
		return (TRUE);
	if (ft_count_redirection(shell->input, shell) == FALSE)
	{
		ft_free_args(shell);
		return (FALSE);
	}
	ft_split_pipe(shell, '|');
	ft_pipe_malloc(shell, shell->input);
	i = -1;
	while (shell->pipe_tab[++i])
	{
		if (check_redirection(shell->pipe_tab[i]))
		{
			shell->pipe_tab[i] = ft_create_redirection(shell->pipe_tab[i],\
			shell);
			ft_split_redirection(shell, shell->pipe_tab[i], '>', '<');
			arg = ft_redirection_arg(shell->redir_tab, shell);
			j = -1;
			k = 0;
			while (shell->pipe_tab[i][++j])
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
				if (shell->pipe_tab[i][j] == '>')
				{
					k++;
					shell->str = ft_redirection_right(shell, &i, &k, arg);
					shell->redirection_read = FALSE;
					j++;
				}
				if (shell->pipe_tab[i][j] == '<')
				{
					k++;
					if (!(shell->str = ft_redirection_left(shell, arg, &k, &i)))
					{
						free(arg);
						free_tab(shell->pipe_tab);
						free_tab(shell->redir_tab);
						ft_free_args(shell);
						return (FALSE);
					}
					shell->redirection_read = TRUE;
					j++;
				}
			}
			shell->index_tab = 0;
			free_tab(shell->redir_tab);
			free(arg);
		}
		else if (i > 0)
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
	if (!shell->redirection_read)
		shell->str = realloc_str(shell->str, "| grep -q \"\"");
	shell->input ? free(shell->input) : 0;
	shell->input = ft_strdup(shell->str);
	ft_putendl_fd(shell->input, 1);
	free(shell->str);
	ft_pipe_main(shell, glo);
	ft_free_args(shell);
	free_tab(shell->pipe_tab);
	return (FALSE);
}
