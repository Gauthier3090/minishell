/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:41:11 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/05 15:25:12 by ldavids          ###   ########.fr       */
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

int			ft_backs_str_simple(t_minishell *shell, char *str, int i)
{
	int		y;

	y = 0;
	shell->backs_input[i] = str[i];
	if ((str[i + 1] && str[i + 1] >= 65 && str[i + 1] <= 90)\
	|| (str[i + 1]
	>= 97 && str[i + 1] <= 122))
	{
		shell->backs_input[i] = '0';
		y = 1;
	}
	else
		y = -1;
	while (str[i])
	{
		str[i] = str[i + y + 1];
		i++;
	}
	i = 0;
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
