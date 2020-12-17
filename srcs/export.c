/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/17 15:33:39 by gpladet          ###   ########.fr       */
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
			return (TRUE);
	}
	return (FALSE);
}

void	create_variable(t_minishell *shell, char **arg)
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
		if (!(tmp = ft_strdup(shell->tab[1])))
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

void	create_env_variable(t_minishell *shell)
{
	char	**arg;

	if (!(arg = ft_split(shell->tab[1], '=')))
		exit(EXIT_FAILURE);
	if (variable_exist(shell->env, arg[0]))
		ft_putendl_fd("EXIST", 1);
	else
		create_variable(shell, arg);
	free_tab(arg);
}

void	export(t_minishell *shell)
{
	if (ft_strlen_tab(shell->tab) == 1)
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	else
		create_env_variable(shell);
}
