/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:05:18 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/01 18:15:47 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_strlen_redirection(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == '<')
			len++;
	}
	return (len);
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

void	ft_check_redirection_simple(t_minishell *shell, int *y)
{
	shell->redir[shell->index_tab] = shell->index;
	shell->index_tab++;
	*y = 1;
	while (shell->input && (shell->input[shell->index + *y] == ' ' ||
		shell->input[shell->index + *y] == '\t' || \
		shell->input[shell->index + *y] == '\v'))
		(*y)++;
}

void	ft_check_redirection_more(t_minishell *shell, int *y)
{
	shell->redir[shell->index_tab] = shell->index;
	shell->index_tab++;
	shell->index += 2;
	*y = 1;
	while (shell->input && (shell->input[shell->index + *y] == ' ' ||
	shell->input[shell->index + *y] == '\t' ||
	shell->input[shell->index + *y] == '\v'))
		(*y)++;
}

int		ft_check_redirection(t_minishell *shell, int c, int c2)
{
	int		y;

	while (shell->input[++shell->index])
	{
		if ((((shell->input[shell->index] == c \
		&& (ft_voided_char_input(shell->index, shell) == FALSE)\
		&& shell->input[shell->index + 1] == c \
		&& (ft_voided_char_input(shell->index + 1, shell) == FALSE))) ||
		((shell->input[shell->index] == c2 &&\
		(ft_voided_char_input(shell->index, shell) == FALSE) &&
		shell->input[shell->index + 1] == c2 \
		&& (ft_voided_char_input(shell->index + 1, shell) == FALSE))
		&& (ft_double_quotes_check(shell->input, shell->index) == FALSE))))
			ft_check_redirection_more(shell, &y);
		else if (shell->input[shell->index] == c && \
		(ft_voided_char_input(shell->index, shell) == FALSE)
		&& ft_double_quotes_check(shell->input, shell->index) == FALSE)
			ft_check_redirection_simple(shell, &y);
	}
	return (TRUE);
}
