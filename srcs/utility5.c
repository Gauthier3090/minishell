/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:58:48 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/27 17:31:37 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_quotes_check_sub(t_minishell *shell, int i, int var, char c)
{
	int		k;
	int		j;

	j = i - 1;
	k = 0;
	while (shell->input[i] && i < ((int)ft_strlen(shell->input)))
	{
		if (shell->input[i] == c)
		{
			k = i;
			if (var < k && var > j)
				return (-1);
			else
			{
				j = 0;
				k = 0;
				break ;
			}
		}
		i++;
	}
	return (i);
}

int		ft_simple_quotes_check(t_minishell *shell, int var)
{
	int		i;

	i = 0;
	while (shell->input && shell->input[i])
	{
		if (shell->input[i] == '\'')
		{
			i++;
			i = ft_quotes_check_sub(shell, i, var, '\'');
			if (i == -1)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int		ft_double_quotes_check(t_minishell *shell, int var)
{
	int		i;

	i = 0;
	while (shell->input[i] && i < ((int)ft_strlen(shell->input) - 1))
	{
		if (shell->input[i] == '"')
		{
			i++;
			i = ft_quotes_check_sub(shell, i, var, '"');
			if (i == -1)
				return (TRUE);
		}
		i++;
	}
	if (ft_simple_quotes_check(shell, var) == TRUE)
		return (TRUE);
	return (FALSE);
}
