/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:40:36 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/28 17:05:18 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	**delete_env(t_minishell *shell, int index)
{
	int		length;
	int		i;
	char	**new_tab;

	length = ft_strlen_tab(shell->env);
	if (!(new_tab = ft_calloc(sizeof(char *), length)))
		return (NULL);
	i = -1;
	while (++i < index)
		new_tab[i] = ft_strdup(shell->env[i]);
	while (shell->env[++i])
		new_tab[index++] = ft_strdup(shell->env[i]);
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
	int		i;

	i = -1;
	if (check_error_unset(variable))
	{
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
	int	i;

	if (ft_strlen_tab(shell->tab) == 1)
		ft_putendl_fd("unset: not enough arguments", 2);
	else
	{
		i = 0;
		while (shell->tab[++i])
			research_env(shell->tab[i], shell);
	}
}
