/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/22 17:17:17 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	export_error(char *variable, char **arg)
{
	int	i;

	i = -1;
	while (variable[++i])
	{
		if (variable[i] == '+' || variable[i] == '-')
			ft_putstr_error("export: not an identifier: ", variable);
	}
	if (ft_strisdigit(variable) && variable[0] != '\0')
		ft_putstr_error("export: not an identifier: ", variable);
	i = -1;
	while (arg[++i])
	{
		if (arg[0] != arg[i] && ft_strcmp(arg[i], "USER"))
			ft_putstr_error("export: not valid in this context: ", variable);
	}
}

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
	export_error(variable, arg);
	free_tab(arg);
	return (variable);
}

char	*export_value(char *str, char **env)
{
	char	*value;
	char	**arg;
	int		i;
	int		j;

	i = -1;
	j = 1;
	if (!(value = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	while (str[++i] != '$' && str[i])
	{
		if (!(value = ft_realloc(value, j + 1)))
			exit(EXIT_FAILURE);
		value[i] = str[i];
		j++;
	}
	if (!(arg = ft_split(&str[i], '$')))
		exit(EXIT_FAILURE);
	if (arg)
		value = export_variable_env(value, arg, env);
	free_tab(arg);
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
		if (!ft_strcmp(shell->tab[i], "="))
		{
			ft_putendl_fd("minishell: bad assigment", 2);
			exit(EXIT_FAILURE);
		}
		if (!(arg = ft_split(shell->tab[i], '=')))
			exit(EXIT_FAILURE);
		variable = export_variable(arg[0], shell->env);
		if (variable[0] == '\0')
			sorting_env(shell->env, ft_strlen_tab(shell->env));
		if (arg[1])
			value = export_value(arg[1], shell->env);
		else
		{
			if (!(value = ft_strdup("''")))
				exit(EXIT_FAILURE);
		}
		ft_putstr_fd(variable, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(value, 1);
		free(variable);
		free(value);
		free_tab(arg);
	}
}
