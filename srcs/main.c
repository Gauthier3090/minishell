/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/07 17:36:38 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_loop_main(t_minishell *shell, t_struct *glo)
{
	shell->variable = ft_strdup("");
	shell->value = ft_strdup("");
	while (shell->tab[++(shell->i)])
		{
			free(shell->variable);
			free(shell->value);
			shell->variable = parse_input(shell,
			delete_char_left(shell->tab[shell->i], '='), TRUE);
			shell->value = parse_input(shell,
			delete_char_right(shell->tab[shell->i], '='), FALSE);
			if (shell->variable)
			{
				if (ft_semicolon(shell, glo) == FALSE)
					return ;
				ft_builtins(shell, glo);
			}
		}
	if (ft_strlen_tab(shell->tab) == 1)
	{
		if (ft_semicolon(shell, glo) == FALSE)
			return ;
		ft_builtins(shell, glo);
	}
}

void	ft_builtins(t_minishell *minishell, t_struct *glo)
{
	if (ft_strcmp(minishell->tab[0], "echo") == 0)
		echo(minishell);
	else if (ft_strcmp(minishell->tab[0], "exit") == 0)
		exit_shell(minishell->tab);
	else if (ft_strcmp(minishell->tab[0], "env") == 0)
		ft_env(minishell->tab, minishell->env);
	else if (ft_strcmp(minishell->tab[0], "export") == 0)
		export(minishell);
	else if (ft_strcmp(minishell->tab[0], "unset") == 0)
		unset(minishell);
	else if (ft_strcmp(minishell->tab[0], "cd") == 0)
		ft_cd(minishell->input, minishell->env, glo);
	else if (ft_strcmp(minishell->tab[0], "pwd") == 0)
		ft_pwd(minishell->input);
	else if (ft_exec(minishell, glo) != 0)
		return ;
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(minishell->tab[0], 2);
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
	if (ft_struct_init(glo) == FALSE)
		exit(EXIT_FAILURE);
	shell->env = env;
	while (1)
	{
		directoryprompt();
		shell->input = getinput();
		shell->input = ft_whitespace(shell->input);
		if (!(shell->tab = ft_split(shell->input, ' ')))
			exit(EXIT_FAILURE);
		shell->i = 0;
		ft_loop_main(shell, glo);
		free_tab(shell->tab);
		free(shell->input);
	}
}
