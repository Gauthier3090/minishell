/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/02 22:25:54 by gpladet          ###   ########.fr       */
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

	shell->variable ? free(shell->variable) : 0;
	shell->value ? free(shell->value) : 0;
	shell->arg ? free(shell->arg) : 0;
	while (shell->tab[++(shell->i)])
	{
		shell->arg = parse_input(shell->tab[shell->i], shell->env, shell->ret);
		input = delete_char_left(shell->tab[shell->i], '=');
		shell->variable = parse_input(input, shell->env, shell->ret);
		free(input);
		input = delete_char_right(shell->tab[shell->i], '=');
		shell->value = parse_input(input, shell->env, shell->ret);
		if (shell->variable)
		{
			if (ft_semicolon(shell, glo) == FALSE)
				return ;
			if (ft_pipe_main(shell, glo) == FALSE)
				return ;
			if (ft_redirection(shell) == TRUE)
				return ;
			ft_builtins(shell, glo);
		}
		shell->variable ? free(shell->variable) : 0;
		shell->value ? free(shell->value) : 0;
		shell->arg ? free(shell->arg) : 0;
		shell->arg = NULL;
		shell->variable = NULL;
		shell->value = NULL;
		if (shell->ret)
			break ;
	}
	if (ft_strlen_tab(shell->tab) == 1)
	{
		shell->variable = NULL;
		shell->value = NULL;
		shell->arg = NULL;
		if (ft_semicolon(shell, glo) == FALSE)
			return ;
		if (ft_pipe_main(shell, glo) == FALSE)
			return ;
		ft_builtins(shell, glo);
	}
	if (glo->pipin == 1)
		exit(EXIT_SUCCESS);
}

void	ft_builtins(t_minishell *shell, t_struct *glo)
{
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		echo(shell);
	else if (ft_strcmp(shell->tab[0], "exit") == 0)
		exit_shell(shell->tab, shell->ret);
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
		if (shell->input[0] != '\0')
		{
			if (check_quotes_close(shell->input))
			{
				if (!(shell->tab = split_input(shell->input)))
					exit(EXIT_FAILURE);
				shell->i = 0;
				shell->variable = NULL;
				shell->value = NULL;
				shell->arg = NULL;
				ft_loop_main(shell, glo);
				free_tab(shell->tab);
			}
			else
				shell->ret = ft_putstr_error("minishell: ", "quotes are not closed", 1);
		}
		free(shell->input);
	}
}
