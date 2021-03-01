/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:27:48 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/01 18:54:15 by gpladet          ###   ########.fr       */
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
	free(shell->backs_input);
	shell->input = ft_whitespace(shell->input, shell);
	shell->backs_input = ft_strdup(shell->pipe_backs_tab[glo->pipe_ite]);
	shell->backs_input = ft_backs_whitespace(shell, shell->backs_input);
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
		if (shell->input[ft_strlen(shell->input) - i] == '|' &&\
		ft_voided_char_input(ft_strlen(shell->input) - i, shell) == FALSE)
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

int		ft_pipe_sub_more(t_minishell *shell, t_struct *glo, int x, int z)
{
	if (!(glo->pipe_tab[x] = ft_substr(shell->input, z, \
		ft_strlen(shell->input) - z)))
		exit(EXIT_FAILURE);
	if (!(shell->pipe_backs_tab[x] = ft_substr(shell->backs_input, z, \
		ft_strlen(shell->backs_input))))
		exit(EXIT_FAILURE);
	shell->pipe_backs_tab[x + 1] = NULL;
	glo->pipe_tab[x + 1] = NULL;
	x = 0;
	if (ft_pipe_loop(shell, glo) == FALSE)
		return (FALSE);
	if (ft_multi_pipe(shell, glo) == FALSE)
		return (FALSE);
	return (TRUE);
}
