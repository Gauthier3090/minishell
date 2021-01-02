/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:17:08 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/02 16:55:13 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_semicolon(t_minishell *minishell, t_struct *glo)
{
	glo->i = 0;
	if (glo->check == 2)
		return (TRUE);
	while (minishell->input && (minishell->input[glo->i] == ' ' || \
	minishell->input[glo->i] == '\t' || minishell->input[glo->i] == '\v'))
		glo->i++;
	if (minishell->input[glo->i] == ';')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;'\n", 1);
		return (FALSE);
	}
	if (ft_check_double_semicolon(minishell, glo) == FALSE)
		return (FALSE);
	if (glo->x == 0)
		return (TRUE);
	if (ft_semicolon_sub(minishell, glo) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	ft_loop_sub(t_minishell *minishell, t_struct *glo, int i)
{
	glo->check = 2;
	free(minishell->input);
	if (!(minishell->input = ft_strdup(glo->forked_tab[i])))
		exit(EXIT_FAILURE);
	free_tab(minishell->tab);
	if (!(minishell->tab = ft_split(minishell->input, ' ')))
		exit(EXIT_FAILURE);
	glo->x--;
	minishell->input = ft_whitespace(minishell->input);
	ft_builtins(minishell, glo);
}

int		ft_semicolon_sub(t_minishell *minishell, t_struct *glo)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (!(glo->forked_tab = ft_split(minishell->input, ';')))
		exit(EXIT_FAILURE);
	if (minishell->input[ft_strlen(minishell->input) - 1] == ';')
		x = 1;
	while (glo->x > -1)
	{
		if (glo->x == 0 && x == 1)
			break ;
		ft_loop_sub(minishell, glo, i);
		i++;
	}
	glo->check = 0;
	glo->x = 0;
	free_tab(glo->forked_tab);
	return (FALSE);
}

int		ft_check_double_semicolon(t_minishell *minishell, t_struct *glo)
{
	int		y;

	while (minishell->input[glo->i])
	{
		if (minishell->input[glo->i] == ';')
		{
			glo->x++;
			glo->check = 1;
			y = 1;
			while (minishell->input && (minishell->input[glo->i + y] == ' ' ||
				minishell->input[glo->i + y] == '\t' || \
				minishell->input[glo->i + y] == '\v'))
				y++;
			if (minishell->input[glo->i + y] == ';')
			{
				ft_putstr_fd("bash: syntax error near unexpected \
token `;'\n", 1);
				glo->x = 0;
				glo->check = 0;
				return (FALSE);
			}
		}
		glo->i++;
	}
	return (TRUE);
}
