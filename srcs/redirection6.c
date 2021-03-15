/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:10:20 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/15 17:02:58 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_redirection_arg(char **redir_tab, t_minishell *shell)
{
	int		i;
	char	*arg;

	i = 0;
	arg = NULL;
	while (redir_tab[++i])
	{
		arg = create_arg(redir_tab, arg, i, shell);
		if (redir_tab[i][0] == ' ' && shell->double_right)
			redir_tab[i][0] = '>';
		if (redir_tab[i][0] == ' ' && shell->double_left)
			redir_tab[i][0] = '<';
		shell->double_left = FALSE;
		shell->double_right = FALSE;
	}
	return (ft_redirection_arg_return(arg, redir_tab));
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
	char	**tab2;

	tab2 = split_input(shell->redir_tab[*k]);
	if ((fd = open(tab2[0], O_RDONLY, 0777)) < 0)
	{
		shell->ret = ft_putstr_error(ERROR_FILE_NOT_FOUND, tab2[0], 1);
		free_tab(tab2);
		return (FALSE);
	}
	close(fd);
	free_tab(tab2);
	return (TRUE);
}
