/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:17:08 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/29 16:36:56 by ldavids          ###   ########.fr       */
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
	while (minishell->input[glo->i])
	{
		if (minishell->input[glo->i] == ';')
		{
			glo->x++;
			glo->check = 1;
		}
		glo->i++;
	}
	if (glo->x == 0)
		return (TRUE);
	if (ft_semicolon_sub(minishell, glo) == FALSE)
		return (FALSE);
	return (TRUE);
}

int		ft_semicolon_sub(t_minishell *minishell, t_struct *glo)
{
	int		i;

	i = 0;
	if (!(glo->forked_tab = ft_split(minishell->input, ';')))
		exit(EXIT_FAILURE);
	while (glo->x > -1)
	{
		glo->check = 2;
		free(minishell->input);
		minishell->input = ft_strdup(glo->forked_tab[i]);
		free_tab(minishell->tab);
		if (!(minishell->tab = ft_split(minishell->input, ' ')))
			exit(EXIT_FAILURE);
		glo->x--;
		minishell->input = ft_whitespace(minishell->input);
		ft_builtins(minishell, glo);
		i++;
	}
	glo->check = 0;
	glo->x = 0;
	free_tab(glo->forked_tab);
	return (FALSE);
}
