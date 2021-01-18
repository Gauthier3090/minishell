/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/18 15:20:43 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

size_t	ft_tablen(char **tab)
{
	int		i;
	size_t	length;

	i = -1;
	length = 0;
	while (tab[++i])
	{
		length += ft_strlen(tab[i]);
		length++;
	}
	return (length);
}

char	*tabtostr(char **tab)
{
	char	*str;
	int		i;
	int		j;
	int		index;

	if (!(str = ft_calloc(1, ft_tablen(tab) * sizeof(char))))
		return (NULL);
	i = -1;
	index = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			str[++index] = tab[i][j];
		if (i != ft_strlen_tab(tab) - 1)
			str[++index] = '\n';
	}
	return (str);
}

void	sorting_env(char **env, int size)
{
	int		i;
	int		j;
	char	*tmp;
	char	**tab;

	tmp = tabtostr(env);
	if (!(tab = ft_split(tmp, '\n')))
		exit(EXIT_FAILURE);
	free(tmp);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
	ft_print_tab(tab);
	free_tab(tab);
}

void	variable_no_exist(t_minishell *shell, char *new_env)
{
	char	*str;

	str = tabtostr(shell->env);
	if (!(str = ft_realloc(str, ft_strlen(str) + ft_strlen(new_env) + 2)))
		exit(EXIT_FAILURE);
	str = ft_strcat(str, "\n");
	str = ft_strcat(str, new_env);
	free_tab(shell->env);
	if (!(shell->env = ft_split(str, '\n')))
		exit(EXIT_FAILURE);
	free(str);
}

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

void	create_variable_env(t_minishell *shell, char *variable, char *value)
{
	int		index;
	char	*new_env;

	if (!value || value[0] == '\0')
	{
		if (!(value = ft_strdup("''")))
			exit(EXIT_FAILURE);
	}
	if (!(new_env = ft_calloc(ft_strlen(variable)
	+ ft_strlen(value) + 2, sizeof(char))))
		exit(EXIT_FAILURE);
	new_env = ft_strcat(new_env, variable);
	new_env = ft_strcat(new_env, "=");
	new_env = ft_strcat(new_env, value);
	if ((index = variable_exist(shell->env, variable)) != -1)
	{
		free(shell->env[index]);
		if (!(shell->env[index] = ft_strdup(new_env)))
			exit(EXIT_FAILURE);
	}
	else
		variable_no_exist(shell, new_env);
	if (!ft_strcmp(value, "''"))
		free(value);
	free(new_env);
}

int		check_error_export(char *variable, char *value, t_minishell *shell)
{
	int		i;

	i = -1;
	while (variable[++i])
	{
		if (variable[i] == '+' || variable[i] == '-')
		{
			shell->ret = ft_putstr_error("export: not an identifier: ",
			variable, 1);
			return (FALSE);
		}
	}
	if (ft_strisdigit(variable) && variable[0] != '\0')
	{
		shell->ret = ft_putstr_error("export: not an identifier: ",
		variable, 1);
		return (FALSE);
	}
	else if (variable[0] == '\0' && value)
	{
		shell->ret = ft_putstr_error("export: this value is not found: ",
		value, 1);
		return (FALSE);
	}
	return (TRUE);
}

void	export(t_minishell *shell)
{
	shell->ret = 0;
	if (ft_strlen_tab(shell->tab) == 1
	|| !ft_strcmp(shell->tab[shell->i], "$USER"))
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	else if (!ft_strcmp(shell->tab[shell->i], "="))
	{
		shell->ret = ft_putstr_error("export: ", "bad assignment", 0);
		return ;
	}
	else
	{
		if (check_error_export(shell->variable, shell->value, shell))
			create_variable_env(shell, shell->variable, shell->value);
	}
}
