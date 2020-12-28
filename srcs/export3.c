/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:09:02 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/28 15:25:45 by gpladet          ###   ########.fr       */
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
