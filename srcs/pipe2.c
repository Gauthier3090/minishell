/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:27:48 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/03 16:45:06 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_error_pipe(int error_numb, t_minishell *shell)
{
	ft_put_errno(error_numb, shell);
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
	if (!(temp = ft_substr(shell->input, 0, x)))
		exit(EXIT_FAILURE);
	if (!(shell->tab = split_input(temp)))
		exit(EXIT_FAILURE);
	free(temp);
	shell->input = ft_whitespace(shell->input);
	shell->i = 0;
	glo->pipe_ite++;
}

int		ft_pipe_loop(t_minishell *shell, t_struct *glo)
{
	int		i;

	i = 1;
	while (shell->input[ft_strlen(shell->input) - i] == ' ' \
		|| shell->input[ft_strlen(shell->input) - i] == '|')
	{
		if (shell->input[ft_strlen(shell->input) - i] == '|')
		{
			shell->ret = ft_putstr_error(\
			"No multiline supported\n", NULL, 1);
			ft_free_args(shell);
			glo->z = 0;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
