/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:38:46 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/03 17:32:04 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		init_shell_arg(t_minishell *shell)
{
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
}

int			ft_builtins(t_minishell *shell, t_struct *glo)
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

char		*create_backslash_quote(char *input, char *tmp, t_minishell *shell)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (input[++i])
	{
		if (shell->backs_input[i] != '0' && input[i] == '\'')
		{
			tmp[++j] = '"';
			tmp[++j] = '\'';
			tmp[++j] = '"';
		}
		else if (shell->backs_input[i] != '0' && input[i] == '"')
		{
			tmp[++j] = '\'';
			tmp[++j] = '"';
			tmp[++j] = '\'';
		}
		else
			tmp[++j] = input[i];
	}
	return (tmp);
}

char		*check_backslash_quote(char *input, t_minishell *shell)
{
	int		i;
	int		size;
	char	*tmp;

	i = -1;
	size = 0;
	while (input[++i])
	{
		if (shell->backs_input[i] != '0'
		&& (input[i] == '"' || input[i] == '\''))
			size += 3;
		else
			size++;
	}
	if (!(tmp = ft_calloc(size + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	tmp = create_backslash_quote(input, tmp, shell);
	free(input);
	return (tmp);
}

int			ft_quotes_check_sub_double(char *str, int i,
			int var, t_minishell *shell)
{
	int		k;
	int		j;

	j = i - 1;
	k = 0;
	while (str[i] && i < ((int)ft_strlen(str)))
	{
		if (str[i] == '"' && shell->backs_input[i] == '0')
		{
			k = i;
			if (var < k && var > j)
				return (-1);
			else
			{
				j = 0;
				k = 0;
				break ;
			}
		}
		i++;
	}
	return (i);
}
