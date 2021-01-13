/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:53:51 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/13 14:29:04 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void ft_pipe(t_minishell *shell, t_struct *glo)
{
	// 0 is read end, 1 is write end
	int pipefd[2];
/*	pid_t p1, p2;*/

	if (pipe(pipefd) < 0) {
		printf("\nPipe could not be initialized");
		return;
	}
	/*if (p1 == 0) {*/
		// Child 1 executing..
		// It only needs to write at the write end
			/*ft_putstr_fd("input = ", 1);
		ft_putstr_fd(shell->input, 1);
		ft_putstr_fd("\n", 1);*/
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		shell->input = ft_strdup(glo->forked_tab[0]);
		ft_putstr_fd("input pipin= ", 1);
		ft_putstr_fd(shell->input, 1);
		ft_builtins(shell, glo);
	/*	}
	else {
		if (p2 == 0) {*/
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		/*ft_putstr_fd("parsedpipe = ", 1);
		ft_putstr_fd(parsedpipe[0], 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("parsedpipe[1] = ", 1);
		ft_putstr_fd(parsedpipe[1], 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("parsedpipe[2] = ", 1);
		ft_putstr_fd(parsedpipe[2], 1);
		ft_putstr_fd("\n", 1);*/

		shell->input = ft_strdup(glo->forked_tab[1]);
		ft_putstr_fd("input pipout= ", 1);
		ft_putstr_fd(shell->input, 1);
		ft_builtins(shell, glo);
}

void	ft_loop_pipe(t_minishell *shell, t_struct *glo, int i)
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
	/*ft_putstr_fd("\n", 1);
	ft_putstr_fd(ft_itoa(glo->x), 1);
	ft_putstr_fd("\n", 1);*/
	ft_pipe(shell, glo);
}

int		ft_pipe_sub(t_minishell *shell, t_struct *glo)
{
	int		i;
	/*int		x;*/

	i = 1;
	/*x = 0;*/
	while (shell->input[ft_strlen(shell->input) - i] == ' ' || shell->input[ft_strlen(shell->input) - i] == '|')
	{
		if (shell->input[ft_strlen(shell->input) - i] == '|')
			{
				ft_putstr_fd("No multiline supported\n", 1);
				return (FALSE);
			}
		i++;
	}
	if (!(glo->forked_tab = ft_split(shell->input, '|')))
		exit(EXIT_FAILURE);
	i = 0;
	/*while (glo->x > -1)
	{
		if (glo->x == 0 && x == 1)
			break ;
		ft_loop_pipe(shell, glo, i);
		i++;
	}*/
	ft_pipe(shell, glo);
	glo->check = 0;
	glo->x = 0;
	free_tab(glo->forked_tab);
	return (FALSE);
}


int		ft_pipe_main(t_minishell *shell, t_struct *glo)
{
	glo->i = 0;
	while (shell->input && (shell->input[glo->i] == ' ' || \
	shell->input[glo->i] == '\t' || shell->input[glo->i] == '\v'))
		glo->i++;
	/*ft_putstr_fd("entering pipe main\n", 1);*/
	if (shell->input[glo->i] == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 1);
		return (FALSE);
	}
	if (ft_check_double_char(shell, glo, '|') == FALSE)
		return (FALSE);
	if (glo->x == 0)
		return (TRUE);
	if (ft_pipe_sub(shell, glo) == FALSE)
		return (FALSE);
	return (TRUE);
}
