/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:02:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/01 16:48:23 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_quotes(char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] != quote)
		(*i)++;
}

int		ft_count_redirection(char *str, int *i, char c)
{
	int	count;

	count = 0;
	while (str[*i] == c)
	{
		count++;
		(*i)++;
	}
	return (count);
}

int		ft_redirection(t_minishell *shell)
{
	int	i;

	i = -1;
	while (shell->input[++i])
	{
		if (shell->input[i] == '"' || shell->input[i] == '\'')
			ft_quotes(shell->input, &i, shell->input[i]);
		if (shell->input[i] == '>')
		{
			if (ft_count_redirection(shell->input, &i, shell->input[i]) > 2)
				shell->ret = ft_putstr_error("minishell: parse error near ",
				"`>'", 1);
			return (TRUE);
		}
	}
	return (FALSE);
}
