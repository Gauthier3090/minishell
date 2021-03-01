/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/01 16:22:10 by ldavids          ###   ########.fr       */
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
		if (shell->variable && shell->value)
		{
			if (!(shell->arg = ft_strjoin(shell->variable, shell->value)))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!(shell->arg = ft_strdup(shell->variable)))
				exit(EXIT_FAILURE);
		}
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

char	*check_backslash_quote(char *input)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = -1;
	size = 0;
	while (input[++i])
	{
		if (input[i] == '\\' && (input[i + 1] == '"' || input[i + 1] == '\''))
		{
			size += 3;
			i++;
		}
		else
			size++;
	}
	if (!(tmp = ft_calloc(size + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (input[++i])
	{
		if (input[i] == '\\' && input[i + 1] == '\'')
		{
			tmp[++j] = '"';
			tmp[++j] = '\'';
			tmp[++j] = '"';
			i++;
		}
		else if (input[i] == '\\' && input[i + 1] == '"')
		{
			tmp[++j] = '\'';
			tmp[++j] = '"';
			tmp[++j] = '\'';
			i++;
		}
		else
			tmp[++j] = input[i];
	}
	free(input);
	return (tmp);
}

void	loop_prompt(t_minishell *shell, t_struct *glo)
{
	char	*tmp;

	while (1)
	{
		ft_signal_hand();
		directoryprompt();
		shell->input = getinput();
		shell->input = ft_whitespace(shell->input, shell);
		if (shell->input[0] != '\0')
		{
			shell->input = check_backslash_quote(shell->input);
			if (check_quotes_close(shell->input))
			{
				if (!(shell->tab = split_input(shell->input)))
					exit(EXIT_FAILURE);
				ft_tab_dup(shell);
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
				/*free_tab(shell->backs_tab);*/
			}
			else
				shell->ret = ft_putstr_error(ERROR_QUOTES_NOT_CLOSED, NULL, 1);
		}
		free(shell->input);
		free(shell->backs_input);
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
