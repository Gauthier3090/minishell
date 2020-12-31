/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:09:02 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/31 14:46:36 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	variable_no_exist(t_minishell *shell, char *variable)
{
	char *str;

	str = tabtostr(shell->env);
	if (!(str = ft_realloc(str, ft_strlen(str) + ft_strlen(variable) + 1)))
		exit(EXIT_FAILURE);
	str = ft_strcat(str, "\n");
	str = ft_strcat(str, variable);
	if (shell->go_free)
		free_tab(shell->env);
	if (!(shell->env = ft_split(str, '\n')))
		exit(EXIT_FAILURE);
	shell->go_free = TRUE;
	free(str);
}

char	*export_variable_start(char *str, int *i)
{
	char	*variable;
	int		j;

	if (!(variable = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	j = 1;
	while (str[++(*i)] != '$' && str[*i])
	{
		if (!(variable = ft_realloc(variable, j + 1)))
			exit(EXIT_FAILURE);
		variable[*i] = str[*i];
		j++;
	}
	return (variable);
}

int		export_error(char *variable)
{
	int	i;

	i = -1;
	while (variable[++i])
	{
		if (variable[i] == '+' || variable[i] == '-')
		{
			ft_putstr_error("export: not an identifier: ", variable);
			return (TRUE);
		}
	}
	if (ft_strisdigit(variable) && variable[0] != '\0')
	{
		ft_putstr_error("export: not an identifier: ", variable);
		return (TRUE);
	}
	return (FALSE);
}

void	export_more(t_minishell *shell, char *tmp_variable, char *tmp_value)
{
	char	*variable;
	char	*value;

	if (!(variable = export_variable(tmp_variable, shell->env)))
	{
		free(tmp_variable);
		return ;
	}
	if (variable[0] == '\0' && !tmp_value)
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	if (!(value = ft_export(variable, tmp_value, shell->env)))
	{
		free(variable);
		free(tmp_variable);
		return ;
	}
	create_variable_env(variable, value, shell);
	free(tmp_variable);
}
