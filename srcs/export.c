/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/17 17:04:07 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		variable_exist(char **env, char *str)
{
	int	i;
	int	j;
	int	length;

	i = -1;
	length = ft_strlen(str);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], str, j) && !ft_strncmp(env[i], str, length))
			return (i);
	}
	return (-1);
}

void	create_variable(t_minishell *shell, char **arg, int i)
{
	char	*str;
	char	*tmp;

	if (!arg[1])
	{
		if (!(tmp = ft_strdup(arg[0])))
			exit(EXIT_FAILURE);
		tmp = ft_realloc(tmp, ft_strlen(tmp) + 5);
		tmp = ft_strcat(tmp, "=''");
	}
	else
	{
		if (!(tmp = ft_strdup(shell->tab[i])))
			exit(EXIT_FAILURE);
	}
	str = tabtostr(shell->env);
	str = ft_realloc(str, ft_strlen(str) + ft_strlen(tmp) + 2);
	str = ft_strcat(str, "\n");
	str = ft_strcat(str, tmp);
	if (!(shell->env = ft_split(str, '\n')))
		exit(EXIT_FAILURE);
	free(str);
	free(tmp);
}

void	create_env_variable(t_minishell *shell, int i)
{
	char	**arg;
	int		index;

	shell->tab[i] = ft_whitespace(shell->tab[i]);
	if (!(arg = ft_split(shell->tab[i], '=')))
		exit(EXIT_FAILURE);
	if ((index = variable_exist(shell->env, arg[0])) != -1)
	{
		if (arg[1])
			shell->env[index] = ft_strdup(shell->tab[i]);
	}
	else
		create_variable(shell, arg, i);
	free_tab(arg);
}

void	export(t_minishell *shell)
{
	int	i;

	if (ft_strlen_tab(shell->tab) == 1)
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	i = 0;
	while (shell->tab[++i])
	{
		if (shell->tab[i][0] == '=')
		{
			ft_putendl_fd("minishell: bad assignment", 2);
			exit(EXIT_FAILURE);
		}
		create_env_variable(shell, i);
	}
}
