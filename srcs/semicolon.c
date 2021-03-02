/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:17:08 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/02 17:33:57 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_loop_sub(t_minishell *shell, t_struct *glo, int i)
{
	int		x;

	x = 0;
	glo->check = 2;
	free(shell->input);
	if (!(shell->input = ft_strdup(glo->semico[i])))
		exit(EXIT_FAILURE);
	free_tab(shell->tab);
	while (shell->input[x])
		x++;
	if (!(shell->tab = split_input(shell->input)))
		exit(EXIT_FAILURE);
	glo->x--;
	shell->input = ft_whitespace(shell->input, shell);
	shell->i = 0;
	free(shell->backs_input);
	shell->backs_input = ft_strdup(shell->semi_backs_tab[i]);
	shell->backs_input = ft_backs_whitespace(shell, shell->backs_input);
	ft_loop_main(shell, glo);
}

int		ft_semicolon_sub(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		x;

	i = 1;
	x = 0;
	ft_semico_malloc(shell, glo);
	while (shell->input[ft_strlen(shell->input) - i] == ' ' ||\
			shell->input[ft_strlen(shell->input) - i] == ';')
	{
		shell->input[ft_strlen(shell->input) - i] == ';' ? x = 1 : 0;
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
	glo->semico ? free_tab(glo->semico) : 0;
	shell->semi_backs_tab ? free_tab(shell->semi_backs_tab) : 0;
	return (FALSE);
}

int		ft_check_double_char(t_minishell *shell, t_struct *glo, char c)
{
	int		y;

	while (shell->input[glo->i])
	{
		if ((shell->input[glo->i] == c) && \
			(ft_double_quotes_check(shell->input, glo->i, shell) == FALSE)\
			&& ft_voided_char_input(glo->i, shell) == FALSE)
		{
			glo->semi[glo->x] = glo->i;
			glo->check = 1;
			y = 1;
			while (shell->input && (shell->input[glo->i + y] == ' ' ||
				shell->input[glo->i + y] == '\t' || \
				shell->input[glo->i + y] == '\v'))
				y++;
			if (shell->input[glo->i + y] == c)
			{
				ft_check_double_char_sub(shell, glo);
				return (FALSE);
			}
			glo->x++;
		}
		glo->i++;
	}
	return (TRUE);
}

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
		shell->ret = ft_putstr_error(\
		"bash: syntax error near unexpected token `;'\n", NULL, 2);
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
