/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:40:36 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/12 16:29:03 by gpladet          ###   ########.fr       */
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
	if (shell->go_free)
		free_tab(shell->env);
	return (new_tab);
}

int		check_error_unset(char *variable, char *value)
{
	if (value || variable[0] == '+')
	{
		ft_putstr_fd("unset: invalid parameter name: ", 2);
		ft_putstr_fd(variable, 2);
		if (value)
			ft_putstr_error("=", value);
		else
			ft_putchar_fd('\n', 2);
		return (FALSE);
	}
	return (TRUE);
}

void	research_env_more(char *variable, t_minishell *shell)
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
			{
				shell->env = delete_env(shell, i);
				shell->go_free = TRUE;
			}
			free(tmp);
		}
	}
}

void	research_env(char *variable, t_minishell *shell)
{
	int		j;

	j = -1;
	while (shell->tab[shell->i][++j])
	{
		if (shell->tab[shell->i][j] == '$')
		{
			ft_putstr_error("unset: invalid paramater name: ", variable);
			return ;
		}
	}
	research_env_more(variable, shell);
}

void	unset(t_minishell *shell)
{
	if (ft_strlen_tab(shell->tab) == 1)
		ft_putendl_fd("unset: not enough arguments", 2);
	else
	{
		if ((shell->variable[0] == '\0' || !ft_strcmp(shell->variable, "-")))
			ft_putendl_fd("unset: not enough arguments", 2);
		else if (shell->variable[0] != '\0')
			research_env(shell->variable, shell);
	}
}
