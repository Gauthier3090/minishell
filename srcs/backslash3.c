/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:14:54 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/04 15:29:31 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			ft_back_str_double_quotes(char *str, int *i)
{
	while (str[*i])
	{
		str[*i] = str[*i + 1];
		(*i)++;
	}
	*i = 0;
	return (*i);
}

int			ft_backs_str_more(char *str, int *i, int y)
{
	while (str[*i])
	{
		str[*i] = str[*i + 1 + y];
		(*i)++;
	}
	*i = 0;
	return (*i);
}

int			ft_backs_str(t_minishell *shell, char *str, int i)
{
	int		y;

	y = 0;
	shell->backs_input[i] = str[i];
	if (str[i + 1] == '"')
		return (ft_back_str_double_quotes(str, &i));
	if (((str[i + 1] >= 65 && str[i + 1] <= 90) || (str[i + 1] \
	>= 97 && str[i + 1] <= 122))
	&& ft_double_quotes_check(str, i, shell) == TRUE)
	{
		shell->backs_input[i] = '0';
		y = 1;
	}
	else if (ft_double_quotes_check(str, i, shell) == FALSE)
		y = 0;
	else
		y = -1;
	if (ft_double_quotes_check(str, i, shell) == TRUE && str[i + 1] == '$')
		y = 0;
	return (ft_backs_str_more(str, &i, y));
}

void		ft_backslash_input_sub_more(t_minishell *shell, char *str, int *i)
{
	shell->backs_input[*i] = str[*i];
	while (str[*i])
	{
		str[*i] = str[*i + 1];
		(*i)++;
	}
	*i = 0;
}

int			ft_backslash_input_sub(char *str, t_minishell *shell, int i)
{
	if (str[i + 1] == '\\' && shell->backs_input[i] == '0')
		ft_backslash_input_sub_more(shell, str, &i);
	else if (str[i + 1] == '"')
		i = ft_backs_str(shell, str, i);
	else if (ft_simple_quotes_check(shell->input, i, shell) == TRUE)
		i = ft_backs_str_simple(shell, str, i);
	else if (ft_double_quotes_check(shell->input, i, shell) == FALSE &&
	ft_simple_quotes_check(shell->input, i, shell) == FALSE)
		i = ft_backs_str(shell, str, i);
	else if (ft_double_quotes_check(shell->input, i, shell) ==\
	TRUE && ft_simple_quotes_check(shell->input, i, shell) == FALSE)
		i = ft_backs_str(shell, str, i);
	else if (ft_simple_quotes_check(shell->input, i, shell) == FALSE)
	{
		shell->backs_input[i] = str[i];
		i = 0;
	}
	return (i);
}
