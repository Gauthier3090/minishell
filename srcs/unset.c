/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:40:36 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/13 16:19:32 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
	free_tab(shell->env);
	return (new_tab);
}

int		check_error_unset(char *variable, char *value)
{
	int	i;

	i = -1;
	while (variable[++i])
	{
		if (value || !ft_isalnum(variable[i]))
		{
			ft_putstr_fd("unset: invalid parameter name: ", 2);
			ft_putstr_fd(variable, 2);
			if (value)
				ft_putstr_error("=", value);
			else
				ft_putchar_fd('\n', 2);
			return (FALSE);
		}
	}
	return (TRUE);
}

void	research_env(char *variable, t_minishell *shell)
{
	int		i;
	char	*tmp;

	if (check_error_unset(variable, shell->value))
	{
		i = -1;
		while (shell->env[++i])
		{
			tmp = delete_char_left(shell->env[i], '=');
			if (ft_strcmp(tmp, variable) == 0)
				shell->env = delete_env(shell, i);
			free(tmp);
		}
	}
}

void	unset(t_minishell *shell)
{
	if (ft_strlen_tab(shell->tab) == 1)
		ft_putendl_fd("unset: not enough arguments", 2);
	else
		research_env(shell->variable, shell);
}
