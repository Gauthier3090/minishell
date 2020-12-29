/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:40:36 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/29 17:03:14 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*unset_variable(char *str, char **env)
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
	free(tmp);
	free_tab(arg);
	return (variable);
}

char	**delete_env(t_minishell *shell, int index)
{
	int		length;
	int		i;
	char	**new_tab;

	length = ft_strlen_tab(shell->env);
	if (!(new_tab = (char **)ft_calloc(sizeof(char *), length + 1)))
		return (NULL);
	i = -1;
	while (++i < index)
	{
		if (!(new_tab[i] = ft_strdup(shell->env[i])))
			exit(EXIT_FAILURE);
	}
	while (shell->env[++i])
	{
		if (!(new_tab[index++] = ft_strdup(shell->env[i])))
			exit(EXIT_FAILURE);
	}
	if (shell->go_free)
		free_tab(shell->env);
	return (new_tab);
}

int		check_error_unset(char *variable)
{
	int	i;

	i = -1;
	while (variable[++i])
	{
		if (variable[i] == '=')
		{
			ft_putstr_fd("unset: invalid parameter name: ", 2);
			ft_putendl_fd(variable, 2);
			return (FALSE);
		}
	}
	return (TRUE);
}

void	research_env(char *variable, t_minishell *shell)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	if (!(tmp2 = ft_strdup(variable)))
		exit(EXIT_FAILURE);
	i = -1;
	while (tmp2[++i])
	{
		if (tmp2[i] == '$' && ft_strcmp(tmp2, "$USER"))
		{
			ft_putstr_error("unset: invalid paramater name: ", variable);
			return ;
		}
	}
	free(tmp2);
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

void	unset(t_minishell *shell)
{
	int		i;
	char	*variable;

	if (ft_strlen_tab(shell->tab) == 1)
		ft_putendl_fd("unset: not enough arguments", 2);
	else
	{
		i = 0;
		while (shell->tab[++i])
		{
			variable = unset_variable(shell->tab[i], shell->env);
			if (variable[0] == '\0' && i == ft_strlen_tab(shell->tab) - 1)
				ft_putendl_fd("unset: not enough arguments", 2);
			else if (variable[0] != '\0')
				research_env(variable, shell);
			free(variable);
		}
	}
}
