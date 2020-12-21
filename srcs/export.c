/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/22 00:37:38 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*export_variable_env(char *variable, char **arg, char **env)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = -1;
	while (arg[++i])
	{
		j = -1;
		while (env[++j])
		{
			tmp = delete_char_left(env[j], '=');
			if (ft_strcmp(tmp, arg[i]) == 0)
			{
				tmp2 = delete_char_right(env[j], '=');
				if (!(variable = ft_realloc(variable,
				ft_strlen(variable) + ft_strlen(tmp2))))
					exit(EXIT_FAILURE);
				variable = ft_strcat(variable, tmp2);
			}
			free(tmp);
		}
	}
	return (variable);
}

char	*export_variable(char *str, char **env)
{
	int		i;
	int		j;
	char	*variable;
	char	**arg;

	i = -1;
	j = 1;
	if (!(variable = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	while (str[++i] != '$' && str[i])
	{
		if (!(variable = ft_realloc(variable, j + 1)))
			exit(EXIT_FAILURE);
		variable[i] = str[i];
		j++;
	}
	if (!(arg = ft_split(&str[i], '$')))
		exit(EXIT_FAILURE);
	if (arg)
		variable = export_variable_env(variable, arg, env);
	free_tab(arg);
	return (variable);
}

void	export(t_minishell *shell)
{
	int		i;
	char	**arg;
	char	*variable;

	if (ft_strlen_tab(shell->tab) == 1)
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	i = 0;
	while (shell->tab[++i])
	{
		if (!(arg = ft_split(shell->tab[i], '=')))
			exit(EXIT_FAILURE);
		variable = export_variable(arg[0], shell->env);
		if (variable[0] == '\0' && ft_strlen_tab(shell->tab) == 2)
			sorting_env(shell->env, ft_strlen_tab(shell->env));
		free(variable);
		free_tab(arg);
	}
}
