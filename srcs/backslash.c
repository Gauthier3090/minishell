/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:41:11 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/03 17:38:38 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_backslash_tab(t_minishell *shell)
{
	int		i;
	int		x;
	int		y;

	y = 0;
	i = 0;
	x = 0;
	free_tab(shell->backs_tab);
	if (!(shell->backs_tab = split_input(shell->input)))
		exit(EXIT_FAILURE);
	while (shell->tab[i])
	{
		x = 0;
		shell->backs_tab[i] = ft_backzero(shell->backs_tab[i]);
		while (shell->tab[i][x] && shell->backs_tab[i][x] &&\
		shell->backs_input[y])
		{
			shell->backs_tab[i][x] = shell->backs_input[y];
			y++;
			x++;
		}
		i++;
	}
}

void		ft_tab_dup(t_minishell *shell, t_struct *glo)
{
	int		x;
	int		y;

	y = 0;
	x = 1;
	while (x <= (int)ft_strlen(shell->input) &&\
	shell->input[ft_strlen(shell->input) - x] &&\
	shell->input[ft_strlen(shell->input) - x] == '\\')
	{
		y++;
		x++;
	}
	if (!(shell->backs_input = ft_strdup(shell->input)))
		exit(EXIT_FAILURE);
	shell->input = ft_backslash_input(shell->input, shell);
	if (y % 2 != 0)
	{
		shell->ret = ft_putstr_error(
				"No multiline supported\n", NULL, 2);
		free(shell->input);
		free(shell->backs_input);
		loop_prompt(shell, glo);
	}
}

int			ft_backs_str(t_minishell *shell, char *str, int i)
{
	shell->backs_input[i] = str[i];
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	i = 0;
	return (i);
}

int			ft_backslash_input_sub(char *str, t_minishell *shell, int i)
{
	if (str[i + 1] == '"')
		i = ft_backs_str(shell, str, i);
	else if (ft_simple_quotes_check(shell->input, i, shell) == FALSE)
	{
		shell->backs_input[i] = str[i];
		i = 0;
	}
	else if (ft_double_quotes_check(shell->input, i, shell) == FALSE)
		i = ft_backs_str(shell, str, i);
	else if (ft_double_quotes_check(shell->input, i, shell) ==\
	TRUE && (str[i + 1] == '$' || str[i + 1] == '\\') &&\
	ft_simple_quotes_check(shell->input, i, shell) == FALSE)
		i = ft_backs_str(shell, str, i);
	/*else if (ft_simple_quotes_check(shell->input, i, shell) == FALSE)
	{
		shell->backs_input[i] = str[i];
		i = 0;
	}*/
	return (i);
}

char		*ft_backslash_input(char *str, t_minishell *shell)
{
	int		i;

	i = 0;
	shell->backs_input = ft_backzero(shell->backs_input);
	while (str[i])
	{
		if (str[i] == '\\' && shell->backs_input[i] == '0')
			i = ft_backslash_input_sub(str, shell, i);
		i++;
	}
	return (str);
}
