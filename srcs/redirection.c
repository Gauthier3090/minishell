/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/12 17:02:35 by gpladet          ###   ########.fr       */
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

int		ft_check_redirection(t_minishell *shell, int c, int c2)
{
	int		y;

	while (shell->input[++shell->index])
	{
		if (shell->input[shell->index] == c && shell->input[shell->index + 1] == c &&
		ft_double_quotes_check(shell, shell->index) == FALSE)
		{
			shell->redir[shell->index_tab] = shell->index;
			shell->index_tab++;
			shell->index += 2;
			y = 1;
			while (shell->input && (shell->input[shell->index + y] == ' ' ||
				shell->input[shell->index + y] == '\t' || \
				shell->input[shell->index + y] == '\v'))
				y++;
		}
		else if (shell->input[shell->index] == c && ft_double_quotes_check(shell, shell->index) == FALSE)
		{
			shell->redir[shell->index_tab] = shell->index;
			shell->index_tab++;
			y = 1;
			while (shell->input && (shell->input[shell->index + y] == ' ' ||
				shell->input[shell->index + y] == '\t' || \
				shell->input[shell->index + y] == '\v'))
				y++;
		}
		else if (shell->input[shell->index] == c2 && shell->input[shell->index + 1] == c2 &&
		ft_double_quotes_check(shell, shell->index) == FALSE)
		{
			shell->redir[shell->index_tab] = shell->index;
			shell->index_tab++;
			shell->index += 2;
			y = 1;
			while (shell->input && (shell->input[shell->index + y] == ' ' ||
				shell->input[shell->index + y] == '\t' || \
				shell->input[shell->index + y] == '\v'))
				y++;
		}
	}
	return (TRUE);
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

int		ft_count_redirection(char *str)
{
	int		i;
	int		count;
	char	*tmp;

	i = -1;
	if (!(tmp = ft_strtrim(str, " ")))
		exit(EXIT_FAILURE);
	if (tmp[ft_strlen(tmp) - 1] == '>' || tmp[ft_strlen(tmp) - 1] == '<')
	{
		free(tmp);
		ft_putstr_error("minishell: parse error near `\\n'\n", NULL, 1);
		return (FALSE);		
	}
	free(tmp);
	while (str[++i])
	{
		if (str[0] == '>')
		{
			ft_putstr_error("minishell: parse error near `>'\n", NULL, 1);
			return (FALSE);
		}
		if (str[0] == '<')
		{
			ft_putstr_error("minishell: parse error near `<'\n", NULL, 1);
			return (FALSE);
		}
		if (str[i] == '>' && i != 0)
		{
			count = 0;
			while (str[i] == '>' && str[i])
			{
				count++;
				i++;
				while (str[i] == ' ')
					i++;
				if (str[i] == '>' && str[i + 1] == '>')
				{
					ft_putstr_error("minishell: parse error near `>>'\n", NULL, 1);
					return (FALSE);
				}
				else if (str[i] == '<')
				{
					ft_putstr_error("minishell: parse error near `<'\n", NULL, 1);
					return (FALSE);
				}
			}
			if (count == 3)
			{
				ft_putstr_error("minishell: parse error near `>'\n", NULL, 1);
				return (FALSE);
			}
			else if (count > 3)
			{
				ft_putstr_error("minishell: parse error near `>>'\n", NULL, 1);
				return (FALSE);
			}
		}
		if (str[i] == '<' && i != 0)
		{
			count = 0;
			while (str[i] == '<' && str[i])
			{
				count++;
				i++;
				while (str[i] == ' ')
					i++;
				if (str[i] == '>' && str[i + 1] == '>')
				{
					ft_putstr_error("minishell: parse error near `>>'\n", NULL, 1);
					return (FALSE);
				}
				else if (str[i] == '>')
				{
					ft_putstr_error("minishell: parse error near `>'\n", NULL, 1);
					return (FALSE);
				}
			}
			if (count > 1)
			{
				ft_putstr_error("minishell: parse error near `<'\n", NULL, 1);
				return (FALSE);
			}
		}
	}
	return (TRUE);
}

char	*ft_create_redirection(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == '<')
			len++;
	}
	if (!(new_str = ft_calloc(ft_strlen(str) + len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '<')
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
