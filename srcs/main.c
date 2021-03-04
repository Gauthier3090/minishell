/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/04 15:34:15 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_loop_main_more(t_minishell *shell, t_struct *glo)
{
	char	*input;

	while (shell->tab[++(shell->i)])
	{
		input = delete_char_left(shell->tab[shell->i], '=');
		shell->variable = parse_input(input, shell);
		free(input);
		input = delete_char_right(shell->tab[shell->i], '=');
		shell->value = parse_input(input, shell);
		init_shell_arg(shell);
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
	ft_backslash_tab(shell);
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

void	loop_prompt_input(t_minishell *shell, t_struct *glo)
{
	char	*tmp;

	ft_tab_dup(shell, glo);
	shell->input = check_backslash_quote(shell->input, -1, shell);
	if (!check_quotes_close(shell->input))
		shell->ret = ft_putstr_error(ERROR_QUOTES_NOT_CLOSED, NULL, 1);
	else
	{
		if (!(shell->tab = split_input(shell->input)))
			exit(EXIT_FAILURE);
		shell->i = 0;
		shell->variable = NULL;
		shell->value = NULL;
		shell->arg = NULL;
		tmp = parse_input(shell->tab[0], shell);
		free(shell->tab[0]);
		if (!(shell->tab[0] = ft_strdup(tmp)))
			exit(EXIT_FAILURE);
		free(tmp);
		ft_loop_main(shell, glo);
		free_tab(shell->tab);
	}
	shell->backs_input ? free(shell->backs_input) : 0;
	ft_free_args(shell);
}

void	loop_prompt(t_minishell *shell, t_struct *glo)
{
	while (1)
	{
		ft_signal_hand();
		directoryprompt();
		shell->input = getinput();
		shell->input = ft_whitespace(shell->input, shell);
		if (shell->input[0] != '\0')
			loop_prompt_input(shell, glo);
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
