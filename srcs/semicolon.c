/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:17:08 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/19 16:53:38 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_semicolon(t_minishell *shell, t_struct *glo)
{
	glo->i = 0;
	if (glo->check == 2)
		return (TRUE);
	while (shell->input && (shell->input[glo->i] == ' ' || \
	shell->input[glo->i] == '\t' || shell->input[glo->i] == '\v'))
		glo->i++;
	if (shell->input[glo->i] == ';')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;'\n", 1);
		return (FALSE);
	}
	if (ft_check_double_char(shell, glo, ';') == FALSE)
		return (FALSE);
	if (glo->x == 0)
		return (TRUE);
	if (ft_semicolon_sub(shell, glo) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	ft_loop_sub(t_minishell *shell, t_struct *glo, int i)
{
	int		x;
	char	*temp;

	x = 0;
	glo->check = 2;
	free(shell->input);
	if (!(shell->input = ft_strdup(glo->forked_tab[i])))
		exit(EXIT_FAILURE);
	free_tab(shell->tab);
	while (shell->input[x])
		x++;
	temp = ft_substr(shell->input, 0, x);
	if (!(shell->tab = ft_split(temp, ' ')))
		exit(EXIT_FAILURE);
	free(temp);
	glo->x--;
	shell->input = ft_whitespace(shell->input);
	shell->i = 0;
	ft_loop_main(shell, glo);
}

int		ft_semicolon_sub(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		x;

	i = 1;
	x = 0;
	if (!(glo->forked_tab = ft_split(shell->input, ';')))
		exit(EXIT_FAILURE);
	while (shell->input[ft_strlen(shell->input) - i] == ' ' || shell->input[ft_strlen(shell->input) - i] == ';')
	{
		if (shell->input[ft_strlen(shell->input) - i] == ';')
			x = 1;
		i++;
	}
	i = 0;
	while (glo->x > -1)
	{
		if (glo->x == 0 && x == 1)
			break ;
		ft_loop_sub(shell, glo, i);
		i++;
	}
	glo->check = 0;
	glo->x = 0;
	free_tab(glo->forked_tab);
	return (FALSE);
}

int		ft_check_double_char(t_minishell *shell, t_struct *glo, char c)
{
	int		y;

	while (shell->input[glo->i])
	{
		if (shell->input[glo->i] == c)
		{
			glo->x++;
			glo->check = 1;
			y = 1;
			while (shell->input && (shell->input[glo->i + y] == ' ' ||
				shell->input[glo->i + y] == '\t' || \
				shell->input[glo->i + y] == '\v'))
				y++;
			if (shell->input[glo->i + y] == c)
			{
				ft_putstr_fd("bash: syntax error near unexpected token `", 1);
				ft_putchar_fd(c, 1);
				ft_putstr_fd("'\n", 1);
				glo->x = 0;
				glo->check = 0;
				return (FALSE);
			}
		}
		glo->i++;
	}
	return (TRUE);
}
