/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:58:48 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/03 16:59:45 by ldavids          ###   ########.fr       */
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

int		ft_struct_init(t_struct *glo, t_minishell *shell)
{
	char		buf[200];

	if (!(glo->env = ft_strdup("")))
		exit(EXIT_FAILURE);
	if (!(glo->arg = ft_strdup("")))
		exit(EXIT_FAILURE);
	if (getcwd(buf, 200) == NULL)
	{
		ft_put_errno(errno, shell);
		return (FALSE);
	}
	if (!(glo->oldpwd = ft_strdup(buf)))
		exit(EXIT_FAILURE);
	glo->cd_count = 0;
	glo->x = 0;
	glo->z = 0;
	glo->check = 0;
	glo->pipin = 0;
	glo->p = 0;
	if (!(glo->save_old_pwd = ft_strdup("")))
		exit(EXIT_FAILURE);
	return (TRUE);
}