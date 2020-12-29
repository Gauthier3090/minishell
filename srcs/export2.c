/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:50:28 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/29 16:36:38 by gpladet          ###   ########.fr       */
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
	char	*variable;
	char	*tmp;
	char	**arg;

	i = -1;
	variable = export_variable_start(str, &i);
	if (!(tmp = ft_strdup(variable)))
		exit(EXIT_FAILURE);
	if (!(arg = ft_split(&str[i], '$')))
		exit(EXIT_FAILURE);
	if (arg)
		variable = export_variable_env(variable, arg, env);
	if (export_error(variable))
	{
		free(tmp);
		free_tab(arg);
		free(variable);
		return (NULL);
	}
	free(tmp);
	free_tab(arg);
	return (variable);
}
