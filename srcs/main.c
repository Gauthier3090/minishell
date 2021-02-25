/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/25 15:01:24 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_loop_main_more(t_minishell *shell, t_struct *glo)
{
	char	*input;

	while (shell->tab[++(shell->i)])
	{
		shell->arg = parse_input(shell->tab[shell->i], shell);
		input = delete_char_left(shell->tab[shell->i], '=');
		shell->variable = parse_input(input, shell);
		free(input);
		input = delete_char_right(shell->tab[shell->i], '=');
		shell->value = parse_input(input, shell);
		if (shell->variable)
		{
			if (ft_semicolon(shell, glo) == FALSE)
				return ;
			if (ft_redirection(shell, glo) == FALSE)
				return ;
			if (ft_pipe_main(shell, glo) == FALSE)
				return ;
			if (ft_builtins(shell, glo) == FALSE)
				return ;
		}
		ft_free_args(shell);
		if (shell->ret)
			break ;
	}
}

void	ft_loop_main(t_minishell *shell, t_struct *glo)
{
	shell->variable ? free(shell->variable) : 0;
	shell->value ? free(shell->value) : 0;
	shell->arg ? free(shell->arg) : 0;
	if (ft_strlen_tab(shell->tab) == 1)
	{
		shell->variable = NULL;
		shell->value = NULL;
		shell->arg = NULL;
		if (ft_semicolon(shell, glo) == FALSE)
			return ;
		if (ft_redirection(shell, glo) == FALSE)
			return ;
		if (ft_pipe_main(shell, glo) == FALSE)
			return ;
		if (ft_builtins(shell, glo) == FALSE)
			return ;
	}
	else
		ft_loop_main_more(shell, glo);
	if (glo->pipin == 1)
		exit(EXIT_SUCCESS);
}

int		ft_builtins(t_minishell *shell, t_struct *glo)
{
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		echo(shell);
	else if (ft_strcmp(shell->tab[0], "exit") == 0)
	{
		if (!(exit_shell(shell->tab, shell)))
			return (FALSE);
	}
	else if (ft_strcmp(shell->tab[0], "env") == 0)
		ft_env(shell->tab, shell->env, shell);
	else if (ft_strcmp(shell->tab[0], "export") == 0)
		export(shell);
	else if (ft_strcmp(shell->tab[0], "unset") == 0)
		unset(shell);
	else if (ft_strcmp(shell->tab[0], "cd") == 0)
		ft_cd(shell->input, shell->env, glo, shell);
	else if (ft_strcmp(shell->tab[0], "pwd") == 0)
		ft_pwd(shell);
	else
		ft_exec(shell, glo);
	return (TRUE);
}

void	loop_prompt(t_minishell *shell, t_struct *glo)
{
	while (1)
	{
		ft_signal_hand();
		directoryprompt();
		shell->input = getinput();
		shell->input = ft_whitespace(shell->input);
		ft_putstr_fd("result = ", 1);
		ft_putstr_fd(shell->input, 1);
		ft_putstr_fd("\nend\n", 1);
		if (shell->input[0] != '\0')
		{
			if (check_quotes_close(shell->input))
			{
				if (!(shell->tab = split_input(shell->input)))
					exit(EXIT_FAILURE);
				ft_tab_dup(shell);
				shell->i = 0;
				shell->variable = NULL;
				shell->value = NULL;
				shell->arg = NULL;
				ft_loop_main(shell, glo);
				free_tab(shell->tab);
			}
			else
				shell->ret = ft_putstr_error(ERROR_QUOTES_NOT_CLOSED, NULL, 1);
		}
		free(shell->input);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_struct	*glo;
	t_minishell	*shell;

	if (argc != 1 || ft_strncmp(argv[0], "./minishell", 12) != 0)
		return (EXIT_FAILURE);
	if (!(glo = malloc(sizeof(t_struct))))
		exit(EXIT_FAILURE);
	if (!(shell = ft_calloc(1, sizeof(t_minishell))))
		exit(EXIT_FAILURE);
	if (ft_struct_init(glo, shell) == FALSE)
		exit(EXIT_FAILURE);
	shell->env = malloc_tab(env);
	if (!shell->env)
		return (ft_putstr_error("minishell: env is null\n", NULL, 1));
	loop_prompt(shell, glo);
	return (EXIT_SUCCESS);
}
