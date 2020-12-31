/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:40:55 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/31 15:43:15 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*unset_value(char *str, char **env)
{
	char	*value;
	char	**arg;
	int		i;

	if (str)
	{
		i = -1;
		value = NULL;
		value = export_value_more(value, str, &i);
		if (!(arg = ft_split(&str[i], '$')))
			exit(EXIT_FAILURE);
		if (arg)
			value = export_variable_env(value, arg, env);
		free_tab(arg);
		return (value);
	}
	return (NULL);
}

void	research_env_more(char *variable, t_minishell *shell)
{
	int		i;
	char	*tmp;

	if (check_error_unset(variable))
	{
		i = -1;
		while (shell->env[++i])
		{
			tmp = delete_char_left(shell->env[i], '=');
			if (ft_strcmp(tmp, variable) == 0)
			{
				shell->env = delete_env(shell, i);
				shell->go_free = TRUE;
			}
			free(tmp);
		}
	}
}
