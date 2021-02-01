/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:53:51 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/01 16:19:25 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_multi_pipe_sub(t_minishell *shell, t_struct *glo, int *pipefd)
{
	pid_t	pid;

	while (glo->p < (glo->z * 2) + 1)
	{
		ft_next_pipe(shell, glo);
		if ((pid = fork()) < 0)
			return (ft_error_pipe(errno));
		if (pid == 0)
		{
			if (glo->p != (glo->z * 2))
			{
				if (dup2(pipefd[glo->p + 1], 1) < 0)
					return (ft_error_pipe(errno));
			}
			if (glo->p != 0)
			{
				if (dup2(pipefd[glo->p - 2], 0) < 0)
					return (ft_error_pipe(errno));
			}
			ft_close_fd(glo, pipefd);
			ft_loop_main(shell, glo);
		}
		glo->p = glo->p + 2;
	}
	return (TRUE);
}

int		ft_multi_pipe(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		pipefd[glo->z * 2];

	i = 0;
	while (i < glo->z)
	{
		if (pipe(pipefd + i * 2) < 0)
			return (ft_error_pipe(errno));
		i++;
	}
	glo->pipin = 1;
	glo->p = 0;
	if (ft_multi_pipe_sub(shell, glo, pipefd) == FALSE)
		return (FALSE);
	ft_close_fd(glo, pipefd);
	i = 0;
	while (i++ < glo->z + 1)
		wait(NULL);
	return (TRUE);
}

int		ft_pipe_sub(t_minishell *shell, t_struct *glo)
{
	int		x;
	int		z;

	x = 0;
	z = 0;
	glo->pipe_tab = malloc((glo->z + 2) * sizeof(char*));
	while (x < glo->z)
	{
		glo->pipe_tab[x] = ft_substr(shell->input, z, (glo->pipe[x]) - z);
		z = glo->pipe[x] + 1;
		x++;
	}
	glo->pipe_tab[x] = ft_substr(shell->input, z, ft_strlen(shell->input) - z);
	glo->pipe_tab[x + 1] = NULL;
	x = 0;
	if (ft_pipe_loop(shell, glo) == FALSE)
		return (FALSE);
	if (ft_multi_pipe(shell, glo) == FALSE)
		return (FALSE);
	glo->z = 0;
	glo->pipin = 0;
	free_tab(glo->pipe_tab);
	ft_free_args(shell);
	return (FALSE);
}

int		ft_check_pipe(t_minishell *shell, t_struct *glo, char c)
{
	int		y;

	while (shell->input[++glo->j])
	{
		if ((shell->input[glo->j] == c) && \
		(ft_double_quotes_check(shell, glo->j) == FALSE))
		{
			glo->pipe[glo->z] = glo->j;
			glo->z++;
			y = 1;
			while (shell->input && (shell->input[glo->j + y] == ' ' ||
				shell->input[glo->j + y] == '\t' || \
				shell->input[glo->j + y] == '\v'))
				y++;
			if (shell->input[glo->j + y] == c)
			{
				ft_putstr_fd(\
				"bash: syntax error near unexpected token `|'\n", 1);
				ft_free_args(shell);
				glo->z = 0;
				return (FALSE);
			}
		}
	}
	return (TRUE);
}

int		ft_pipe_main(t_minishell *shell, t_struct *glo)
{
	glo->j = 0;
	glo->pipe_ite = 0;
	while (shell->input && (shell->input[glo->j] == ' ' || \
	shell->input[glo->j] == '\t' || shell->input[glo->j] == '\v'))
		glo->j++;
	if (shell->input[glo->j] == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 1);
		return (FALSE);
	}
	if (glo->z != 0)
		return (TRUE);
	if (ft_check_pipe(shell, glo, '|') == FALSE)
		return (FALSE);
	if (glo->z == 0)
		return (TRUE);
	if (ft_pipe_sub(shell, glo) == FALSE)
		return (FALSE);
	return (TRUE);
}
