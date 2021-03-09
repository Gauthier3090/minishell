/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:58:59 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/09 13:59:52 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		error_redirection(char *error, char *var, int ret, t_minishell *shell)
{
	ft_putstr_error(error, var, ret);
	shell->ret = ret;
	return (FALSE);
}

int		ft_pipe_malloc_more(t_minishell *shell, char *str, int x, int z)
{
	if (!(shell->pipe_tab[x] = ft_substr(str, z, \
		ft_strlen(str) - z)))
		exit(EXIT_FAILURE);
	shell->pipe_tab[x + 1] = NULL;
	return (TRUE);
}

int		ft_pipe_malloc(t_minishell *shell, char *str)
{
	int		x;
	int		z;

	x = 0;
	z = 0;
	if (!(shell->pipe_tab = malloc((shell->z + 2) * sizeof(char*))))
		exit(EXIT_FAILURE);
	while (x < shell->z)
	{
		if (!(shell->pipe_tab[x] = ft_substr(str, z, \
			(shell->pipe[x]) - z)))
			exit(EXIT_FAILURE);
		z = shell->pipe[x] + 1;
		x++;
	}
	if (!(ft_pipe_malloc_more(shell, str, x, z)))
		return (FALSE);
	return (FALSE);
}

int		ft_split_pipe(t_minishell *shell, char c)
{
	int		y;

	while (shell->input[++shell->j])
	{
		if ((shell->input[shell->j] == c) && !ft_double_quotes_check(
		shell->input, shell->j, shell)
		&& !ft_voided_char_input(shell->j, shell))
		{
			shell->pipe[shell->z] = shell->j;
			shell->z++;
			y = 1;
			while (shell->input && (shell->input[shell->j + y] == ' ' ||
			shell->input[shell->j + y] == '\t' ||
			shell->input[shell->j + y] == '\v'))
				y++;
			if (shell->input[shell->j + y] == c)
			{
				shell->ret = ft_putstr_error(ERROR_PIPE, NULL, 2);
				ft_free_args(shell);
				shell->z = 0;
				return (FALSE);
			}
		}
	}
	return (TRUE);
}
