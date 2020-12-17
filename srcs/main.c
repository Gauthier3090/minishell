/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/17 16:16:50 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_builtins(t_minishell *minishell, t_struct *glo)
{
	if (minishell->tab[0])
	{
		if (ft_strncmp(minishell->tab[0], "echo", 4) == 0)
			echo(minishell->tab, minishell->env);
		else if (ft_strncmp(minishell->tab[0], "exit", 4) == 0)
			exit_shell(minishell->tab);
		else if (ft_strncmp(minishell->tab[0], "env", 3) == 0)
			ft_env(minishell->tab, minishell->env);
		else if (ft_strncmp(minishell->tab[0], "export", 6) == 0)
			export(minishell);
		else if (ft_strncmp("cd", minishell->input, 2) == 0)
			ft_cd(minishell->input, minishell->env, glo);
		else if (ft_strncmp("pwd", minishell->input, 3) == 0)
			ft_pwd(minishell->input);
		else if (ft_strncmp("ls", minishell->input, 2) == 0)
			ft_ls(minishell->input);
		else
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(minishell->tab[0], 2);
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	t_struct	*glo;
	t_minishell	*minishell;

	if (argc != 1 || ft_strncmp(argv[0], "./minishell", 12) != 0)
		return (EXIT_FAILURE);
	if (!(glo = malloc(sizeof(t_struct))))
		exit(EXIT_FAILURE);
	if (!(minishell = ft_calloc(1, sizeof(t_minishell))))
		exit(EXIT_FAILURE);
	if (ft_struct_init(glo) == FALSE)
		exit(EXIT_FAILURE);
	minishell->env = env;
	minishell->is_active = 1;
	while (minishell->is_active)
	{
		directoryprompt();
		minishell->input = getinput();
		minishell->input = ft_whitespace(minishell->input);
		if (!(minishell->tab = ft_split(minishell->input, ' ')))
			exit(EXIT_FAILURE);
		ft_builtins(minishell, glo);
		free_tab(minishell->tab);
		free(minishell->input);
	}
}
