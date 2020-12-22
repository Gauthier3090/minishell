/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/22 23:25:11 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*export_value_more(char *value, char *str, int *i)
{
	int	j;

	j = 1;
	if (!(value = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	while (str[++(*i)] != '$' && str[*i])
	{
		if (!(value = ft_realloc(value, j + 1)))
			exit(EXIT_FAILURE);
		value[*i] = str[*i];
		j++;
	}
	return (value);
}

char	*export_value(char *str, char **env)
{
	char	*value;
	char	**arg;
	int		i;

	i = -1;
	value = NULL;
	value = export_value_more(value, str, &i);
	if (!(arg = ft_split(&str[i], '$')))
		exit(EXIT_FAILURE);
	if (arg)
	{
		value = export_variable_env(value, arg, env);
		if (value[0] == '\0')
		{
			if (!(value = ft_strdup("''")))
				exit(EXIT_FAILURE);
		}
	}
	free_tab(arg);
	return (value);
}

char	**create_variable_env(char *variable, char *value, char **env)
{
	char	*str;
	int		index;

	if ((index = variable_exist(env, variable)) != -1)
	{
		if (!ft_strcmp(value, "''"))
			return (env);
		free(env[index]);
		env[index] = NULL;
	}
	if (!(variable = ft_realloc(variable, ft_strlen(value) + 2)))
		exit(EXIT_FAILURE);
	variable = ft_strcat(variable, "=");
	variable = ft_strcat(variable, value);
	str = tabtostr(env);
	if (!(str = ft_realloc(str, ft_strlen(str) + ft_strlen(variable) + 2)))
		exit(EXIT_FAILURE);
	str = ft_strcat(str, "\n");
	str = ft_strcat(str, variable);
	if (!(env = ft_split(str, '\n')))
		exit(EXIT_FAILURE);
	free(str);
	free(variable);
	free(value);
	return (env);
}

char	*ft_export(char *variable, char *value, char **arg, char **env)
{
	if (arg[1])
		value = export_value(arg[1], env);
	else
	{
		if (!(value = ft_strdup("''")))
			exit(EXIT_FAILURE);
	}
	if (variable[0] == '\0' && arg[1])
		ft_putstr_error("minishell: this value is not found: ", value);
	return (value);
}

void	export(t_minishell *shell)
{
	int		i;
	char	**arg;
	char	*variable;
	char	*value;

	if (ft_strlen_tab(shell->tab) == 1)
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	i = 0;
	while (shell->tab[++i])
	{
		shell->tab[i] = ft_whitespace(shell->tab[i]);
		if (!ft_strncmp(shell->tab[i], "=", 1))
		{
			ft_putendl_fd("minishell: bad assigment", 2);
			exit(EXIT_FAILURE);
		}
		if (!(arg = ft_split(shell->tab[i], '=')))
			exit(EXIT_FAILURE);
		variable = export_variable(arg[0], shell->env);
		if (variable[0] == '\0' && !arg[1])
			sorting_env(shell->env, ft_strlen_tab(shell->env));
		value = ft_export(variable, value, arg, shell->env);
		shell->env = create_variable_env(variable, value, shell->env);
		free_tab(arg);
	}
}
