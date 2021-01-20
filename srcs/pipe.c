/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:53:51 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/20 11:42:36 by ldavids          ###   ########.fr       */
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
	int		i;

	i = 1;
	while (shell->input[ft_strlen(shell->input) - i] == ' ' \
		|| shell->input[ft_strlen(shell->input) - i] == '|')
	{
		if (shell->input[ft_strlen(shell->input) - i] == '|')
		{
			ft_putstr_fd("No multiline supported\n", 1);
			return (FALSE);
		}
		i++;
	}
	if (!(glo->pipe_tab = ft_split(shell->input, '|')))
		exit(EXIT_FAILURE);
	i = 0;
	if (ft_multi_pipe(shell, glo) == FALSE)
		return (FALSE);
	glo->z = 0;
	glo->pipin = 0;
	free_tab(glo->pipe_tab);
	shell->variable ? free(shell->variable) : 0;
	shell->value ? free(shell->value) : 0;
	shell->variable = NULL;
	shell->value = NULL;
	return (FALSE);
}

int		ft_check_pipe(t_minishell *shell, t_struct *glo, char c)
{
	int		y;

	while (shell->input[glo->i])
	{
		if (shell->input[glo->i] == c)
		{
			glo->z++;
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
				glo->z = 0;
				return (FALSE);
			}
		}
		glo->i++;
	}
	return (TRUE);
}

int		ft_pipe_main(t_minishell *shell, t_struct *glo)
{
	glo->i = 0;
	glo->pipe_ite = 0;
	while (shell->input && (shell->input[glo->i] == ' ' || \
	shell->input[glo->i] == '\t' || shell->input[glo->i] == '\v'))
		glo->i++;
	if (shell->input[glo->i] == '|')
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
