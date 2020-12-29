/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/29 17:23:32 by gpladet          ###   ########.fr       */
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

void	create_variable_env(char *variable, char *value, t_minishell *shell)
{
	char	*tmp;
	int		index;

	tmp = ft_strdup(variable);
	if (!(variable = ft_realloc(variable,
	ft_strlen(variable) + ft_strlen(value) + 1)))
		exit(EXIT_FAILURE);
	variable = ft_strcat(variable, "=");
	variable = ft_strcat(variable, value);
	if ((index = variable_exist(shell->env, tmp)) != -1)
	{
		if (ft_strcmp(value, "''"))
		{
			free(shell->env[index]);
			shell->env[index] = ft_strdup(variable);
		}
	}
	else
		variable_no_exist(shell, variable);
	variable ? free(variable) : 0;
	value ? free(value) : 0;
	tmp ? free(tmp) : 0;
}

char	*ft_export(char *variable, char *value, char **env)
{
	if (value)
		value = export_value(value, env);
	else
	{
		if (!(value = ft_strdup("''")))
			exit(EXIT_FAILURE);
	}
	if (variable[0] == '\0' && value)
	{
		ft_putstr_error("minishell: this value is not found: ", value);
		free(value);
		return (NULL);
	}
	return (value);
}

void	export(t_minishell *shell)
{
	int		i;
	char	*tmp_variable;
	char	*tmp_value;

	if (ft_strlen_tab(shell->tab) == 1)
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	i = 0;
	while (shell->tab[++i])
	{
		shell->tab[i] = ft_whitespace(shell->tab[i]);
		if (!ft_strncmp(shell->tab[i], "=", 1))
		{
			ft_putstr_error("minishell: ", "bad assigment");
			return ;
		}
		tmp_variable = delete_char_left(shell->tab[i], '=');
		tmp_value = delete_char_right(shell->tab[i], '=');
		export_more(shell, tmp_variable, tmp_value);
	}
}
