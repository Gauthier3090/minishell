/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:04:42 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/09 14:04:59 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
