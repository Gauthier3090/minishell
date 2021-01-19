/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:27:48 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/19 14:38:03 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_error_pipe(int error_numb)
{
	ft_put_errno(error_numb);
	return (FALSE);
}

void	ft_next_pipe(t_minishell *shell, t_struct *glo)
{
	char	*temp;
	int		x;

	x = 0;
	free(shell->input);
	if (!(shell->input = ft_strdup(glo->pipe_tab[glo->pipe_ite])))
		exit(EXIT_FAILURE);
	free_tab(shell->tab);
	while (shell->input && shell->input[x])
		x++;
	temp = ft_substr(shell->input, 0, x);
	if (!(shell->tab = ft_split(temp, ' ')))
		exit(EXIT_FAILURE);
	free(temp);
	shell->input = ft_whitespace(shell->input);
	shell->i = 0;
	glo->pipe_ite++;
}
