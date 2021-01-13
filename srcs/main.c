/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/13 14:31:37 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"

char	**malloc_tab(char **tab)
{
	int		i;
	char	**new_tab;

	i = -1;
	if (!(new_tab = ft_calloc(ft_strlen_tab(tab) + 1, sizeof(char *))))
		exit(EXIT_FAILURE);
	while (tab[++i])
	{
		if (!(new_tab[i] = ft_strdup(tab[i])))
			exit(EXIT_FAILURE);
	}
	return (new_tab);
}

void	ft_loop_main(t_minishell *shell, t_struct *glo)
{
	char	*input;

	while (shell->tab[++(shell->i)])
	{
		input = delete_char_left(shell->tab[shell->i], '=');
		shell->variable = parse_input(input, shell->env);
		free(input);
		input = delete_char_right(shell->tab[shell->i], '=');
		shell->value = parse_input(input, shell->env);
		if (shell->variable)
		{
			if (ft_semicolon(shell, glo) == FALSE)
				return ;
			if (ft_pipe_main(shell, glo) == FALSE)
				return ;
			ft_builtins(shell, glo);
		}
		/*free(shell->variable);
		free(shell->value);*/
	}
	if (ft_strlen_tab(shell->tab) == 1)
	{
		if (ft_semicolon(shell, glo) == FALSE)
			return ;
		if (ft_pipe_main(shell, glo) == FALSE)
				return ;
		ft_builtins(shell, glo);
	}
}

void	ft_builtins(t_minishell *shell, t_struct *glo)
{
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		echo(shell);
	else if (ft_strcmp(shell->tab[0], "exit") == 0)
		exit_shell(shell->tab);
	else if (ft_strcmp(shell->tab[0], "env") == 0)
		ft_env(shell->tab, shell->env);
	else if (ft_strcmp(shell->tab[0], "export") == 0)
		export(shell);
	else if (ft_strcmp(shell->tab[0], "unset") == 0)
		unset(shell);
	else if (ft_strcmp(shell->tab[0], "cd") == 0)
		ft_cd(shell->input, shell->env, glo);
	else if (ft_strcmp(shell->tab[0], "pwd") == 0)
		ft_pwd(shell->input);
	else if (ft_exec(shell, glo) != 0)
		return ;
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(shell->tab[0], 2);
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
	shell->env = malloc_tab(env);
	while (1)
	{
		directoryprompt();
		shell->input = getinput();
		shell->input = ft_whitespace(shell->input);
		if (check_quotes_close(shell->input))
		{
			if (!(shell->tab = split_input(shell->input)))
				exit(EXIT_FAILURE);
			shell->i = 0;
			ft_loop_main(shell, glo);
			free_tab(shell->tab);
		}
		else
			ft_putendl_fd("minishell: quote is not closed", 2);
		free(shell->input);
	}
}
